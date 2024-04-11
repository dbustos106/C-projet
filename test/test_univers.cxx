#include <gtest/gtest.h>
#include "../include/univers.hxx"
/*
TEST(UniversTest, testConstructorAndGetters){
    Univers univers(3, 1, Vecteur(3, 3, 3));

    ASSERT_EQ(univers.getNombreDimensions(), 3);
    ASSERT_EQ(univers.getNombreParticules(), 0);
    ASSERT_EQ(univers.getNc(), Vecteur(3, 3, 3));

    const Vecteur &nc = univers.getNc();
    for(int i = 0; i < 9; i++){
        Cellule &cellule = univers.getCellule(i);

        int y = static_cast<int>(i / nc.getZ()) % static_cast<int>(nc.getY());
        int z = i % static_cast<int>(nc.getZ());
        int x = i / (nc.getY() * nc.getZ());

        ASSERT_EQ(cellule.getIndice(), Vecteur(x, y, z));
    }

    Cellule &centre = univers.getCellule(13);
    ASSERT_EQ(centre.getVoisines().size(), 27);

    Cellule &bord = univers.getCellule(4);
    ASSERT_EQ(bord.getVoisines().size(), 18);

}

TEST(UniversTest, testAjouterParticule){
    int lx = 3;
    int ly = 3;
    int lz = 3;

    Univers univers(3, 1, Vecteur(lx, ly, lz));
    
    Particule particule(1.2, 0, -1);
    univers.ajouterParticule(particule);

    int indice = 2 * ly*lz + 1 * lz + 0;
    Cellule &cellule = univers.getCellule(indice);

    ASSERT_EQ(cellule.getParticules().size(), 1);
    ASSERT_EQ(univers.getNombreParticules(), 1);
}

TEST(UniversTest, testAjouterParticules){
    Univers univers(3, 1, Vecteur(3, 3, 3));
    univers.ajouterParticulesAleatoires(5);
    ASSERT_EQ(univers.getNombreParticules(), 5);
}
*/