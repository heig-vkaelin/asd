/*
-----------------------------------------------------------------------------------
Nom du fichier : main_test.cpp
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 02.03.2021
Description    : Fichier du 1er programme principal qui vérifie que nos 3
                 fonctions de tri "maison" fonctionnent correctement.
                 Fonctions testées: bubble sort, insert sort et selection sort.
Remarque(s)    : -
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>
#include <iostream>
#include "complexity.h"

using namespace std;

int main() {
	cout << boolalpha
		  << "1er programme principal: verification des fonctions de tri: " << endl;
	// Boucle seulement sur les 3 premières fonctions de tri de la map: nos fonctions
	// maisons sans inclure celles de la libraire standard
	for (auto it = SORT_FUNCTIONS<int>.begin();
		  it != next(SORT_FUNCTIONS<int>.begin(), 3); ++it) {
		bool sorted = sortCorrectly((*it).second);
		cout << (*it).first << " -> "
			  << (sorted ? "OK, resultat trie" : "KO, erreur lors du tri du vecteur")
			  << endl;
	}

	return EXIT_SUCCESS;
}
