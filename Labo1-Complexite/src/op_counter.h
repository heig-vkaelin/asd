/*
-----------------------------------------------------------------------------------
Nom du fichier : op_counter.h
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 02.03.2021
Description    : Class agissant comme un nombre et permettant de compter le nombre
                 d'opérations réalisées sur ses différentes instances.
                 2 types d'opérations sont comptés:
                 - Les opérations de comparaison (ex: < ou >)
                 - Les opérations d'affectations (ex: constructeur ou copie)
Remarque(s)    : -
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#ifndef ASD_L1_COMPLEXITE_OP_COUNTER_H
#define ASD_L1_COMPLEXITE_OP_COUNTER_H

class OpCounter {
	friend bool operator<(const OpCounter &lhs, const OpCounter &rhs);

	friend bool operator>(const OpCounter &lhs, const OpCounter &rhs);

public:
	explicit OpCounter();

	explicit OpCounter(int i);

	OpCounter(const OpCounter &obj);

	OpCounter &operator=(const OpCounter &obj);

	// Opérateur utilisé lors de la création de vecteurs avec iota mais pas directement
	// dans les algorithmes de tris, il n'incrémente donc pas le compteur
	OpCounter &operator=(int val);

	static void resetCounters();

	static unsigned getAssignmentCount();

	static unsigned getComparisonCount();

private:
	int i;
	static unsigned assignmentCounter, comparisonCounter;
};

#endif // ASD_L1_COMPLEXITE_OP_COUNTER_H
