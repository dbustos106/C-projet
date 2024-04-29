#include "lecture.hxx"

void lectureDuFichier(const std::string& adresseFichier, Univers& univers){
    
    /* Créer un vecteur pour stocker les particules */
    std::vector<Particule> particules;
    unsigned long nombreParticules = -1;

    /* Ouvrir le fichier de lecture */
    std::ifstream fichier = ouvrirFichierDEntree(adresseFichier);
    std::string line;

    /* Lire le nombre de particules dans le fichier */
    while(std::getline(fichier, line)){
        if(line.find("NumberOfPoints=") != std::string::npos){
            size_t quote_start = line.find("\""); 
            size_t quote_end = line.find("\"", quote_start + 1); 
            if(quote_start == std::string::npos || quote_end == std::string::npos){
                throw std::invalid_argument("Nombre de points mal définis");
            }
    
            std::string substr = line.substr(quote_start + 1, quote_end - quote_start - 1);
            nombreParticules = std::stoi(substr);
            break;
        }
    }

    /* Vérifier la lecture du nombre de particules */
    if(nombreParticules == static_cast<unsigned long>(-1)){
        throw std::invalid_argument("Nombre de points non défini");
    }

    /* Lire les positions et insérer les particules dans le vecteur */
    while(std::getline(fichier, line)){
        if(line.find("\"Position\"") != std::string::npos){
            if(!std::getline(fichier, line)){
                throw std::invalid_argument("Erreur de lecture de la ligne des positions");
            } 
            std::stringstream stream(line);
            
            double x, y, z;
            for(unsigned long i = 0; i < nombreParticules; i++){
                if(!(stream >> x >> y >> z)){
                    throw std::invalid_argument("Erreur dans la lecture des positions");
                }
                Particule particule(x, y, z);
                particules.push_back(particule);
            }
            break;
        }
    }

    /* Vérifier que la taille du vecteur corresponde au nombre de particules */
    if(nombreParticules != particules.size()){
        throw std::invalid_argument("Nombre de points ne correspond pas au nombre de positions");
    }

    /* Lire les vitesses des particules */
    while(std::getline(fichier, line)){
        if(line.find("\"Velocity\"") != std::string::npos){
            if(!std::getline(fichier, line)){
                throw std::invalid_argument("Erreur de lecture de la ligne des vitesses");
            } 
            std::stringstream stream(line);
        
            for(unsigned long i = 0; i < nombreParticules; i++){
                double vx, vy, vz;
                if(!(stream >> vx >> vy >> vz)){
                    throw std::invalid_argument("Erreur dans la lecture des vitesses");
                }
        
                particules[i].setVitesse(Vecteur<double>(vx, vy, vz));
            }
            break;
        }
    }

    /* Lire les masses des particules */
    while(std::getline(fichier, line)){
        if(line.find("\"Masse\"") != std::string::npos){
            if(!std::getline(fichier, line)){
                throw std::invalid_argument("Erreur de lecture de la ligne des masses");
            } 
            std::stringstream stream(line);
        
            for(unsigned long i = 0; i < nombreParticules; i++){
                double masse;
                if(!(stream >> masse)){
                    throw std::invalid_argument("Erreur dans la lecture des masses");
                }
                particules[i].setMasse(masse);
            }
            break;
        }
    }

    /* Ajouter les particules à l'univers */
    for(auto& particule : particules){
        univers.ajouterParticule(particule);
    }

    fichier.close();
}
