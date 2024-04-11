#pragma once

#include <string>
#include <fstream>
#include <sys/stat.h>
#include "univers.hxx"

/**
* @brief Fonction qui crée un nouveau répertoire s'il n'existe pas.
* @param nomDossier est le nom du répertoire à créer.
*/

void creerDossier(std::string& nomDossier);

/**
* @brief Fonction qui ouvre un fichier à une adresse donnée.
* @param[in] AdresseFichier est l'adresse du fichier.
*/

std::ofstream ouvrirFichier(std::string&& adresseFichier);

/**
* @brief Fonction qui sauvegarde l'état de l'univers dans un fichier texte.
* @param[in] fichierTexte est le descripteur du fichier de sortie.
* @param[in] univers est l'univers à sauvegarder.
* @param[in] i est le numéro de l'itération.
*/

void sauvegarderEtatEnTexte(std::ofstream& fichierTexte, Univers& univers, int i);

/**
* @brief Fonction qui sauvegarde l’état de l’univers dans un fichier VTU.
* @param[in] nomDossier est le nom du dossier où les fichiers seront sauvegardés.
* @param[in] univers est l'univers à sauvegarder.
* @param[in] i est le numéro de l'itération.
*/

void sauvegarderEtatEnVTU(std::string& nomDossier, Univers& univers, int i);
