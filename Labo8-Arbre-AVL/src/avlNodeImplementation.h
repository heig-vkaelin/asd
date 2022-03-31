#ifndef ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
#define ASD_LABS_2021_AVLNODEIMPLEMENTATION_H

#include "avlNode.h"

namespace avl {

	template<typename Key>
	std::istream& operator>>(std::istream& in, Node <Key>*& node) {
		Key key;
		in >> key;
		node = new Node<Key>{key, Node<Key>::NO_CHILD, 1};
		return in;
	}

	template<typename Key>
	void insert_in_subtree(Node <Key>*& r, Key const& k) {
		if (r == nullptr) {
			r = new Node<Key>{k, Node<Key>::NO_CHILD, 1};
		} else if (k == r->key) {
			return;
		} else {
			Side s = k < r->key ? LEFT : RIGHT;
			insert_in_subtree(r->children[s], k);
			rebalance(r);
		}
	}

	template<typename Key>
	std::ostream& show_indented(Node <Key>* r,
										 std::ostream& out,
										 std::string before,
										 bool isright) {
		out << before;
		if (not r) {
			out << ".\n";
		} else {
			if (not before.empty()) {
				before[before.size() - 2] = ' ';
				if (isright) {
					before[before.size() - 3] = ' ';
				}
			}
			out << r->key << std::endl;
			if (r->children != Node<Key>::NO_CHILD) {
				for (Side s : {LEFT, RIGHT}) {
					show_indented(r->children[s], out, before + "|_ ", s);
				}
			}
		}
		return out;
	}

	template<typename Key>
	std::ostream& show_inline(Node <Key>* const r, std::ostream& out) {
		if (!r) { return out << "."; }

		out << r->key;
		out << "(";
		show_inline(r->left(), out);
		out << ",";
		show_inline(r->right(), out);
		out << ")";

		return out;
	}

	template<typename Key>
	void from_string(std::istream& in, Node <Key>*& out) {
		char c;
		in.get(c);
		if (isdigit(c)) {
			in.putback(c);
			in >> out;

			in.get(c);
			if (c != '(') throw std::invalid_argument("Flux invalide");

			from_string(in, out->left());

			in.get(c);
			if (c != ',') throw std::invalid_argument("Flux invalide");

			from_string(in, out->right());

			computeHeight(out);

			in.get(c);
			if (c != ')') throw std::invalid_argument("Flux invalide");
		} else if (c != '.') {
			throw std::invalid_argument("Flux invalide");
		}
	}

	template<typename Key>
	Key const& extremum(Node <Key>* const node, Side side) {
		if (!node) {
			throw std::invalid_argument("Extremum n'existe pas dans un arbre vide");
		}

		auto extremum = node;
		while (extremum->children[side])
			extremum = extremum->children[side];
		return extremum->key;
	}

	template<typename Key>
	bool contains(Node <Key>* const node, const Key& k) {
		if (!node) {
			return false;
		}
		if (node->key == k) {
			return true;
		}
		if (node->key < k) {
			return contains(node->right(), k);
		}
		return contains(node->left(), k);
	}

	template<typename Key>
	Node <Key>* exit_min(Node <Key>*& node) {
		if (node->left()) {
			return exit_min(node->left());
		} else {
			Node<Key>* tmp = node;
			node = node->right();
			return tmp;
		}
	}

	template<typename Key>
	void delete_key(Node <Key>*& node, const Key& k) {
		if (!node) { return; }

		if (k < node->key) {
			delete_key(node->left(), k);
			rebalance(node);
		} else if (k > node->key) {
			delete_key(node->right(), k);
			rebalance(node);
		} else {
			Node<Key>* tmp = node;
			if (!node->left()) {
				node = node->right();
			} else if (!node->right()) {
				node = node->left();
			} else {
				Node<Key>* m = exit_min(node->right());
				m->right() = node->right();
				m->left() = node->left();
				node = m;
			}
			delete tmp;
			tmp = nullptr;
		}
	}

	template<typename Key>
	Node <Key>* copy(Node <Key>* const node) {
		if (!node) { return nullptr; }

		Node<Key>* leftTree = copy(node->left());
		Node<Key>* rightTree = copy(node->left());

		return new Node<Key>{node->key, leftTree, rightTree, node->height};
	}

	template<typename Key>
	void destroy(Node <Key>*& node) {
		if (!node) { return; }

		destroy(node->left());
		destroy(node->right());

		delete node;
		node = nullptr;
	}

	template<typename Key>
	unsigned char height(const Node <Key>* const& node) {
		return node ? node->height : 0;
	}

	template<typename Key>
	void computeHeight(Node <Key>* const& node) {
		if (!node) { return; }

		node->height = (unsigned char)
			(1 + std::max(height(node->left()), height(node->right())));
	}

	template<typename Key>
	void rotateLeft(Node <Key>*& node) {
		Node<Key>* temp = node->right();
		node->right() = temp->left();
		temp->left() = node;
		node = temp;
		computeHeight(node->left());
		computeHeight(node);
	}

	template<typename Key>
	void rotateRight(Node <Key>*& node) {
		Node<Key>* temp = node->left();
		node->left() = temp->right();
		temp->right() = node;
		node = temp;
		computeHeight(node->right());
		computeHeight(node);
	}

	template<typename Key>
	int balance(Node <Key>* const node) {
		if (!node) { return 0; }

		return height(node->left()) - height(node->right());
	}

	template<typename Key>
	void rebalance(Node <Key>*& node) {
		if (!node) { return; }

		if (balance(node) < -1) {
			if (balance(node->right()) > 0) { // penche à droite
				rotateRight(node->right());
			}
			rotateLeft(node);
		} else if (balance(node) > 1) { // penche à gauche
			if (balance(node->left()) < 0) {
				rotateLeft(node->left());
			}
			rotateRight(node);
		} else {
			computeHeight(node);
		}
	}
}

#endif // ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
