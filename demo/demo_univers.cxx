/**
* @mainpage Demo univers
*
* Voici la documentation de Demo Univers.
* Demo Univers est un programme conçu pour simuler le mouvement de
* particules dans un univers. Il existe 3 types de forces qui peuvent 
* affecter une particule : la force d'interaction du potentiel de 
* Lennard-Jones, la force d'interaction gravitationnelle et la
* force du potentiel gravitationnel.
*
* De plus, il existe 3 types de conditions limites :
*
* 1. Réflexion : Les particules subissent une force de réflexion 
*                lorsqu'elles se rapprochent à une distance inférieure
*                à rCutReflexion de l'une des limites de l'univers.
* 2. Absorption : Les particules disparaissent lorsqu'elles atteignent
*                 les limites de l'univers.
* 3. Périodique : Les particules se déplacent dans un univers périodique.
*
* D'autre part, pour simplifier les calculs, les forces d'interaction ne 
* sont calculées que si la distance entre les particules est inférieure à
* rCut. Ainsi, seules les particules qui contribuent à une attraction 
* significative sont prises en compte.
*
* ## Utilisation du programme 
*
* Le programme peut être exécuté avec les options suivantes. Si une 
* valeur n'est pas fournie, les valeurs par défaut sont utilisées :
* 
* - `-h, --help` : Afficher ce message d'aide.
* - `-v, --version` : Afficher les informations de version.
* - `--ldX <valeur>` (valeur par défaut : 0) : Définir la longueur en X.
* - `--ldY <valeur>` (valeur par défaut : 0) : Définir la longueur en Y.
* - `--ldZ <valeur>` (valeur par défaut : 0) : Définir la longueur en Z.
* - `--rCut <valeur>` (valeur par défaut : 2.5) : Définir la distance de coupure.
* - `--conditionLimite <valeur>` (valeur par défaut : 2) : Définir la condition limite.
* - `--rCutReflexion <valeur>` (valeur par défaut : 2^(1/6)) : Définir la distance de coupure pour la réflexion.
* - `--limiterVitesse` (valeur par défaut : faux) : Limiter la vitesse.
* - `--energieDesiree <valeur>` (valeur par défaut : 0.005) : Définir l'énergie désirée.
* - `--forceLJ` (valeur par défaut : faux) : Utiliser la force de Lennard-Jones.
* - `--forceIG` (valeur par défaut : faux) : Utiliser la force gravitationnelle.
* - `--forcePG` (valeur par défaut : faux) : Utiliser le potentiel gravitationnel.
* - `--epsilon <valeur>` (valeur par défaut : 5.0) : Définir la valeur d'epsilon.
* - `--sigma <valeur>` (valeur par défaut : 1.0) : Définir la valeur de sigma.
* - `--G <valeur>` (valeur par défaut : -12) : Définir la valeur de G.
* - `--delta <valeur>` (valeur par défaut : 0.00005) : Définir la valeur de delta.
* - `--tFinal <valeur>` (valeur par défaut : 19.5) : Définir la valeur de tFinal.
* - `--adresseFichier <valeur>` : Définir l'adresse du fichier d'entrée. 
*
* Si aucune variable n'est fournie, le programme exécutera les tests de performance
* sur les différents types de collections et mesurera le temps pour différentes tailles de données.
*
* ## Exemple d'utilisation :
* 
* `./demo_univers --ldX 250 --ldY 130 --forceLJ --adresseFichier lecture.vtu`
* 
* Cela initialisera la simulation avec un univers de dimensions (250 x 130), 
* avec une distance de coupure de 2,5 et une condition limite de type absorbant. 
* Pour le calcul de la force de Lennard-Jones, epsilon est égal à 5 et sigma est 
* égal à 1. La valeur de delta est de 0,00005 et le temps final de la simulation est de 19,5.
* 
* [Documentation détaillée](annotated.html)
* 
* [Index des classes](classes.html)
* 
* [Index des fichiers](files.html)
*
*/

#include "configuration.hxx"
#include "performance.hxx"
#include "collections.hxx"
#include "simulation.hxx"
#include "particule.hxx"
#include "univers.hxx"
#include "lecture.hxx"
#include <limits>

