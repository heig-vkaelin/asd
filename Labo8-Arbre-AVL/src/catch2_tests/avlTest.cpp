#include "catch.hpp"
#include "../avlTree.h"

#include <sstream>
#include <string>

using namespace std;

avlTree<int> make_easy_test_tree() { // order of insertion requires AVL no balancing
	avlTree<int> tree;
	for (int i : {6, 3, 9, 2, 4, 7, 10, 1, 5, 8})
		tree.insert(i);
	return tree;
}

TEST_CASE("operator<<", "[avlTree]") {

	SECTION("Empty tree") {
		avlTree<int> tree;

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == ".");
	}

	SECTION("Easy test tree") {
		avlTree<int> tree = make_easy_test_tree();

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
	}
}

TEST_CASE("operator>>", "[avlTree]") {

	SECTION("Empty tree") {
		avlTree<int> tree;

		stringstream in(".");
		in >> tree;

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == ".");
	}

	SECTION("Example tree") {
		avlTree<int> tree;

		stringstream in("3(2(1(.,.),.),5(4(.,.),6(.,8(.,.))))");
		in >> tree;

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == "3(2(1(.,.),.),5(4(.,.),6(.,8(.,.))))");
		REQUIRE(tree.height() == 4);
	}
}

TEST_CASE("insert", "[avlTree]") {

	SECTION("Insert into empty tree") {
		avlTree<int> tree;
		tree.insert(42);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "42\n");
	}

	SECTION("Insert smaller to the left") {
		avlTree<int> tree;
		tree.insert(3);
		tree.insert(2);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "3\n"
									"|_ 2\n"
									"|_ .\n");
	}

	SECTION("Insert larger to the right") {
		avlTree<int> tree;
		tree.insert(3);
		tree.insert(4);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "3\n"
									"|_ .\n"
									"|_ 4\n");
	}

	SECTION("Insert twice has no effect") {
		avlTree<int> tree;
		tree.insert(3);
		tree.insert(4);
		tree.insert(4);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "3\n"
									"|_ .\n"
									"|_ 4\n");
	}

	SECTION("Easy tree") {
		avlTree<int> tree = make_easy_test_tree();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "6\n"
									"|_ 3\n"
									"|  |_ 2\n"
									"|  |  |_ 1\n"
									"|  |  |_ .\n"
									"|  |_ 4\n"
									"|     |_ .\n"
									"|     |_ 5\n"
									"|_ 9\n"
									"   |_ 7\n"
									"   |  |_ .\n"
									"   |  |_ 8\n"
									"   |_ 10\n");
	}
}

TEST_CASE("copy constructor", "[avlTree]") {

	SECTION("Copy into empty tree") {
		avlTree<int> tree;
		tree.insert(42);
		avlTree<int> tree2(tree);
		tree2.insert(43);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "42\n");

		ostringstream oss2;
		tree2.show_indented(oss2);
		REQUIRE(oss2.str() == "42\n"
									 "|_ .\n"
									 "|_ 43\n");
		REQUIRE(tree2.height() == 2);
	}
}

TEST_CASE("operator=", "[avlTree]") {

	SECTION("Affect into empty tree") {
		avlTree<int> tree;
		tree.insert(42);
		avlTree<int> tree2;
		tree2 = tree;

		ostringstream oss;
		tree2.show_indented(oss);
		REQUIRE(oss.str() == "42\n");
	}

	SECTION("Affect into existing tree") {
		avlTree<int> tree;
		tree.insert(42);
		avlTree<int> tree2;
		tree2.insert(23);
		tree2 = tree;
		tree2.insert(43);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "42\n");

		ostringstream oss2;
		tree2.show_indented(oss2);
		REQUIRE(oss2.str() == "42\n"
									 "|_ .\n"
									 "|_ 43\n");
		REQUIRE(tree2.height() == 2);
	}
}

