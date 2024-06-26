#include "htclsadr.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize) {
    vecSize = nextPow(newSize);
    vec = new List<Data>[vecSize] {};
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const MappableContainer<Data> &other) : HashTableClsAdr(other.Size()) {
    InsertAll(other);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, const MappableContainer<Data> &other) : HashTableClsAdr(newSize) {
    InsertAll(other);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MutableMappableContainer<Data> &&other) noexcept : HashTableClsAdr(other.Size()) {
    InsertAll(std::move(other));
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, MutableMappableContainer<Data> &&other) noexcept : HashTableClsAdr(newSize) {
    InsertAll(std::move(other));
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data> &other) : HashTable<Data>(other) {
    vec = new List<Data>[vecSize] {};
    for(ulong i{0}; i<vecSize; i++) vec[i]=other.vec[i];
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data> &&other) noexcept : HashTable<Data>(std::move(other)) {
    vec = new List<Data>[vecSize] {};
    std::swap(vec, other.vec);
}

template <typename Data>
HashTableClsAdr<Data>::~HashTableClsAdr() {
    delete [] vec;
}

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr &other) {
    HashTable<Data>::operator=(other);
    delete[] vec;
    vec = new List<Data>[vecSize] {};
    for (ulong i = 0; i < vecSize; i++) vec[i] = other.vec[i];
    return *this;
}

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr &&other) noexcept {
    HashTable<Data>::operator=(std::move(other));
    std::swap(vec, other.vec);
    return *this;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr &other) const noexcept {
    if(other.size!=size) return false;
    bool result=true;
    for(ulong i{0}; i<vecSize; i++){
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
    bool result = false;
    ulong index = this->HashKey(Hashable<Data>()(val));
    result = vec[index].List<Data>::Insert(val);
    if(result) size++;
    if(vec[index].Size()>((vecSize/max_dict_size)+2)) Resize(vecSize*2);
    return result;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data &&val) {
    bool result = false;
    ulong index = this->HashKey(Hashable<Data>()(val));
    result = vec[index].List<Data>::Insert(std::move(val));
    if(result) size++;
    if(vec[index].Size()>((vecSize/max_dict_size)+2)) Resize(vecSize*2);
    return result;
}


template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data &val) {
    bool result = false;
    ulong index = this->HashKey(Hashable<Data>()(val));
    
    result = vec[index].List<Data>::Remove(val);
    if(result) size--;
    if(this->Size()<vecSize/5 && vecSize>HASHTABLE_INIT_SIZE) Resize(vecSize/2);
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
    for(ulong i{0}; i<vecSize; i++) vec[i].List<Data>::Clear();
    size = 0;
}

template <typename Data>
void HashTableClsAdr<Data>::printTable() const {
    std::cout<<std::endl;
    for(ulong i{0}; i<vecSize; i++){
        std::cout<<"Array["<<i<<"]=";
        vec[i].Map(
            [](const Data& dat) {std::cout<<"\t"<<dat;}
        );
        std::cout<<std::endl;
    }
}

/* ************************************************************************** */

}
