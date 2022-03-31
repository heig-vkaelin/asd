/*
-----------------------------------------------------------------------------------
Nom du fichier : graph.h
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 17.06.2021
Description    : Déclaration de la classe Graph.
Remarque(s)    : -
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#ifndef ASD_LABO9_GRAPH_H
#define ASD_LABO9_GRAPH_H

#include <unordered_map>
#include "vertex.h"

class Graph {
public:
	explicit Graph(const Vertex& s);

	/*
	 * Parcours le graphe en largeur en marquant le sommet parent du sommet actuel.
	 */
	void parentsBFS();

	/*
	 * Retourne la chaîne la plus courte pour atteindre le finalVertex qui
	 * représente l'état du taquin résolu.
	 */
	std::string searchSmallestChain() const;

private:
	Vertex initialVertex;
	Vertex finalVertex;
	std::unordered_map<Vertex, Vertex, Vertex> parents;
};

#endif // ASD_LABO9_GRAPH_H
