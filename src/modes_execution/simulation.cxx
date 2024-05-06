#include "simulation.hxx"

/* Constructeur */

Simulation::Simulation(Univers& univers) : univers(univers){

    /* Accéder à l'instance de configuration */
    Configuration& configuration = Configuration::getInstance();

    forceLJ = configuration.getForceLJ();
    forceIG = configuration.getForceIG();
    forcePG = configuration.getForcePG();
    limiterVitesse = configuration.getLimiterVitesse();
    energieDesiree = configuration.getEnergieDesiree();
    epsilon = configuration.getEpsilon();
    sigma = configuration.getSigma();
    G = configuration.getG();
    delta = configuration.getDelta();
    tFinal = configuration.getTFinal();
    nomDossier = configuration.getNomDossier();

    if(nomDossier != "test"){
        /* Créer un dossier pour les fichiers de sortie */
        creerDossier(nomDossier);

        /* Ouvrir le fichier texte qui sera utilisé pour stocker l'état de l'univers */
        fichierTexte = ouvrirFichierDeSortie(nomDossier + "/simulation.txt");
    }

    /* Ajouter des particules aux cellules */
    univers.remplirCellules();
}

/* Méthodes publiques */

void Simulation::stromerVerlet(){

    /* Calculer les forces */
    calculerForcesDuSysteme();

    double t = 0;
    for(int i = 0; t < tFinal; t = t + delta, i++){

        if(i % 1000 == 0 && nomDossier != "test"){
            /* Sauvegarder l'etat de l'univers */
            sauvegarderEtatEnTexte(fichierTexte, univers, i);
            sauvegarderEtatEnVTU(nomDossier, univers, i);
        }

        /* Mettre à jour les paramètres de position */
        for(const auto& cellule : univers.getGrille()){
            for(const auto particule : cellule.getParticules()){
                univers.deplacerParticule(particule, particule->getVitesse()*delta + (0.5/particule->getMasse())*particule->getForce()*pow(delta, 2));
                particule->setFold(particule->getForce());
                particule->setCelluleConfirmee(false);
            }
        }
        univers.corrigerCellules();

        /* Calculer les forces */
        calculerForcesDuSysteme();
        
        /* Mettre à jour les paramètres de vitesse */
        for(const auto& cellule : univers.getGrille()){
            for(const auto particule : cellule.getParticules()){
                particule->accelerer(delta*(0.5/particule->getMasse())*(particule->getForce() + particule->getFold()));
            }
        }

        /* Mettre à jour la vitesse */
        if(limiterVitesse && i % 1000 == 0){
            double energieCinetique = calculerEnergieCinetique();
            if(energieCinetique > energieDesiree){
                double beta = std::sqrt(energieDesiree/energieCinetique);
                for(const auto& cellule : univers.getGrille()){
                    for(const auto particule : cellule.getParticules()){
                        particule->setVitesse(particule->getVitesse() * beta);
                    }
                }
            }
        }

    }
}

/* Méthodes privées */

void Simulation::calculerForcesDuSysteme(){ 
    
    /* Calculer les forces de réflexion */
    if(univers.getConditionLimite() == ConditionLimite::Reflexion){
        for(const auto& cellule : univers.getGrille()){
            if(cellule.isBord()){
                for(const auto particule : cellule.getParticules()){
                    calculerForceReflexive(particule);
                }
            }
        }
    }

    /* Calculer les forces pour chaque particule */
    for(const auto& cellule : univers.getGrille()){
        for(const auto particule : cellule.getParticules()){
            calculerForceSurParticule(cellule, particule);
        }
    }

}

void Simulation::calculerForceReflexive(Particule* particule){
    double rCutReflexion = univers.getRCutReflexion();
    const Vecteur<double>& ld = univers.getLd();

    const Vecteur<double> &position = particule->getPosition();

    double dx = position.getX();
    double dy = position.getY();
    double dz = position.getZ();

    if(std::abs(dx) > ld.getX() / 2){
        dx -= std::copysign(ld.getX(), dx);
    }
    if(std::abs(dy) > ld.getY() / 2){
        dy -= std::copysign(ld.getY(), dy);
    }
    if(std::abs(dz) > ld.getZ() / 2){
        dz -= std::copysign(ld.getZ(), dz);
    }
    
    Vecteur<double> force(0, 0, 0);
    double aux1 = -24 * epsilon;

    if(dx < rCutReflexion && ld.getX() > 0){
        double aux2 = pow(sigma/(2*dx), 6);
        force.setX(aux1 * (1.0/(2*dx))*aux2*(1-2*aux2));
    }
    if(dy < rCutReflexion && ld.getY() > 0){
        double aux2 = pow(sigma/(2*dy), 6);
        force.setY(aux1 * (1.0/(2*dy))*aux2*(1-2*aux2));
    }
    if(dz < rCutReflexion && ld.getZ() > 0){
        double aux2 = pow(sigma/(2*dz), 6);
        force.setZ(aux1 * (1.0/(2*dz))*aux2*(1-2*aux2));
    }

    particule->setForce(particule->getForce() + force);
}

void Simulation::calculerForceSurParticule(const Cellule& cellule, Particule* particule){
    
    /* Initialiser la force pour chaque particule. */
    particule->setForce(particule->getForce() - particule->getFold());

    if(forcePG){
        /* Calculer la force du potentiel gravitationnel */
        Vecteur<double> force(0, particule->getMasse() * G, 0);
        particule->setForce(particule->getForce() + force);
    }

    /* Calculer les forces d'interaction entre particules */
    double aux1 = 24*epsilon;
    double aux2 = 4*pow(M_PI,2);
    for(const auto voisine : cellule.getVoisines()){
        for(const auto autreParticule : voisine->getParticules()){

            if(particule->getId() > autreParticule->getId()){

                /* Calculer vecteur direction et distance entre les particules */
                Vecteur<double> direction = univers.calculerVecteurDirection(particule, autreParticule); 
                double distance = direction.norme();
                
                /* Ajouter la force d’interaction du potentiel de Lennard-Jones */      
                if(forceLJ && distance < univers.getRCut() && distance != 0){     
                    double aux3 = pow(sigma/distance, 6);
                    double magnitude = aux1*(1/pow(distance, 2))*aux3*(1-2*aux3);
                    Vecteur<double> force = direction * magnitude;
                    particule->setForce(particule->getForce() + force);
                    autreParticule->setForce(autreParticule->getForce() - force);
                }

                /* Ajouter la force d’interaction gravitationnelle */
                if(forceIG && distance < univers.getRCut() && distance != 0){
                    double magnitude = aux2*particule->getMasse()*autreParticule->getMasse() / pow(distance, 3);
                    Vecteur<double> force = direction * magnitude;
                    autreParticule->setForce(autreParticule->getForce() - force);
                    particule->setForce(particule->getForce() + force);
                }
            }

        }
    }
}

double Simulation::calculerEnergieCinetique(){
    double energieCinetique = 0;
    for(const auto& cellule : univers.getGrille()){
        for(const auto particule : cellule.getParticules()){
            energieCinetique += particule->getMasse()*particule->getVitesse().normeCarre();
        }
    }
    energieCinetique /= 2;
    return energieCinetique;
}
