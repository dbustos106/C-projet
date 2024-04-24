#include "univers.hxx"

/* Constructeur */

Univers::Univers() : nombreParticules(0){

    /* Accéder à l'instance de configuration */
    Configuration& configuration = Configuration::getInstance();
    
    /* Vérifier les rayons de coupure */
    rCutReflexion = configuration.getRCutReflexion();
    rCut = configuration.getRCut();
    if(rCut < rCutReflexion){
        std::cerr << "Erreur : Rayon de coupure inférieur au rayon de réflexion\n";
        exit(0);
    }

    /* Créer un vecteur de longueurs caractéristiques */
    double ldX = configuration.getLdX();
    double ldY = configuration.getLdY();
    double ldZ = configuration.getLdZ();
    ld = Vecteur<double>(ldX, ldY, ldZ);

    /* Récupérer la condition limite */
    conditionLimite = configuration.getConditionLimite();

    /* Calculer le nombre de cellules par direction */
    nc.setX((ldX != 0) ? floor(ldX / rCut) : 1);
    nc.setY((ldY != 0) ? floor(ldY / rCut) : 1);
    nc.setZ((ldZ != 0) ? floor(ldZ / rCut) : 1);

    /* Vérifier les nombres de cellules */
    if(nc.getX() <= 0 || nc.getY() <= 0 || nc.getZ() <= 0){
        std::cerr << "Erreur : Une des longueurs caractéristiques est inférieure à rCut";
        exit(0);
    }
    
    /* Vérifier les dimensions de l'univers */
    if(ldX == 0 && ldY == 0 && ldZ == 0){
        std::cerr << "Erreur : Les dimensions de l'univers sont (0, 0, 0).\n";
        exit(0);
    }

    /* Redimensionner la liste de cellules */
    grille.resize(nc.getX() * nc.getY() * nc.getZ());

    /* Initialiser les cellules */
    for(int x = 0; x < nc.getX(); x++){
        for(int y = 0; y < nc.getY(); y++){
            for(int z = 0; z < nc.getZ(); z++){
                
                /* Définir l’indice de la cellule */
                int indice = x*nc.getY()*nc.getZ() + y*nc.getZ() + z;
                grille[indice].setIndices(x, y, z);

                /* Déterminer si c’est bord ou non */
                if(((x == 0 || x == nc.getX()-1) && ld.getX() > 0) ||
                    ((y == 0 || y == nc.getY()-1) && ld.getY() > 0) ||
                    ((z == 0 || z == nc.getZ()-1) && ld.getZ() > 0) ){
                    grille[indice].setBord(true);
                }

                /* Ajouter les voisines de la cellule */
                ajouterVoisines(indice, x, y, z);
            }
        }
    }

    //imprimerGrilleSurConsole(grille);

}

/* Méthodes privées */

void Univers::ajouterVoisines(int indice, int x, int y, int z){
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dy++){
            for(int dz = -1; dz <= 1; dz++){
                
                /* Éviter les voisins répétés en nombre de cellule égale à 1 et 2 */
                if((nc.getX() == 1 && dx != 0) || (nc.getX() == 2 && dx < 0) || 
                    (nc.getY() == 1 && dy != 0) || (nc.getY() == 2 && dy < 0) ||
                    (nc.getZ() == 1 && dz != 0) || (nc.getZ() == 2 && dz < 0)) {
                    continue;
                }

                /* Calculer les indices */
                int nx = x + dx;
                int ny = y + dy;
                int nz = z + dz;

                /* Appliquer des conditions périodiques */
                if(conditionLimite == ConditionLimite::Periodique){
                    nx = (nx + nc.getX()) % nc.getX();
                    ny = (ny + nc.getY()) % nc.getY();
                    nz = (nz + nc.getZ()) % nc.getZ();
                }

                /* Vérifier les limites de la grille */
                if(nx >= 0 && nx < nc.getX() && 
                    ny >= 0 && ny < nc.getY() && 
                    nz >= 0 && nz < nc.getZ()){
                    int indiceVoisine = nx*nc.getY()*nc.getZ() + ny*nc.getZ() + nz;
                    grille[indice].ajouterVoisine(&grille[indiceVoisine]);
                }
            }
        }
    }
}

/* Méthodes publiques */

void Univers::ajouterParticule(Particule& particule){
    
    /* Faire la translation par rapport
    au centre du premier quadrant */
    particule.deplacer(ld / 2);

    /* Ajouter la particule à l'univers */
    particules.push_back(particule);

}

