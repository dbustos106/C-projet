#pragma once

#include "collections.hxx"
#include "particule.hxx"

/**
* @brief Classe représentant une cellule de l'univers de particules.
*/

class Cellule{

    private:

        std::vector<Particule*> particules; /**< Vecteur de pointeurs vers les particules contenues dans la cellule. */
        std::vector<Cellule*> voisines; /**< Vecteur de pointeurs vers les cellules voisines. */

        Vecteur indices; /**< Indices identifiant la position de la cellule dans l'univers. */
        bool bord; /**< Indique si la cellule se trouve sur le bord de l'univers. */

    public:

        /* Constructeur */

        /**
        * @brief Constructeur par défaut de la classe Cellule.
        */

        Cellule();
        
        /* Méthodes publiques */

        /**
        * @brief Fonction qui compare les indices de la cellule avec ceux fournis.
        * @param x est la valeur X à comparer.
        * @param y est la valeur Y à comparer.
        * @param z est la valeur Z à comparer.
        * @return True si les indices correspondent, False sinon.
        */

        bool comparerIndices(int x, int y, int z);
        
        /**
        * @brief Fonction qui ajoute une particule à la cellule.
        * @param particule est le pointeur vers la particule à ajouter.
        */

        void ajouterParticule(Particule* particule);
        
        /**
        * @brief Fonction qui ajoute une cellule voisine.
        * @param voisine est le pointeur vers la cellule voisine à ajouter.
        */
        
        void ajouterVoisine(Cellule* voisine);

        /* Getters */

        /**
        * @brief Fonction qui obtient les particules contenues dans la cellule.
        * @return Vecteur de pointeurs vers les particules contenues.
        */

        std::vector<Particule*>& getParticules();
        
        /**
        * @brief Fonction qui obtient les cellules voisines.
        * @return Vecteur de pointeurs vers les cellules voisines.
        */
        
        std::vector<Cellule*>& getVoisines();
        
        /**
        * @brief Fonction qui obtient les indices de la cellule.
        * @return Vecteur contenant les indices de la cellule.
        */

        Vecteur getIndices();
        
        /**
        * @brief Fonction qui vérifie si la cellule est sur le bord du système.
        * @return True si la cellule est sur le bord, False sinon.
        */

        bool isBord();

        /* Setters */

        /**
        * @brief Fonction qui définit les indices de la cellule.
        * @param newX est la nouvelle valeur pour la coordonnée X.
        * @param newY est la nouvelle valeur pour la coordonnée Y.
        * @param newZ est la nouvelle valeur pour la coordonnée Z.
        */

        void setIndices(int newX, int newY, int newZ);
        
        /**
        * @brief Fonction qui définit si la cellule est sur le bord du système.
        * @param newBord est un booléen indiquant si la cellule est sur le bord.
        */

        void setBord(bool newBord);

};
