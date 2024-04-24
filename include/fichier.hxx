#pragma once

#include <fstream>
#include <iostream>
#include <sys/stat.h>

/**
* @brief Fonction qui ouvre un fichier de sortie situé à une adresse donnée
* @param[in] adresseFichier est l'adresse du fichier.
*/

std::ofstream ouvrirFichierDeSortie(const std::string& adresseFichier);

/**
* @brief Fonction qui ouvre un fichier d'entrée situé à une adresse donnée.
* @param[in] adresseFichier est l'adresse du fichier.
*/

std::ifstream ouvrirFichierDEntree(const std::string& adresseFichier);

/**
* @brief Fonction qui crée un nouveau dossier s'il n'existe pas.
* @param nomDossier est le nom du dossier à créer.
*/

void creerDossier(const std::string& nomDossier);
