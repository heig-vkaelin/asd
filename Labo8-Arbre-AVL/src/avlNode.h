#ifndef ASD_LABS_2021_AVLNODE_H
#define ASD_LABS_2021_AVLNODE_H

namespace avl {

	enum Side {
		LEFT = 0, RIGHT = 1
	};

	template<typename Key>
	struct Node;

	template<typename Key>
	std::istream& operator>>(std::istream& in, Node<Key>*& node);

	template<typename Key>
	struct Node {
		Key const key;
		std::array<Node*, 2> children;
		unsigned char height;

		inline Node*& left() noexcept { return children[LEFT]; }

		inline Node*& right() noexcept { return children[RIGHT]; }

		static constexpr std::array<Node*, 2> NO_CHILD{nullptr, nullptr};
	};

	template<typename Key>
	void insert_in_subtree(Node<Key>*& r,
								  Key const& k);

	template<typename Key>
	std::ostream& show_indented(Node<Key>* r,
										 std::ostream& out = std::cout,
										 std::string before = "",
										 bool isright = false);

	template<typename Key>
	std::ostream& show_inline(Node<Key>* const r, std::ostream& out);

	template<typename Key>
	void from_string(std::istream& in, Node<Key>*& out);

	template<typename Key>
	Key const& extremum(Node<Key>* const node, Side side);

	template<typename Key>
	bool contains(Node<Key>* const node, const Key& k);

	template<typename Key>
	Node<Key>* exit_min(Node<Key>*& node);

	template<typename Key>
	void delete_key(Node<Key>*& node, const Key& k);

	template<typename Key>
	Node<Key>* copy(Node<Key>* const node);

	template<typename Key>
	void destroy(Node<Key>*& node);

	template<typename Key>
	unsigned char height(const Node<Key>* const& node);

	template<typename Key>
	void computeHeight(Node<Key>* const& node);

	template<typename Key>
	void rotateLeft(Node<Key>*& node);

	template<typename Key>
	void rotateRight(Node<Key>*& node);

	template<typename Key>
	int balance(Node<Key>* const node);

	template<typename Key>
	void rebalance(Node<Key>*& node);
}

#include "avlNodeImplementation.h"

#endif // ASD_LABS_2021_AVLNODE_H
