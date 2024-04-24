#include "cellule.hxx"

/* Constructeur */

Cellule::Cellule() : bord(false) {}

/* Méthodes publiques */

void Cellule::ajouterParticule(Particule* particule) {
    particules.push_back(particule);
}

void Cellule::ajouterVoisine(Cellule* voisine){
    voisines.push_back(voisine);
}

bool Cellule::comparerIndices(int autreX, int autreY, int autreZ) const{
    return indices.getX() == autreX && indices.getY() == autreY && indices.getZ() == autreZ;
}

std::vector<Particule*>::const_iterator Cellule::suprimerParticule(std::vector<Particule*>::const_iterator it){
    return particules.erase(it);
}

/* Getters */

const std::vector<Particule*>& Cellule::getParticules() const{
    return particules;
}

const std::vector<Cellule*>& Cellule::getVoisines() const{
    return voisines;
}

const Vecteur<int>& Cellule::getIndices() const{
    return indices;
}

bool Cellule::isBord() const{
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
