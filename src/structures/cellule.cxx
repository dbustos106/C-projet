#include "../../include/cellule.hxx"

/* Constructeur */

Cellule::Cellule() : bord(false) {}

/* Méthodes publiques */

bool Cellule::comparerIndices(int autreX, int autreY, int autreZ){
    return indices.getX() == autreX && indices.getY() == autreY && indices.getZ() == autreZ;
}

void Cellule::ajouterParticule(Particule* particule) {
    particules.push_back(particule);
}

void Cellule::ajouterVoisine(Cellule* voisine){
    voisines.push_back(voisine);
}

/* Getters */

std::vector<Particule*>& Cellule::getParticules(){
    return particules;
}

std::vector<Cellule*>& Cellule::getVoisines(){
    return voisines;
}

Vecteur Cellule::getIndices(){
    return indices;
}

bool Cellule::isBord(){
    return bord;
}

/* Setters */

void Cellule::setIndices(int newX, int newY, int newZ){
    indices.setX(newX);
    indices.setY(newY);
    indices.setZ(newZ);
}

void Cellule::setBord(bool newBord){
    bord = newBord;
}
