#pragma once

#include <string>
#include "vecteur.hxx"

/**
* @brief 
* Classe représentant une particule de l'univers.
*/

class Particule{
    
    private:

        int id; /**< Identifiant unique de la particule. */
        static int nextId; /**< Prochain identifiant unique disponible à attribuer à une nouvelle particule. */
        bool celluleConfirmee; /**< Booléen indiquant si la particule est classée dans la cellule correcte */
        std::string categorie; /**< Catégorie de la particule. */
        
        Vecteur<double> position; /**< Position de la particule dans l'univers. */
        Vecteur<double> vitesse; /**< Vitesse de la particule. */
        Vecteur<double> force; /**< Force appliquée à la particule. */
        Vecteur<double> Fold; /**< Force précédente appliquée à la particule. */
        
        double masse; /**< Masse de la particule. */

    public:
        
        /* Constructeur */

        /**
        * @brief Constructeur de la classe Particule.
        * @param posX est la position initiale sur l'axe X.
        * @param posY est la position initiale sur l'axe Y.
        * @param posZ est la position initiale sur l'axe Z.
        */

        Particule(double posX, double posY, double posZ);
        
        /**
        * @brief 
        * Constructeur de la classe Particule.
        * @param categorie est la catégorie de la particule.
        * @param posX est la position initiale sur l'axe X.
        * @param posY est la position initiale sur l'axe Y.
        * @param posZ est la position initiale sur l'axe Z.
        * @param vitX est la vitesse initiale sur l'axe X.
        * @param vitY est la vitesse initiale sur l'axe Y.
        * @param vitZ est la vitesse initiale sur l'axe Z.
        * @param masse est la masse de la particule.
        */

        Particule(std::string categorie, double posX, double posY, double posZ, 
                                         double vitX, double vitY, double vitZ, double masse);

        /* Méthodes publiques */

        /**
        * @brief 
        * Fonction qui accélère la particule.
        * @param vec est le vecteur de changement de vitesse.
        */

        void accelerer(const Vecteur<double>& vec);
        
        /**
        * @brief 
        * Fonction qui déplace la particule.
        * @param vec est le vecteur de changement de position.
        */
        
        void deplacer(const Vecteur<double>& vec);

        /* Getters */

        /**
        * @brief 
        * Fonction qui obtient l'identifiant unique de la particule.
        * @return Identifiant unique de la particule.
        */

        int getId() const;

        /**
        * @brief 
        * Fonction qui vérifie si la particule appartient à la cellule correcte.
        * @return True si la particule appartient à la cellule correcte,
        * False sinon.
        */

        bool isCelluleConfirmee() const;

        /**
        * @brief 
        * Fonction qui obtient la catégorie de la particule.
        * @return Catégorie de la particule.
        */

        const std::string& getCategorie() const;
        
        /**
        * @brief 
        * Fonction qui obtient la position de la particule.
        * @return Position de la particule.
        */
        
        const Vecteur<double>& getPosition() const;
        
        /**
        * @brief 
        * Fonction qui obtient la vitesse de la particule.
        * @return Vitesse de la particule.
        */
        
        const Vecteur<double>& getVitesse() const;
        
        /**
        * @brief 
        * Fonction qui obtient la force appliquée à la particule.
        * @return Force appliquée à la particule.
        */
        
        const Vecteur<double>& getForce() const;
        
        /**
        * @brief 
        * Fonction qui obtient
        * la force précédente appliquée à la particule.
        * @return Force précédente appliquée à la particule.
        */
        
        const Vecteur<double>& getFold() const;
        
        /**
        * @brief 
        * Fonction qui obtient la masse de la particule.
        * @return Masse de la particule.
        */
        
        double getMasse() const;

        /* Setters */

        /**
        * @brief 
        * Fonction qui définit l'identifiant unique de la particule.
        * @param newId est le nouvel identifiant unique.
        */
        
        void setId(int newId);        
        
        /**
        * @brief 
        * Fonction qui définit si une particule est dans la cellule correcte.
        * @param newCelluleConfirmee est un booléen, true si elle est dans
        * la bonne cellule, false sinon.
        */

        void setCelluleConfirmee(bool newCelluleConfirmee);

        /**
        * @brief 
        * Fonction qui définit la position de la particule.
        * @param newPosition est la nouvelle position de la particule.
        */
        
        void setPosition(const Vecteur<double>& newPosition);
        
        /**
        * @brief 
        * Fonction qui définit la vitesse de la particule.
        * @param newVitesse est la nouvelle vitesse de la particule.
        */
        
        void setVitesse(const Vecteur<double>& newVitesse);
        
        /**
        * @brief 
        * Fonction qui définit la force appliquée à la particule.
        * @param newForce est la nouvelle force appliquée à la particule.
        */
        
        void setForce(const Vecteur<double>& newForce);
        
        /**
        * @brief 
        * Fonction qui définit la force précédente appliquée à la particule.
        * @param newFold est la force précédente appliquée à la particule.
        */
        
        void setFold(const Vecteur<double>& newFold);
        
        /**
        * @brief 
        * Fonction qui définit la masse de la particule.
        * @param newMasse est la nouvelle masse de la particule.
        */
        
        void setMasse(double newMasse);

        /* Surcharge interne des operateurs */

        /**
        * @brief 
        * Surcharge de l'opérateur < pour comparer des objets
        * Particule en fonction de la valeur de leur identifiant.
        * @param autre est l'autre vecteur avec lequel il est comparé.
        * @return Vrai si cet objet Particule a un identifiant inférieur
        * à celui de l'autre particule, faux sinon.
        */

        bool operator<(const Particule& autre) const;

        /* Surcharge d'opérateurs amis */

        /**
        * @brief 
        * Surcharge de l'opérateur d'insertion 
        * pour imprimer une particule dans un flux de sortie.
        * @param os Flux de sortie où la particule sera imprimée.
        * @param particule est la particule à imprimer.
        * @return Référence au flux de sortie pour permettre la concaténation.
        */

        friend std::ostream& operator<<(std::ostream& os, const Particule& particule);

};
