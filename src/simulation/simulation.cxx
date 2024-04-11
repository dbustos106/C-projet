#include "../../include/simulation.hxx"

/* Constructeur */

Simulation::Simulation(Univers& univers, bool forceLJ, bool forceIG, bool forcePG, 
        double G, double sigma, double epsilon, double energieDesiree, std::string& nomDossier) : 
    univers(univers), forceLJ(forceLJ), forceIG(forceIG), forcePG(forcePG),
    G(G), sigma(sigma), epsilon(epsilon), energieDesiree(energieDesiree), nomDossier(nomDossier)
{
    /* Ajouter des particules aux cellules */
    univers.ajouterParticulesAuxCellules();
}

/* Méthodes publiques */

void Simulation::stromerVerlet(double delta, double tFinal, bool limiterVitesse){

    /* Calculer les forces */
    calculerForcesDuSysteme();

    /* Sauvegarder l'etat de l'univers */
    //std::ofstream fichierTexte = ouvrirFichier(dossier + "/sim.txt");
    //sauvegarderEtatEnTexte(fichierTexte, univers, 0);
    creerDossier(nomDossier);
    sauvegarderEtatEnVTU(nomDossier, univers, 0);

    double t = 0;
    for(int i = 0; t < tFinal; t = t + delta, i++){

        /* Mettre à jour les paramètres de position */
        for(auto& cellule : univers.getGrille()){
            for(const auto& particulePtr : cellule.getParticules()){
                Particule& particule = *particulePtr;
                univers.deplacerParticule(particule, particule.getVitesse()*delta + (0.5/particule.getMasse())*particule.getForce()*pow(delta, 2));
                particule.setFold(particule.getForce());
                particule.setCelluleConfirmee(false);
            }
        }
        univers.corrigerCellules();

        /* Calculer les forces */
        calculerForcesDuSysteme();
        
        /* Mettre à jour les paramètres de vitesse */
        for(auto& cellule : univers.getGrille()){
            for(const auto& particulePtr : cellule.getParticules()){
                Particule& particule = *particulePtr;
                particule.accelerer(delta*(0.5/particule.getMasse())*(particule.getForce() + particule.getFold()));
            }
        }

        /* mettre à jour la vitesse */
        if(limiterVitesse && i % 1000 == 0){
            double energieCinetique = calculerEnergieCinetique();
            double beta = std::sqrt(energieDesiree/energieCinetique);
            for(auto& cellule : univers.getGrille()){
                for(const auto& particulePtr : cellule.getParticules()){
                    Particule& particule = *particulePtr;
                    particule.setVitesse(particule.getVitesse() * beta);
                }
            }
        }

        if(i % 1000 == 0){
            /* Sauvegarder l'etat de l'univers */
            //sauvegarderEtatEnTexte(fichierTexte, univers, i);
            sauvegarderEtatEnVTU(nomDossier, univers, i);
        }

    }
}

/* Méthodes privées */

void Simulation::calculerForcesDuSysteme(){ 
    
    /* Calculer les forces de réflexion */
    if(univers.getConditionLimite() == 1){
        for(auto& cellule : univers.getGrille()){
            if(cellule.isBord()){
                for(const auto& particulePtr : cellule.getParticules()){
                    Particule& particule = *particulePtr;
                    calculerForceReflexive(particule);
                }
            }
        }
    }

    /* Calculer les forces pour chaque particule */
    for(auto& cellule : univers.getGrille()){
        for(const auto& particulePtr : cellule.getParticules()){
            Particule& particule = *particulePtr;
            calculerForceSurParticule(cellule, particule);
        }
    }

}

void Simulation::calculerForceReflexive(Particule& particule){
    double rCutReflexion = univers.getRCutReflexion();
    const Vecteur& ld = univers.getLd();

    Vecteur &position = particule.getPosition();

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
    
    Vecteur force(0, 0, 0);
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

    particule.setForce(particule.getForce() + force);
}

void Simulation::calculerForceSurParticule(Cellule& cellule, Particule& particule){
    
    /* Initialiser la force pour chaque particule. */
    particule.setForce(particule.getForce() - particule.getFold());

    if(forcePG){
        /* Calculer la force du potentiel gravitationnel */
        Vecteur force = Vecteur(0, particule.getMasse() * G, 0);
        particule.setForce(particule.getForce() + force);
    }

    /* Calculer les forces d'interaction entre particules */
    double aux1 = 24*epsilon;
    for(auto& voisine : cellule.getVoisines()){
        for(const auto& autreParticulePtr : voisine->getParticules()){
            Particule& autreParticule = *autreParticulePtr;

            if(particule.getId() > autreParticule.getId()){

                /* Calculer vecteur direction et distance entre les particules */
                Vecteur direction = univers.calculerVecteurDirection(particule, autreParticule); 
                double distance = direction.norme();
                
                /* Ajouter la force d’interaction du potentiel de Lennard-Jones */      
                if(forceLJ && distance < univers.getRCut() && distance != 0){     
                    double aux2 = pow(sigma/distance, 6);
                    double magnitude = aux1*(1/pow(distance, 2))*aux2*(1-2*aux2);
                    Vecteur force = direction * magnitude;
                    autreParticule.setForce(autreParticule.getForce() - force);
                    particule.setForce(particule.getForce() + force);
                }

                /* Ajouter la force d’interaction gravitationnelle */
                if(forceIG && distance < univers.getRCut() && distance != 0){
                    double magnitude = particule.getMasse()*autreParticule.getMasse() / pow(distance, 3);
                    Vecteur force = direction * magnitude;
                    autreParticule.setForce(autreParticule.getForce() - force);
                    particule.setForce(particule.getForce() + force);
                }
            }

        }
    }
}

double Simulation::calculerEnergieCinetique(){
    double energieCinetique = 0;
    for(auto& cellule : univers.getGrille()){
        for(const auto& particulePtr : cellule.getParticules()){
            Particule& particule = *particulePtr;
            energieCinetique += particule.getMasse()*pow(particule.getVitesse().norme(), 2);
        }
    }
    energieCinetique /= 2;
    return energieCinetique;
}
