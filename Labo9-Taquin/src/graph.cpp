/*
-----------------------------------------------------------------------------------
Nom du fichier : graph.cpp
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 17.06.2021
Description    : Implémentation de la classe Graph.
Remarque(s)    : -
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <queue>
#include <algorithm>
#include "graph.h"

using namespace std;

Graph::Graph(const Vertex& s) : initialVertex(s), finalVertex(s) {
	sort(finalVertex.positions.begin(), finalVertex.positions.end());
}

void Graph::parentsBFS() {
	queue<Vertex> q;
	Vertex v;
	q.push(initialVertex);
	parents[initialVertex] = initialVertex;

	while (!q.empty()) {
		v = q.front();
		q.pop();

		for (const Vertex& w : v.getNeighbors()) {
			if (parents.find(w) == parents.end()) {
				q.push(w);
				parents[w] = v;
			}
			// Arrêter le parcours si la solution est trouvée
			if (w == finalVertex) {
				return;
			}
		}
	}
}

string Graph::searchSmallestChain() const {
	string chaine;
	Vertex w = finalVertex;
	if (parents.find(w) != parents.end()) {
		while (!(parents.find(w)->second == w)) {
			chaine.insert(0, to_string(w.indexEmptyCase()) + " ");
			w = parents.find(w)->second;
		}
	} else {
		chaine = "Aucune solution disponible.";
	}
	return chaine;
}