TEST_CASE("destructor", "[avlTree]") {

	SECTION("Empty tree") {
		avlTree<int> tree;
		tree.~avlTree();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == ".\n");
	}

	SECTION("Easy tree") {
		avlTree<int> tree = make_easy_test_tree();
		tree.~avlTree();
		ostringstream oss;
		tree.show_indented(oss);

		REQUIRE(!tree.contains(1));
		REQUIRE(!tree.contains(2));
		REQUIRE(!tree.contains(5));
		REQUIRE(oss.str() == ".\n");
	}

	SECTION("Destruct multiple times") {
		avlTree<int> tree = make_easy_test_tree();
		tree.~avlTree();
		tree.~avlTree();
		tree.~avlTree();
		ostringstream oss;
		tree.show_indented(oss);

		REQUIRE(!tree.contains(1));
		REQUIRE(!tree.contains(2));
		REQUIRE(!tree.contains(5));
		REQUIRE(oss.str() == ".\n");
	}
}

TEST_CASE("contains", "[avlTree]") {

	SECTION("Empty tree") {
		avlTree<int> tree;
		int key = 42;

		REQUIRE(!tree.contains(key));
	}

	SECTION("Easy tree contains key") {
		avlTree<int> tree = make_easy_test_tree();
		int key = 3;

		REQUIRE(tree.contains(key));
	}

	SECTION("Easy tree does not contain key") {
		avlTree<int> tree = make_easy_test_tree();
		int key = 11;

		REQUIRE(!tree.contains(key));
	}
}

TEST_CASE("min", "[avlTree]") {

	SECTION("Throws for empty tree") {
		avlTree<int> tree;
		REQUIRE_THROWS(tree.min());
	}

	SECTION("Easy tree") {
		avlTree<int> tree = make_easy_test_tree();
		REQUIRE(tree.min() == 1);
	}
}

TEST_CASE("max", "[avlTree]") {

	SECTION("Throws for empty tree") {
		avlTree<int> tree;
		REQUIRE_THROWS(tree.min());
	}

	SECTION("Easy tree") {
		avlTree<int> tree = make_easy_test_tree();
		REQUIRE(tree.max() == 10);
	}
}

TEST_CASE("erase_min", "[avlTree]") {

	SECTION("Erase min into empty tree") {
		avlTree<int> tree;
		REQUIRE_THROWS(tree.erase_min());
	}

	SECTION("Erase min key into easy tree") {
		avlTree<int> tree = make_easy_test_tree();
		tree.erase_min();

		ostringstream oss;
		tree.show_indented(oss);

		REQUIRE(tree.min() == 2);
		REQUIRE(oss.str() == "6\n"
									"|_ 3\n"
									"|  |_ 2\n"
									"|  |_ 4\n"
									"|     |_ .\n"
									"|     |_ 5\n"
									"|_ 9\n"
									"   |_ 7\n"
									"   |  |_ .\n"
									"   |  |_ 8\n"
									"   |_ 10\n");
	}
}

TEST_CASE("erase_max", "[avlTree]") {

	SECTION("Erase max into empty tree") {
		avlTree<int> tree;
		REQUIRE_THROWS(tree.erase_max());
	}

	SECTION("Erase max key into easy tree") {
		avlTree<int> tree = make_easy_test_tree();
		tree.erase_max();

		ostringstream oss;
		tree.show_indented(oss);

		REQUIRE(tree.max() == 9);
		REQUIRE(oss.str() == "6\n"
									"|_ 3\n"
									"|  |_ 2\n"
									"|  |  |_ 1\n"
									"|  |  |_ .\n"
									"|  |_ 4\n"
									"|     |_ .\n"
									"|     |_ 5\n"
									"|_ 8\n"
									"   |_ 7\n"
									"   |_ 9\n");
	}
}

