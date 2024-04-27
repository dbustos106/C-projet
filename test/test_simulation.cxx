#include <gtest/gtest.h>
#include "simulation.hxx"

TEST(SimulationTest, testCasDeuxCorps){
    
    /* Établir la configuration de l'univers */
    Configuration& configuration = Configuration::getInstance();
    configuration.setForces(false, true, false);
    configuration.setLd(3, 3, 0);
    configuration.setDelta(0.005);
    configuration.setTFinal(0.045);
    configuration.setRCut(3);

    Univers univers;

    Particule particule1("A", 1.333333,20,0, 0,3.162,0, 1);
    Particule particule2("B", -0.6666667,20,0, 0,-1.581,0, 2);
    univers.ajouterParticule(particule1);
    univers.ajouterParticule(particule2);
    univers.remplirCellules();

    Simulation simulation(univers);
    simulation.stromerVerlet();

    const Cellule& cellule = univers.getCelluleParIndices(0,0,0);
    const Particule* particulePtr1 = cellule.getParticules().front();
    const Particule* particulePtr2 = cellule.getParticules().back();

    ASSERT_EQ(particulePtr1->getPosition(), Vecteur<double>(1.31752, 0.125986, 0));
    ASSERT_EQ(particulePtr2->getPosition(), Vecteur<double>(-0.658758, -0.0629929, 0));

}
