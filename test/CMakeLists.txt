# Pour chaque test (famille de test), un exécutable est cré
add_executable(test_vecteur test_vecteur.cxx)
add_executable(test_cellule test_cellule.cxx)
add_executable(test_univers test_univers.cxx)

## Ne pas oublier d'ajouter la bibliothèque du projet (xxxx)
target_link_libraries(test_vecteur gtest_main particules)
target_link_libraries(test_cellule gtest_main particules)
target_link_libraries(test_univers gtest_main particules)

include(GoogleTest)
gtest_discover_tests(test_vecteur)
gtest_discover_tests(test_cellule)
gtest_discover_tests(test_univers)
