/*
-----------------------------------------------------------------------------------
Nom du fichier : tri_rapide.h
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 09.04.2021
Description    : Implémentation du tri rapide avec choix de pivot aléatoire.
Remarque(s)    : Nous utilisons l'approche "semi-récursive" vue en cours.
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#ifndef TRI_RAPIDE
#define TRI_RAPIDE

#include <random>
#include <algorithm>

/**
 * Partitionne le conteneur entré en paramètres via les itérateurs en plaçant à
 * gauche du pivot les éléments plus petits ou égaux et à droite les éléments plus
 * grands.
 * La fonction suppose que le pivot a été placé en dernière position avant son appel.
 * @tparam Iterator : type de l'itérateur des éléments du conteneur
 * @param first : itérateur sur le 1er élément du conteneur
 * @param last : itérateur après le dernier élément du conteneur
 * @return la position du pivot après partition
 */
template<typename Iterator>
Iterator partition(Iterator first, Iterator last) {
	Iterator i = first - 1;
	Iterator j = last - 1;
	Iterator pivot = j;

	while (true) {
		do {
			i++;
		} while (*i < *pivot);

		do {
			j--;
		} while (first < j && *pivot < *j);

		// Condition non simplifiée afin de n'utiliser que l'opérateur "<"
		if (!(i < j)) {
			break;
		}

		std::iter_swap(i, j);
	}

	std::iter_swap(i, pivot);

	return i;
}

/**
 * Implémentation du tri rapide en utilisant la fonction de partition définie
 * précédemment.
 * Le choix du pivot est fait de façon aléatoire.
 * @tparam Iterator : type de l'itérateur des éléments du conteneur
 * @param first : itérateur sur le 1er élément du conteneur
 * @param last : itérateur après le dernier élément du conteneur
 */
template<typename Iterator>
void tri_rapide(Iterator first, Iterator last) {
	while (first < last - 1) {
		// Nous avons utilisé un seed afin de pouvoir debug plus facilement nos
		// résultats en ayant des positions de pivot similaires entre chaque
		// compilation.
		std::mt19937_64 generator(1234);

		long long size = distance(first, last);
		std::uniform_int_distribution<long long> distribution(0, size - 1);
		auto offset = distribution(generator);

		// Choisit un pivot au hasard et le place en dernière position.
		Iterator randomPickedPivot = first + offset;
		std::iter_swap(last - 1, randomPickedPivot);

		auto pivot = partition(first, last);

		if (pivot - first < (last - 1) - pivot) {
			tri_rapide(first, pivot);
			first = pivot + 1;
		} else {
			tri_rapide(pivot + 1, last);
			last = pivot;
		}
	}
}

#endif
