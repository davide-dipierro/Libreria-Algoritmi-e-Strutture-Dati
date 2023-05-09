
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
void inline MappableContainer<Data>::Fold(FoldFunctor func, void* acc) const { // Override di Fold con Map
    Map( // Vengono iterati tutti gli elementi del container attraverso Map
        [&func, &acc](const Data& dat) {
            func(dat, acc); // Ciascun elemento (dat) viene passato alla FoldFunctor func e il risultato ottenuto in acc
        }
    ); // Map richiede un solo parametro
}

template <typename Data>
void inline PreOrderMappableContainer<Data>::PreOrderFold(FoldFunctor func, void* acc) const { // Override di PreOrderFold con PreOrderMap
    PreOrderMap( // Vengono iterati tutti gli elementi del container attraverso PreOrderMap
        [&func, &acc](const Data& dat) {
            func(dat, acc); // Ciascun elemento (dat) viene passato alla FoldFunctor func e il risultato ottenuto in acc
        }
    ); // Map richiede un solo parametro
}

template <typename Data>
void inline PostOrderMappableContainer<Data>::PostOrderFold(FoldFunctor func, void* acc) const { // Override di PostOrderFold con PostOrderMap
    PostOrderMap( // Vengono iterati tutti gli elementi del container attraverso PostOrderMap
        [&func, &acc](const Data& dat) {
            func(dat, acc); // Ciascun elemento (dat) viene passato alla FoldFunctor func e il risultato ottenuto in acc
        }
    ); // Map richiede un solo parametro
}

template <typename Data>
void InOrderMappableContainer<Data>::InOrderFold(FoldFunctor func, void* acc) const { 
    InOrderMap(
        [&func, &acc](const Data& dat) {
            func(dat, acc);
        }
    );
}

template <typename Data>
void BreadthMappableContainer<Data>::BreadthFold(FoldFunctor func, void* acc) const { 
    BreadthMap(
        [&func, &acc](const Data& dat) {
            func(dat, acc);
        }
    );
}

/* ************************************************************************** */

}