void Univers::ajouterParticulesAleatoires(int n){
    
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<double> distX(-ld.getX()/2, ld.getX()/2);
    std::uniform_real_distribution<double> distY(-ld.getY()/2, ld.getY()/2);
    std::uniform_real_distribution<double> distZ(-ld.getZ()/2, ld.getZ()/2);

    for(int i = 0; i < n; i++){
        Particule particule(distX(mt), distY(mt), distZ(mt));
        ajouterParticule(particule);
    }
}

Vecteur<double> Univers::calculerVecteurDirection(Particule* particule1, Particule* particule2){
    const Vecteur<double>& pos1 = particule1->getPosition();
    const Vecteur<double>& pos2 = particule2->getPosition();

    double dx = pos2.getX() - pos1.getX();
    double dy = pos2.getY() - pos1.getY();
    double dz = pos2.getZ() - pos1.getZ();

    /* Corriger la direction s'il y 
    a une périodicité aux limites */
    if(conditionLimite == ConditionLimite::Periodique){
        if(std::abs(dx) > ld.getX() / 2){
            dx -= std::copysign(ld.getX(), dx);
        }
        if(std::abs(dy) > ld.getY() / 2){
            dy -= std::copysign(ld.getY(), dy);
        }
        if(std::abs(dz) > ld.getZ() / 2){
            dz -= std::copysign(ld.getZ(), dz);
        }
    }

    return Vecteur<double>(dx, dy, dz);
}

void Univers::deplacerParticule(Particule* particule, Vecteur<double>&& vec){
    
    /* Déplacer la particule */
    particule->deplacer(std::move(vec));

    /* Corriger la position s'il y a périodicité */
    if(conditionLimite == ConditionLimite::Periodique){
        const Vecteur<double> &position = particule->getPosition();

        double posX = position.getX();
        double posY = position.getY();
        double posZ = position.getZ();

        if(posX < 0){
            posX = ld.getX() + posX; 
        }else if(posX >= ld.getX()){
            posX = posX - ld.getX();
        }

        if(posY < 0){
            posY = ld.getY() + posY;
        }else if(posY >= ld.getY()){
            posY = posY - ld.getY();
        }

        if(posZ < 0){
            posZ = ld.getZ() + posZ;
        }else if(posZ >= ld.getZ()){
            posZ = posZ - ld.getZ();
        }

        particule->setPosition(Vecteur<double>(posX, posY, posZ));

    }

}

void Univers::remplirCellules(){
    for(auto& particule : particules){

        /* Calculer les indices de la cellule */
        const Vecteur<double>& position = particule.getPosition();
        int x = floor(position.getX() / rCut);
        int y = floor(position.getY() / rCut);
        int z = floor(position.getZ() / rCut);

        /* Ajouter la particule à la liste de la cellule */
        if(x >= 0 && x < nc.getX() && y >= 0 && y < nc.getY() && z >= 0 && z < nc.getZ()){
            int indice = x*nc.getY()*nc.getZ() + y*nc.getZ() + z;
            grille[indice].ajouterParticule(&particule);
            nombreParticules += 1;
        }

    }
}

void Univers::corrigerCellules(){
    for(auto& cellule : grille){
        auto& particulesCellule = cellule.getParticules();
        for(auto it = particulesCellule.begin(); it != particulesCellule.end();){
            Particule &particule = *(*it);

            /* Vérifier si sa cellule a déjà été confirmée */
            if(particule.isCelluleConfirmee()){
                it++;
                continue;
            }

            /* Calculer les indices auxquels appartient la cellule */
            const Vecteur<double>& position = particule.getPosition();
            int x = floor(position.getX() / rCut);
            int y = floor(position.getY() / rCut);
            int z = floor(position.getZ() / rCut);

            /* Comparer les indices de la particule avec les indices de la cellule */
            if(cellule.comparerIndices(x, y, z)){
                it++;
                continue;
            }

            /* Ajouter la particule à la cellule correspondante */
            if(x >= 0 && x < nc.getX() && y >= 0 && y < nc.getY() && z >= 0 && z < nc.getZ()){  
                int indice = x*nc.getY()*nc.getZ() + y * nc.getZ() + z;
                grille[indice].ajouterParticule(&particule);
                particule.setCelluleConfirmee(true);
            }else{
                nombreParticules--;
            }

            /* Supprimer la particule de la cellule actuelle */
            it = cellule.suprimerParticule(it);
        }
    }
}

/* Getters */

const std::vector<Cellule>& Univers::getGrille() const{
    return grille;
}

const Vecteur<double>& Univers::getLd() const{
    return ld;
}

double Univers::getRCut() const{
    return rCut;
}

double Univers::getRCutReflexion() const{
    return rCutReflexion;
}

int Univers::getNombreParticules() const{
    return nombreParticules;
}

ConditionLimite Univers::getConditionLimite() const{
    return conditionLimite;
}
