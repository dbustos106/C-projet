/**
* @mainpage Demo univers
*
* Voici la documentation de Demo Univers.
*
* Ce programme a deux modes :
*
* 1. Mode de simulation de particules : C'est le mode principal du programme, qui consiste 
*    en la simulation d'un univers de particules interagissant sous l'influence de diverses \n
*    forces physiques. Ces forces peuvent inclure l'interaction gravitationnelle, le potentiel 
*    de Lennard-Jones et le potenciel gravitationnel; \n \n
*
* 2. Mode de mesure des performances : C'est un mode secondaire dans lequel les performances
*    des collections standard de C++ sont évaluées pour différentes tailles de données. \n
*    De plus, il mesure le temps nécessaire à la création d'un univers de différentes 
*    tailles de particules. \n
*
* ## Mode de simulation
* 
* Dans le mode de simulation, il existe 3 types de conditions limites :
*
* 1. Réflexion : Les particules subissent une force de réflexion lorsqu'elles se rapprochent 
*                à une distance inférieure à rCutReflexion de l'une des limites de l'univers. \n
* 2. Absorption : Les particules disparaissent lorsqu'elles atteignent les limites de l'univers. 
* 3. Périodique : Les particules se déplacent dans un univers périodique. \n
*
*
* Pour simplifier les calculs, les forces d'interaction ne sont calculées que si la distance
* entre les particules est inférieure à rCut. Ainsi, seules les particules qui contribuent \n
* à une attraction significative sont prises en compte. \n \n
*
* D'autre part, les particules d'entrée à la simulation doivent être centrées autour du point
* (0, 0, 0). Elles doivent être fournies via un fichier vtu, dont le nom sera identique à \n
* celui du dossier de sortie contenant les fichiers de sortie.
*
* ## Fichier de configuration
* 
* Les différentes variables de configuration, avec lesquelles le programme peut être exécuté, 
* doivent être spécifiées dans le fichier "configuracion" du dossier demo. Si l'une des variables \n
* est omise, le programme prendra la valeur par défaut spécifiée ci-dessous: \n
*
* - ADRESSE_FICHIER = Définit l'adresse du fichier vtu à partir duquel les particules d'entrée seront lues.
* - FORCE_LJ = OUI pour activer la force du potentiel de Lennard-Jones (défaut : NON)
* - FORCE_IG = OUI pour activer la force d'interaction gravitationnelle (défaut : NON)
* - FORCE_PG = OUI pour activer la force du potentiel gravitationnel (défaut : NON)
* - LD_X = Définit la longueur caractéristique de l'axe X (défaut : 0)
* - LD_Y = Définit la longueur caractéristique de l'axe Y (défaut : 0)
* - LD_Z = Définit la longueur caractéristique de l'axe Z (défaut : 0)
* - R_CUT = Définit le rayon de coupure pour la construction de la grille (défaut : 2.5)
* - CONDITION_LIMITE = Définit le traitement au bord de l'univers. 'Reflexion', 'Absorption' ou 'Periodique' (défaut : Absorption)
* - LIMITER_VITESSE = OUI pour activer la limitation d'énergie (défaut : NON)
* - ENERGIE_DESIREE = En cas de limitation d'énergie, définit l'énergie desirée du système (défaut : 0.005)
* - EPSILON = Définit la valeur d'epsilon (défaut : 5.0)
* - SIGMA = Définit la valeur de sigma (défaut : 1.0)
* - G = Définit la valeur de G (défaut : -12)
* - DELTA = Définit la valeur de delta avec laquelle le temps est incrémenté dans la simulation (défaut : 0.00005)
* - T_FINAL = Définit le temps de fin de la simulation (défaut : 19.5)
*
* ## Exemple de configuration :
* 
* `   ADRESSE_FICHIER  = colision1.vtu` \n
* `   FORCE_LJ         = OUI` \n
* `   LD_X             = 250` \n
* `   LD_Y             = 130` \n \n
* 
* Cela initialisera la simulation avec un univers de dimensions (250 x 130), 
* avec une distance de coupure de 2,5 et une condition limite de type absorbant. \n 
* Pour le calcul de la force de Lennard-Jones, epsilon est égal à 5 et sigma est 
* égal à 1. La valeur de delta est de 0,00005 et le temps final de la simulation est de 19,5. \n \n
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
    std::cout << "Ce programme a deux modes :\n\n";
    std::cout << "1. Mode de simulation de particules : C'est le mode principal du programme, qui consiste\n"
              << "   en la simulation d'un univers de particules interagissant sous l'influence de diverses\n"
              << "   forces physiques. Ces forces peuvent inclure l'interaction gravitationnelle, le potentiel\n"
              << "   de Lennard-Jones et le potenciel gravitationnel.\n";
    std::cout << "2. Mode de mesure des performances : C'est un mode secondaire dans lequel les performances\n" 
              << "   des collections standard de C++ sont évaluées pour différentes tailles de données.\n"
              << "   De plus, il mesure le temps nécessaire à la création d'un univers de différentes\n"
              << "   tailles de particules.\n\n";

    std::cout << "Veuillez saisir: \n\n"
              << " 1 pour le mode de simulation de particules\n"
              << " 2 pour le mode de mesure des performances\n\n"
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
    if(option == 2){
        mesurerPerformance();

    /* Exécute le mode de simulation de particules */
    }else{

        try{

            Configuration& configuration = Configuration::getInstance();

            /* Afficher les paramètres et demander confirmation */
            configuration.afficherParametresPossibles();

            /* Lire le fichier de configuration et afficher les les paramètres choisis */
            configuration.lireFichierConfiguration();
            configuration.afficherParametresChoisis();

            /* Mesurer le temps de début de la simulation */
            auto start = std::chrono::steady_clock::now();

            /* Créer un univers et lire le fichier .vtu d'entrée */
            Univers univers;
            const std::string& adresseFichier = configuration.getAdresseFichier();
            lectureDuFichier(adresseFichier, univers);
    
            /* Créer la simulation et démarrer l'algorithme de Stromer-Verlet */
            Simulation simulation(univers);
            simulation.stromerVerlet();
    
            /* Mesurer le temps de fin de la simulation */
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout << "Temps de simulation: " << elapsed_seconds.count() << " secondes\n";

        }catch(const std::exception& e){
            std::cerr << "Erreur : " << e.what() << std::endl;
        }
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
}*/

/*
double xCircle = 0;
double yCircle = 20;
double zCircle = 0;
double radius = 13;
double changeAnglePrev = 0;
int nombreParticulesPerCercle = 1;

double distance = 1.2;
for(double j = 1; j < radius; j = j+distance){
    nombreParticulesPerCercle += 6;
    double changeAngle = 2 * M_PI / nombreParticulesPerCercle;
    for(int i = 0; i < nombreParticulesPerCercle; i++){
        double xPoint = xCircle + j * cos(changeAngle*i + changeAnglePrev);
        double yPoint = yCircle + j * sin(changeAngle*i + changeAnglePrev);
        Particule particle("circle", xPoint, yPoint, zCircle, 0,-10,0, 10);
        univers.ajouterParticule(particle);
    }
    changeAnglePrev = changeAngle;
}

double xRectangle = -125;
double yRectangle = -90;
double zRectangle = 0;

distance = 0.8;
for(int i = 0; i < 312; i++){
    for(int j = 0; j < 55; j++){
        Particule particuleRectangle("rectangle", xRectangle + i*distance, yRectangle + j*distance, zRectangle, 0,0,0, 1);
        univers.ajouterParticule(particuleRectangle);
    }
}*/