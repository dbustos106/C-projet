#include "imprimer.hxx"

void imprimerParticulesSurConsole(const std::vector<Particule>& particules){
    for(auto& particule : particules){
        std::cout << particule << "\n";
    }
}

void imprimerGrilleSurConsole(const std::vector<Cellule>& grille){
    for(const auto& cellule : grille){
        std::cout << "Indice : " << cellule.getIndices() << "\n";
        std::cout << "Voisines : " << "\n";
        for(auto voisine : cellule.getVoisines()){
            std::cout << "  " << voisine->getIndices() << "\n";
        }
    }
}
