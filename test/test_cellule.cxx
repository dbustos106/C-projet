#include <gtest/gtest.h>
#include "../include/cellule.hxx"

TEST(CelluleTest, testGettersAndSetters){
    Cellule cellule;

    cellule.setIndices(3, 5, 2);
    ASSERT_EQ(cellule.getIndices(), Vecteur(3, 5, 2));

    Particule particule(3.0, 4.0, 5.0);
    cellule.ajouterParticule(&particule);

    //ASSERT_EQ
}

