#include "../../include/sauvegardage.hxx"

void creerDossier(std::string& nomDossier){
    struct stat info;
    if(stat(nomDossier.c_str(), &info) != 0){
        if(mkdir(nomDossier.c_str(), 0777) != 0){
            std::cerr << "Erreur : échec de la création du dossier.";
            exit(0);
        }
    }
}

std::ofstream ouvrirFichier(std::string&& adresseFichier){
    std::ofstream fichier(adresseFichier);
    if(!fichier.is_open()){
        throw std::runtime_error("Erreur lors de l'overture du fichier de sortie.");
    }
    return fichier;
}

void sauvegarderEtatEnTexte(std::ofstream& fichierTexte, Univers& univers, int i){
    fichierTexte << "Iteration " << std::to_string(i) << " : ";
    for(auto& cellule : univers.getGrille()){
        for(const auto& particulePtr : cellule.getParticules()){
            Particule& particule = *particulePtr;
            fichierTexte << particule << " ";
        }
    }
}

void sauvegarderEtatEnVTU(std::string& nomDossier, Univers& univers, int i){

    const Vecteur& ld = univers.getLd();
    std::ofstream fichierVTU = ouvrirFichier(nomDossier + "/Iteration." + std::to_string(i) + ".vtu");

    fichierVTU << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"BigEndian\">\n";
    fichierVTU << "  <UnstructuredGrid>\n";
    fichierVTU << "    <Piece NumberOfPoints=\"" << std::to_string(univers.getNombreParticules()) << "\" NumberOfCells=\"0\">\n";
    fichierVTU << "      <Points>\n";
    fichierVTU << "        <DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    fichierVTU << "          ";

    /* Sauvegarder les positions */
    for(auto& cellule : univers.getGrille()){
        for(const auto& particulePtr : cellule.getParticules()){
            Particule& particule = *particulePtr;
            Vecteur& position = particule.getPosition();
            fichierVTU << position.getX() - ld.getX()/2 << " ";
            fichierVTU << position.getY() - ld.getY()/2 << " ";
            fichierVTU << position.getZ() - ld.getZ()/2 << " ";
        }
    }
    fichierVTU << "\n";

    fichierVTU << "        </DataArray>\n";
    fichierVTU << "      </Points>\n";
    fichierVTU << "      <PointData Vectors=\"vector\">\n";
    fichierVTU << "        <DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    fichierVTU << "          ";

    /* Sauvegarder les vitesses */
    for(auto& cellule : univers.getGrille()){
        for(const auto& particulePtr : cellule.getParticules()){
            Particule& particule = *particulePtr;
            Vecteur& vitesse = particule.getVitesse();
            fichierVTU << vitesse.getX() << " ";
            fichierVTU << vitesse.getY() << " ";
            fichierVTU << vitesse.getZ() << " ";
        }
    }
    fichierVTU << "\n";

    fichierVTU << "        </DataArray>\n";
    fichierVTU << "        <DataArray type=\"Float32\" Name=\"Masse\" format=\"ascii\">\n";
    fichierVTU << "          ";

    /* Sauvegarder les masses */
    for(auto& cellule : univers.getGrille()){
        for(const auto& particulePtr : cellule.getParticules()){
            Particule& particule = *particulePtr;
            fichierVTU << particule.getMasse() << " ";
        }
    }
    fichierVTU << "\n";

    fichierVTU << "        </DataArray>\n";
    fichierVTU << "      </PointData>\n";
    fichierVTU << "      <Cells>\n";
    fichierVTU << "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n";
    fichierVTU << "        </DataArray>\n";
    fichierVTU << "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n";
    fichierVTU << "        </DataArray>\n";
    fichierVTU << "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n";
    fichierVTU << "        </DataArray>\n";
    fichierVTU << "      </Cells>\n";
    fichierVTU << "    </Piece>\n";
    fichierVTU << "  </UnstructuredGrid>\n";
    fichierVTU << "</VTKFile>\n";

    fichierVTU.close();

}
