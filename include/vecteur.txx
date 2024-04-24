/* Constructeur */

template <typename T>
Vecteur<T>::Vecteur() : x(0), y(0), z(0) {}

template <typename T>
Vecteur<T>::Vecteur(T x, T y, T z) : x(x), y(y), z(z) {}

/* Méthodes publiques */

template <typename T>
double Vecteur<T>::distance(const Vecteur<T> &autre) const{
    return std::sqrt(pow(x-autre.x, 2) + pow(y-autre.y, 2) + pow(z-autre.z, 2));
}

template <typename T>
double Vecteur<T>::norme() const{
    return std::sqrt(x*x + y*y + z*z);
}

/* Getters */

template <typename T>
T Vecteur<T>::getX() const{
    return x; 
}

template <typename T>
T Vecteur<T>::getY() const{ 
    return y; 
}

template <typename T>
T Vecteur<T>::getZ() const{ 
    return z; 
}

/* Setters */

template <typename T>
void Vecteur<T>::setX(T newX){ 
    x = newX; 
}

template <typename T>
void Vecteur<T>::setY(T newY){
    y = newY; 
}

template <typename T>
void Vecteur<T>::setZ(T newZ){
    z = newZ;
}

/* Surcharge interne des operateurs */

template <typename T>
bool Vecteur<T>::operator==(Vecteur<T>&& autre) const {
    return x == autre.x && y == autre.y && z == autre.z;
}

template <typename T>
bool Vecteur<T>::operator==(const Vecteur<T>& autre) const{
    return x == autre.x && y == autre.y && z == autre.z;
}

template <typename T>
Vecteur<T>& Vecteur<T>::operator+=(const Vecteur<T>& autre) {
    x += autre.x;
    y += autre.y;
    z += autre.z;
    return *this;
}

template <typename T>
Vecteur<T>& Vecteur<T>::operator-=(const Vecteur<T>& autre) {
    x -= autre.x;
    y -= autre.y;
    z -= autre.z;
    return *this;
}

/* Surcharge d'opérateurs amis */

template <typename U>
std::ostream& operator<<(std::ostream& os, const Vecteur<U>& vec){
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

/* Surcharge externe des operateurs */

template <typename T>
Vecteur<T> operator+(const Vecteur<T>& vec1, const Vecteur<T>& vec2){
    return Vecteur<T>(vec1.getX() + vec2.getX(), vec1.getY() + vec2.getY(), vec1.getZ() + vec2.getZ());
}

template <typename T>
Vecteur<T> operator-(const Vecteur<T>& vec1, const Vecteur<T>& vec2){
    return Vecteur<T>(vec1.getX() - vec2.getX(), vec1.getY() - vec2.getY(), vec1.getZ() - vec2.getZ());
}

template <typename T>
Vecteur<T> operator*(const Vecteur<T>& vec, double scalaire){
    return Vecteur<T>(vec.getX() * scalaire, vec.getY() * scalaire, vec.getZ() * scalaire);
}

template <typename T>
Vecteur<T> operator*(double scalaire, const Vecteur<T>& vec){
    return Vecteur<T>(vec.getX() * scalaire, vec.getY() * scalaire, vec.getZ() * scalaire);
}

template <typename T>
Vecteur<T> operator/(const Vecteur<T>& vec, double scalaire){
    return Vecteur<T>(vec.getX() / scalaire, vec.getY() / scalaire, vec.getZ() / scalaire);
}
