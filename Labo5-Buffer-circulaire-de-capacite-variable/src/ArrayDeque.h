#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <ostream>

template<class T>
class ArrayDeque {
public:
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using size_type = std::size_t;

private:
	pointer buffer;
	size_type capacite;
	size_type debut;
	size_type taille;

	size_type index_physique(size_type index_logique) const {
		return (debut + index_logique + capacite) % capacite;
	}

	void nouvelle_capacite(bool adapter_a_la_taille = false) {
		// Le paramètre permet de diminuer la capacité du buffer à sa taille au lieu de
		// laisser l'algorithme décider lui-même. Fonctionnalité utilisée pour
		// l'implémentation de la méthode "shrink_to_fit".
		size_type nouvelleCapacite;
		if (adapter_a_la_taille) {
			nouvelleCapacite = taille;
		} else {
			nouvelleCapacite = capacite == 0 ? 1 : capacite * 2;
		}
		ArrayDeque<value_type> tmp(nouvelleCapacite);
		for (size_type i = 0; i < taille; ++i) {
			new(tmp.buffer + i) value_type(std::move(buffer[index_physique(i)]));
			++tmp.taille;
		}

		std::swap(buffer, tmp.buffer);
		std::swap(capacite, tmp.capacite);
		std::swap(debut, tmp.debut);
	}

public:
	ArrayDeque(size_type _capacite = 0) : buffer(nullptr), capacite(_capacite),
													  debut(0), taille(0) {
		if (capacite)
			buffer = reinterpret_cast<pointer> (
				::operator new(capacite * sizeof(value_type)));
	}

	// Clang-Tidy: ne comprend pas que les champs capacité et taille sont initialisés
	// dans le constructeur prenant un size_type.
	ArrayDeque(const ArrayDeque<value_type>& other) : ArrayDeque(other.capacite) {
		debut = other.debut;
		for (size_type i = 0; i < other.taille; ++i) {
			new(buffer + index_physique(i)) value_type(other[i]);
			++taille;
		}
	}

	~ArrayDeque() {
		for (size_type i = 0; i < taille; ++i) {
			buffer[index_physique(i)].~value_type();
		}
		::operator delete(buffer);
		buffer = nullptr;
	}

	size_type capacity() const {
		return capacite;
	}

	size_type size() const {
		return taille;
	}

	reference front() const {
		return operator[](0);
	}

	reference back() const {
		return operator[](taille - 1);
	}

	bool empty() const {
		return taille == 0;
	}

	void push_back(const_reference v) {
		if (taille >= capacite) {
			nouvelle_capacite();
		}

		new(buffer + index_physique(taille)) value_type(v);
		taille++;
	}

	void push_front(const_reference v) {
		if (taille >= capacite) {
			nouvelle_capacite();
		}

		size_type avant = index_physique(capacite - 1);
		new(buffer + avant) value_type(v);
		debut = avant;
		taille++;
	}

	void pop_back() {
		if (taille) {
			buffer[index_physique(taille - 1)].~value_type();
			taille--;
		}
	}

	void pop_front() {
		if (taille) {
			buffer[debut].~value_type();
			debut = index_physique(1);
			taille--;
		}
	}

	void swap(ArrayDeque<value_type>& other) {
		using std::swap;
		swap(buffer, other.buffer);
		swap(capacite, other.capacite);
		swap(debut, other.debut);
		swap(taille, other.taille);
	}

	void shrink_to_fit() {
		nouvelle_capacite(true);
	}

	reference operator[](size_type i) const {
		return buffer[index_physique(i)];
	}

	ArrayDeque<value_type>& operator=(const ArrayDeque<value_type>& other) {
		if (this == &other) { return *this; }

		ArrayDeque<value_type> tmp(other);
		swap(tmp);
		return *this;
	}

};

template<typename T>
inline
std::ostream& operator<<(std::ostream& s,
								 const ArrayDeque<T>& v) {
	s << "(" << v.size() << "/" << v.capacity() << ") : ";
	if (not v.empty())
		s << v.front() << " -> " << v.back() << " : ";
	s << "[";
	for (size_t i = 0; i < v.size(); ++i) {
		s << v[i];
		if (i != v.size() - 1)
			s << ", ";
	}
	s << "]";
	return s;
}

#endif /* ArrayDeque_hpp */
