template <typename Collection>
void mesurerPerformanceInsertion(Collection& particules, int size){
    auto start = std::chrono::steady_clock::now();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-1, 1);

    for(int i = 0; i < size; i++){
        Particule particule(dist(mt), dist(mt), dist(mt));
        particules.insert(particules.end(), particule);
    }
    
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Insertion de " << size << " particules dans une collection " 
              << TypeCollection<Collection>::name << " : " << elapsed_seconds.count() << " secondes\n";

}

template <typename Collection>
void mesurerPerformanceComptage(Collection& particules){
    auto start = std::chrono::steady_clock::now();

    int size = particules.size();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Comptage de " << size << " particules dans la collection " 
              << TypeCollection<Collection>::name << " : " << elapsed_seconds.count() << " secondes\n";

}

template <typename Collection>
void mesurerPerformanceSuppression(Collection& particules){
    auto start = std::chrono::steady_clock::now();

    particules.clear();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Suppression de la collection " << TypeCollection<Collection>::name
              << " : " << elapsed_seconds.count() << " secondes\n";

}
