#include <gtest/gtest.h>
#include "cellule.hxx"

TEST(CelluleTest, testGettersAndSetters){
    Cellule cellule;

    /* Vérifier les indices et les bords */
    cellule.setIndices(3, 5, 2);
    cellule.setBord(true);
    ASSERT_EQ(cellule.getIndices(), Vecteur<int>(3, 5, 2));
    ASSERT_EQ(cellule.isBord(), true);

    /* Ajouter une cellule voisine et vérifier */
    Cellule autreCellule;
    cellule.ajouterVoisine(&autreCellule);
    ASSERT_EQ(cellule.getVoisines().size(), 1);
    ASSERT_EQ(*cellule.getVoisines().begin(), &autreCellule);

    /* Ajouter une particule et vérifier */
    Particule particule(3, 4, 5);
    cellule.ajouterParticule(&particule);
    ASSERT_EQ(cellule.getParticules().size(), 1);
    ASSERT_EQ(*cellule.getParticules().begin(), &particule);

    /* Supprimer la particule et vérifier */
    std::list<Particule*>::const_iterator it = cellule.getParticules().begin(); 
    cellule.suprimerParticule(it);
    ASSERT_EQ(cellule.getParticules().size(), 0);
}

TEST(CelluleTest, testComparerIndices){
    Cellule cellule;

    cellule.setIndices(3, 5, 2);
    ASSERT_EQ(cellule.comparerIndices(3, 5, 2), true);
}
