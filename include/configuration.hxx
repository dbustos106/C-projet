#pragma once

#include "fichier.hxx"
#include <sstream>
#include <cmath>

/**
* @brief Énumération représentant les différentes conditions limites 
*        qui peuvent être appliquées aux bords de la simulation.
*/ 

enum class ConditionLimite{ Reflexion, Absorption, Periodique };

/**
* @brief Classe représentant la configuration avec laquelle la simulation sera exécuté. 
*/

class Configuration{

    private:

        bool forceLJ = false; /**< Indique si la force du potentiel de Lennard-Jones doit être utilisée. */
        bool forceIG = false; /**< Indique si la force d'interaction gravitationnelle doit être utilisée. */
        bool forcePG = false; /**< Indique si le potentiel gravitationnel doit être utilisé. */
        bool limiterVitesse = false; /**< Indique si la vitesse doit être limitée. */
        double energieDesiree = 0.005; /**< Définit l'énergie désirée du système. */

        double ldX = 0; /**< Définit la longueur caractéristique dans la dimension X. */
        double ldY = 0; /**< Définit la longueur caractéristique dans la dimension Y. */
        double ldZ = 0; /**< Définit la longueur caractéristique dans la dimension Z. */

        double G = -12; /**< Définit la valeur de G pour le calcul du potentiel gravitationnel. */
        double epsilon = 5.0; /**< Définit la valeur d'epsilon de la force de Lennard-Jones. */
        double sigma = 1.0; /**< Définit la valeur de sigma de la force de Lennard-Jones. */

        double rCut = 2.5; /**< Définit la distance de coupure pour calculer les forces d'interaction. */
        double rCutReflexion = pow(2, 1.0/6); /**< Définit la distance de coupure pour calculer la force de réflexion. */
        ConditionLimite conditionLimite = ConditionLimite::Absorption; /**< Définit le type de condition limite. */
    
        double delta = 0.00005; /**< Définit la valeur de delta. */
        double tFinal = 19.5; /**< Définit la valeur de tFinal. */
    
        std::string adresseFichier; /**< Définit le nom du fichier de lecture VTU. */
        std::string nomDossier; /**< Définit le nom du dossier dans lequel sont sauvegardés les fichiers de sortie. */

        /**
        * @brief Constructeur privé par défaut de la classe Configuration.
        */

        Configuration(){}; 

        /**
        * @brief Constructeur de copie supprimé pour éviter la copie d'instances.
        * @param autre Instance de Configuration à partir de laquelle copier.
        */

        Configuration(Configuration const& autre) = delete;
        
        /**
        * @brief Constructeur de déplacement supprimé pour éviter le transfert d'instances.
        * @param autre Instance de Configuration à partir de laquelle déplacer.
        */
        
        Configuration(Configuration&& autre) = delete;
        
        /**
        * @brief Opérateur d'assignation supprimé pour éviter l'assignation d'instances.
        * @param autre Instance de Configuration à partir de laquelle assigner.
        */
        
        void operator=(Configuration const&) = delete;

    public:

        /* Méthodes publiques */

        /**
        * @brief Fonction statique pour accéder à l'unique instance de Configuration.
        */

        static Configuration& getInstance();

        /**
        * @brief Fonction qui lit les paramètres fournis par l'utilisateur
        *        dans le fichier de configuration.
        */

        void lireFichierConfiguration();

        /**
        * @brief Fonction qui affiche sur la console les paramètres choisis
        *        avec lesquels la simulation sera exécutée.
        */

        void afficherParametresChoisis();

        /**
        * @brief Fonction qui affiche sur la console la variété de paramètres
        *        que l'utilisateur peut définir dans le fichier de configuration.
        */

        void afficherParametresPossibles();

        /* getters */

        /**
        * @brief Fonction qui indique si la force de Lennard-Jones sera utilisée
        *        dans la simulation.
        * @return True si la force de Lennard-Jones est utilisée, False sinon.
        */

        bool getForceLJ() const;

        /**
        * @brief Fonction qui indique si la force d'interaction gravitationnelle
        *        sera utilisée dans la simulation.
        * @return True si la force d'interaction gravitationnelle est utilisée, False sinon.
        */

        bool getForceIG() const;

        /**
        * @brief Fonction qui indique si la force du potenciel gravitationnel
        *        sera utilisée dans la simulation.
        * @return True si la force du potenciel gravitationnel est utilisée, False sinon.
        */

        bool getForcePG() const;

        /**
        * @brief Fonction qui obtient la longueur caractéristique sur l'axe X.
        * @return Longueur caractéristique de l'axe X.
        */

        double getLdX() const;

        /**
        * @brief Fonction qui obtient la longueur caractéristique sur l'axe Y.
        * @return Longueur caractéristique de l'axe Y.
        */

        double getLdY() const;

        /**
        * @brief Fonction qui obtient la longueur caractéristique sur l'axe Z.
        * @return Longueur caractéristique de l'axe Z.
        */

        double getLdZ() const;

        /**
        * @brief Fonction qui obtient le rayon de coupure pour les interactions attractives.
        * @return Rayon de coupure pour les interactions attractives.
        */

        double getRCut() const;

        /**
        * @brief Fonction qui obtient le rayon de coupure pour les réflexions aux bords.
        * @return Rayon de coupure pour les réflexions aux bords.
        */

        double getRCutReflexion() const;

        /**
        * @brief Fonction qui obtient le type de condition limite appliqué aux
        *        particules aux limites de l'univers.
        * @return Type de condition limite appliqué.
        */

        const ConditionLimite& getConditionLimite() const;

        /**
        * @brief Fonction qui indique si la limitation de vitesse sera appliquée
        *        pour maintenir l'énergie cinétique du système.
        * @return True si la vitesse sera limitée, False sinon.
        */

        bool getLimiterVitesse() const;

        /**
        * @brief Fonction qui indique l'énergie désirée en cas de limitation
        *        de vitesse activée.
        * @return Valeur de l'énergie désirée.
        */

        double getEnergieDesiree() const;

        /**
        * @brief Fonction qui obtient la valeur d'epsilon utilisée dans le
        *        calcul des forces.
        * @return Valeur d'epsilon.
        */

        double getEpsilon() const;

        /**
        * @brief Fonction qui obtient la valeur de sigma utilisée dans le
        *        calcul des forces.
        * @return Valeur d'sigma.
        */

        double getSigma() const;

        /**
        * @brief Fonction qui obtient la valeur de G utilisée dans le calcul
        *        des forces.
        * @return Valeur de G.
        */

        double getG() const;

        /**
        * @brief Function qui obtient la valeur delta par laquelle le temps de
        *        simulation avance.
        * @return Valeur de delta.
        */

        double getDelta() const;

        /**
        * @brief Fonction qui obtient la valeur finale du temps jusqu'à laquelle
        *        la simulation sera exécutée.
        * @return Valeur du temps final.
        */

        double getTFinal() const;

        /**
        * @brief Fonction qui obtient le chemin du fichier d'entrée où sont stockées
        *        les particules à utiliser pour la simulation.
        * @return Adresse du fichier d'entrée.
        */

        const std::string& getAdresseFichier() const;

        /**
        * @brief Fonction qui obtient le nom du dossier dans lequel 
        *        seront stockés les documents de sortie de la simulation.
        * @return Nom du dossier.
        */

        const std::string& getNomDossier() const;
        
        /* Setters */

        /**
        * @brief Fonction qui permet de modifier la configuration pour les 
        *        longueurs caractéristiques de l'univers.
        */

        void setLd(double newLdX, double newLdY, double newLdZ);

};
