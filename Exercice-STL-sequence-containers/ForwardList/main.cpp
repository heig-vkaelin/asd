//IN 0
//IN 1
//IN 2
//IN 3
//IN 4
//IN 5

#include <iostream>          // std::cout, std::cin
#include <initializer_list>  // std::initializer_list<T>
#include "util.h"            // class C, message<T>
#include "tripartite.h"      // tripartite, CONTAINER

template <typename T>
void display(CONTAINER<T> const& v) {
    std::cout << "{";
    for(auto i = v.begin(); i != v.end(); ++i) {
        if(i != v.begin())
            std::cout << ",";
        std::cout << " " << *i ;
    }
    std::cout << " }";
}

template <typename T>
void codecheck( std::initializer_list<T> init ) {
    {
        message<T>("\nConstruction de v : ");
        CONTAINER<T> v{init};
        message<T>("\n");
        std::cout << "v in  : ";
        display(v);
        {
            message<T>("\nFonction tripartite : ");
            CONTAINER<T> w = tripartite(v);
            std::cout << "\nv out : ";
            display(v);
            std::cout << "\nw out : ";
            display(w);
            message<T>("\nDestruction de w : ");
        }
        message<T>("\nDestruction de v : ");
    }
    message<T>("\nDestruction de init : ");
}

int main() {
    int i;
    std::cin >> i;

    switch(i) {
        case 0: {
            codecheck<int>({ 2, 1, 5, 6, 8, 7, 3, 9, 4, 3, 6, 7, 8, 7, 9, 4, 1 });
            break;
        }
        case 1: {
            codecheck<int>({ 1, 4, 6, 2, 3, 3, 6, 9, 1, 2 });
            break;
        }
        case 2: {
            codecheck<int>({ 3, 3, 2, 3, 6, 8, 5, 9, 9 });
            break;
        }
        case 3: {
            codecheck<C>({ 2, 1, 5, 6, 8, 7, 3, 9, 4, 3, 6, 7, 8, 7, 9, 4, 1 });
            break;
        }
        case 4: {
            codecheck<C>({ 1, 4, 6, 2, 3, 3, 6, 9, 1, 2 });
            break;
        }
        case 5: {
            codecheck<C>({ 3, 3, 2, 3, 6, 8, 5, 9, 9 });
            break;
        }
        default:
            std::cout << "Unknown CC test\n";
    }
}