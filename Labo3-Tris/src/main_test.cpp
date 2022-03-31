/*
-----------------------------------------------------------------------------------
Nom du fichier : main_test.cpp
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 09.04.2021
Description    : Fichier du 1er programme principal qui vérifie que nos
                 fonctions de tri fonctionnent correctement.
                 Fonctions testées: partition, tri_rapide, tri_comptage et
                 tri_par_base.
Remarque(s)    : Le tri par base est testé avec des groupes de 1, 2, 4, 8 et 16 bits.
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include "vectors_utils.h"
#include "tri_rapide.h"
#include "tri_par_base.h"

using namespace std;

/**
 * Teste le bon fonctionnement de la fonction de partition utilisée dans le tri
 * rapide
 */
void testPartition();

/**
 * Teste le bon fonctionnement du tri rapide
 * @param vectors : vecteurs à trier
 */
void testQuickSort(vector<vector<unsigned>> vectors);

/**
 * Teste le bon fonctionnement du tri comptage
 * @param vectors : vecteurs à trier
 */
void testCountingSort(vector<vector<unsigned>> vectors);

/**
 * Teste le bon fonctionnement du tri par base avec des groupes
 * de 1, 2, 4, 8 et 16 bits.
 * @param originalVectors : vecteurs à trier
 */
void testRadixSort(const vector<vector<unsigned>> &originalVectors);

int main() {
	cout << "1er programme principal: verification des differentes fonctions:"
		  << endl;

	const unsigned NB_VECTORS = 10;
	vector<vector<unsigned>> vectors = generateVectors(NB_VECTORS);

	testPartition();
	testQuickSort(vectors);
	testCountingSort(vectors);
	testRadixSort(vectors);

	return EXIT_SUCCESS;
}

void testPartition() {
	cout << "Partitions: -> ";
	// Tuple: Valeur initiale / Résultat attendu / Position du pivot attendue
	vector<tuple<vector<char>, vector<char>, unsigned>> data = {
		{
			{'E', 'X', 'E', 'M', 'P', 'L', 'E', 'D', 'E', 'T', 'R', 'I'},
			{'E', 'E', 'E', 'D', 'E', 'I', 'P', 'M', 'X', 'T', 'R', 'L'},
			5
		},
		{
			{'E', 'E', 'E', 'D', 'E'},
			{'D', 'E', 'E', 'E', 'E'},
			2
		},
		{
			{'P', 'M', 'X', 'T', 'R', 'L'},
			{'L', 'M', 'X', 'T', 'R', 'P'},
			0
		},
		{
			{'J', 'H', 'L', 'I', 'D', 'A', 'F', 'E', 'C', 'G', 'B', 'K'},
			{'J', 'H', 'B', 'I', 'D', 'A', 'F', 'E', 'C', 'G', 'K', 'L'},
			10
		},
		{
			{'U', 'N', 'B', 'O', 'N', 'E', 'X', 'E', 'M', 'P', 'L', 'E'},
			{'E', 'E', 'B', 'E', 'N', 'N', 'X', 'U', 'M', 'P', 'L', 'O'},
			3
		},
	};

	for (auto &row : data) {
		vector<char> v = get<0>(row);
		vector<char> expectedVector = get<1>(row);
		unsigned expectedPivot = get<2>(row);
		auto pivotPosition = partition(v.begin(), v.end());

		if (!equal(v.begin(), v.end(), expectedVector.begin()) ||
			 distance(v.begin(), pivotPosition) != expectedPivot) {
			cout << "KO - ERREUR!" << endl;
			return;
		}
	}
	cout << "OK" << endl;
}

void testQuickSort(vector<vector<unsigned>> vectors) {
	cout << "Tri rapide: -> ";

	for (auto &v : vectors) {
		tri_rapide(v.begin(), v.end());

		if (!is_sorted(v.begin(), v.end())) {
			cout << "KO - ERREUR!" << endl;
			return;
		}
	}
	cout << "OK" << endl;
}

void testCountingSort(vector<vector<unsigned>> vectors) {
	cout << "Tri comptage: -> ";
	vector<vector<unsigned>> results(vectors.size());

	for (unsigned i = 0; i < vectors.size(); ++i) {
		results[i].reserve(vectors[i].size());

		tri_comptage(vectors[i].begin(), vectors[i].end(), results[i].begin(),
						 [](unsigned val) {
							 return val;
						 }, *max_element(vectors[i].begin(), vectors[i].end()) + 1);

		if (!is_sorted(results[i].begin(), results[i].end())) {
			cout << "KO - ERREUR!" << endl;
			return;
		}
	}
	cout << "OK" << endl;
}

void testRadixSort(const vector<vector<unsigned>> &originalVectors) {
	vector<vector<unsigned>> vectors = originalVectors;
	const size_t BIT_GROUPS[] = {1, 2, 4, 8, 16};

	for (size_t nbBits : BIT_GROUPS) {
		vectors = originalVectors;

		cout << "Tri par base (" << nbBits << " bit"
			  << (nbBits > 1 ? "s" : "") << "): -> ";
		string name = "radix " + to_string(nbBits);

		for (vector<unsigned> &v : vectors) {
			radixFunctions<unsigned>[name](v.begin(), v.end());

			if (!is_sorted(v.begin(), v.end())) {
				cout << "KO - ERREUR!" << endl;
				return;
			}
		}
		cout << "OK" << endl;
	}
}
