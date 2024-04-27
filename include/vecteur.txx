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

template <typename T>
double Vecteur<T>::normeCarre() const{
    return x*x + y*y + z*z;
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
Vecteur<T> Vecteur<T>::operator-() const{
    return Vecteur<T>(-x, -y, -z);
}

template <typename T>
template <typename S>
bool Vecteur<T>::operator==(Vecteur<S>&& autre) const{
    return x == autre.getX() && y == autre.getY() && z == autre.getZ();
}

template <typename T>
template <typename S>
bool Vecteur<T>::operator==(const Vecteur<S>& autre) const{
    return x == autre.getX() && y == autre.getY() && z == autre.getZ();
}

template <typename T>
template <typename S>
Vecteur<T>& Vecteur<T>::operator+=(const Vecteur<S>& autre) {
    x += autre.getX();
    y += autre.getY();
    z += autre.getZ();
    return *this;
}

template <typename T>
template <typename S>
Vecteur<T>& Vecteur<T>::operator-=(const Vecteur<S>& autre) {
    x -= autre.getX();
    y -= autre.getY();
    z -= autre.getZ();
    return *this;
}

/* Surcharge d'opérateurs amis */

template <typename U>
std::ostream& operator<<(std::ostream& os, const Vecteur<U>& vec){
    os << "(" << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << ")";
    return os;
}

/* Surcharge externe des operateurs */

template <typename T, typename S>
Vecteur<T> operator+(const Vecteur<T>& vec1, const Vecteur<S>& vec2){
    return Vecteur<T>(vec1.getX() + vec2.getX(), vec1.getY() + vec2.getY(), vec1.getZ() + vec2.getZ());
}

template <typename T, typename S>
Vecteur<T> operator-(const Vecteur<T>& vec1, const Vecteur<S>& vec2){
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
