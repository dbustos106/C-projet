#include "configuration.hxx"

/* Méthodes publiques */

Configuration& Configuration::getInstance(){
    static Configuration instance;
    return instance;
}

void Configuration::lireFichierConfiguration(){

    /* Ouvrir le fichier de configuration */
    std::ifstream configuration = ouvrirFichierDEntree("configuration.conf");

    std::string line;
    /* Lire chacune des lignes du fichier */
    while(std::getline(configuration, line)){
                
        /* Supprimer les commentaires s'ils existent */
        size_t commentPos = line.find("//");
        if(commentPos != std::string::npos){
            line = line.substr(0, commentPos);
        } 

        /* Continuer si la ligne est vide */
        if(line.find_first_not_of(" \t\r\n") == std::string::npos){
            continue;
        }
                    
        /* Séparer la ligne en clé et valeur */
        std::string key, value;
        std::istringstream iss(line);
        if(!std::getline(iss, key, '=')){
            throw std::invalid_argument("Format de fichier de configuration incorrect");
        }
            
        /* Continuer si value est vide */
        if(!std::getline(iss, value)){
            continue;
        }
        
        /* Supprimer les espaces autour de la clé et de la valeur */
        key.erase(0, key.find_first_not_of(" \t\r\n"));
        key.erase(key.find_last_not_of(" \t\r\n") + 1);
        value.erase(0, value.find_first_not_of(" \t\r\n"));
        value.erase(value.find_last_not_of(" \t\r\n") + 1);

        /* Continuer si value est vide */
        if(value.empty()){
            continue;
        }

        /* Stocker la valeur de la clé */
        if(key == "FORCE_LJ"){
            forceLJ = (value == "OUI");
        }else if(key == "FORCE_IG"){
            forceIG = (value == "OUI");
        }else if(key == "FORCE_PG"){
            forcePG = (value == "OUI");
        }else if(key == "LD_X"){
            ldX = std::stod(value);
        }else if(key == "LD_Y"){
            ldY = std::stod(value);
        }else if(key == "LD_Z"){
            ldZ = std::stod(value);
        }else if(key == "R_CUT"){
            rCut = std::stod(value);
        }else if(key == "R_CUT_REFLEXION"){
            rCutReflexion = std::stod(value);
        }else if(key == "LIMITER_VITESSE"){
            limiterVitesse = (value == "OUI");
        }else if(key == "ENERGIE_DESIREE"){
            energieDesiree = std::stod(value);
        }else if(key == "EPSILON"){
            epsilon = std::stod(value);
        }else if(key == "SIGMA"){
            sigma = std::stod(value);
        }else if(key == "G"){
            G = std::stod(value);
        }else if(key == "DELTA"){
            delta = std::stod(value);
        }else if(key == "T_FINAL"){
            tFinal = std::stod(value);
        }else if(key == "ADRESSE_FICHIER"){
            adresseFichier = value;
        }else if(key == "CONDITION_LIMITE"){
            if(value == "Absorption"){
                conditionLimite = ConditionLimite::Absorption;
            }else if(value == "Reflexion"){
                conditionLimite = ConditionLimite::Reflexion;
            }else if(value == "Periodique"){
                conditionLimite = ConditionLimite::Periodique;
            }else{
                throw std::invalid_argument("Valeur de condition limite non valide: " + value);
            }
        }else{
            throw std::invalid_argument("Option inconnue '" + key + "'");
        }
    }

    /* Fermer le descripteur de fichier */
    configuration.close();

    /* Si l'adresse du fichier d'entrée n'est pas fournie, demandez-la */
    if(adresseFichier.empty()){
        throw std::invalid_argument("Le fichier d'entrée n'a pas été saisi"); 
    }

    /* Vérifier le format du fichier d'entrée */
    size_t positionExtension = adresseFichier.find_last_of(".");
    if(positionExtension == std::string::npos || adresseFichier.substr(positionExtension) != ".vtu"){
        throw std::invalid_argument("Extension de fichier différente de .vtu");
    }

    /* Prendre le nom du fichier d'entrée comme nom pour le dossier de sortie */
    std::string nomFichier = adresseFichier.substr(0, positionExtension);
    size_t PositionDernierSlash = nomFichier.find_last_of("/\\");
    if(PositionDernierSlash != std::string::npos){
        nomFichier = nomFichier.substr(PositionDernierSlash + 1);
    }
    nomDossier = nomFichier;

}

void Configuration::afficherParametresChoisis(){
    std::cout << "\nLes paramètres de simulation choisis sont:\n"
              << "\tLongueur en X : " << ldX << "\n"
              << "\tLongueur en Y : " << ldY << "\n"
              << "\tLongueur en Z : " << ldZ << "\n"
              << "\tDistance de coupure : " << rCut << "\n";

    std::cout << "\tCondition limite : ";
    switch(conditionLimite){
        case ConditionLimite::Absorption:
            std::cout << "Absorption\n";
            break;
        case ConditionLimite::Reflexion:
            std::cout << "Reflexion\n";
            break;
        case ConditionLimite::Periodique:
            std::cout << "Periodique\n";
            break;
    }

    if(conditionLimite == ConditionLimite::Reflexion){
        std::cout << "\tDistance de coupure pour la réflexion : " << rCutReflexion << "\n";
    }

    std::cout << "\tLimiter la vitesse : " << (limiterVitesse ? "oui" : "non") << "\n";
    if(limiterVitesse){
        std::cout << "\tÉnergie désirée : " << energieDesiree << "\n";
    }

    std::cout << "\tForce de Lennard-Jones : " << (forceLJ ? "activée" : "désactivée") << "\n"
              << "\tForce gravitationnelle : " << (forceIG ? "activée" : "désactivée") << "\n"
              << "\tPotentiel gravitationnel : " << (forcePG ? "activé" : "désactivé") << "\n";

    if(forceLJ || forceIG){
        std::cout << "\tEpsilon : " << epsilon << "\n" << "\tSigma : " << sigma << "\n";
    }

    if(forcePG){
        std::cout << "\tG : " << G << "\n";
    }

    std::cout << "\tDelta : " << delta << "\n" << "\ttFinal : " << tFinal << "\n\n";
}