void afficherLogo(){
    std::cout << "  _____    _    __  __    __   __   __          _      _____   _____    _    _    ___ \n";
    std::cout << " / ____|  | |  |  \\/  |  | |  | |  | |         / \\    |_   _| | ____|  | |  | |  |  _ \\ \n";
    std::cout << "| (___    | |  | |\\/| |  | |  | |  | |        / _ \\     | |   | |___   | |  | |  | |_) |\n";
    std::cout << " \\___ \\   | |  | |  | |  | |  | |  | |       / ___ \\    | |   |  ___|  | |  | |  |____/ \n";
    std::cout << " ____) |  | |  | |  | |  | |  | |  | |___   / _____ \\   | |   | |___   | |  | |  | | |\\ \n";
    std::cout << "|_____/   |_|  |_|  |_|  |____|_|  |_____| /_/     \\_\\  |_|   |_____|  |____|_|  |_| |_\\ \n";

    std::cout << "\t\t  ____     _      ____   _____   _     ____  __   __   __      _____    / ___|\n";
    std::cout << "\t\t | __ )   / \\    | __ ) |_   _| | |  / ____| | |  | | | |     | ____|  | |___ \n";
    std::cout << "\t\t |       / _ \\   |  \\ \\   | |   | | | |      | |  | | | |     | |___    \\___ \\ \n";
    std::cout << "\t\t | |    / ___ \\  | | \\ \\  | |   | | | |      | |  | | | |___  |  ___|    ___) |\n";
    std::cout << "\t\t |_|   /_/   \\_\\ |_|  \\_\\ |_|   |_|  \\_____| |____|_| |_____| | |____   |____/ \n\n";
}

void afficherDebut(){
    std::cout << "Ce programme a deux modes principaux :\n\n";
    std::cout << "1. Mode de mesure des performances : Dans ce mode, le programme évalue les performances\n"
              << "   des collections standard de C++ pour différentes tailles de données. De plus, il mesure\n" 
              << "   le temps nécessaire à la création d'un univers de différentes tailles de particules.\n\n";

    std::cout << "2. Mode de simulation de particules : Dans ce mode, le programme simule un univers de\n"
              << "   particules interagissant sous l'influence de diverses forces physiques. Ces forces\n"
              << "   peuvent inclure l'interaction gravitationnelle, le potentiel de Lennard-Jones et le\n" 
              << "   potenciel gravitationnel.\n\n";   

    std::cout << "Veuillez saisir: \n\n"
              << " 1 pour le mode de mesure des performances\n"
              << " 2 pour le mode de simulation de particules\n\n"
              << ">> ";
}

int main(int argc, char *argv[]){

    int option;
    afficherLogo();

    do{
       afficherDebut();
       std::cin >> option;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }while(option != 1 && option != 2);

    /* Exécute le mode de mesure des performances */
    if(option == 1){
        mesurerPerformance();

    /* Exécute le mode de simulation de particules */
    }else{

        Configuration& configuration = Configuration::getInstance();

        /* Afficher les paramètres et demander confirmation */
        configuration.afficherParametres();

        /* Lire le fichier de configuration et analyser les options */
        configuration.lireFichierConfiguration();
        configuration.parserParametres();
        configuration.afficherParametresChoisis();

        /* Mesurer le temps de début de la simulation */
        auto start = std::chrono::steady_clock::now();

        /* Créer un univers et lire le fichier d'entrée */
        Univers univers;

        /* lire les particules du fichier vtu */
        lectureDuFichier(configuration.getAdresseFichier(), univers);
    
        /* Créer la simulation et démarrer l'algorithme de Stromer-Verlet */
        Simulation simulation(univers);
        simulation.stromerVerlet();
    
        /* Mesurer le temps de fin de la simulation */
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Temps de simulation: " << elapsed_seconds.count() << " secondes\n";
    }

    return 0;
}


/*  
    double distance = pow(2, 1.0/6);

    double xCarre = -pow(2, 1.0/6)*20;
    double yCarre = 8;
    double zCarre = 0;
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 40; j++){
            Particule particuleCarre("carre", xCarre + i*distance, yCarre + j*distance, zCarre, 0,-10,0, 1);
            univers.ajouterParticule(particuleCarre);
        }
    }

    double xRectangle = -pow(2, 1.0/6)*80;
    double yRectangle = -pow(2, 1.0/6)*40 + 4;
    double zRectangle = 0;
    for(int i = 0; i < 160; i++){
        for(int j = 0; j < 40; j++){
            Particule particuleRectangle("rectangle", xRectangle + i*distance, yRectangle + j*distance, zRectangle, 0,0,0, 1);
            univers.ajouterParticule(particuleRectangle);
        }
    }
*/


/*
    Particule soleil("etoile", 21.333333,20,0, 0,3.162,0, 1);
    Particule terre("planete", 19.333333,20,0, 0,-1.581,0, 1);
*/
