#include <iostream>
#include <sstream>
#include "avlTree.h"

using namespace std;

int main() {
	avlTree<int> t;

	for (int i : {1, 2, 3, 5, 4, 6, 7}) {
		t.insert(i);
		cout << "Hauteur " << (int) t.height() << "\nNode insere " << i << endl;
		t.show_indented();
		cout << endl;
	}

	// Check la rebalance de ces arbres de bg après un erase
	avlTree<int> t2;
	for (int i : {8, 3, 10, 2, 5, 9, 11, 1, 4, 7, 12, 6}) {
		t2.insert(i);
	}
	t2.show_indented();
	cout << t2 << endl;
	t2.erase(9);
	cout << t2 << endl;

	// Entrée pour tester l'opérateur >>
	// 3(2(1(.,.),.),5(4(.,.),6(., 8(.,.))))

	avlTree<int> t3;
	cout << "Entre un arbre bro:" << endl;
	cout << "Exemple: 3(2(1(.,.),.),5(4(.,.),6(.,8(.,.))))" << endl;
	cin >> t3;
	t2.show_indented();
	cout << t3 << endl;
}
