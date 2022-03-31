/*
-----------------------------------------------------------------------------------
Nom du fichier : main_operations.cpp
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 02.03.2021
Description    : Fichier du 3ème programme principal qui compte le nombre de
                 comparaisons et le nombre d'affectations des différents algorithmes
                 de tri.
Remarque(s)    : Les résultats sont sauvegardés dans des fichiers csv dans le
                 dossier rapport/csv.
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>
#include <vector>
#include <map>
#include <iostream>
#include "op_counter.h"
#include "complexity.h"

using namespace std;

int main() {
	const vector<size_t> N_VALUES = {10, 100, 1000, 10000};
	const unsigned SEED = 420;

	vector<vector<OpCounter>> vectors;
	vectors.reserve(N_VALUES.size());
	map<string, vector<double>> assignmentMeasures;
	map<string, vector<double>> comparisonMeasures;

	cout << "3e programme principal: nombre d'operations" << endl;

	for (const auto &parameter : parameterNameFiles()) {
		// Régénérer les vecteurs à trier
		vectors.clear();
		vectors.reserve(N_VALUES.size());
		for (size_t n : N_VALUES) {
			vectors.push_back(generateVector<OpCounter>(n, SEED, parameter.first));
		}
		// Somme du nombre d'opérations des fonctions de tri pour divers valeurs
		for (const auto &pair : SORT_FUNCTIONS<OpCounter>) {
			assignmentMeasures[pair.first] = vector<double>();
			assignmentMeasures[pair.first].reserve(N_VALUES.size());
			comparisonMeasures[pair.first] = vector<double>();
			comparisonMeasures[pair.first].reserve(N_VALUES.size());
			for (size_t i = 0; i < N_VALUES.size(); ++i) {
				OpCounter::resetCounters();
				pair.second(vectors.at(i).begin(), vectors.at(i).end());
				assignmentMeasures[pair.first].push_back(
					OpCounter::getAssignmentCount());
				comparisonMeasures[pair.first].push_back(
					OpCounter::getComparisonCount());
			}
		}
		exportCSV("../../rapport/csv/assignment/" + parameter.second + ".csv",
					 N_VALUES, assignmentMeasures);
		exportCSV("../../rapport/csv/comparison/" + parameter.second + ".csv",
					 N_VALUES, comparisonMeasures);
		cout << "Les 2 fichiers " << parameter.second << ".csv ont bien ete crees."
			  << endl;
	}

	cout << "Creation des " << parameterNameFiles().size() * 2
		  << " fichiers CSV terminee." << endl;
}
