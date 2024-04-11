#pragma once

#include <iostream>
#include "cellule.hxx"

/**
* @brief Fonction pour imprimer sur la console l'univers de particules.
* @param[in] particules est le vecteur de particules.
*/

void imprimerParticulesSurConsole(std::vector<Particule>& particules);

/**
* @brief Fonction pour imprimer sur la console les cellules
*        qui composent l'univers avec leurs voisins.
* @param[in] grille est la grille à imprimer.
*/

void imprimerGrilleSurConsole(std::vector<Cellule>& grille);
