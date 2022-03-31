/*
-----------------------------------------------------------------------------------
Nom du fichier : main.cpp
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 16.03.2021
Description    : Fichier du programme principal qui génère les solutions d'un
                 "puzzle impossible".
Remarque(s)    : Les résultats sont affichés dans la console. Une ligne correspond à
                 une solution. L'algorithme de double échange sans échange inutile a
                 été utilisé pour trouver les solutions.
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>
#include <iostream>
#include "piece_structure.h"

using namespace std;

// Compteurs du nombre de solutions et d'appel de la fonction generateSolutions
size_t solutionCounter = 0;
size_t callCounter = 0;

/**
 * Vérifie la correspondance entre les côtés de deux pièces.
 * @param a1 : 1er côté de pièce à comparer
 * @param a2 : 2ème côté de pièce à comparer
 * @return true si les côtés des pièces correspondent
 */
bool verifyAttachement(AttachementType a1, AttachementType a2);

/**
 * Teste les côtés des pièces en fonction de leur position dans le puzzle. On ne
 * teste que le côté droit, bas ou les deux.
 *
 * Représentation des pièces d'un puzzle 3x3:
 *
  *  0  1  2
 *   3  4  5
 *   6  7  8
 *
 * @param board : Vecteur de PieceStructure représentant le puzzle
 * @param piecePosition : Position de de la pièce à tester
 * @param width : Nombre de colonnes du puzzle
 * @param height : Nombre de lignes du puzzle
 * @return true si les côtés testés correspondent.
 */
bool testPiece(const Board &board, size_t piecePosition,
					unsigned width, unsigned height);

/**
 * Génère les solutions du puzzle ligne par ligne dans la console.
 * Utilise un algoritme de double échange sans échange inutile.
 * @param board : Vecteur de PieceStructure représentant le puzzle
 * @param remainingPieces : Nombre de pièces à traiter
 * @param width : Nombre de colonnes du puzzle
 * @param height : Nombre de lignes du puzzle
 */
void generateSolutions(Board &board, size_t remainingPieces,
							  unsigned width, unsigned height);

bool verifyAttachement(AttachementType a1, AttachementType a2) {
	switch (a1) {
		case FILLE_HAUT:
			return a2 == FILLE_BAS;
		case FILLE_BAS:
			return a2 == FILLE_HAUT;
		case DAME_HAUT:
			return a2 == DAME_BAS;
		case DAME_BAS:
			return a2 == DAME_HAUT;
		case ARROSOIR_GAUCHE:
			return a2 == ARROSOIR_DROIT;
		case ARROSOIR_DROIT:
			return a2 == ARROSOIR_GAUCHE;
		case ARROSOIR_INVERSE:
			return a2 == NONE;
		case GATEAU_GAUCHE:
			return a2 == GATEAU_DROIT;
		case GATEAU_DROIT:
			return a2 == GATEAU_GAUCHE;
		default:
			return false;
	}
}

bool testPiece(const Board &board, size_t piecePosition,
					unsigned width, unsigned height) {
	bool rightSide = true;
	bool botSide = true;

	if (piecePosition % width != width - 1) {
		rightSide = verifyAttachement(
			board[piecePosition].getAttachement(1),
			board[piecePosition + 1].getAttachement(3)
		);
	}
	if (piecePosition < width * (height - 1)) {
		botSide = verifyAttachement(
			board[piecePosition].getAttachement(2),
			board[piecePosition + width].getAttachement(0)
		);
	}
	return rightSide && botSide;
}

void generateSolutions(Board &board, size_t remainingPieces,
							  unsigned width, unsigned height) {
	++callCounter;
	if (remainingPieces == 0) {
		for (const PieceStructure &p : board) {
			cout << p << " ";
		}
		cout << endl;
		++solutionCounter;
	} else {
		for (size_t i = 0; i < remainingPieces - 1; ++i) {
			for (board[i].rotation = 0; board[i].rotation < 4; ++board[i].rotation) {
				swap(board[i], board[remainingPieces - 1]);
				if (testPiece(board, remainingPieces - 1, width, height)) {
					generateSolutions(board, remainingPieces - 1, width, height);
				}
				swap(board[i], board[remainingPieces - 1]);
			}
		}
		// Dernière pièce sans échange inutile
		size_t i = remainingPieces - 1;
		for (board[i].rotation = 0; board[i].rotation < 4; ++board[i].rotation) {
			if (testPiece(board, remainingPieces - 1, width, height)) {
				generateSolutions(board, remainingPieces - 1, width, height);
			}
		}
	}
}

int main() {
	// Dimensions du puzzle
	Board board = {PieceStructure(0), PieceStructure(1), PieceStructure(2),
						PieceStructure(3), PieceStructure(4), PieceStructure(5),
						PieceStructure(6), PieceStructure(7), PieceStructure(8)};

	const unsigned WIDTH = 3, HEIGHT = 3;
	generateSolutions(board, WIDTH * HEIGHT, WIDTH, HEIGHT);

	cout << endl << "Nombre de solutions: " << solutionCounter << endl;
	cout << "Nombre d'appels de la fonction generateSolutions: " << callCounter
		  << endl;
}
