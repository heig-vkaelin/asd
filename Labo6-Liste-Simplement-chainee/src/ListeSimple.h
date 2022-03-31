#ifndef LISTE_H
#define LISTE_H

#include "LSIterator.h"
#include "util.h"
#include <utility> // std::swap;

template<typename T>
class ListeSimple {
public:
	using value_type = T;
	using reference = T&;
	using const_reference = T const&;

private:
	struct Maillon {
		value_type valeur;
		Maillon* suivant;
	};

	Maillon avant_premier;

public:
	using iterator = LSIterator<value_type>;
	friend iterator;

	using const_iterator = LSConstIterator<value_type>;
	friend const_iterator;

	const_iterator cbegin() const noexcept {
		return const_iterator(avant_premier.suivant);
	}

	iterator begin() noexcept {
		return iterator(avant_premier.suivant);
	}

	const_iterator begin() const noexcept {
		return cbegin();
	}

	ListeSimple() : avant_premier{value_type{}, nullptr} {}

	ListeSimple(const ListeSimple<value_type>& other) : ListeSimple() {
		auto it = before_begin();
		for (const_iterator i = other.begin(); i != other.end(); ++i) {
			insert_after(it, *i);
			it++;
		}
	}

	~ListeSimple() {
		while (!empty()) {
			pop_front();
		}
	}

	ListeSimple<value_type>& operator=(const ListeSimple<value_type>& other) {
		if (this == &other) { return *this; }

		ListeSimple<value_type> tmp(other);
		swap(tmp);
		return *this;
	}

	const_iterator cend() const noexcept {
		return const_iterator(nullptr);
	}

	iterator end() noexcept {
		return iterator(nullptr);
	}

	const_iterator end() const noexcept {
		return cend();
	}

	const_iterator cbefore_begin() const noexcept {
		return const_iterator(&avant_premier);
	}

	iterator before_begin() noexcept {
		return iterator(&avant_premier);
	}

	const_iterator before_begin() const noexcept {
		return cbefore_begin();
	}

	bool empty() const noexcept {
		return begin() == nullptr;
	}

	reference front() noexcept {
		return *begin();
	}

	const_reference front() const noexcept {
		return *cbegin();
	}

	void insert_after(iterator i, const_reference v) {
		if (i.m) {
			i.m->suivant = new Maillon{v, i.m->suivant};
		}
	}

	void push_front(const_reference v) {
		insert_after(before_begin(), v);
	}

	void erase_after(iterator i) {
		if (i.m && i.m->suivant) {
			auto tmp = i.m->suivant;
			i.m->suivant = tmp->suivant;
			delete tmp;
		}
	}

	void pop_front() {
		erase_after(before_begin());
	}

	void swap(ListeSimple<value_type>& other) noexcept {
		using std::swap;
		swap(avant_premier, other.avant_premier);
	}

	void splice_after(iterator position, iterator first, iterator last) {
		if (first == last) {
			return;
		}

		auto after_first = first.m->suivant;

		first.m->suivant = last.m->suivant;
		last.m->suivant = position.m->suivant;
		position.m->suivant = after_first;
	}

	/**
	 * Tri par sélection
	 */
	void sort() {
		iterator j = before_begin();
		while (next(j, 2) != end()) {
			iterator iMin = j;
			iterator i = next(j);
			while (next(i) != end()) {
				if (*next(iMin) > *next(i))
					iMin = i;
				i++;
			}

			splice_after(j, iMin, next(iMin));
			j++;
		}
	}
};

#endif // LISTE_H
