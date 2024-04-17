#include "univers.hxx"

/* Constructeur */

Univers::Univers(Vecteur& ld, double rCut, double rCutReflexion, int conditionLimite) :
    ld(ld), rCut(rCut), rCutReflexion(rCutReflexion), 
    nombreParticules(0), conditionLimite(conditionLimite) 
{

    /* Vérifier les rayons de coupure */
    if(rCut < rCutReflexion){
        std::cerr << "Erreur : Rayon de coupure inférieur au rayon de réflexion\n";
        exit(0);
    }

    /* Calculer le nombre de cellules par direction */
    nc.setX((ld.getX() != 0) ? floor(ld.getX() / rCut) : 1);
    nc.setY((ld.getY() != 0) ? floor(ld.getY() / rCut) : 1);
    nc.setZ((ld.getZ() != 0) ? floor(ld.getZ() / rCut) : 1);

    /* Vérifier les nombres de cellules */
    if(nc.getX() <= 0){
        std::cerr << "Erreur : Longueur caractéristique de X inférieure à rCut";
        exit(0);
    }
    
    if(nc.getY() <= 0){
        std::cerr << "Erreur : Longueur caractéristique de Y inférieure à rCut";
        exit(0);
    }
    
    if(nc.getZ() <= 0){
        std::cerr << "Erreur : Longueur caractéristique de Z inférieure à rCut";
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
                if ((nc.getX() == 1 && dx != 0) || (nc.getX() == 2 && dx < 0) || 
                    (nc.getY() == 1 && dy != 0) || (nc.getY() == 2 && dy < 0) ||
                    (nc.getZ() == 1 && dz != 0) || (nc.getZ() == 2 && dz < 0)) {
                    continue;
                }

                /* Calculer les indices */
                int nx = x + dx;
                int ny = y + dy;
                int nz = z + dz;

                /* Appliquer des conditions périodiques */
                if (conditionLimite == 3) {
                    nx = std::fmod(nx + nc.getX(), nc.getX());
                    ny = std::fmod(ny + nc.getY(), nc.getY());
                    nz = std::fmod(nz + nc.getZ(), nc.getZ());
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

Vecteur Univers::calculerVecteurDirection(Particule& particule1, Particule& particule2){
    Vecteur& pos1 = particule1.getPosition();
    Vecteur& pos2 = particule2.getPosition();

    double dx = pos2.getX() - pos1.getX();
    double dy = pos2.getY() - pos1.getY();
    double dz = pos2.getZ() - pos1.getZ();

    /* Corriger la direction s'il y 
    a une périodicité aux limites */
    if(conditionLimite == 3){
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

    return Vecteur(dx, dy, dz);
}

void Univers::deplacerParticule(Particule& particule, Vecteur&& vec){
    
    /* Déplacer la particule */
    particule.deplacer(std::move(vec));

    /* Corriger la position s'il y a périodicité */
    if(conditionLimite == 3){
        Vecteur &position = particule.getPosition();

        if(position.getX() < 0){
            position.setX(ld.getX() + position.getX()); 
        }else if(position.getX() >= ld.getX()){
            position.setX(position.getX() - ld.getX());
        }

        if(position.getY() < 0){
            position.setY(ld.getY() + position.getY()); 
        }else if(position.getY() >= ld.getY()){
            position.setY(position.getY() - ld.getY());
        }

        if(position.getZ() < 0){
            position.setZ(ld.getZ() + position.getZ()); 
        }else if(position.getZ() >= ld.getZ()){
            position.setZ(position.getZ() - ld.getZ());
        }

    }

}

void Univers::remplirCellules(){
    for(auto& particule : particules){

        /* Calculer les indices de la cellule */
        Vecteur& position = particule.getPosition();
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
            Vecteur& position = particule.getPosition();
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
            it = particulesCellule.erase(it);

        }
    }
}

/* Getters */

std::vector<Cellule>& Univers::getGrille(){
    return grille;
}

std::vector<Particule>& Univers::getParticules(){
    return particules;
}

const Vecteur& Univers::getLd() const{
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

int Univers::getConditionLimite() const{
    return conditionLimite;
}
