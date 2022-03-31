/*
-----------------------------------------------------------------------------------
Nom du fichier : piece_structure.cpp
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 09.03.2021
Description    : Implémentation de la classe piece_structure.
Remarque(s)    : Nous avons surchargés l'opérateur d'écriture sur un flux afin de
                 faciliter l'affichage des pièces. L'affichage des pièces se fait
                 sous la forme "No" avec N, un chiffre compris entre 1 et 9
                 (indiquant l'emplacement de la pièce) et o, une lettre entre 'a'
                 et 'd' (indiquant l'orientation de la pièce).
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>
#include <iostream>
#include "piece_structure.h"

using namespace std;

ostream &operator<<(ostream &os, const PieceStructure &obj) {
	return os << obj.id + 1 << (char) ('a' + obj.rotation);
}

PieceStructure::PieceStructure(unsigned id, unsigned rotation)
	: id(id), rotation(rotation) {}

Piece PieceStructure::getPiece() const {
	return PIECES[id];
}

AttachementType PieceStructure::getAttachement(size_t r) const {
	return getPiece()[(rotation + r) % 4];
}
