#include "performance.hxx"

void mesurerPerformance(){

    std::set<Particule> particuleSet;
    std::list<Particule> particuleList;
    std::deque<Particule> particuleDeque;
    std::vector<Particule> particuleVector;

    for(int size = 64; size <= 65536; size*=2){
        std::cout << "Taille de la collection : " << size << " particules\n\n";

        // Mesure le performance pour la insertion 
        mesurerPerformanceInsertion(particuleSet, size);
        mesurerPerformanceInsertion(particuleList, size);
        mesurerPerformanceInsertion(particuleDeque, size);
        mesurerPerformanceInsertion(particuleVector, size);

        // Mesure le performance pour le comptage 
        mesurerPerformanceComptage(particuleSet);
        mesurerPerformanceComptage(particuleList);
        mesurerPerformanceComptage(particuleDeque);
        mesurerPerformanceComptage(particuleVector);

        // Mesure le performance pour la suppression 
        mesurerPerformanceSuppression(particuleSet);
        mesurerPerformanceSuppression(particuleList);
        mesurerPerformanceSuppression(particuleDeque);
        mesurerPerformanceSuppression(particuleVector);

        std::cout << "\n";
    }

    for(int k = 3; k < 7; k++){
        mesurerPerformanceInsertionUnivers(pow(pow(2, k), 3));
    }
}

void mesurerPerformanceInsertionUnivers(int nombreParticules){
    auto start = std::chrono::steady_clock::now();

    Configuration& configuration = Configuration::getInstance();
    configuration.setLd(200, 130, 0);

    Univers univers;
    univers.ajouterParticulesAleatoires(nombreParticules);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Creation d'un univers de " << nombreParticules 
              << " particules : " << elapsed_seconds.count() << " secondes\n";
}
