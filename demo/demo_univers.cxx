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

#include "../include/performance.hxx"
#include "../include/collections.hxx"
#include "../include/simulation.hxx"
#include "../include/particule.hxx"
#include "../include/univers.hxx"
#include "../include/lecture.hxx"

/**
* @brief Structure définissant les options par défaut du programme.
*/

struct Options {
    bool help = false; /**< Indique si le message d'aide doit être affiché. */
    bool version = false; /**< Indique si les informations sur la version du programme doivent être affichées. */
    bool forceLJ = false; /**< Indique si la force du potentiel de Lennard-Jones doit être utilisée. */
    bool forceIG = false; /**< Indique si la force d'interaction gravitationnelle doit être utilisée. */
    bool forcePG = false; /**< Indique si le potentiel gravitationnel doit être utilisé. */
    bool limiterVitesse = false; /**< Indique si la vitesse doit être limitée. */
    int conditionLimite = 2; /**< Définit le type de condition limite. */
    
    double ldX = 0; /**< Définit la longueur caractéristique dans la dimension X. */
    double ldY = 0; /**< Définit la longueur caractéristique dans la dimension Y. */
    double ldZ = 0; /**< Définit la longueur caractéristique dans la dimension Z. */

    double rCut = 2.5; /**< Définit la distance de coupure pour calculer les forces d'interaction. */
    double rCutReflexion = pow(2, 1.0/6); /**< Définit la distance de coupure pour calculer la force de réflexion. */
    double energieDesiree = 0.005; /**< Définit l'énergie désirée du système. */
    double epsilon = 5.0; /**< Définit la valeur d'epsilon. */
    double sigma = 1.0; /**< Définit la valeur de sigma. */
    double G = -12; /**< Définit la valeur de G pour le calcul du potentiel gravitationnel. */
    
    double delta = 0.00005; /**< Définit la valeur de delta. */
    double tFinal = 19.5; /**< Définit la valeur de tFinal. */
    
    std::string adresseFichier; /**< Indiquer le nom du fichier de lecture VTU. */

};

/**
* @brief Fonction qui lit les options saisies par l'utilisateur
*        et les renvoie dans une structure d'options.
* @param argc est le nombre d'arguments de la ligne de commande.
* @param argv est le tableau des arguments de la ligne de commande.
* @return Structure d'options contenant les configurations obtenues 
*         à partir des arguments de la ligne de commande.
*/

Options parseOptions(int argc, char* argv[]) {
    Options options;

    for(int i = 1; i < argc; ++i){
        std::string arg = argv[i];

        if(arg == "-h" || arg == "--help"){
            options.help = true;
        }else if(arg == "-v" || arg == "--version"){
            options.version = true;
        }else if(arg == "--forceLJ"){
            options.forceLJ = true;
        }else if(arg == "--forceIG"){
            options.forceIG = true;
        }else if(arg == "--forcePG"){
            options.forcePG = true;
        }else if(arg == "--limiterVitesse"){
            options.limiterVitesse = true;
        }else if(arg == "--conditionLimite" && i + 1 < argc){
            options.conditionLimite = std::atoi(argv[++i]);
        }else if(arg == "--ldX" && i + 1 < argc){
            options.ldX = std::stod(argv[++i]);
        }else if(arg == "--ldY" && i + 1 < argc){
            options.ldY = std::stod(argv[++i]);
        }else if(arg == "--ldZ" && i + 1 < argc){
            options.ldZ = std::stod(argv[++i]);
        }else if(arg == "--rCut" && i + 1 < argc){
            options.rCut = std::stod(argv[++i]);
        }else if(arg == "--rCutReflexion" && i + 1 < argc){
            options.rCutReflexion = std::stod(argv[++i]);
        }else if(arg == "--energieDesiree" && i + 1 < argc){
            options.energieDesiree = std::stod(argv[++i]);
        }else if(arg == "--epsilon" && i + 1 < argc){
            options.epsilon = std::stod(argv[++i]);
        }else if(arg == "--sigma" && i + 1 < argc){
            options.sigma = std::stod(argv[++i]);
        }else if(arg == "--G" && i + 1 < argc){
            options.G = std::stod(argv[++i]);
        }else if(arg == "--delta" && i + 1 < argc){
            options.delta = std::stod(argv[++i]);
        }else if(arg == "--tFinal" && i + 1 < argc){
            options.tFinal = std::stod(argv[++i]);
        }else if(arg == "--adresseFichier" && i + 1 < argc){
            options.adresseFichier = argv[++i];
        }else{
            std::cerr << "Erreur : option inconnue '" << arg << "'\n";
            options.help = true;
        }
    }

    return options;
}

/**
* @brief Fonction qui affiche les options avec lesquelles le programme peut être exécuté.
*/

void printUsage() {
    std::cout << "Utilisation : demo_univers [options]\n"
                 "Options :\n"
                 "  -h, --help                  Afficher ce message d'aide\n"
                 "  -v, --version               Afficher les informations de version\n"
                 "  --ldX <valeur>              Définir la longueur en X\n"
                 "  --ldY <valeur>              Définir la longueur en Y\n"
                 "  --ldZ <valeur>              Définir la longueur en Z\n"
                 "  --rCut <valeur>             Définir la distance de coupure\n"
                 "  --conditionLimite <valeur>  Définir la condition limite\n"
                 "  --rCutReflexion <valeur>    Définir la distance de coupure pour la réflexion\n"
                 "  --limiterVitesse            Limiter la vitesse\n"
                 "  --energieDesiree <valeur>   Définir l'énergie désirée\n"
                 "  --forceLJ                   Utiliser la force de Lennard-Jones\n"
                 "  --forceIG                   Utiliser la force gravitationnelle\n"
                 "  --forcePG                   Utiliser le potentiel gravitationnel\n"
                 "  --epsilon <valeur>          Définir la valeur d'epsilon\n"
                 "  --sigma <valeur>            Définir la valeur de sigma\n"
                 "  --G <valeur>                Définir la valeur de G\n"
                 "  --delta <valeur>            Définir la valeur de delta\n"
                 "  --tFinal <valeur>           Définir la valeur de tFinal\n"
                 "  --adresseFichier <valeur>   Définir l'adresse du fichier d'entrée\n";
}

