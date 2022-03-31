/*
-----------------------------------------------------------------------------------
Nom du fichier : some_bits.h
Auteur(s)      : Olivier Cuisenaire
Date creation  : 22.03.2021
Description    :
Remarque(s)    :
Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#ifndef SOME_BITS
#define SOME_BITS

template<typename T>
class SomeBits {
    size_t shift;
    T mask;
public:
    SomeBits(size_t nombreDeBits, size_t part)
            : shift(part * nombreDeBits),
              mask((T(1u) << nombreDeBits) - T(1u)) {

    }
    T operator()(T const& t) {
        return T(mask & (t >> shift));
    }
};

#endif
