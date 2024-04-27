#pragma once

#include <string>
#include "univers.hxx"
#include "fichier.hxx"

/**
* @brief 
* Fonction qui sauvegarde l'état de l'univers dans un fichier texte.
* @param[in] fichierTexte est le descripteur du fichier de sortie.
* @param[in] univers est l'univers à sauvegarder.
* @param[in] i est le numéro de l'itération.
*/

void sauvegarderEtatEnTexte(std::ofstream& fichierTexte, const Univers& univers, int i);

/**
* @brief 
* Fonction qui sauvegarde l’état de l’univers dans un fichier VTU.
* @param[in] nomDossier est le nom du dossier où les fichiers seront sauvegardés.
* @param[in] univers est l'univers à sauvegarder.
* @param[in] i est le numéro de l'itération.
*/

void sauvegarderEtatEnVTU(const std::string& nomDossier, const Univers& univers, int i);
