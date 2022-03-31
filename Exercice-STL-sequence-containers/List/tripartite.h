//
// Created by Olivier Cuisenaire on 04.05.20.
//

#ifndef ASD1_LABS_2020_TRIPARTITE_H
#define ASD1_LABS_2020_TRIPARTITE_H

#include <list>

#define CONTAINER std::list

template<typename T>
std::list<T> tripartite(std::list<T>& L) {
	std::list<T> Lo;

	for (auto i = L.begin(); i != L.end();) {
		switch (*i % 3) {
			case 0: {
				// l'élément est déplacé dans le conteneur retourné
				auto tmp = next(i);
				Lo.splice(Lo.end(), L, i);
				i = tmp;
				break;
			}
			case 1:
				// l'élément reste dans le conteneur original
				++i;
				break;
			case 2:
				// l'élément est supprimé
				i = L.erase(i);
				break;
		}
	}
	return Lo;
}

#endif // ASD1_LABS_2020_TRIPARTITE_H
