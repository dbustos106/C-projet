#pragma once

#include <sstream>
#include <fstream>
#include "univers.hxx"

/**
* @brief La fonction qui crée et charge des particules dans
*        l'univers à partir des informations lues dans un fichier VTU.
* @param[in] adresseFichier est l'adresse du fichier d'entrée.
* @param[in] univers est l'univers.
*/

void lectureDuFichier(const std::string& adresseFichier, Univers& univers);
