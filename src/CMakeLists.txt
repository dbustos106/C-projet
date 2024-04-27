# Créer une bibliothèque à partir d'un ensemble de fichiers de définitions (.cxx) sans main.
# Ces fichiers ne contiennent pas de fonction main

add_library(
    projet SHARED 
    configuration/configuration.cxx
    modele/univers.cxx 
    modele/particule.cxx 
    structures/cellule.cxx 
    modes_execution/simulation.cxx 
    modes_execution/performance.cxx
    entree_sortie/sauvegardage.cxx 
    entree_sortie/lecture.cxx
    utils/fichier.cxx
    utils/imprimer.cxx 
)
