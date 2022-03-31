/*
-----------------------------------------------------------------------------------
Nom du fichier : piece_structures.cpp
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 09.03.2021
Description    : Déclaration de la classe piece_structure. Elle représente une
                 pièce du puzzle. Elle contient des méthodes qui permettent de
                 faire une rotation de la pièce ainsi que de donner ses symboles en
                 fonction de son orientation.
Remarque(s)    : -
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#ifndef ASD_L2_RECURSIVITE_PIECE_STRUCTURE_H
#define ASD_L2_RECURSIVITE_PIECE_STRUCTURE_H

#include <vector>
#include "pieces.h"

class PieceStructure {
	friend std::ostream &operator<<(std::ostream &os, const PieceStructure &obj);

public:
	explicit PieceStructure(unsigned id, unsigned rotation = 0);

	Piece getPiece() const;

	AttachementType getAttachement(size_t r) const;

	unsigned id; // 0, 1, 2, ... , 8
	unsigned rotation; // 0, 1, 2, 3
};

using Board = std::vector<PieceStructure>;

#endif // ASD_L2_RECURSIVITE_PIECE_STRUCTURE_H
