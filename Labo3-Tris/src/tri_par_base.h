/*
-----------------------------------------------------------------------------------
Nom du fichier : tri_par_base.h
Auteur(s)      : Jonathan Friedli, Valentin Kaelin, Lazar Pavicevic
Date creation  : 09.04.2021
Description    : Implémentations du tri comptage et du tri par base.
Remarque(s)    : Le tri par base fonctionne uniquement sur des entiers non signés.
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#ifndef TRI_PAR_BASE
#define TRI_PAR_BASE

#include <cstdlib>
#include <iterator>
#include <vector>
#include <map>
#include <type_traits>
#include "some_bits.h"

/**
 * Tri comptage de la plage d'éléments [first, last). Stocke le résultat trié dans
 * un conteneur commençant au paramètre output_first.
 * @tparam Iterator : type de l'itérateur des éléments du conteneur
 * @tparam Fn : type de la fonction pour déterminer la case de comptage
 * @param first : itérateur sur le 1er élément du conteneur
 * @param last : itérateur après le dernier élément du conteneur
 * @param output_first : itérateur sur le 1er élément du futur conteneur trié
 * @param index_fn : fonction permettant de déterminer la case de comptage des
 * éléments du conteneur
 * @param N : nombre de cases de comptage
 */
template<typename Iterator, typename Fn>
void tri_comptage(Iterator first, Iterator last, Iterator output_first, Fn index_fn,
						size_t N) {
	using T = typename Iterator::value_type;
	std::vector<T> counters(N);

	for (Iterator i = first; i != last; ++i) {
		counters.at(index_fn(*i)) += 1;
	}

	unsigned index = 0;
	for (size_t i = 0; i < N; ++i) {
		T temp = counters.at(i);
		counters.at(i) = index;
		index += temp;
	}

	for (Iterator i = first; i != last; ++i) {
		*(output_first + counters.at(index_fn(*i))) = *i;
		counters.at(index_fn(*i)) += 1;
	}
}

/**
 * Tri par base.
 * Les bases utilisées sont des groupes de NBITS bits de la représentation binaire
 * des éléments du conteneur à trier.
 * @tparam Iterator : type de l'itérateur des éléments du conteneur
 * @tparam NBITS : nombre de bits par groupe
 * @param first : itérateur sur le 1er élément du conteneur
 * @param last : itérateur après le dernier élément du conteneur
 */
template<typename Iterator, size_t NBITS>
void tri_par_base(Iterator first, Iterator last) {
	using T = typename Iterator::value_type;
	static_assert(std::is_unsigned<T>::value);

	const auto SIZE = (size_t) std::distance(first, last);
	const auto N = (size_t) std::pow(2, NBITS);
	std::vector<T> sorted(SIZE);

	for (unsigned i = 0; i < std::numeric_limits<T>::digits / NBITS; i++) {
		auto fn = SomeBits<T>(NBITS, i);

		// Nous passons en paramètre sorted 1x sur 2 afin d'éviter de copier sorted
		// dans [first,last) après chaque appel de tri_comptage.
		if (i % 2 == 0) {
			tri_comptage(first, last, sorted.begin(), fn, N);
		} else {
			tri_comptage(sorted.begin(), sorted.end(), first, fn, N);
		}
	}
}

/**
 * Itérateur sur un vecteur de type générique
 */
template<typename T>
using vIterator = typename std::vector<T>::iterator;

/**
 * Type des fonctions de tri par base
 */
template<typename T>
using radixFunc = void (*)(vIterator<T>, vIterator<T>);

/**
 * Map retournant l'intégralité des fonctions de tris par base à utiliser pour ce
 * laboratoire.
 * @tparam T : type des éléments à trier
 */
template<typename T>
std::map<std::string, radixFunc<T>> radixFunctions = {
	{"radix 1",  tri_par_base<vIterator<T>, 1>},
	{"radix 2",  tri_par_base<vIterator<T>, 2>},
	{"radix 4",  tri_par_base<vIterator<T>, 4>},
	{"radix 8",  tri_par_base<vIterator<T>, 8>},
	{"radix 16", tri_par_base<vIterator<T>, 16>},
};

#endif
