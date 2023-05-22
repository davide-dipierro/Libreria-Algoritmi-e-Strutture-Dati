#include "htopnadr.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize) {
    vecSize = nextPow(newSize);
    Elements = new Data[vecSize] {};
    Bits = new std::bitset<2>[vecSize] {};
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const MappableContainer<Data> &other) {
    vecSize = nextPow(other.Size()*2);
    Elements = new Data[vecSize] {};
    Bits = new std::bitset<2>[vecSize] {};
    InsertAll(other);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, const MappableContainer<Data> &other) {
    vecSize = nextPow(newSize);
    Elements = new Data[vecSize] {};
    Bits = new std::bitset<2>[vecSize] {};
    InsertAll(other);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(MutableMappableContainer<Data>&& other) noexcept {
    vecSize = nextPow(other.Size()*2);
    Elements = new Data[vecSize] {};
    Bits = new std::bitset<2>[vecSize] {};
    InsertAll(std::move(other));
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, MutableMappableContainer<Data> &&other) noexcept {
    vecSize = nextPow(newSize);
    Elements = new Data[vecSize] {};
    Bits = new std::bitset<2>[vecSize] {};
    InsertAll(std::move(other));
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data> &other) {
    vecSize = other.vecSize;
    Elements = new Data[vecSize] {};
    Bits = new std::bitset<2>[vecSize] {};
    for(ulong i{0}; i<vecSize; i++) if(other.Bits[i].all()) Insert(other.Elements[i]);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data> &&other) noexcept {
    std::swap(vecSize, other.vecSize);
    std::swap(Elements, other.Elements);
    std::swap(Bits, other.Bits);
    std::swap(size, other.size);
}

template <typename Data>
HashTableOpnAdr<Data>::~HashTableOpnAdr() {
    delete [] Bits;
    delete [] Elements; 
}

template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr &other) {
    delete [] Bits;
    delete [] Elements; 
    vecSize = other.vecSize;
    Elements = new Data[vecSize] {};
    Bits = new std::bitset<2>[vecSize] {};
    for(ulong i{0}; i<vecSize; i++) if(other.Bits[i].all()) Insert(other.Elements[i]);
    return *this;
}

template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr &&other) noexcept {
    std::swap(vecSize, other.vecSize);
    std::swap(Elements, other.Elements);
    std::swap(Bits, other.Bits);
    std::swap(size, other.size);
    return *this;
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr &other) const noexcept {
    if(size!=other.Size()) return false;
    for(ulong i{0}; i<vecSize; i++){
        if(other.Bits[i].all()){
            if(!other.Exists(Elements[i])) return false;
        }
    }
    return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& dat) {
    if(size*2>=vecSize) Resize(vecSize*2);
    ulong index = HashKey(Hashable<Data>()(dat));
    index = FindEmpty(index, dat);
    if(Bits[index][valid_bit]==0){
        Elements[index] = dat;
        Bits[index].set();
        size++;
        return !Remove(index, dat); 
    }
    return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& dat) {
    if(size*2>=vecSize) Resize(vecSize*2);
    ulong index = HashKey(Hashable<Data>()(dat));
    index = FindEmpty(index, dat);
    if(Bits[index][valid_bit]==0){
        std::swap(Elements[index], dat);
        Bits[index].set();
        size++;
        return !Remove(index, dat); 
    }
    return false; 
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data &dat) {
    if(size<vecSize/5) Resize(vecSize/2);
    ulong index = HashKey(Hashable<Data>()(dat));
    if(Bits[index].all() && Elements[index] == dat){
        Bits[index][valid_bit]=0;
        size--;
        return true;
    }
    return Remove(index, dat);
}

template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data &dat) const noexcept {
    ulong index = HashKey(Hashable<Data>()(dat));
    return Find(index, dat);
}

template <typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong newSize) {
    ulong tmpvecSize = nextPow(newSize);
    Data* tmpElements = new Data[tmpvecSize] {};
    std::bitset<2>* tmpBits = new std::bitset<2>[tmpvecSize] {};

    std::swap(tmpvecSize, vecSize);
    std::swap(tmpElements, Elements);
    std::swap(tmpBits, Bits);

    size = 0;
    for(int i{0}; i<tmpvecSize; i++){
        if(tmpBits[i].all()) Insert(tmpElements[i]);
    }
    delete [] tmpElements;
    delete [] tmpBits;
}

template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
    for(int i{0}; i<vecSize; i++) Bits[i][valid_bit]=0;
    size=0;
}

template <typename Data>
ulong HashTableOpnAdr<Data>::HashKey(const ulong index, ulong &prob_index, const ulong key) const noexcept {
    return (index+(++prob_index))%vecSize;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Find(ulong& index, const Data &dat) const noexcept {
    ulong prob_index = 0;
    ulong tmp_index = index;
    do{
        if(prob_index == vecSize-1) return false;
        if(Elements[tmp_index]==dat && Bits[tmp_index].all()) {
            index=tmp_index;
            return true;
        }
        tmp_index = HashKey(index, prob_index, Hashable<Data>()(dat));
    }while(!Bits[tmp_index].none());
    return false;
}

template <typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(const ulong index, const Data &dat) noexcept {
    ulong prob_index = 0;
    ulong tmp_index = index;
    while(Bits[tmp_index].all() && Elements[tmp_index]!=dat) {   
        tmp_index = HashKey(index, prob_index, Hashable<Data>()(dat));
    }
    return tmp_index;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(ulong index, const Data &dat) {
    ulong prob_index = 0;
    ulong tmp_index = index;
    tmp_index = HashKey(index, prob_index, Hashable<Data>()(dat));
    if(Find(tmp_index, dat)){
        Bits[tmp_index][valid_bit]=0;
        size--;
        return true;
    }
    return false;
}

template <typename Data>
void HashTableOpnAdr<Data>::CheckDirtyBit() {
    bool result = true;
    for(int i{0}; i<vecSize; i++) result&=Bits[i][full_bit] == 1;
    if(result) std::cout<<"RIEMPITO";
}

/* ************************************************************************** */
}
