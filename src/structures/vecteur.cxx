#include "../../include/vecteur.hxx"

/* Méthodes publiques */

double Vecteur::distance(const Vecteur &autre) const{
    return std::sqrt(pow(x-autre.x, 2) + pow(y-autre.y, 2) + pow(z-autre.z, 2));
}

double Vecteur::norme() const{
    return std::sqrt(x*x + y*y + z*z);
}

/* Getters */

double Vecteur::getX() const{
    return x; 
}

double Vecteur::getY() const{ 
    return y; 
}

double Vecteur::getZ() const{ 
    return z; 
}

/* Setters */

void Vecteur::setX(double newX){ 
    x = newX; 
}

void Vecteur::setY(double newY){
    y = newY; 
}

void Vecteur::setZ(double newZ){
    z = newZ;
}

/* Surcharge interne des operateurs */

bool Vecteur::operator==(Vecteur&& autre) const {
    return x == autre.x && y == autre.y && z == autre.z;
}

bool Vecteur::operator==(const Vecteur& autre) const{
    return x == autre.x && y == autre.y && z == autre.z;
}

Vecteur& Vecteur::operator+=(const Vecteur& autre) {
    x += autre.x;
    y += autre.y;
    z += autre.z;
    return *this;
}

Vecteur& Vecteur::operator-=(const Vecteur& autre) {
    x -= autre.x;
    y -= autre.y;
    z -= autre.z;
    return *this;
}

/* Surcharge d'opérateurs amis */

std::ostream& operator<<(std::ostream& os, const Vecteur& vec){
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

/* Surcharge externe des operateurs */

Vecteur operator+(const Vecteur& vec1, const Vecteur& vec2){
    return Vecteur(vec1.getX() + vec2.getX(), vec1.getY() + vec2.getY(), vec1.getZ() + vec2.getZ());
}

Vecteur operator-(const Vecteur& vec1, const Vecteur& vec2){
    return Vecteur(vec1.getX() - vec2.getX(), vec1.getY() - vec2.getY(), vec1.getZ() - vec2.getZ());
}

Vecteur operator*(const Vecteur& vec, double scalaire){
    return Vecteur(vec.getX() * scalaire, vec.getY() * scalaire, vec.getZ() * scalaire);
}

Vecteur operator*(double scalaire, const Vecteur& vec){
    return Vecteur(vec.getX() * scalaire, vec.getY() * scalaire, vec.getZ() * scalaire);
}

Vecteur operator/(const Vecteur& vec, double scalaire){
    return Vecteur(vec.getX() / scalaire, vec.getY() / scalaire, vec.getZ() / scalaire);
}
