#include <gtest/gtest.h>
#include "univers.hxx"

TEST(UniversTest, testConstructorAndGetters){

    /* Établir la configuration de l'univers */
    Configuration& configuration = Configuration::getInstance();
    configuration.setLd(7.5, 7.5, 7.5);
    configuration.setRCut(2.5);

    Univers univers;

    /* Vérifier les getters */
    ASSERT_EQ(univers.getGrille().size(), 27);
    ASSERT_EQ(univers.getLd(), Vecteur<double>(7.5, 7.5, 7.5));
    ASSERT_EQ(univers.getConditionLimite(), ConditionLimite::Absorption);
    ASSERT_EQ(univers.getRCutReflexion(), pow(2, 1.0/6));
    ASSERT_EQ(univers.getNombreParticules(), 0);
    ASSERT_EQ(univers.getRCut(), 2.5);

    /* Vérifier la grille des cellules */
    for(const auto& cellule : univers.getGrille()){
        const Vecteur<int>& indices = cellule.getIndices();
        
        int x = indices.getX();
        int y = indices.getY();
        int z = indices.getZ();
        int bords = 0;

        if(x == 0 || x == 2){
            bords += 1;
        }

        if(y == 0 || y == 2){
            bords += 1;
        }

        if(z == 0 || z == 2){
            bords += 1;
        }

        if(bords == 0){
            ASSERT_EQ(cellule.getVoisines().size(), 27);
        }

        if(bords == 1){
            ASSERT_EQ(cellule.getVoisines().size(), 18);
        }

        if(bords == 2){
            ASSERT_EQ(cellule.getVoisines().size(), 12);
        }

        if(bords == 3){
            ASSERT_EQ(cellule.getVoisines().size(), 8);
        }

    }
}

TEST(UniversTest, testDirectionParticulesEnConditionPeriodique){
    
    /* Établir la configuration de l'univers */
    Configuration& configuration = Configuration::getInstance();
    configuration.setConditionLimite(ConditionLimite::Periodique);
    configuration.setLd(10, 10, 10);
    configuration.setRCut(2.5);

    Univers univers;

    /* Créer des particules */
    Particule particule1(-4, -3, 0);
    Particule particule2(4, 3, 4);

    /* Calculer le vecteur direction entre les particules */
    Vecteur<double> direction = univers.calculerVecteurDirection(&particule1, &particule2);
    ASSERT_EQ(direction, Vecteur<double>(-2, -4, 4));
    ASSERT_EQ(direction.norme(), 6);
}

TEST(UniversTest, testDirectionParticulesEnConditionAbsorption){
    
    /* Établir la configuration de l'univers */
    Configuration& configuration = Configuration::getInstance();
    configuration.setConditionLimite(ConditionLimite::Absorption);
    configuration.setLd(10, 10, 10);
    configuration.setRCut(2.5);

    Univers univers;

    /* Créer des particules */
    Particule particule1(-1, 1, 0.5);
    Particule particule2(2, 4, 2);

    /* Calculer le vecteur direction entre les particules */
    Vecteur<double> direction = univers.calculerVecteurDirection(&particule1, &particule2);
    ASSERT_EQ(direction, Vecteur<double>(3, 3, 1.5));
    ASSERT_EQ(direction.norme(), 4.5);
}

TEST(UniversTest, testDeplacerParticulePeriodique){

    /* Établir la configuration de l'univers */
    Configuration& configuration = Configuration::getInstance();
    configuration.setConditionLimite(ConditionLimite::Periodique);
    configuration.setLd(10, 10, 10);
    configuration.setRCut(2.5);

    Univers univers;

    /* Créer une particule */
    Particule particule(3, 6, 8);

    /* Deplacer la particule et verifier */
    univers.deplacerParticule(&particule, Vecteur<double>(-7, 6, 1));
    ASSERT_EQ(particule.getPosition(), Vecteur<double>(6, 2, 9));
}

TEST(UniversTest, testDeplacerParticuleAbsorption){

    /* Établir la configuration de l'univers */
    Configuration& configuration = Configuration::getInstance();
    configuration.setConditionLimite(ConditionLimite::Absorption);
    configuration.setLd(10, 10, 10);
    configuration.setRCut(2.5);

    Univers univers;

    /* Ajouter une particule */
    Particule particule(3, 6, 8);

    /* Deplacer la particule et vérifier */
    univers.deplacerParticule(&particule, Vecteur<double>(-7, 6, 1));
    ASSERT_EQ(particule.getPosition(), Vecteur<double>(-4, 12, 9));
}

TEST(UniversTest, testAjouterAuxCellules){
    
    /* Établir la configuration de l'univers */
    Configuration& configuration = Configuration::getInstance();
    configuration.setConditionLimite(ConditionLimite::Periodique);
    configuration.setLd(10, 10, 10);
    configuration.setRCut(2.5);

    Univers univers;

    /* Créer 5 particules aléatoires et les ajouter aux cellules*/
    univers.ajouterParticulesAleatoires(5);
    univers.remplirCellules();

    /* Vérifier le nombre de particules */
    ASSERT_EQ(univers.getNombreParticules(), 5);
}

TEST(UniversTest, testCorrigerCellules){
    
    /* Établir la configuration de l'univers */
    Configuration& configuration = Configuration::getInstance();
    configuration.setConditionLimite(ConditionLimite::Periodique);
    configuration.setLd(10, 10, 10);
    configuration.setRCut(2.5);

    Univers univers;

    /* Créer une particule et l'ajouter */
    Particule particule1(-4, -4, 4);
    univers.ajouterParticule(particule1);
    univers.remplirCellules();

    /* Obtenir un pointeur vers la particule stockée */
    const Cellule& cellule = univers.getCelluleParIndices(0, 0, 3);
    Particule* particuleStockee = *cellule.getParticules().begin();

    /* Deplacer la particule stockee */
    univers.deplacerParticule(particuleStockee, Vecteur<double>(5, -4, 2));
    univers.corrigerCellules();

    /* Vérifier la position de la particule stockée */
    ASSERT_EQ(particuleStockee->getPosition(), Vecteur<double>(6, 7, 1));

    /* Vérifier la nouvelle cellule à laquelle appartient la particule stockée */  
    const Cellule& nouvelleCellule =  univers.getCelluleParIndices(2, 2, 0);
    ASSERT_EQ(*nouvelleCellule.getParticules().begin(), particuleStockee);  
    
}
