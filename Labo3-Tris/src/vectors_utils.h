/*
-----------------------------------------------------------------------------------
Nom du fichier : utils.h
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 09.04.2021
Description    : Fichier contenant diverses fonctions utilitaires pour la
                 génération de vecteurs.
Remarque(s)    : -
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#ifndef ASD_LABOS_2021_VECTORS_UTILS_H
#define ASD_LABOS_2021_VECTORS_UTILS_H

#include <cstdlib>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

/**
 * Génère un vecteur du type souhaité rempli de valeurs aléatoires.
 * Les valeurs du vecteur sont toutes uniques.
 * @tparam T : type des éléments du vecteur à générer
 * @param size : taille du vecteur à générer
 * @param seed : clé unique pour générer à nouveau le même vecteur
 * @return le vecteur généré
 */
template<typename T>
std::vector<T> generateRandomizedVector(size_t size, unsigned seed) {
	std::vector<T> v(size);
	if (size < 1) {
		return v;
	}

	iota(v.begin(), v.end(), 1);

	std::mt19937_64 generator(seed);
	std::shuffle(v.begin(), v.end(), generator);

	return v;
}

/**
 * Génère le nombre de vecteurs aléatoires souhaité.
 * @param n : nombre de vecteurs à générer
 * @param factor : facteur de multiplication de la taille entre chaque vecteur
 * @return une matrice contenant tous les vecteurs générés
 */
std::vector<std::vector<unsigned>> generateVectors(size_t n, size_t factor = 10) {
	std::vector<std::vector<unsigned>> vectors;
	vectors.reserve(n);
	for (unsigned i = 1; i <= n; ++i) {
		vectors.push_back(generateRandomizedVector<unsigned>(factor * i, i));
	}
	return vectors;
}

#endif
