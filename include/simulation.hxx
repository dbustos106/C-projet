#pragma once

#include "univers.hxx"
#include "sauvegardage.hxx"

/**
* @brief Classe représentant la simulation de particules interagissant.
*/

class Simulation{
    
    private:

        Univers& univers; /**< Référence à l'univers dans lequel la simulation est réalisée. */

        bool forceLJ; /**< Indicateur de l'application de la force de Lennard-Jones dans la simulation. */
        bool forceIG; /**< Indicateur de l'application de la force d'interaction gravitationnelle dans la simulation. */
        bool forcePG; /**< Indicateur de l'application de la force du potentiel gravitationnel dans la simulation. */

        double G; /**< Constante gravitationnelle utilisée dans la simulation. */
        double sigma; /**< Paramètre sigma de la force de Lennard-Jones. */
        double epsilon; /**< Paramètre epsilon de la force de Lennard-Jones. */
        double energieDesiree; /**< Énergie désirée dans la simulation. */

        std::string nomDossier; /**< Nom du dossier dans lequel les fichiers de sortie seront créés. */

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
        
        void calculerForceReflexive(Particule& particule);
        
        /**
        * @brief Fonction qui calcule les forces qui affectent une particule 
        *        appartenant à une cellule donnée. Les forces peuvent être dues 
        *        au potentiel de Lennard-Jones, à l'interaction gravitationnelle 
        *        ou au potentiel gravitationnel.
        * @param[in] cellule est la cellule.
        * @param[in] particule est la particule.
        */
        
        void calculerForceSurParticule(Cellule& cellule, Particule& particule);
        
        /**
        * @brief fonction qui calcule l'énergie cinétique du système à un moment donné.
        */

        double calculerEnergieCinetique();

    public:

        /* Constructeur */

        /**
        * @brief Constructeur de la classe Simulation.
        * @param univers est une référence à l'univers dans lequel la simulation sera réalisée.
        * @param forceLJ est un indicateur de l'application de la force de Lennard-Jones dans la simulation.
        * @param forceIG est un indicateur de l'application de la force d'interaction gravitationnelle dans la simulation.
        * @param forcePG est un indicateur de l'application de la force d'interaction électrostatique dans la simulation.
        * @param G est la valeur de la constante gravitationnelle utilisée dans la simulation.
        * @param sigma est la valeur du paramètre sigma de la force de Lennard-Jones.
        * @param epsilon est la valeur du paramètre epsilon de la force de Lennard-Jones.
        * @param energieDesiree est la valeur de l'énergie désirée dans la simulation.
        * @param nomDossier est le nom du dossier dans lequel les fichiers de sortie seront crées.
        */

        Simulation(Univers& univers, bool forceLJ, bool forceIG, bool forcePG, 
                    double G, double sigma, double epsilon, double energieDesiree, std::string& nomDossier);

        /* Méthodes publiques */

        /**
        * @brief Fonction qui exécute l’algorithme Stromer verlet.
        * @param[in] delta est la valeur de delta.
        * @param[in] tFinal est la valeur finale du temps.
        * @param[in] limiterVitesse est un booléen pour limiter la vitesse des particules.
        */

        void stromerVerlet(double delta, double tFinal, bool limiterVitesse);

};
