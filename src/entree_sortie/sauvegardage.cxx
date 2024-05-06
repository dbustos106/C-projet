#include "sauvegardage.hxx"

void sauvegarderEtatEnTexte(std::ofstream& fichierTexte, const Univers& univers, int i){
    fichierTexte << "Iteration " << std::to_string(i) << " : ";
    for(const auto& cellule : univers.getGrille()){
        for(const auto particule : cellule.getParticules()){
            fichierTexte << *particule << " ";
        }
    }
}

void sauvegarderEtatEnVTU(const std::string& nomDossier, const Univers& univers, int i){

    const Vecteur<double>& ld = univers.getLd();
    std::ofstream fichierVTU = ouvrirFichierDeSortie(nomDossier + "/Iteration." + std::to_string(i) + ".vtu");

    fichierVTU << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"BigEndian\">\n";
    fichierVTU << "  <UnstructuredGrid>\n";
    fichierVTU << "    <Piece NumberOfPoints=\"" << std::to_string(univers.getNombreParticules()) << "\" NumberOfCells=\"0\">\n";
    fichierVTU << "      <Points>\n";
    fichierVTU << "        <DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    fichierVTU << "          ";

    /* Sauvegarder les positions */
    for(const auto& cellule : univers.getGrille()){
        for(const auto particule : cellule.getParticules()){
            const Vecteur<double>& position = particule->getPosition();
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
    for(const auto& cellule : univers.getGrille()){
        for(const auto particule : cellule.getParticules()){
            const Vecteur<double>& vitesse = particule->getVitesse();
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
    for(const auto& cellule : univers.getGrille()){
        for(const auto particule : cellule.getParticules()){
            fichierVTU << particule->getMasse() << " ";
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
