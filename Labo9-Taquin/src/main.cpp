/*
-----------------------------------------------------------------------------------
Nom du fichier : main.cpp
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 17.06.2021
Description    : Fichier du programme principal qui permet la résolution d'un taquin.
Remarque(s)    : Le programme prend un input utilisateur de nombres séparés par un
                 espace. Ceux-ci représentent chacun une pièce du taquin. Le
                 programme retourne la séquence de résolution du taquin.
                 de ce dernier.
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>
#include <iostream>
#include <chrono>
#include "graph.h"

using namespace std;

int main() {
	string input;
	char stopInput;
	const char STOP = 'o';
	do {
		cout << "Entrez la position initiale des pieces :";
		getline(cin, input);

		Graph g = Graph(Vertex(input));

		auto t1 = chrono::high_resolution_clock::now();

		g.parentsBFS();
		string chaine = g.searchSmallestChain();

		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> time_ms = t2 - t1;
		cout << "Temps de resolution: " << time_ms.count() << " ms" << endl;

		cout << "\nSequence des pieces a deplacer:" << endl;
		cout << chaine << endl;

		cout << "\nVoulez-vous quitter le programme ? (o/n):";
		cin >> stopInput;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (stopInput != STOP);

	return EXIT_SUCCESS;
}
