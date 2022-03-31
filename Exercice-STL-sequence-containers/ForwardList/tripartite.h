//
// Created by Olivier Cuisenaire on 04.05.20.
//

#ifndef ASD1_LABS_2020_TRIPARTITE_H
#define ASD1_LABS_2020_TRIPARTITE_H

#include <forward_list>

#define CONTAINER std::forward_list

template<typename T>
std::forward_list<T> tripartite(std::forward_list<T>& L) {
	std::forward_list<T> Lo;

	auto last = Lo.before_begin();
	for (auto p = L.before_begin(); next(p) != L.end();) {
		auto i = next(p);
		switch (*i % 3) {
			case 0: {
				// l'élément est déplacé dans le conteneur retourné
				Lo.splice_after(last, L, p);
				++last;
				break;
			}
			case 1:
				// l'élément reste dans le conteneur original
				++p;
				break;
			case 2:
				// l'élément est supprimé
				L.erase_after(p);
				break;
		}
	}
	return Lo;
}

#endif //ASD1_LABS_2020_TRIPARTITE_H
