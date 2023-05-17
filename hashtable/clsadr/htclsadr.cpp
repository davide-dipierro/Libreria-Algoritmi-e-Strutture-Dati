#include "htclsadr.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize) {
    vecSize = newPow(newSize);
    vec = new List*[vecSize] {};
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const MappableContainer<Data> &other) {
    vecSize = newPow(other.Size());
    vec = new List*[vecSize] {};
    InsertAll(other);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, const MappableContainer<Data> &other) {
    vecSize = newPow(newSize);
    vec = new List*[vecSize] {};
    InsertAll(other);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MutableMappableContainer<Data> &&other) noexcept {
    vecSize = newPow(other.Size());
    vec = new List*[vecSize] {};
    InsertAll(std::move(other));
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, MutableMappableContainer<Data> &&other) noexcept {
    vecSize = newPow(newSize);
    vec = new List*[vecSize] {};
    InsertAll(std::move(other));
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data> &other) {
    vecSize = other.vecSize;
    vec = new List*[vecSize] {};
    for(ulong i{0}; i<vecSize; i++) if(other.vec[i]!=nullptr) InsertAll(*other.vec[i]);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data> &&other) noexcept {
    vecSize = other.vecSize;
    vec = new List*[vecSize] {};
    std::swap(this->size, other.Size());
    this->size = 0;
    for(ulong i{0}; i<vecSize; i++) if(other.vec[i]!=nullptr) InsertAll(std::move(*other.vec[i]));
}

template <typename Data>
HashTableClsAdr<Data>::~HashTableClsAdr() {
    Clear();
}

template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr &other) const noexcept {
    return true;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data &val) {
    bool resut = false;
    index = HashKey(Hashable<int>::val());
    if(vec[index]==nullptr) vec[i] = new List<Data>();
    
    result = vec[i].Insert(val);
    if(result) size++;

    return result;


}

template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data &val) const noexcept {
    for(ulong i{0}; i<vecSize; i++) if(vec[i].Exists(val)) return true;
    return false;
}

template <typename Data>
void HashTableClsAdr<Data>::Resize(const ulong n) {
    tempSize = nextPow(n);
    tempVec = new List*[tempSize] {};
    std::swap(tempVec, vec);
    for(ulong i{0}; i<vecSize; i++){
        if(tempVec[i]!=nullptr) InsertAll(tempVec[i]);
    }
    for(int i{0}; i<vecSize; i++) delete tempVec[i];
    vecSize = tempSize;
}

template <typename Data>
inline void HashTableClsAdr<Data>::Clear() {
    for (int i{0}; i<vecSize; i++) delete vec[i];
}

void nextPow(unsigned int num) {
    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    return num + 1;
}



/* ************************************************************************** */

}
