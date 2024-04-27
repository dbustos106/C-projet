#pragma once

#include <chrono>
#include <iostream>
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
void mesurerPerformanceInsertion(Collection& particules, int size);

/**
* @brief Fonction permettant de mesurer les performances
*        de comptage dans une collection de particules.
* @param[in] particules est la collection de particules.
*/

template <typename Collection>
void mesurerPerformanceComptage(Collection& particules);

/**
* @brief Fonction permettant de mesurer les performances
*        de suppression dans une collection de particules.
* @param[in] particules est la collection de particules.
*/

template <typename Collection>
void mesurerPerformanceSuppression(Collection& particules);

#include "performance.txx"