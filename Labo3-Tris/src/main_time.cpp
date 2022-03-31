/*
-----------------------------------------------------------------------------------
Nom du fichier : main_time.cpp
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 09.04.2021
Description    : Fichier du 2ème programme principal qui mesure le temps de
                 calcul que prennent les différentes fonctions pour trier des
                 vector<unsigned>.
                 Les vectors testés sont complètement aléatoires et de longueurs
                 variables allant de 10 à 1'000'000 éléments.
Remarque(s)    : Les résultats sont sauvegardés dans un fichier csv dans le
                 dossier rapport/csv.
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>
#include <string>
#include <vector>
#include <chrono>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "vectors_utils.h"
#include "tri_rapide.h"
#include "tri_par_base.h"

using namespace std;

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
double measureTime(Fn f, vector<T> v);

/**
 * Exporte une matrice de données dans un fichier .csv
 * @param filename : emplacement et nom du fichier à créer
 * @param nValues : valeurs de l'entête du fichier .csv
 * @param measures : valeurs à utiliser dans le fichier .csv
 */
void exportCSV(const string &filename,
					const vector<size_t> &nValues,
					const map<string, vector<double>> &measures);

/**
 * Mesure le temps d'exécution du tri rapide pour un jeu de données entré en
 * paramètres
 * @param vectors : vecteurs à trier
 * @param measures : map dans laquelle introduire les mesures de temps
 */
void measureQuickSort(const vector<vector<unsigned>> &vectors,
							 map<string, vector<double>> &measures);

/**
 * Mesure le temps d'exécution du tri par base pour un jeu de données entré en
 * paramètres. Les bases testés sont les suivantes: 1, 2, 4, 8 et 16
 * @param originalVectors : vecteurs à trier
 * @param measures : map dans laquelle introduire les mesures de temps
 */
void measureRadixSort(const vector<vector<unsigned>> &originalVectors,
							 map<string, vector<double>> &measures);

int main() {
	const vector<size_t> N_VALUES = {10, 100, 1000, 10000, 100000, 1000000};
	const unsigned TIME_SEED = 420;

	vector<vector<unsigned>> vectors;
	vectors.reserve(N_VALUES.size());
	map<string, vector<double>> measures;

	cout << "2e programme principal: temps de tri" << endl;

	for (size_t n : N_VALUES) {
		vectors.push_back(generateRandomizedVector<unsigned>(n, TIME_SEED));
	}

	measureQuickSort(vectors, measures);
	measureRadixSort(vectors, measures);

	exportCSV("../../rapport/csv/measures.csv", N_VALUES, measures);
	cout << endl << "Le fichier measures.csv a bien ete cree." << endl;
	cout << "Mesures des temps terminees." << endl;

	return EXIT_SUCCESS;
}

template<typename Fn, typename T>
double measureTime(Fn f, vector<T> v) {
	auto t1 = chrono::high_resolution_clock::now();
	f(v.begin(), v.end());
	auto t2 = chrono::high_resolution_clock::now();
	chrono::duration<double, milli> time_ms = t2 - t1;

	return time_ms.count();
}

void exportCSV(const string &filename,
					const vector<size_t> &nValues,
					const map<string, vector<double>> &measures) {
	ofstream out(filename);

	if (not out.is_open()) {
		cerr << "Ouverture du fichier en ecriture impossible" << endl;
		return;
	}

	// Précision spécifiée afin d'éviter la notation scientifique
	out << setprecision(10) << "n";
	for (size_t n : nValues) out << "," << n;
	out << endl;

	for (const auto &pair : measures) {
		out << pair.first;
		for (double d : pair.second)
			out << "," << d;
		out << endl;
	}
}

void measureQuickSort(const vector<vector<unsigned>> &vectors,
							 map<string, vector<double>> &measures) {
	cout << "Algorithme en cours: tri rapide" << endl;

	measures["quick"] = vector<double>();
	measures["quick"].reserve(vectors.size());

	for (const vector<unsigned> &v : vectors) {
		measures["quick"].push_back(measureTime(
			[](auto l, auto r) { tri_rapide(l, r); },
			v)
		);
	}
}

void measureRadixSort(const vector<vector<unsigned>> &originalVectors,
							 map<string, vector<double>> &measures) {
	cout << "Algorithme en cours: tri par base" << endl;

	vector<vector<unsigned>> vectors = originalVectors;
	const size_t BIT_GROUPS[] = {1, 2, 4, 8, 16};

	for (size_t nbBits : BIT_GROUPS) {
		vectors = originalVectors;
		string name = "radix " + to_string(nbBits);
		for (vector<unsigned> &v : vectors) {
			measures[name].push_back(measureTime(radixFunctions<unsigned>[name], v));
		}
	}
}