void Configuration::afficherParametresPossibles(){
    std::cout << "\nLes différentes variables de configuration doivent être spécifiées dans le fichier\n" 
              << "\"configuracion\" du dossier demo. Si l'une des variables est omise, le programme prendra\n" 
              << "la valeur par défaut spécifiée ci-dessous.\n\n";
    std::cout << " - ADRESSE_FICHIER = Définit l'adresse du fichier vtu à partir duquel les particules d'entrée seront lues.\n";
    std::cout << " - FORCE_LJ = OUI pour activer la force du potentiel de Lennard-Jones (défaut : NON)\n";
    std::cout << " - FORCE_IG = OUI pour activer la force d'interaction gravitationnelle (défaut : NON)\n";
    std::cout << " - FORCE_PG = OUI pour activer la force du potentiel gravitationnel (défaut : NON)\n";
    std::cout << " - LD_X = Définit la longueur caractéristique de l'axe X (défaut : 0)\n";
    std::cout << " - LD_Y = Définit la longueur caractéristique de l'axe Y (défaut : 0)\n";
    std::cout << " - LD_Z = Définit la longueur caractéristique de l'axe Z (défaut : 0)\n";
    std::cout << " - R_CUT = Définit le rayon de coupure pour la construction de la grille (défaut : 2.5)\n";
    std::cout << " - CONDITION_LIMITE = Définit le traitement au bord de l'univers. 'Reflexion', 'Absorption' ou 'Periodique' (défaut : Absorption)\n";
    std::cout << " - LIMITER_VITESSE = OUI pour activer la limitation d'énergie (défaut : NON)\n";
    std::cout << " - ENERGIE_DESIREE = En cas de limitation d'énergie, définit l'énergie desirée du système (défaut : 0.005)\n";
    std::cout << " - EPSILON = Définit la valeur d'epsilon (défaut : 5.0)\n";
    std::cout << " - SIGMA = Définit la valeur de sigma (défaut : 1.0)\n";
    std::cout << " - G = Définit la valeur de G (défaut : -12)\n";
    std::cout << " - DELTA = Définit la valeur de delta avec laquelle le temps est incrémenté dans la simulation (défaut : 0.00005)\n";
    std::cout << " - T_FINAL = Définit le temps de fin de la simulation (défaut : 19.5)\n\n";
    std::cout << "Entrez la lettre (Y) pour confirmer la simulation. Toute autre entrée terminera l'exécution >> ";

    std::string confirmation;
    std::cin >> confirmation;

    if(confirmation != "Y"){
        exit(0);
    }

}

/* getters */

bool Configuration::getForceLJ() const{
    return forceLJ; 
}

bool Configuration::getForceIG() const{
    return forceIG; 
}

bool Configuration::getForcePG() const{
    return forcePG; 
}

double Configuration::getLdX() const{
    return ldX; 
}

double Configuration::getLdY() const{
    return ldY; 
}

double Configuration::getLdZ() const{
    return ldZ; 
}

double Configuration::getRCut() const{
    return rCut; 
}

double Configuration::getRCutReflexion() const{ 
    return rCutReflexion; 
}

const ConditionLimite& Configuration::getConditionLimite() const{ 
    return conditionLimite; 
}

bool Configuration::getLimiterVitesse() const{ 
    return limiterVitesse; 
}

double Configuration::getEnergieDesiree() const{ 
    return energieDesiree; 
}

double Configuration::getEpsilon() const{ 
    return epsilon; 
}

double Configuration::getSigma() const{ 
    return sigma; 
}

double Configuration::getG() const{ 
    return G; 
}

double Configuration::getDelta() const{
    return delta;
}

double Configuration::getTFinal() const{ 
    return tFinal;
}

const std::string& Configuration::getAdresseFichier() const{ 
    return adresseFichier;
}

const std::string& Configuration::getNomDossier() const{ 
    return nomDossier;
}

/* Setters */

void Configuration::setLd(double newLdX, double newLdY, double newLdZ){
    ldX = newLdX;
    ldY = newLdY;
    ldZ = newLdZ;
}

void Configuration::setForces(bool newForceLJ, bool newForceIG, bool newForcePG){
    forceLJ = newForceLJ;
    forceIG = newForceIG;
    forcePG = newForcePG;
}

void Configuration::setConditionLimite(ConditionLimite newConditionLimite){
    conditionLimite = newConditionLimite;
}

void Configuration::setRCut(double newRCut){
    rCut = newRCut;
}

void Configuration::setDelta(double newDelta){
    delta = newDelta;
}

void Configuration::setTFinal(double newTFinal){
    tFinal = newTFinal;
}

void Configuration::setNomDossier(const std::string& newNomDossier){
    nomDossier = newNomDossier;
}
