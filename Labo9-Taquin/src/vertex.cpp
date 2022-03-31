/*
-----------------------------------------------------------------------------------
Nom du fichier : vertex.cpp
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 17.06.2021
Description    : Implémentation de la class Vertex.
Remarque(s)    : -
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <sstream>
#include <cmath>
#include <algorithm>
#include "vertex.h"

using namespace std;

const int EMPTY_CASE = 0;

bool operator==(const Vertex& lhs, const Vertex& rhs) {
	return lhs.positions == rhs.positions;
}

Vertex::Vertex(std::vector<uint32_t> v) : positions(std::move(v)) {}

Vertex::Vertex(const std::string& s) {
	istringstream stream(s);
	positions.reserve((s.size() + 1) / 2);
	uint32_t val;
	while (stream >> val) {
		positions.push_back(val);
	}
	// Vérification de la séquence
	auto size = (size_t) sqrt(positions.size());
	if (!size || size * size != positions.size() ||
		 find(positions.begin(), positions.end(), EMPTY_CASE) == positions.end()) {
		throw invalid_argument("Séquence invalide.");
	}
}

/*
 * Source:
 * https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
 */
size_t Vertex::operator()(const Vertex& k) const {
	size_t seed = k.positions.size();
	for (auto& i : k.positions) {
		seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}

/*
 * Ajoute un sommet dans la liste chaînée simple des sommets adjacents.
 */
void addVertex(forward_list<Vertex>& neighbors, vector<uint32_t> initialPositions,
					size_t indexEmpty, size_t indexToSwap) {
	swap(initialPositions[indexEmpty], initialPositions[indexToSwap]);
	neighbors.emplace_front(initialPositions);
}

size_t Vertex::indexEmptyCase() const {
	return (size_t) (
		distance(
			positions.begin(),
			find(positions.begin(), positions.end(), EMPTY_CASE))
	);
}

forward_list<Vertex> Vertex::getNeighbors() const {
	forward_list<Vertex> neighbors;

	const size_t LEN_POSITIONS = positions.size();
	const auto SIZE_TAQUIN = (size_t) sqrt(LEN_POSITIONS);
	size_t emptyCase = indexEmptyCase();

	// Voisins à Droite => pas en dernière colonne
	if (emptyCase % SIZE_TAQUIN != SIZE_TAQUIN - 1) {
		addVertex(neighbors, positions, emptyCase, emptyCase + 1);
	}
	// Voisins à Gauche => pas en 1ère colonne
	if (emptyCase % SIZE_TAQUIN != 0) {
		addVertex(neighbors, positions, emptyCase, emptyCase - 1);
	}
	// Voisins en Haut => pas en 1ère ligne
	if (emptyCase >= SIZE_TAQUIN) {
		addVertex(neighbors, positions, emptyCase, emptyCase - SIZE_TAQUIN);
	}
	// Voisins en Bas => pas en dernière ligne
	if (emptyCase < LEN_POSITIONS - SIZE_TAQUIN) {
		addVertex(neighbors, positions, emptyCase, emptyCase + SIZE_TAQUIN);
	}
	return neighbors;
}
