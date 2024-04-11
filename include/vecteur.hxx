#pragma once

#include <iostream>
#include <cmath>

/**
* @brief Classe représentant un vecteur dans l'espace tridimensionnel.
*/

class Vecteur{

    private:
        
        double x, /**< Composante sur l'axe X du vecteur. */
               y, /**< Composante sur l'axe Y du vecteur. */
               z; /**< Composante sur l'axe Z du vecteur. */

    public: 

        /* Constructeur */
        
        /**
        * @brief Constructeur par défaut. Initialise le vecteur avec les composantes (0, 0, 0).
        */
        
        Vecteur() : x(0), y(0), z(0) {};

        /**
        * @brief Constructeur permettant de spécifier les composantes du vecteur.
        * @param x Composante sur l'axe X du vecteur.
        * @param y Composante sur l'axe Y du vecteur.
        * @param z Composante sur l'axe Z du vecteur.
        */

        Vecteur(double x, double y, double z) : x(x), y(y), z(z) {}

        /* Méthodes publiques */

        /**
        * @brief Fonction qui calcule la distance entre ce vecteur et un autre vecteur donné.
        * @param autre est l'autre vecteur pour calculer la distance.
        * @return La distance entre les deux vecteurs.
        */
        
        double distance(const Vecteur &autre) const;
        
        /**
        * @brief Fonction qui calcule la norme de ce vecteur.
        * @return La norme (module) du vecteur.
        */

        double norme() const;

        /* Getters */

        /**
        * @brief Fonction qui obtient la composante X du vecteur.
        * @return La composante X du vecteur.
        */
        
        double getX() const;
        
        /**
        * @brief Fonction qui obtient la composante Y du vecteur.
        * @return La composante Y du vecteur.
        */
        
        double getY() const;
        
        /**
        * @brief Fonction qui obtient la composante Z du vecteur.
        * @return La composante Z du vecteur.
        */
        
        double getZ() const;

        /* Setters */

        /**
        * @brief Fonction qui définit la composante X du vecteur.
        * @param newX est la nouvelle valeur pour la composante X.
        */
        
        void setX(double newX);
        
        /**
        * @brief Fonction qui définit la composante Y du vecteur.
        * @param newX est la nouvelle valeur pour la composante Y.
        */
        
        void setY(double newY);
        
        /**
        * @brief Fonction qui définit la composante Z du vecteur.
        * @param newX est la nouvelle valeur pour la composante Z.
        */
        
        void setZ(double newZ);

        /* Surcharge interne des operateurs */

        /**
        * @brief Surcharge interne de l'opérateur d'égalité.
        * @param autre est l'autre vecteur avec lequel il est comparé.
        * @return Vrai si les vecteurs sont égaux, faux sinon.
        */

        bool operator==(Vecteur&& autre) const;
        
        /**
        * @brief Surcharge interne de l'opérateur d'égalité.
        * @param autre est l'autre vecteur avec lequel il est comparé.
        * @return Vrai si les vecteurs sont égaux, faux sinon.
        */

        bool operator==(const Vecteur& autre) const;
        
        /**
        * @brief Surcharge de l'opérateur d'addition et d'affectation.
        * @param autre est le vecteur qui est ajouté à ce vecteur.
        * @return Une référence à ce vecteur après l'opération.
        */

        Vecteur& operator+=(const Vecteur& autre);
        
        /**
        * @brief Surcharge de l'opérateur de soustraction et d'affectation.
        * @param autre est le vecteur qui est soustrait à ce vecteur.
        * @return Une référence à ce vecteur après l'opération.
        */
        
        Vecteur& operator-=(const Vecteur& autre);

        /* Surcharge d'opérateurs amis */

        /**
        * @brief Surcharge de l'opérateur d'insertion dans un flux de sortie.
        * @param os est le flux de sortie.
        * @param vec est le vecteur à insérer dans le flux.
        * @return Une référence au flux de sortie.
        */

        friend std::ostream& operator<<(std::ostream& os, const Vecteur& vec);
                
};

/* Surcharge externe des operateurs */

/**
* @brief Surcharge de l'opérateur d'addition pour ajouter deux vecteurs.
* @param vec1 est le premier vecteur.
* @param vec2 est le deuxième vecteur.
* @return Le résultat de l'addition des deux vecteurs.
*/

Vecteur operator+(const Vecteur& vec1, const Vecteur& vec2);

/**
* @brief Surcharge de l'opérateur de soustraction pour soustraire deux vecteurs.
* @param vec1 est le vecteur duquel on soustrait.
* @param vec2 est le vecteur soustrait.
* @return Le résultat de la soustraction des deux vecteurs.
*/

Vecteur operator-(const Vecteur& vec1, const Vecteur& vec2);

/**
* @brief Surcharge de l'opérateur de multiplication par un scalaire pour multiplier un vecteur par un scalaire.
* @param vec est le vecteur à multiplier.
* @param scalaire est le scalaire par lequel le vecteur est multiplié.
* @return Le résultat de la multiplication du vecteur par le scalaire.
*/

Vecteur operator*(const Vecteur& vec, double scalaire);

/**
* @brief Surcharge de l'opérateur de multiplication par un scalaire pour multiplier un vecteur par un scalaire.
* @param scalaire est le scalaire par lequel le vecteur est multiplié.
* @param vec est le vecteur à multiplier.
* @return Le résultat de la multiplication du vecteur par le scalaire.
*/

Vecteur operator*(double scalaire, const Vecteur& vec);

/**
* @brief Surcharge de l'opérateur de division pour diviser un vecteur par un scalaire.
* @param vec est le vecteur à diviser.
* @param scalaire est le scalaire par lequel le vecteur est divisé.
* @return Le résultat de la division du vecteur par le scalaire.
*/

Vecteur operator/(const Vecteur& vec, double scalaire);
