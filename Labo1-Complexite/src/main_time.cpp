/*
-----------------------------------------------------------------------------------
Nom du fichier : main_time.cpp
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 02.03.2021
Description    : Fichier du 2ème programme principal qui mesure le temps de
                 calcul que prennent les différentes fonctions pour trier des
                 vector<int>.
                 Les vectors testés sont de 4 types différents (trié croissant,
                 décroissant, aléatoire et presque trié croissant).
Remarque(s)    : Les résultats sont sauvegardés dans des fichiers csv dans le
                 dossier rapport/csv.
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>
#include <vector>
#include <map>
#include <iostream>
#include "complexity.h"

using namespace std;

int main() {
	const vector<size_t> N_VALUES = {10, 100, 1000, 10000, 25000};
	const unsigned SEED = 420;

	vector<vector<int>> vectors;
	vectors.reserve(N_VALUES.size());
	map<string, vector<double>> measures;

	cout << "2e programme principal: temps de tri" << endl;

	for (const auto &parameter : parameterNameFiles()) {
		// Regénère les vecteurs à trier
		vectors.clear();
		vectors.reserve(N_VALUES.size());
		for (size_t n : N_VALUES) {
			vectors.push_back(generateVector<int>(n, SEED, parameter.first));
		}
		// Mesure du temps d'exécution des fonctions de tri pour divers valeurs
		for (const auto &pair : SORT_FUNCTIONS<int>) {
			measures[pair.first] = vector<double>();
			measures[pair.first].reserve(N_VALUES.size());
			for (size_t i = 0; i < N_VALUES.size(); ++i) {
				measures[pair.first].push_back(measureTime(pair.second, vectors.at(i)));
			}
		}
		exportCSV("../../rapport/csv/time/" + parameter.second + ".csv",
					 N_VALUES, measures);
		cout << "Le fichier " << parameter.second << ".csv a bien ete cree." << endl;
	}

	cout << "Creation des " << parameterNameFiles().size()
		  << " fichiers CSV terminee." << endl;
	return EXIT_SUCCESS;
}
