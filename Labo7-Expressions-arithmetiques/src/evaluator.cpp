#include "evaluator.h"
#include <stack> // std::stack
#include <cctype>

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
	stack<char> pileOp;
	stack<int> pileVal;

	for (auto it = expression.begin(); it != expression.end(); ++it) {
		if (*it == '(' || isblank(*it)) {
			continue;
		} else if (OPERATEURS.find(*it) != string::npos) {
			pileOp.push(*it);
		} else if (isdigit(*it)) {
			int val = 0;
			do {
				val = val * 10 + *it++ - '0';
			} while (isdigit(*it));
			--it;
			pileVal.push(val);
		} else if (*it == ')') {
			// Vérification qu'une opération binaire est effectuable
			if (pileVal.size() < 2 || pileOp.empty()) {
				throw bad_expression();
			}
			int v2 = pileVal.top();
			pileVal.pop();
			int v1 = pileVal.top();
			pileVal.pop();
			char op = pileOp.top();
			pileOp.pop();
			pileVal.push(appliquerOperation(v1, v2, op));
		} else {
			throw bad_expression();
		}
	}

	// Vérification que l'évaluation s'est terminée dans un état correct
	if (pileVal.size() != 1 || !pileOp.empty()) {
		throw bad_expression();
	}

	return pileVal.top();
}
