#include <iostream>
using std::cout;
using std::endl;

#include "util.h"

C::C(int i) : _i(i) {
    cout << "I(" << _i << ") ";
}

C::C(const C& c) : _i(c._i) {
    cout << "C(" << _i << ") ";
}

C& C::operator= (const C& other) {
    _i = other._i;
    cout << "=(" << _i << ") ";
    return *this;
}

C::C(C&& other) : _i(other._i) {
    other._i = -1;
    cout << "M(" << _i << ") ";
}

C& C::operator= (C&& other) noexcept {
    if(this != &other) {
        _i = other._i;
        other._i = -1;
    }
    cout << "m(" << _i << ") ";
    return *this;
}

C::~C() {
    if(_i == -1) cout << "D(moved) ";
    else cout << "D(" << _i << ") ";
}

bool C::operator==(const C& other) const noexcept {
    return other._i == _i;
}

int C::operator%(int m) const noexcept {
    return _i % m;
}

bool C::operator<(const C& other) const noexcept {
    return _i < other._i;
}

bool C::operator>(const C& other) const noexcept {
    return other < *this;
}

bool C::operator<=(const C& other) const noexcept {
    return not(other < *this);
}

bool C::operator>=(const C& other) const noexcept {
    return not(*this < other);
}

std::ostream& operator<<(std::ostream& s, const C& c) {
    s << c._i;
    return s;
}
