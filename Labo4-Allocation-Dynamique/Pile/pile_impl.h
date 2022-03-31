#ifndef PILE_IMPL_H
#define PILE_IMPL_H

#include <stdexcept> // std::out_of_range
#include "pile.h"

// AJOUTEZ VOTRE CODE ICI ...

template<typename T>
Pile<T>::Pile(size_t n) : taille(0), capacite(n) {
	data = (T *) ::operator new(sizeof(T) * n);
}

template<typename T>
Pile<T>::~Pile<T>() {
	for (size_t i = 0; i < taille; ++i) {
		data[i].~T();
	}
	::operator delete(data);
}

template<typename T>
void Pile<T>::push(T e) {
	if (full()) {
		throw std::out_of_range("push");
	}
	new(data + taille++)T(std::move(e));
}

template<typename T>
void Pile<T>::pop() {
	if (empty()) {
		throw std::out_of_range("pop");
	}
	data[--taille].~T();
}

template<typename T>
const T &Pile<T>::top() const {
	if (empty()) {
		throw std::out_of_range("top");
	}
	return data[taille - 1];
}

template<typename T>
bool Pile<T>::empty() const noexcept {
	return taille == 0;
}

template<typename T>
bool Pile<T>::full() const noexcept {
	return taille == capacite;
}

// Clang-Tidy: ne comprend pas que le champs capactité est initialisé dans le constructeur.
template<typename T>
Pile<T>::Pile(const Pile<T> &other) : Pile(other.capacite) {
   taille = other.taille;
   for (size_t i = 0; i < taille; ++i) {
      new(data + i) T(other.data[i]);
   }
}

template<typename T>
void Pile<T>::swap(Pile<T> &other) noexcept {
	using std::swap;
	swap(capacite, other.capacite);
	swap(taille, other.taille);
	swap(data, other.data);
}

template<typename T>
Pile<T> &Pile<T>::operator=(const Pile<T> &other) {
	if (this == &other) return *this;

	if (other.taille <= capacite) {
		// sans réallouer
		for (size_t i = 0; i < other.taille; ++i) {
			if (i < taille) {
				data[i] = other.data[i];
			} else {
				new(data + i)T(other.data[i]);
			}
		}
		for (size_t i = other.taille; i < taille; ++i) {
			data[i].~T();
		}
		taille = other.taille;
	} else {
		Pile<T> tmp(other);
		swap(tmp);
	}
	return *this;
}

// ... FIN DE VOTRE CODE

#endif