TEST_CASE("erase", "[avlTree]") {

	SECTION("Erase into empty tree") {
		avlTree<int> tree;
		tree.erase(42);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == ".\n");
	}

	SECTION("Erase non-existent key into easy tree") {
		avlTree<int> tree = make_easy_test_tree();
		tree.erase(11);
		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "6\n"
									"|_ 3\n"
									"|  |_ 2\n"
									"|  |  |_ 1\n"
									"|  |  |_ .\n"
									"|  |_ 4\n"
									"|     |_ .\n"
									"|     |_ 5\n"
									"|_ 9\n"
									"   |_ 7\n"
									"   |  |_ .\n"
									"   |  |_ 8\n"
									"   |_ 10\n");
	}

	SECTION("Erase existing key into easy tree") {
		avlTree<int> tree = make_easy_test_tree();
		tree.erase(8);
		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "6\n"
									"|_ 3\n"
									"|  |_ 2\n"
									"|  |  |_ 1\n"
									"|  |  |_ .\n"
									"|  |_ 4\n"
									"|     |_ .\n"
									"|     |_ 5\n"
									"|_ 9\n"
									"   |_ 7\n"
									"   |_ 10\n");
	}
}

TEST_CASE("height", "[avlTree]") {

	SECTION("Empty Tree") {
		avlTree<int> tree;
		REQUIRE(tree.height() == 0);
	}

	SECTION("Easy tree") {
		avlTree<int> tree = make_easy_test_tree();
		REQUIRE(tree.height() == 4);
	}

	SECTION("Tree with one element added") {
		avlTree<int> tree;
		REQUIRE(tree.height() == 0);

		tree.insert(1);
		REQUIRE(tree.height() == 1);
	}

	SECTION("Tree with one element erased") {
		avlTree<int> tree;
		tree.insert(1);
		REQUIRE(tree.height() == 1);

		tree.erase(1);
		REQUIRE(tree.height() == 0);
	}
}

TEST_CASE("display_indented", "[avlTree]") {

	SECTION("Empty tree") {
		avlTree<int> tree;

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == ".\n");
	}

	SECTION("Easy test tree") {
		avlTree<int> tree = make_easy_test_tree();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "6\n"
									"|_ 3\n"
									"|  |_ 2\n"
									"|  |  |_ 1\n"
									"|  |  |_ .\n"
									"|  |_ 4\n"
									"|     |_ .\n"
									"|     |_ 5\n"
									"|_ 9\n"
									"   |_ 7\n"
									"   |  |_ .\n"
									"   |  |_ 8\n"
									"   |_ 10\n");
	}
}

TEST_CASE("rebalance", "[avlTree]") {

	SECTION("Insert elements and rebalance") {
		avlTree<int> tree;
		tree.insert(1);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "1\n");

		ostringstream oss2;
		tree.insert(2);
		tree.show_indented(oss2);
		REQUIRE(oss2.str() == "1\n"
									 "|_ .\n"
									 "|_ 2\n");

		ostringstream oss3;
		tree.insert(3);
		tree.show_indented(oss3);
		REQUIRE(oss3.str() == "2\n"
									 "|_ 1\n"
									 "|_ 3\n");

		ostringstream oss4;
		tree.insert(4);
		tree.insert(5);
		tree.insert(6);
		tree.insert(7);
		tree.show_indented(oss4);
		REQUIRE(oss4.str() == "4\n"
									 "|_ 2\n"
									 "|  |_ 1\n"
									 "|  |_ 3\n"
									 "|_ 6\n"
									 "   |_ 5\n"
									 "   |_ 7\n");
	}

	SECTION("Delete element and needs rebalance") {
		avlTree<int> tree;
		for (int i : {8, 3, 10, 2, 5, 9, 11, 1, 4, 7, 12, 6}) {
			tree.insert(i);
		}

		tree.erase(9);

		ostringstream oss;
		oss << tree;
		REQUIRE(
			oss.str() == "5(3(2(1(.,.),.),4(.,.)),8(7(6(.,.),.),11(10(.,.),12(.,.))))"
		);
	}
}