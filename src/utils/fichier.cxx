#include "fichier.hxx"

std::ifstream ouvrirFichierDEntree(const std::string& adresseFichier){
    std::ifstream fichier(adresseFichier);
    if(!fichier.is_open()){
        throw std::runtime_error("Erreur lors de l'overture du fichier d'entrée " + adresseFichier);
    }
    return fichier;
}

std::ofstream ouvrirFichierDeSortie(const std::string& adresseFichier){
    std::ofstream fichier(adresseFichier);
    if(!fichier.is_open()){
        throw std::runtime_error("Erreur lors de l'overture du fichier de sortie " + adresseFichier);
    }
    return fichier;
}

void creerDossier(const std::string& nomDossier){
    struct stat info;
    if(stat(nomDossier.c_str(), &info) != 0){
        if(mkdir(nomDossier.c_str(), 0777) != 0){
            throw std::runtime_error("Erreur lors de la création du dossier");
        }
    }
}
