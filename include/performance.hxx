#pragma once

#include <iostream>
#include <chrono>

#include "configuration.hxx"
#include "collections.hxx"
#include "univers.hxx"

/**
* @brief Fonction permettant de mesurer une série 
*        de performances sur les collections de particules.
*/

void mesurerPerformance();

/**
* @brief Fonction permettant de mesurer les performances de 
*        création d'un univers avec un nombre de particules aléatoires
* @param[in] nombreParticules est le nombre de particules aléatoires à créer.
*/

void mesurerPerformanceInsertionUnivers(int nombreParticules);

/**
* @brief Fonction permettant de mesurer les performances 
*        d'insertion dans une collection de particules
* @param[in] particules est la collection de particules.
* @param[in] size est le nombre de particules à créer.
*/

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

/**
* @brief Fonction permettant de mesurer les performances
*        de comptage dans une collection de particules.
* @param[in] particules est la collection de particules.
*/

template <typename Collection>
void mesurerPerformanceComptage(Collection& particules){
    auto start = std::chrono::steady_clock::now();

    int size = particules.size();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Comptage de " << size << " particules dans la collection " 
                    << TypeCollection<Collection>::name << " : " << elapsed_seconds.count() << " secondes\n";

}

/**
* @brief Fonction permettant de mesurer les performances
*        de suppression dans une collection de particules.
* @param[in] particules est la collection de particules.
*/

template <typename Collection>
void mesurerPerformanceSuppression(Collection& particules){
    auto start = std::chrono::steady_clock::now();

    particules.clear();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Suppression de la collection " << TypeCollection<Collection>::name
                         << " : " << elapsed_seconds.count() << " secondes\n";

}
