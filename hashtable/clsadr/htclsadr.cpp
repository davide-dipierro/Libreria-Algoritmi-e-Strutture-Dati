#include "htclsadr.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize) {
    vecSize = nextPow(newSize);
    vec = new List<Data>[vecSize] {};
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const MappableContainer<Data> &other) {
    vecSize =  nextPow(other.Size());
    vec = new List<Data>[vecSize] {};
    InsertAll(other);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, const MappableContainer<Data> &other) {
    vecSize = nextPow(newSize);
    vec = new List<Data>[vecSize] {};
    InsertAll(other);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MutableMappableContainer<Data> &&other) noexcept {
    vecSize = nextPow(other.Size());
    vec = new List<Data>[vecSize] {};
    InsertAll(std::move(other));
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, MutableMappableContainer<Data> &&other) noexcept {
    vecSize = nextPow(newSize);
    vec = new List<Data>[vecSize] {};
    InsertAll(std::move(other));
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data> &other) {
    vecSize = other.vecSize;
    vec = new List<Data>[vecSize] {};
    for(ulong i{0}; i<vecSize; i++) InsertAll(other.vec[i]);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data> &&other) noexcept {
    std::swap(size, other.size);
    std::swap(vec, other.vec);
    std::swap(vecSize, other.vecSize);
}

template <typename Data>
HashTableClsAdr<Data>::~HashTableClsAdr() {
    delete [] vec;
}

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr &other) {
    // Clear();
    delete [] vec;
    vecSize = other.vecSize;
    vec = new List<Data>[vecSize] {};
    for(ulong i{0}; i<vecSize; i++) InsertAll(other.vec[i]);
    return *this;
}

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr &&other) noexcept {
    std::swap(size, other.size);
    std::swap(vec, other.vec);
    std::swap(vecSize, other.vecSize);
    return *this;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr &other) const noexcept {
    if(other.size!=size) return false;
    bool result=true;
    for(int i{0}; i<vecSize; i++){
        vec[i].Map(
            [&other, &result](const Data& dat){
                result&=other.Exists(dat);
            }
        );
        if(!result) return false;
    }
    return true;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data &val) {
    // std::cout<<"\nCHIAMA & \n";
    bool result = false;
    ulong index = this->HashKey(Hashable<Data>()(val));
    result = vec[index].List<Data>::Insert(val);
    if(result) size++;

    return result;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data &&val) {
    // std::cout<<"\nCHIAMA && \n";
    bool result = false;
    ulong index = this->HashKey(Hashable<Data>()(val));
    result = vec[index].List<Data>::Insert(std::move(val));
    if(result) size++;

    return result;
}


template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data &val) {
    bool result = false;
    ulong index = this->HashKey(Hashable<Data>()(val));
    
    result = vec[index].List<Data>::Remove(val);
    if(result) size--;

    return result;
}

template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data &dat) const noexcept {
    ulong index = this->HashKey(Hashable<Data>()(dat));
    return vec[index].List<Data>::Exists(dat);
}

template <typename Data>
void HashTableClsAdr<Data>::Resize(const ulong n) {
    size = 0;
    ulong tempSize = nextPow(n);
    List<Data>* tempVec = new List<Data>[tempSize] {};
    std::swap(tempVec, vec);
    std::swap(tempSize, vecSize);
    for(ulong i{0}; i<tempSize; i++) InsertAll(tempVec[i]);
    delete [] tempVec;
}

template <typename Data>
inline void HashTableClsAdr<Data>::Clear() {
    for(int i{0}; i<vecSize; i++) vec[i].List<Data>::Clear();
    size = 0;
}



/* ************************************************************************** */

}
