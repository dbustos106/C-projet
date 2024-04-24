#include "particule.hxx"

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

void Particule::deplacer(Vecteur<double>&& vec){
    position += vec;
}

void Particule::accelerer(Vecteur<double>&& vec){
    vitesse += vec;
}

/* Getters */

int Particule::getId() const{
    return id;
}

bool Particule::isCelluleConfirmee() const{
    return celluleConfirmee;
}

const std::string& Particule::getCategorie() const{
    return categorie;
}

const Vecteur<double>& Particule::getPosition() const{
    return position;
}

const Vecteur<double>& Particule::getVitesse() const{
    return vitesse;
}

const Vecteur<double>& Particule::getForce() const{
    return force;
}

const Vecteur<double>& Particule::getFold() const{
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

void Particule::setPosition(const Vecteur<double>& newPosition){
    position = newPosition;
}

void Particule::setPosition(Vecteur<double>&& newPosition){
    position = std::move(newPosition);
}

void Particule::setVitesse(const Vecteur<double>& newVitesse){
    vitesse = newVitesse;
}

void Particule::setVitesse(Vecteur<double>&& newVitesse){
    vitesse = std::move(newVitesse);
}

void Particule::setForce(const Vecteur<double>& newForce){
    force = newForce;
}

void Particule::setForce(Vecteur<double>&& newForce){
    force = std::move(newForce);
}

void Particule::setFold(const Vecteur<double>& newFold){
    Fold = newFold;
}

void Particule::setFold(Vecteur<double>&& newFold){
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

std::ostream& operator<<(std::ostream& os, const Particule& particule){
    os << "Particule ID : " << particule.getId() << " "
        << "Categorie : " << particule.getCategorie() << " "
        << "Position : " << particule.getPosition() << " "
        << "Vitesse : " << particule.getVitesse() << " "
        << "Force : " << particule.getForce() << " "
        << "Masse : " << particule.getMasse() << " ";
    return os;
}
