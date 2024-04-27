#include <gtest/gtest.h>
#include "particule.hxx"

TEST(ParticuleTest, testGettersAndSetters){
    Particule particule("NA", 3,4,5, 0,-10,0, 1);

    ASSERT_EQ(particule.getCategorie(), "NA");
    ASSERT_EQ(particule.getPosition(), Vecteur<double>(3, 4, 5));
    ASSERT_EQ(particule.getVitesse(), Vecteur<double>(0, -10, 0));
    ASSERT_EQ(particule.getForce(), Vecteur<double>(0, 0, 0));
    ASSERT_EQ(particule.getMasse(), 1);
}

TEST(ParticuleTest, testDeplacerAccelerer){
    Particule particule(3,4,5);

    particule.accelerer(Vecteur<double>(0, 5, 0));
    particule.accelerer(Vecteur<double>(0, 5, 0));
    particule.deplacer(Vecteur<double>(2, -1, 5.5));

    ASSERT_EQ(particule.getPosition(), Vecteur<double>(5, 3, 10.5));
    ASSERT_EQ(particule.getVitesse(), Vecteur<double>(0, 10, 0));
}

TEST(ParticuleTest, testOperatorComparaison){
    Particule particule1(1,2,3);
    Particule particule2(4,1,3);

    ASSERT_EQ(particule1 < particule2, true);
}

TEST(ParticuleTest, testOperatorOutput){
    Particule particule("NA", 3,4,5, 0,-10,0, 1);

    std::stringstream ss;
    ss << particule;

    std::string str = "Particule ID : 1 Categorie : NA Position : (3, 4, 5) Vitesse : (0, -10, 0) Force : (0, 0, 0) Masse : 1 ";

    ASSERT_EQ(ss.str(), str);
}
