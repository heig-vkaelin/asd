//
// Created by Olivier Cuisenaire on 04.05.20.
//

#ifndef ASD1_LABS_2020_TRIPARTITE_H
#define ASD1_LABS_2020_TRIPARTITE_H

#include <vector>

#define CONTAINER std::vector

template<typename T>
std::vector<T> tripartite(std::vector<T>& v) {
	std::vector<T> w;
	w.reserve(v.size());

	auto iwrite = v.begin();
	for (auto iread = v.begin(); iread != v.end(); ++iread) {
		switch (*iread % 3) {
			case 0:
				// l'élément est déplacé dans le conteneur retourné
				w.push_back(std::move(*iread));
				break;
			case 1:
				// l'élément reste dans le conteneur original
				*iwrite = std::move(*iread);
				++iwrite;
				break;
			case 2:
				// l'élément est supprimé
				break;
		}
	}
	v.erase(iwrite, v.end());
	return w;
}

#endif // ASD1_LABS_2020_TRIPARTITE_H