/**
* @brief Fonction qui vérifie les options fournies par l'utilisateur.
* @param options sont les options sélectionnées.
*/

void verifierOptions(const Options& options){
    if(options.help){
        printUsage();
        exit(0);
    }

    if(options.version){
        std::cout << "demo_univers 1.0\n";
        exit(0);
    }
    
    if(options.adresseFichier.empty()){
        std::cout << "Entrez l'adresse du fichier d'entrée\n"; 
        exit(0);
    }

    size_t positionExtension = options.adresseFichier.find_last_of(".");
    if(positionExtension == std::string::npos || options.adresseFichier.substr(positionExtension) != ".vtu"){
        std::cerr << "Erreur : Extension de fichier différente de .vtu\n";
        exit(0);
    }

    if(options.ldX == 0 && options.ldY == 0 && options.ldZ == 0){
        std::cerr << "Attention : les dimensions de l'univers sont (0, 0, 0).\n";
        exit(0);
    }

}

/**
* @brief Fonction qui affiche les options sélectionnées lors de l'exécution du programme.
* @param options sont les options sélectionnées.
*/

void printOptions(const Options& options) {
    std::cout << "Options de simulation :\n"
              << "\tLongueur en X : " << options.ldX << "\n"
              << "\tLongueur en Y : " << options.ldY << "\n"
              << "\tLongueur en Z : " << options.ldZ << "\n"
              << "\tDistance de coupure : " << options.rCut << "\n";

    std::cout << "\tCondition limite : " << options.conditionLimite << "\n";
    if(options.conditionLimite == 1){
        std::cout << "\tDistance de coupure pour la réflexion : " << options.rCutReflexion << "\n";
    }

    std::cout << "\tLimiter la vitesse : " << (options.limiterVitesse ? "oui" : "non") << "\n";
    if(options.limiterVitesse){
        std::cout << "\tÉnergie désirée : " << options.energieDesiree << "\n";
    }

    std::cout << "\tForce de Lennard-Jones : " << (options.forceLJ ? "activée" : "désactivée") << "\n"
              << "\tForce gravitationnelle : " << (options.forceIG ? "activée" : "désactivée") << "\n"
              << "\tPotentiel gravitationnel : " << (options.forcePG ? "activé" : "désactivé") << "\n";

    if(options.forceLJ || options.forceIG){
        std::cout << "\tEpsilon : " << options.epsilon << "\n"
                  << "\tSigma : " << options.sigma << "\n";
    }

    if(options.forcePG){
        std::cout << "\tG : " << options.G << "\n";
    }

    std::cout << "\tDelta : " << options.delta << "\n"
              << "\ttFinal : " << options.tFinal << "\n\n";

}

/**
* @brief Fonction qui extrait le nom du fichier d'une adresse de fichier.
* @param adresseFichier est l'adresse du fichier dont le nom doit être extrait.
* @return Nom du fichier sans l'extension.
*/

std::string extraireNomFichier(const std::string& adresseFichier) {
    /* Trouver l'apparition de l'extension ".vtu" et la supprimer */
    size_t positionExtension = adresseFichier.find_last_of(".");
    std::string nomFichier = adresseFichier.substr(0, positionExtension);

    /* Trouver la dernière occurrence du caractère diagonal (/) */
    size_t PositionDernierSlash = nomFichier.find_last_of("/\\");

    /* Si aucun slash n'est trouvé, retourner l'adresse complète */
    if (PositionDernierSlash == std::string::npos){
        return nomFichier;
    }

    /* Extraire la partie de la chaîne après le dernier slash */
    return nomFichier.substr(PositionDernierSlash + 1);
}

int main(int argc, char *argv[]){

    if(argc == 1){
        mesurerPerformance();
        exit(0);
    }

    Options options = parseOptions(argc, argv);
    verifierOptions(options);
    printOptions(options);

    /* Mesurer le temps de début de la simulation */
    auto start = std::chrono::steady_clock::now();

    /* Créer un univers avec les options fournies */
    Vecteur ld(options.ldX, options.ldY, options.ldZ);
    Univers univers(ld, options.rCut, options.rCutReflexion, options.conditionLimite);

    /* Ajouter les particules du fichier d'entrée */
    lectureDuFichier(options.adresseFichier, univers);

    /* Obtenir le nom du dossier où les fichiers de sortie VTU seront sauvegardés */
    std::string nomDossier = extraireNomFichier(options.adresseFichier);
    
    /* Créer la simulation et démarrer l'algorithme de Stromer-Verlet */
    Simulation simulation(univers, options.forceLJ, options.forceIG, options.forcePG, 
                    options.G, options.sigma, options.epsilon, options.energieDesiree, nomDossier);
    simulation.stromerVerlet(options.delta, options.tFinal, options.limiterVitesse);
    
    /* Mesurer le temps de fin de la simulation */
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Temps de simulation: " << elapsed_seconds.count() << " secondes\n";

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
