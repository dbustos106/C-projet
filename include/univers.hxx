#pragma once

#include <random>

#include "cellule.hxx"
#include "collections.hxx"
#include "imprimer.hxx"

/**
* @brief Classe représentant un univers de particules.
*/

class Univers{

    private:

        std::vector<Cellule> grille; /**< Vecteur contenant les cellules de l'univers. */
        std::vector<Particule> particules; /**< Vecteur contenant les particules de l'univers. */

        Vecteur ld; /**< Vecteur des longueurs caractéristiques de l'univers. */
        Vecteur nc; /**< Nombre de cellules dans chaque dimension de la grille. */
        double rCut; /**< Rayon de coupure pour les interactions attractives. */
        double rCutReflexion; /**< Rayon de coupure pour les réflexions aux bords. */

        int nombreParticules; /**< Nombre total de particules dans l'univers. */
        int conditionLimite; /**< Type de condition limite appliquée à l'univers. */

        /* Méthodes privées */

        /**
        * @brief Fonction qui ajoute les voisins d'une cellule avec un indice
        *        dont la position tridimensionnelle est (x, y, z).
        * @param[in] indice est l’indice de la cellule.
        * @param[in] x est le composant X de la cellule.
        * @param[in] y est le composant Y de la cellule.
        * @param[in] z est le composant Z de la cellule.
        */

        void ajouterVoisines(int indice, int x, int y, int z);
        
    public:

        /* Constructeur */

        /**
        * @brief Constructeur de la classe Univers.
        * @param ld est le vecteur des longueurs caractéristiques de l'univers.
        * @param rCut est le rayon de coupure pour les interactions attractives.
        * @param rCutReflexion est le rayon de coupure pour les réflexions aux bords.
        * @param conditionLimite est le type de condition limite appliquée à l'univers.
        */

        Univers(Vecteur& ld, double rCut, double rCutReflexion, int conditionLimite);

        /* Méthodes publiques */

        /**
        * @brief Fonction qui ajoute une particule à l'univers.
        * @param[in] particule est la particule.
        */

        void ajouterParticule(Particule& particule);

        /**
        * @brief Fonction qui ajoute un nombre donné de particules aléatoires à l'univers.
        * @param[in] n est le nombre de particules à créer.
        */

        void ajouterParticulesAleatoires(int n);

        /**
        * @brief Fonction qui calcule le vecteur direction entre deux particules.
        * @param[in] particule1 est la première particule.
        * @param[in] particule2 est la deuxième particule.
        * @return vecteur direction entre les deux particules.
        */

        Vecteur calculerVecteurDirection(Particule& particule1, Particule& particule2);
        
        /**
        * @brief Fonction qui déplace une particule vers une direction donnée.
        * @param[in] particule est la particule.
        * @param[in] vec est la direction à déplacer.
        */

        void deplacerParticule(Particule& particule, Vecteur&& vec);

        /**
        * @brief Une fonction qui remplit le vecteur de pointeurs de
        *        chaque cellule avec les particules correspondantes. 
        */

        void remplirCellules();
        
        /**
        * @brief Fonction qui vérifie la position des particules 
        *        et les place dans la cellule correcte.
        */

        void corrigerCellules();
        
        /* Getters */

        /**
        * @brief Fonction qui obtient une référence au vecteur de cellules de l'univers.
        * @return Référence au vecteur de cellules de l'univers.
        */

        std::vector<Cellule>& getGrille();
        
        /**
        * @brief Fonction qui obtient une référence au vecteur de particules de l'univers.
        * @return Référence au vecteur de particules de l'univers.
        */
        
        std::vector<Particule>& getParticules();
        
        /**
        * @brief Fonction qui obtient une référence au vecteur des longueurs caractéristiques de l'univers.
        * @return Référence au vecteur des longueurs caractéristiques.
        */

        const Vecteur& getLd() const;
        
        /**
        * @brief Fonction qui obtient le rayon de coupure pour les réflexions aux bords.
        * @return Rayon de coupure pour les réflexions aux bords.
        */

        double getRCutReflexion() const;
        
        /**
        * @brief Fonction qui obtient le rayon de coupure pour les interactions attractives.
        * @return Rayon de coupure pour les interactions attractives.
        */

        double getRCut() const;

        /**
        * @brief Fonction qui obtient le nombre total de particules dans l'univers.
        * @return Nombre total de particules dans l'univers.
        */
        
        int getNombreParticules() const;
        
        /**
        * @brief Fonction qui obtient le type de condition limite appliquée à l'univers.
        * @return Type de condition limite appliquée à l'univers.
        */
        
        int getConditionLimite() const;

};
