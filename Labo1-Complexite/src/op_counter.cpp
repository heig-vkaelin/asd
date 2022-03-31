/*
-----------------------------------------------------------------------------------
Nom du fichier : op_counter.cpp
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 02.03.2021
Description    : Implémentation de la classe OpCounter
Remarque(s)    : -
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include "op_counter.h"

/* Static */
unsigned OpCounter::assignmentCounter = 0;
unsigned OpCounter::comparisonCounter = 0;

unsigned OpCounter::getAssignmentCount() {
	return assignmentCounter;
}

unsigned OpCounter::getComparisonCount() {
	return comparisonCounter;
}

void OpCounter::resetCounters() {
	OpCounter::comparisonCounter = 0;
	OpCounter::assignmentCounter = 0;
}

/* Constructors */
OpCounter::OpCounter() : i(0) {}

OpCounter::OpCounter(int i) : i(i) {}

OpCounter::OpCounter(const OpCounter &obj) {
	i = obj.i;
	++assignmentCounter;
}

/* Operators */
bool operator<(const OpCounter &lhs, const OpCounter &rhs) {
	++OpCounter::comparisonCounter;
	return lhs.i < rhs.i;
}

bool operator>(const OpCounter &lhs, const OpCounter &rhs) {
	return !(lhs < rhs);
}

OpCounter &OpCounter::operator=(const OpCounter &obj) {
	if (this != &obj) {
		this->i = obj.i;
		++OpCounter::assignmentCounter;
	}
	return *this;
}

OpCounter &OpCounter::operator=(int val) {
	i = val;
	return *this;
}
