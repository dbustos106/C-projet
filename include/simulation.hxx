#pragma once

#include "configuration.hxx"
#include "sauvegardage.hxx"
#include "fichier.hxx"
#include "univers.hxx"

/**
* @brief Classe représentant la simulation de particules interagissant.
*/

class Simulation{
    
    private:

        Univers& univers; /**< Référence à l'univers dans lequel la simulation est réalisée. */

        bool forceLJ; /**< Indique si la force du potentiel de Lennard-Jones doit être utilisée. */
        bool forceIG; /**< Indique si la force d'interaction gravitationnelle doit être utilisée. */
        bool forcePG; /**< Indique si le potentiel gravitationnel doit être utilisé. */

        bool limiterVitesse; /**< Indique si la vitesse doit être limitée. */
        double energieDesiree; /**< Définit l'énergie désirée du système. */
        
        double G; /**< Définit la valeur de G pour le calcul du potentiel gravitationnel. */
        double epsilon; /**< Définit la valeur d'epsilon de la force de Lennard-Jones. */
        double sigma; /**< Définit la valeur de sigma de la force de Lennard-Jones. */
        
        double delta; /**< Définit la valeur de delta. */
        double tFinal; /**< Définit la valeur de tFinal. */

        std::string nomDossier; /**< Définit le nom du dossier dans lequel les fichiers de sortie seront créés. */
        std::ofstream fichierTexte; /**< Définit le descripteur du fichier texte dans lequel l'état des particules est sauvegardé */

        /* Méthodes privées */

        /**
        * @brief Fonction qui calcule toutes les forces impliquées dans le système.
        */

        void calculerForcesDuSysteme();
        
        /**
        * @brief Fonction qui calcule les forces réfléchissantes qui affectent 
        *        une particule lorsqu'elle se trouve très près du bord.
        * @param[in] particule est la particule.
        */
        
        void calculerForceReflexive(Particule* particule);
        
        /**
        * @brief Fonction qui calcule les forces qui affectent une particule 
        *        appartenant à une cellule donnée. Les forces peuvent être dues 
        *        au potentiel de Lennard-Jones, à l'interaction gravitationnelle 
        *        ou au potentiel gravitationnel.
        * @param[in] cellule est la cellule.
        * @param[in] particule est la particule.
        */
        
        void calculerForceSurParticule(const Cellule& cellule, Particule* particule);
        
        /**
        * @brief Fonction qui calcule l'énergie cinétique du système à un moment donné.
        */

        double calculerEnergieCinetique();

    public:

        /* Constructeur */

        /**
        * @brief Constructeur de la classe Simulation.
        * @param univers est une référence à l'univers dans lequel la simulation sera réalisée.
        */

        Simulation(Univers& univers);

        /* Méthodes publiques */

        /**
        * @brief Fonction qui exécute l’algorithme Stromer verlet.
        */

        void stromerVerlet();

};
