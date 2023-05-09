
#include <stdexcept>
#include <iostream>
/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */  //CLASS LINEAR

template<typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer& other) const noexcept {
    if(size!=other.size) return false;
    for(ulong i=0; i<size; i++) if(operator[](i)!=other[i]) return false;
    return true;
}

/* ************************************************************************** */

template<typename Data>
const Data& LinearContainer<Data>::Front() const {
    if(!this->Empty()) return this->operator[](0);  
    else throw std::length_error("LinearContainer: the vector is empty in Front()");
}

template<typename Data>
Data& LinearContainer<Data>::Front() {
    if(!this->Empty()) return this->operator[](0);  
    else throw std::length_error("LinearContainer: the vector is empty in Front()");
}

template<typename Data>
const Data& LinearContainer<Data>::Back() const {
    if(!this->Empty()) return this->operator[](size-1);  
    else throw std::length_error("LinearContainer: the vector is empty in Back()");
}

template<typename Data>
Data& LinearContainer<Data>::Back() {
    if(!this->Empty()) return this->operator[](size-1);  
    else throw std::length_error("LinearContainer: the vector is empty in Back()");
}

template <typename Data>
void LinearContainer<Data>::PreOrderMap(MapFunctor func) const {
    for(ulong i=0; i<size; i++) func(this->operator[](i));
}

/* ************************************************************************** */

template <typename Data>
void LinearContainer<Data>::PostOrderMap(const MapFunctor func) const {
    ulong i = size;
    while (i>0) func(operator[](--i));
}

template <typename Data>
void LinearContainer<Data>::PreOrderMap(MutableMapFunctor func) {
    for(ulong i=0; i<size; i++) func(operator[](i));
}

template <typename Data>
void LinearContainer<Data>::PostOrderMap(MutableMapFunctor func){
    ulong i = size;
    while (i>0) func(operator[](--i));
}

/* ************************************************************************** */    //CLASS SORTABLE

template<typename Data>
ulong SortableLinearContainer<Data>::Partition(ulong p, ulong r) noexcept {
    Data x = this->operator[](p);
    ulong i = p - 1;
    ulong j = r + 1;
    
    do {
        do { j--; } while ( x < this->operator[](j) );
        do { i++; } while ( this->operator[](i) < x );
        if (i < j) { std::swap(this->operator[](i), this->operator[](j)); }
    } while (i < j);

    return j;
}

template<typename Data>
void SortableLinearContainer<Data>::QuickSort(ulong p, ulong r) noexcept {
    if (p < r) {
    ulong q = Partition(p, r);
    QuickSort(p, q);
    QuickSort(q + 1, r);
  }
}

/* ************************************************************************** */

}
