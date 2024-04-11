# Créer une bibliothèque à partir d'un ensemble de fichiers de définitions (.cxx) sans main.
# Ces fichiers ne contiennent pas de fonction main

add_library(
    particules SHARED 
    modele/univers.cxx 
    modele/particule.cxx 
    structures/vecteur.cxx 
    structures/cellule.cxx 
    simulation/simulation.cxx 
    io/sauvegardage.cxx 
    io/lecture.cxx
    utils/imprimer.cxx 
    utils/performance.cxx
)
