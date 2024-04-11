#pragma once

#include <set>
#include <list>
#include <deque>
#include <vector>

/**
* @brief Modèle pour déterminer le type de conteneur STL.
* @tparam Collection est le type de conteneur STL.
*/

template <typename Collection>
struct TypeCollection { 
    static constexpr const char* typeName = "Unknown";
};

/**
* @brief Spécialisation du modèle TypeCollection pour std::set.
* @tparam T est le type des éléments stockés dans l'ensemble.
* @tparam Compare est la fonction de comparaison pour ordonner les éléments.
* @tparam Alloc est le type d'allocation utilisé pour allouer et désallouer la mémoire.
*/

template <typename T, typename Compare, typename Alloc>
struct TypeCollection<std::set<T, Compare, Alloc>> {
    static constexpr const char* name = "std::set";
};

/**
* @brief Spécialisation du modèle TypeCollection pour std::list.
* @tparam T est le type des éléments stockés dans la liste.
* @tparam Alloc est le type d'allocation utilisé pour allouer et désallouer la mémoire.
*/

template <typename T, typename Alloc>
struct TypeCollection<std::list<T, Alloc>> {
    static constexpr const char* name = "std::list";
};

/**
* @brief Spécialisation du modèle TypeCollection pour std::deque.
* @tparam T est le type des éléments stockés dans la file double.
* @tparam Alloc est le type d'allocation utilisé pour allouer et désallouer la mémoire.
*/

template <typename T, typename Alloc>
struct TypeCollection<std::deque<T, Alloc>> {
    static constexpr const char* name = "std::deque";
};

/**
* @brief Spécialisation du modèle TypeCollection pour std::vector.
* @tparam T est le type des éléments stockés dans le vecteur.
* @tparam Alloc est le type d'allocation utilisé pour allouer et désallouer la mémoire.
*/

template <typename T, typename Alloc>
struct TypeCollection<std::vector<T, Alloc>> {
    static constexpr const char* name = "std::vector";
};
