/*
-----------------------------------------------------------------------------------
Nom du fichier : sort_functions.h
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 02.03.2021
Description    : Implémentation des trois fonctions de tri suivantes:
                 - Bubble sort
                 - Insert sort
                 - Selection sort
Remarque(s)    : Les fonctions ont été implémentées avec des iterator pour pouvoir
                 les utiliser avec tout type de container.
                 Le type SortFuncIter est utilisé dans une map afin de pouvoir
                 appeler les fonctions les unes après les autres via une boucle.
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <algorithm>
#include <vector>

/**
 * Type utilisé dans une map afin de pouvoir boucler sur les différentes fonctions
 * de tri dans nos programmes principaux.
 */
template<typename T, typename iterator = typename std::vector<T>::iterator>
using SortFuncIter = void (*)(iterator begin, iterator end);

template<typename iterator>
void bubbleSort(iterator begin, iterator end) {
	if (end - begin <= 1) {
		return;
	}
	bool isEnded = false;
	while (!isEnded) {
		isEnded = true;
		for (auto i = begin; i < end - 1; ++i) {
			if (*i > *(i + 1)) {
				std::iter_swap(i, i + 1);
				isEnded = false;
			}
		}
		--end;
	}
}

template<typename iterator>
void insertSort(iterator begin, iterator end) {
	if (end - begin <= 1) {
		return;
	}

	// On lui donne une valeur initiale afin qu'il puisse déterminer le type
	auto temp = *begin;
	iterator j;
	for (auto i = begin + 1; i != end; ++i) {
		temp = *i;
		j = i;
		while (j >= begin + 1 && *(j - 1) > temp) {
			*j = *(j - 1);
			--j;
		}
		*j = temp;
	}
}

template<typename iterator>
void selectionSort(iterator begin, iterator end) {
	if (end - begin <= 1) {
		return;
	}
	iterator iMin;
	for (auto i = begin; i != end; ++i) {
		iMin = i;
		for (auto j = i + 1; j != end; ++j) {
			if (*j < *iMin) {
				iMin = j;
			}
		}
		std::iter_swap(i, iMin);
	}
}
