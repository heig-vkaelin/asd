#include "evaluator.h"
#include <algorithm>

using namespace std;

int appliquerOperation(int v1, int v2, char op) {
	switch (op) {
		case '+':
			return v1 + v2;
		case '-':
			return v1 - v2;
		case '*':
			return v1 * v2;
		case '/':
			return v1 / v2;
		case '%':
			return v1 % v2;
		default:
			throw bad_expression();
	}
}

int evalue(string const& expression) {
	const string OPERATEURS = "+-*/%";

	// Cela signifie que l'évaluation n'est pas évaluable : il y a eu un problème
	// lors de la création des substrings.
	if (expression.empty()) {
		throw bad_expression();
	}

	// Supprimer les espaces de l'expression
	string str = expression;
	str.erase(remove(str.begin(), str.end(), ' '), str.end());

	// Condition de sortie : que des digits dans la string
	if (str.find_first_not_of("0123456789") == string::npos) {
		return stoi(str);
	}

	// Recherche du prochain opérateur à effectuer
	size_t indexOperateur = 0;
	size_t nbParentheses = 0;
	for (auto it = str.begin(); it != str.end(); ++it) {
		if (*it == '(') {
			++nbParentheses;
		} else if (*it == ')') {
			--nbParentheses;
		} else if (OPERATEURS.find(*it) != string::npos && nbParentheses == 1) {
			indexOperateur = (size_t) distance(str.begin(), it);
			break;
		}
	}

	string strGauche = str.substr(1, indexOperateur - 1);
	size_t nbCharDroite = str.length() - indexOperateur - 2;
	string strDroite = str.substr(indexOperateur + 1, nbCharDroite);
	int v1 = evalue(strGauche);
	int v2 = evalue(strDroite);

	return appliquerOperation(v1, v2, str[indexOperateur]);
}
