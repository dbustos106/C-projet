#include "univers.hxx"

/* Constructeur */

Univers::Univers() : nombreParticules(0){

    /* Accéder à l'instance de configuration */
    Configuration& configuration = Configuration::getInstance();
    
    /* Vérifier les rayons de coupure */
    rCutReflexion = configuration.getRCutReflexion();
    rCut = configuration.getRCut();
    if(rCut < rCutReflexion){
        throw std::invalid_argument("Rayon de coupure inférieur au rayon de réflexion");
    }

    /* Créer un vecteur de longueurs caractéristiques */
    double ldX = configuration.getLdX();
    double ldY = configuration.getLdY();
    double ldZ = configuration.getLdZ();
    ld = Vecteur<double>(ldX, ldY, ldZ);

    /* Vérifier les longueurs de l'univers */
    if(ldX == 0 && ldY == 0 && ldZ == 0){
        throw std::invalid_argument("Les dimensions de l'univers sont (0, 0, 0)");
    }

    /* Récupérer la condition limite */
    conditionLimite = configuration.getConditionLimite();

    /* Calculer le nombre de cellules par direction */
    nc.setX((ldX != 0) ? floor(ldX / rCut) : 1);
    nc.setY((ldY != 0) ? floor(ldY / rCut) : 1);
    nc.setZ((ldZ != 0) ? floor(ldZ / rCut) : 1);

    /* Vérifier les nombres de cellules */
    if(nc.getX() <= 0 || nc.getY() <= 0 || nc.getZ() <= 0){
        throw std::invalid_argument("Une des longueurs caractéristiques est inférieure à rCut");
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

    /* Définir des distributions uniformes pour les coordonnées X, Y et Z */
    std::uniform_real_distribution<double> distX(-ld.getX()/2, ld.getX()/2);
    std::uniform_real_distribution<double> distY(-ld.getY()/2, ld.getY()/2);
    std::uniform_real_distribution<double> distZ(-ld.getZ()/2, ld.getZ()/2);

    /* Ajouter les particules aléatoires */
    for(int i = 0; i < n; i++){
        Particule particule(distX(mt), distY(mt), distZ(mt));
        ajouterParticule(particule);
    }
}

Vecteur<double> Univers::calculerVecteurDirection(Particule* particule1, Particule* particule2){
    const Vecteur<double>& pos1 = particule1->getPosition();
    const Vecteur<double>& pos2 = particule2->getPosition();

    /* Calculer la différence entre les positions */
    double dx = pos2.getX() - pos1.getX();
    double dy = pos2.getY() - pos1.getY();
    double dz = pos2.getZ() - pos1.getZ();

    /* Corriger en cas de périodicité aux limites */
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

void Univers::deplacerParticule(Particule* particule, const Vecteur<double>& vec){
    
    /* Déplacer la particule */
    particule->deplacer(vec);

    /* Corriger la position en cas de périodicité */
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
        const auto& particulesCellule = cellule.getParticules();
        for(auto it = particulesCellule.begin(); it != particulesCellule.end();){

            /* Vérifier si sa cellule a déjà été confirmée */
            if((*it)->isCelluleConfirmee()){
                it++;
                continue;
            }

            /* Calculer les indices auxquels appartient la cellule */
            const Vecteur<double>& position = (*it)->getPosition();
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
                grille[indice].ajouterParticule(*it);
                (*it)->setCelluleConfirmee(true);
            }else{
                nombreParticules--;
            }

            /* Supprimer la particule de la cellule actuelle */
            it = cellule.suprimerParticule(it);
        }
    }
}

const Cellule& Univers::getCelluleParIndices(int x, int y, int z){
    int indice = x*nc.getY()*nc.getZ() + y * nc.getZ() + z;
    return grille[indice];
}

/* Getters */

const std::vector<Cellule>& Univers::getGrille() const{
    return grille;
}

ConditionLimite Univers::getConditionLimite() const{
    return conditionLimite;
}

int Univers::getNombreParticules() const{
    return nombreParticules;
}

double Univers::getRCutReflexion() const{
    return rCutReflexion;
}

double Univers::getRCut() const{
    return rCut;
}

const Vecteur<double>& Univers::getLd() const{
    return ld;
}
