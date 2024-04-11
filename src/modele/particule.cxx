#include "../../include/particule.hxx"

int Particule::nextId = 1;

/* Constructeur */

Particule::Particule(double posX, double posY, double posZ) :
    id(nextId++), categorie("N/A"), 
    position(posX, posY, posZ), 
    masse(1.0)
{}

Particule::Particule(std::string categorie, double posX, double posY, double posZ, 
                                double vitX, double vitY, double vitZ, double masse) :
    id(nextId++), categorie(categorie), position(posX, posY, posZ), 
    vitesse(vitX, vitY, vitZ), masse(masse)
{}

/* Méthodes publiques */

void Particule::deplacer(Vecteur&& vec){
    position += vec;
}

void Particule::accelerer(Vecteur&& vec){
    vitesse += vec;
}

/* Getters */

int Particule::getId() const{
    return id;
}

bool Particule::isCelluleConfirmee() const{
    return celluleConfirmee;
}

std::string& Particule::getCategorie(){
    return categorie;
}

Vecteur& Particule::getPosition(){
    return position;
}

Vecteur& Particule::getVitesse(){
    return vitesse;
}

Vecteur& Particule::getForce(){
    return force;
}

Vecteur& Particule::getFold(){
    return Fold;
}

double Particule::getMasse() const{
    return masse;
}

/* Setters */

void Particule::setId(int newId){
    id = newId;
}

void Particule::setCelluleConfirmee(bool newCelluleConfirmee){
    celluleConfirmee = newCelluleConfirmee;
}

void Particule::setPosition(const Vecteur& newPosition){
    position = newPosition;
}

void Particule::setPosition(Vecteur&& newPosition){
    position = std::move(newPosition);
}

void Particule::setVitesse(const Vecteur& newVitesse){
    vitesse = newVitesse;
}

void Particule::setVitesse(Vecteur&& newVitesse){
    vitesse = std::move(newVitesse);
}

void Particule::setForce(const Vecteur& newForce){
    force = newForce;
}

void Particule::setForce(Vecteur&& newForce){
    force = std::move(newForce);
}

void Particule::setFold(const Vecteur& newFold){
    Fold = newFold;
}

void Particule::setFold(Vecteur&& newFold){
    Fold = std::move(newFold);
}

void Particule::setMasse(double newMasse){
    masse = newMasse;
}

/* Surcharge interne des operateurs */

bool Particule::operator<(const Particule& autre) const{
    if(id < autre.getId()){
        return true;
    }
    return false;
}

/* Surcharge externe des operateurs */

std::ostream& operator<<(std::ostream& os, Particule& particule){
    os << "Particule ID : " << particule.getId() << " "
        << "Categorie : " << particule.getCategorie() << " "
        << "Position : " << particule.getPosition() << " "
        << "Vitesse : " << particule.getVitesse() << " "
        << "Force : " << particule.getForce() << " "
        << "Masse : " << particule.getMasse() << " ";
    return os;
}
