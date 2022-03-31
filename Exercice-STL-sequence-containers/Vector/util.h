#ifndef ASD1_LABS_2020_UTIL_H
#define ASD1_LABS_2020_UTIL_H

#include <iostream>      // std::cout
#include <ostream>       // std::ostream
#include <string>        // std::string
#include <type_traits>   // std::is_same

class C {
    friend std::ostream& operator<<(std::ostream& s, const C& v);
    int _i;
public:
    C(int i = -42);
    C(const C& c);
    C& operator= (const C& other);
    C(C&& c);
    C& operator= (C&& other) noexcept;
    ~C();
    bool operator==(const C& other) const noexcept;
    int operator%(int m) const noexcept;
    bool operator<(const C& other) const noexcept;
    bool operator>(const C& other) const noexcept;
    bool operator<=(const C& other) const noexcept;
    bool operator>=(const C& other) const noexcept;
};

std::ostream& operator<<(std::ostream& s, const C& v);

// n'affiche le message que si T est C
template < typename T >
void message(const std::string& s) {
    if(std::is_same<T,C>::value)
        std::cout << s;
}

#endif //ASD1_LABS_2020_UTIL_H
