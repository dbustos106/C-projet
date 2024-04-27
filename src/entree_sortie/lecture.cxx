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
                throw std::runtime_error("Erreur dans la lecture du nombre de particules\n");
            }
    
            std::string substr = line.substr(quote_start + 1, quote_end - quote_start - 1);
            nombreParticules = std::stoi(substr);
            break;
        }
    }

    /* Vérifier la lecture du nombre de particules */
    if(nombreParticules == static_cast<unsigned long>(-1)){
        throw std::runtime_error("Erreur : nombre de points non défini");
    }

    /* Lire les positions et insérer les particules dans le vecteur */
    while(std::getline(fichier, line)){
        if(line.find("\"Position\"") != std::string::npos){
            if(!std::getline(fichier, line)){
                throw std::runtime_error("Erreur de lecture de la ligne des positions\n");
            } 
            std::stringstream stream(line);
            
            double x, y, z;
            for(unsigned long i = 0; i < nombreParticules; i++){
                if(!(stream >> x >> y >> z)){
                    throw std::runtime_error("Erreur dans la lecture des positions\n");
                }
                Particule particule(x, y, z);
                particules.push_back(particule);
            }
            break;
        }
    }

    /* Vérifier que la taille du vecteur corresponde au nombre de particules */
    if(nombreParticules != particules.size()){
        throw std::runtime_error("Erreur : nombre de points ne correspond pas au nombre de positions");
    }

    /* Lire les vitesses des particules */
    while(std::getline(fichier, line)){
        if(line.find("\"Velocity\"") != std::string::npos){
            if(!std::getline(fichier, line)){
                throw std::runtime_error("Erreur de lecture de la ligne des vitesses\n");
            } 
            std::stringstream stream(line);
        
            for(unsigned long i = 0; i < nombreParticules; i++){
                double vx, vy, vz;
                if(!(stream >> vx >> vy >> vz)){
                    throw std::runtime_error("Erreur dans la lecture des vitesses\n");
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
                throw std::runtime_error("Erreur de lecture de la ligne des masses\n");
            } 
            std::stringstream stream(line);
        
            for(unsigned long i = 0; i < nombreParticules; i++){
                double masse;
                if(!(stream >> masse)){
                    throw std::runtime_error("Erreur dans la lecture des masses\n");
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
