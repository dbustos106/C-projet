#include <gtest/gtest.h>
#include "simulation.hxx"

TEST(SimulationTest, testCasDeuxCorps){
    
    /* Établir la configuration de l'univers */
    Configuration& configuration = Configuration::getInstance();
    configuration.setConditionLimite(ConditionLimite::Absorption);
    configuration.setForces(false, true, false);
    configuration.setNomDossier("test");
    configuration.setDelta(0.005);
    configuration.setTFinal(0.04);
    configuration.setLd(3, 3, 0);
    configuration.setRCut(3);

    Univers univers;

    Particule particule1("A", 1.333333,0,0, 0,3.162,0, 1);
    Particule particule2("B", -0.6666667,0,0, 0,-1.581,0, 2);
    univers.ajouterParticule(particule1);
    univers.ajouterParticule(particule2);

    Simulation simulation(univers);
    simulation.stromerVerlet();

    const Cellule& cellule = univers.getCelluleParIndices(0,0,0);
    Particule* particulePtr1 = cellule.getParticules().front();
    Particule* particulePtr2 = cellule.getParticules().back();

    Vecteur<double> ldM = -univers.getLd() / 2;
    univers.deplacerParticule(particulePtr1, ldM);
    univers.deplacerParticule(particulePtr2, ldM);

    ASSERT_EQ(particulePtr1->getPosition().getX() - 1.31752 > -0.00001, true);
    ASSERT_EQ(particulePtr1->getPosition().getX() - 1.31752 < 0.00001, true);

    ASSERT_EQ(particulePtr1->getPosition().getY() - 0.125986 > -0.000001, true);
    ASSERT_EQ(particulePtr1->getPosition().getY() - 0.125986 < 0.000001, true);

    ASSERT_EQ(particulePtr2->getPosition().getX() - (-0.658758) > -0.000001, true);
    ASSERT_EQ(particulePtr2->getPosition().getX() - (-0.658758) < 0.000001, true);

    ASSERT_EQ(particulePtr2->getPosition().getY() - (-0.0629929) > -0.0000001, true);
    ASSERT_EQ(particulePtr2->getPosition().getY() - (-0.0629929) < 0.0000001, true);

}

TEST(SimulationTest, testCasChuteCorp){
    
    /* Établir la configuration de l'univers */
    Configuration& configuration = Configuration::getInstance();
    configuration.setConditionLimite(ConditionLimite::Absorption);
    configuration.setForces(false, false, true);
    configuration.setNomDossier("test");
    configuration.setLd(2, 20, 0);
    configuration.setDelta(0.005);
    configuration.setTFinal(1);
    configuration.setRCut(2);

    Univers univers;

    Particule particule("A", 0,9,0, 0,0,0, 1);
    univers.ajouterParticule(particule);

    Simulation simulation(univers);
    simulation.stromerVerlet();

    const Cellule& cellule = univers.getCelluleParIndices(0,6,0);
    Particule* particulePtr = cellule.getParticules().front();

    Vecteur<double> ldM = -univers.getLd() / 2;
    univers.deplacerParticule(particulePtr, ldM);

    ASSERT_EQ(particulePtr->getPosition().getY(), 3);

}
