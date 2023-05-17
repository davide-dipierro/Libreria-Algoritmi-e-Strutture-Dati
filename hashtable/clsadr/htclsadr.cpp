#include "htclsadr.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize) {
    vecSize = nextPow(newSize);
    vec = new List<Data>*[vecSize] {};
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const MappableContainer<Data> &other) {
    vecSize =  nextPow(other.Size());
    vec = new List<Data>*[vecSize] {};
    InsertAll(other);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, const MappableContainer<Data> &other) {
    vecSize = nextPow(newSize);
    vec = new List<Data>*[vecSize] {};
    InsertAll(other);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MutableMappableContainer<Data> &&other) noexcept {
    vecSize = nextPow(other.Size());
    vec = new List<Data>*[vecSize] {};
    InsertAll(std::move(other));
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, MutableMappableContainer<Data> &&other) noexcept {
    vecSize = nextPow(newSize);
    vec = new List<Data>*[vecSize] {};
    InsertAll(std::move(other));
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data> &other) {
    vecSize = other.vecSize;
    vec = new List<Data>*[vecSize] {};
    for(ulong i{0}; i<vecSize; i++) if(other.vec[i]!=nullptr) InsertAll(*other.vec[i]);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data> &&other) noexcept {
    vecSize = other.vecSize;
    vec = new List<Data>*[vecSize] {};
    std::swap(this->size, other.Size());
    this->size = 0;
    for(ulong i{0}; i<vecSize; i++) if(other.vec[i]!=nullptr) InsertAll(std::move(*other.vec[i]));
}

template <typename Data>
HashTableClsAdr<Data>::~HashTableClsAdr() {
    for (ulong i{0}; i<vecSize; i++) {
        delete vec[i];
    }
    delete [] vec;
}

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr &other) {
    Clear();
    vecSize = other.vecSize;
    vec = new List<Data>*[vecSize] {};
    for(ulong i{0}; i<vecSize; i++) if(other.vec[i]!=nullptr) InsertAll(*other.vec[i]);
    return *this;
}

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr &&other) noexcept {
    vecSize = other.vecSize;
    vec = new List<Data>*[vecSize] {};
    std::swap(this->size, other.size);
    this->size = 0;
    for(ulong i{0}; i<vecSize; i++) if(other.vec[i]!=nullptr) InsertAll(std::move(*other.vec[i]));
    return *this;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr &other) const noexcept {
    return true;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data &val) {
    bool result = false;
    ulong index = this->HashKey(Hashable<Data>()(val));
    if(vec[index]==nullptr) vec[index] = new List<Data>();
    
    result = vec[index]->Insert(val);
    if(result) size++;

    return result;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data &&val) {
    bool result = false;
    ulong index = this->HashKey(Hashable<Data>()(val));
    
    if(vec[index]==nullptr) vec[index] = new List<Data>();
    
    result = vec[index]->Insert(std::move(val));
    if(result) size++;

    return result;
}


template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data &val) {
    bool result = false;
    ulong index = this->HashKey(Hashable<Data>()(val));
    if(vec[index]==nullptr) return true;
    
    result = vec[index]->Remove(val);
    if(result) size--;

    return result;
}

template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data &val) const noexcept {
    for(ulong i{0}; i<vecSize; i++) {
        if(vec[i]!=nullptr) {
            if(vec[i]->Exists(val)) return true;
        }
    }
    return false;
}

template <typename Data>
void HashTableClsAdr<Data>::Resize(const ulong n) {
    if(n==0) {
        Clear();
        return; 
    }
    this->size = 0;
    ulong tempSize = nextPow(n);
    List<Data>** tempVec = new List<Data>*[tempSize] {};
    std::swap(tempVec, vec);
    std::swap(tempSize, vecSize);
    for(ulong i{0}; i<tempSize; i++){
        if(tempVec[i]!=nullptr) InsertAll(*tempVec[i]);
    }
    for(ulong i{0}; i<tempSize; i++) delete tempVec[i];
    delete [] tempVec;

}

template <typename Data>
inline void HashTableClsAdr<Data>::Clear() {
    for (ulong i{0}; i<vecSize; i++) {
        delete vec[i];
        vec[i] = nullptr;
    }
    this->size=0;
}


template <typename Data>
ulong HashTableClsAdr<Data>::nextPow(ulong num) {
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
