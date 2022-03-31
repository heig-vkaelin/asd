/*
-----------------------------------------------------------------------------------
Nom du fichier : complexity.h
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 02.03.2021
Description    : Fichier principal du laboratoire visant à tester la complexité de
                 divers algorithmes de tris. Ce fichier contient les fonctions et
                 les structures de données nécessaires pour le bon fonctionnement
                 des 3 programmes principaux.
Remarque(s)    : Les fonctions ont été implémentées dans un fichier header car
                 elles sont quasiment toutes génériques.
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#ifndef ASD_L1_COMPLEXITE_COMPLEXITY_H
#define ASD_L1_COMPLEXITE_COMPLEXITY_H

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "sort_functions.h"
#include "op_counter.h"

enum class Parameters {
	ASCENDING, DESCENDING, RANDOM, ALMOST_SORTED
};

/**
 * Map utilisée pour boucler sur les différentes fonctions de tri dans nos
 * programmes principaux.
 * @tparam T : type des éléments à trier
 */
template<typename T>
const std::map<std::string, SortFuncIter<T>> SORT_FUNCTIONS = {
	{"bubble",           bubbleSort},
	{"insert",           insertSort},
	{"selection",        selectionSort},
	{"std::sort",        std::sort},
	{"std::stable_sort", std::stable_sort}
};

/**
 * Fonction retournant une map contenant les noms de fichiers pour chaque
 * paramètre de vecteur.
 * Implémentation via une fonction pour ne pas avoir de warning avec une variable
 * globale car elle dépend de l'instanciation de l'enum class Parameters
 * @return la map <Parameters, nom_fichier>
 */
std::map<Parameters, std::string> parameterNameFiles() {
	const static std::map<Parameters, std::string> params{
		{Parameters::ASCENDING,     "ascending"},
		{Parameters::DESCENDING,    "descending"},
		{Parameters::RANDOM,        "random"},
		{Parameters::ALMOST_SORTED, "almostSorted"},
	};
	return params;
}

/**
 * Génère un vecteur selon les paramètres fournis
 * @tparam T : type des éléments du vecteur
 * @param size : taille du vecteur
 * @param seed : seed pour régénérer le même vecteur
 * @param param : type de vecteur souhaité
 * @return le vecteur généré
 */
template<typename T>
std::vector<T> generateVector(size_t size, unsigned seed, Parameters param) {
	std::vector<T> v(size);
	if (size < 1) {
		return v;
	}

	iota(v.begin(), v.end(), 1);

	switch (param) {
		case Parameters::DESCENDING: {
			std::reverse(v.begin(), v.end());
			break;
		}
		case Parameters::RANDOM: {
			std::default_random_engine generator(seed);
			std::shuffle(v.begin(), v.end(), generator);
			break;
		}
		case Parameters::ALMOST_SORTED: {
			// Génère les valeurs aléatoires à insérer dans le tableau.
			std::default_random_engine generator(seed);
			std::uniform_int_distribution<int> distribution(1, (int) size);

			// Détermine s'il faut insérer un nombre trié ou aléatoire.
			// Dans notre cas, le vecteur sera trié aux alentours de 70%
			const int RATIO = 7;
			std::uniform_int_distribution<int> roll(1, 10);

			for (size_t i = 0; i < size; ++i) {
				if (roll(generator) > RATIO) {
					v[i] = (T) distribution(generator);
				}
			}
			break;
		}
		default:
			break;
	}
	return v;
}

/**
 * Mesure le temps d'exécution de la fonction passée en paramètre en lui passant
 * en paramètre le vecteur.
 * @tparam Fn : type de la fonction à tester
 * @tparam T : type des éléments du vecteur
 * @param f : fonction à tester
 * @param v : vecteur sur lequel appliquer la fonction
 * @return le temps d'exécution en ms
 */
template<typename Fn, typename T>
double measureTime(Fn f, std::vector<T> v) {
	auto t1 = std::chrono::high_resolution_clock::now();
	f(v.begin(), v.end());
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> time_ms = t2 - t1;

	return time_ms.count();
}

/**
 * Vérifie que la fonction passée en paramètre trie bien quelques vecteurs.
 * @tparam Fn : type de la fonction à tester
 * @param f : fonction à tester
 * @return true si la fonction trie bien, false autrement
 */
template<typename Fn>
bool sortCorrectly(Fn f) {
	std::vector<std::vector<int>> vectorsToTest = {
		{4, 2, 7, 1, 2,   5,   6,    2},
		{1, 2, 7, 5, 232, 5,   9313, 232},
		{4, 2, 9, 1, 2,   222, 6,    422},
		{1, 2, 3, 4},
		{4, 3, 2, 1, 0},
		{1, 1, 1, 0, 0},
	};

	for (auto v : vectorsToTest) {
		f(v.begin(), v.end());
		if (!is_sorted(v.begin(), v.end())) {
			return false;
		}
	}
	return true;
}

/**
 * Exporte une matrice de données dans un fichier .csv
 * @param filename : emplacement et nom du fichier à créer
 * @param nValues : valeurs de l'entête du fichier .csv
 * @param measures : valeurs à utiliser dans le fichier .csv
 */
void exportCSV(const std::string &filename,
					const std::vector<size_t> &nValues,
					const std::map<std::string, std::vector<double>> &measures) {
	std::ofstream out(filename);

	if (not out.is_open()) {
		std::cerr << "Ouverture du fichier en ecriture impossible" << std::endl;
		return;
	}

	// Précision spécifiée afin d'éviter la notation scientifique
	out << std::setprecision(10) << "n";
	for (size_t n : nValues) out << "," << n;
	out << std::endl;

	for (const auto &pair : measures) {
		out << pair.first;
		for (double d : pair.second)
			out << "," << d;
		out << std::endl;
	}
}

#endif // ASD_L1_COMPLEXITE_COMPLEXITY_H
