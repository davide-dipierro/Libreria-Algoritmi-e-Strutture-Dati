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
    for(ulong i{0}; i<vecSize; i++) if(other.Bits[i][full_bit]&&other.Bits[i][valid_bit]) Insert(other.Elements[i]);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data> &&other) noexcept {
    std::swap(vecSize, other.vecSize);
    std::swap(Elements, other.Elements);
    std::swap(Bits, other.Bits);
    std::swap(size, other.size);
}

template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr &other) {
    Clear();
    vecSize = other.vecSize;
    Elements = new Data[vecSize] {};
    Bits = new std::bitset<2>[vecSize] {};
    for(ulong i{0}; i<vecSize; i++) if(other.Bits[i][full_bit]&&other.Bits[i][valid_bit]) Insert(other.Elements[i]);
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
    // for(ulong i{0}; i<vecSize; i++){
    //     if(other.Bits[i].all()){
    //         if(!other.Exists(Elements[i])) return false;
    //     }
    // }
    return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& dat) {
    ulong index = HashKey(Hashable<Data>()(dat));
    if(Bits[index].none()){
        std::cout<<"\nKEBAB CIPOLA";
        Elements[index]=dat;
        Bits[index].set();
        size++;
        return true;
    }else{
        std::cout<<"\nKEBAB NO CIPOLA";
        FindEmpty(index, dat);
        Elements[index]=dat;
        Bits[index].set();
        if(Find(index, dat)) { 
            Bits[index][valid_bit]=0;
            return false;
        } else {
            size++;
            return true;
        }
    }
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& dat) {
    ulong index = HashKey(Hashable<Data>()(dat));
    if(Bits[index].none()){
        std::cout<<"\nKEBAB PICANTE";
        std::swap(Elements[index], dat);
        Bits[index].set();
        size++;
        return true;
    }else{
        std::cout<<"\nKEBAB NO PICANTE";
        FindEmpty(index, dat);
        std::swap(Elements[index], dat);
        Bits[index].set();
        if(Find(index, dat)) { 
            Bits[index][valid_bit]=0;
            return false;
        } else {
            size++;
            return true;
        }
    }
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data &dat) {
    ulong index = HashKey(Hashable<Data>()(dat));
    if(Find(index, dat)){
        Bits[index][valid_bit]=0;
        size--;
        return true;
    }
    return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data &dat) const noexcept {
    ulong index = HashKey(Hashable<Data>()(dat));
    return (Elements[index]==dat) ? true : Find(index, dat);
}

template <typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong newSize) {
    ulong tmpvecSize = nextPow(newSize);
    Data* tmpElements = new Data[tmpvecSize] {};
    std::bitset<2>* tmpBits = new std::bitset<2>[tmpvecSize] {};

    std::swap(tmpvecSize, vecSize);
    std::swap(tmpElements, Elements);
    std::swap(tmpBits, Bits);

    for(int i{0}; i<tmpvecSize; i++){
        if(tmpBits[i].all()) Insert(tmpElements[i]);
    }

}

template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
    // delete Elements; delete Bits;
    for(int i{0}; i<vecSize; i++) Bits[i][valid_bit]=0;
    size=0;
}

template <typename Data>
ulong HashTableOpnAdr<Data>::HashKey(ulong index, const ulong key) const noexcept {
    return (index+1)%vecSize;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Find(ulong &index, const Data &dat) const noexcept {
    index = HashKey(index, Hashable<Data>()(dat));
    if(Bits[index].none()) return false;
    if(Bits[index].all()) if(Elements[index]==dat) return true;
    return Find(index, dat);
}

template <typename Data>
bool HashTableOpnAdr<Data>::FindEmpty(ulong& index, const Data &dat) const noexcept {
    while(Bits[index][valid_bit]==1){
        index = HashKey(index, Hashable<Data>()(dat));
    }
    return true;
}

/* ************************************************************************** */
}
