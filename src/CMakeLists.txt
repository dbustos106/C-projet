# Créer une bibliothèque à partir d'un ensemble de fichiers de définitions (.cxx) sans main.
# Ces fichiers ne contiennent pas de fonction main

add_library(
    particules SHARED 
    configuration/configuration.cxx
    modele/univers.cxx 
    modele/particule.cxx 
    structures/cellule.cxx 
    simulation/simulation.cxx 
    simulation/performance.cxx
    io/sauvegardage.cxx 
    io/lecture.cxx
    utils/fichier.cxx
    utils/imprimer.cxx 
)
