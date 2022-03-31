/*
-----------------------------------------------------------------------------------
Nom du fichier : vertex.h
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 17.06.2021
Description    : Déclaration de la classe Vertex. Elle représente un sommet du
                 graphe. Un sommet contient les positions des pièces du taquin.
Remarque(s)    : -
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#ifndef ASD_LABO9_VERTEX_H
#define ASD_LABO9_VERTEX_H

#include <cstdint>
#include <forward_list>
#include <vector>
#include <string>

extern const int EMPTY_CASE;

class Vertex {
	/*
	 * La comparaison d'égalité se fait sur les positions des pièces représentées
	 * par un vector.
	 */
	friend bool operator==(const Vertex& lhs, const Vertex& rhs);

public:
	/* Constructors */
	explicit Vertex(std::vector<uint32_t> v = {});

	explicit Vertex(const std::string& s);

	/*
	 * Retourne un hash à partir du contenu du vector de positions issu du sommet.
	 */
	size_t operator()(const Vertex& k) const;

	/*
	 * Retourne l'index de la case vide.
	 */
	[[nodiscard]] size_t indexEmptyCase() const;

	/*
	 * Retourne la liste des sommets adjacents au sommet actuel.
	 */
	[[nodiscard]] std::forward_list<Vertex> getNeighbors() const;

	std::vector<uint32_t> positions;
};

#endif // ASD_LABO9_VERTEX_H
