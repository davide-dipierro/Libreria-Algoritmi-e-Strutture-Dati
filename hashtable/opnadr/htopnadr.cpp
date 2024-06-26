#include "htopnadr.hpp"

#include <functional>

namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize) {
    vecSize = nextPow(newSize);
    Elements = new Data[vecSize] {};
    Bits = new std::bitset<2>[vecSize] {};
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const MappableContainer<Data> &other) : HashTableOpnAdr(other.Size()*2) {
    InsertAll(other);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, const MappableContainer<Data> &other) : HashTableOpnAdr(newSize) {
    InsertAll(other);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(MutableMappableContainer<Data>&& other) noexcept : HashTableOpnAdr(other.Size()*2) {
    InsertAll(std::move(other));
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, MutableMappableContainer<Data> &&other) noexcept : HashTableOpnAdr(newSize)  {
    InsertAll(std::move(other));
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data> &other) : HashTable<Data>(other) {
    Elements = new Data[vecSize] {};
    Bits = new std::bitset<2>[vecSize] {};
    for(ulong i{0}; i<vecSize; i++) {
        Elements[i]=other.Elements[i];
        Bits[i][0]=other.Bits[i][0];
        Bits[i][1]=other.Bits[i][1];
    }
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data> &&other) noexcept : HashTable<Data>(std::move(other)) {
    std::swap(Elements, other.Elements);
    std::swap(Bits, other.Bits);
}

template <typename Data>
HashTableOpnAdr<Data>::~HashTableOpnAdr() {
    delete [] Bits;
    delete [] Elements; 
}

template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr &other) {
    HashTable<Data>::operator=(other);
    delete[] Elements;
    delete[] Bits;
    Elements = new Data[vecSize]{};
    Bits = new std::bitset<2>[vecSize]{};
    for (ulong i = 0; i < vecSize; i++) {
        Elements[i] = other.Elements[i];
        Bits[i][0] = other.Bits[i][0];
        Bits[i][1] = other.Bits[i][1];
    }
    return *this;

    // //std::cout<<"\nOPERATOR=";
    // HashTableOpnAdr* tmp = new HashTableOpnAdr(other);
    // std::swap(*this, *tmp);
    // delete tmp;
    // return *this;
}

template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr &&other) noexcept {
    HashTable<Data>::operator=(std::move(other));
    std::swap(Elements, other.Elements);
    std::swap(Bits, other.Bits);
    return *this;
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr &other) const noexcept {
    if(size!=other.Size()) return false;
    for(ulong i{0}; i<vecSize; i++){
        if(Bits[i].all()){
            if(!other.Exists(Elements[i])) return false;
        }
    }
    return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& dat) {
    ulong prob_index = 0;
    if(size*2>=vecSize) Resize(vecSize*2);
    ulong tmp_index = FindEmpty(dat, prob_index);
    if(Bits[tmp_index][valid_bit]==0){
        Elements[tmp_index] = dat;
        if(Bits[tmp_index][full_bit]==1) holes--;
        Bits[tmp_index].set();
        size++;
        return !Remove(Elements[tmp_index], ++prob_index); 
    }
    prob_index = 0;
    return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& dat) {
    ulong prob_index = 0;
    if(size*2>=vecSize) Resize(vecSize*2);
    ulong tmp_index = FindEmpty(dat, prob_index);
    if(Bits[tmp_index][valid_bit]==0){
        std::swap(Elements[tmp_index], dat);
        if(Bits[tmp_index][full_bit]==1) holes--;
        Bits[tmp_index].set();
        size++;
        return !Remove(Elements[tmp_index], ++prob_index); 
    }
    prob_index = 0;
    return false; 
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data &dat) {
    ulong prob_index = 0;
    return Remove(dat, prob_index);
}

template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data &dat) const noexcept {
    ulong prob_index = 0;
    ulong index = HashKey(Hashable<Data>()(dat));
    return Find(index, dat, prob_index);
}

template <typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong newSize) {
    ulong tmpVecSize = (newSize<this->Size()) ? nextPow(this->Size()) : nextPow(newSize);

    // **** PIU' VELOCE ****
    Data* tmpElements = new Data[tmpVecSize] {};
    std::bitset<2>* tmpBits = new std::bitset<2>[tmpVecSize] {};

    std::swap(tmpVecSize, vecSize);
    std::swap(tmpElements, Elements);
    std::swap(tmpBits, Bits);

    size = 0; holes = 0;
    for(ulong i{0}; i<tmpVecSize; i++){
        if(tmpBits[i].all()) Insert(tmpElements[i]);
    }
    delete [] tmpElements;
    delete [] tmpBits;

    // **** MOLTO MENO VELOCE ****
    // HashTableOpnAdr<Data>* tmp = new HashTableOpnAdr<Data>(newSize, *this);
    // std::swap(*tmp, *this);
    // delete tmp;
}

template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
    for(ulong i{0}; i<vecSize; i++) Bits[i][valid_bit]=0;
    size=0;
}

template <typename Data>
ulong HashTableOpnAdr<Data>::HashKey(const Data &dat, ulong& prob_index) const noexcept {
    // return (index+(++prob_index))%vecSize;
    return (HashKey(Hashable<Data>()(dat))+(((prob_index*prob_index)+prob_index)/2)+vecSize)%vecSize;
    // return static_cast<long>(std::hash<ulong>{}(key))%vecSize;
    // return (HashKey(Hashable<Data>()(dat))+1)%vecSize;
    // return (index+ (hash*prob_index))%vecSize;

}

template <typename Data>
bool HashTableOpnAdr<Data>::Find(ulong& index, const Data &dat, ulong& prob_index) const noexcept {
    ulong tmp_index = HashKey(dat, prob_index);
    ulong jumps = 0;
    ulong aviable_swap_index;
    bool aviable_swap_find = false;
    do {
        if(jumps == vecSize-1) return false;
        if(Elements[tmp_index]==dat && Bits[tmp_index].all()) {
            if(aviable_swap_find){
                Elements[aviable_swap_index]=Elements[tmp_index];
                std::swap(Bits[aviable_swap_index], Bits[tmp_index]);
                index=aviable_swap_index;
            }else{
                index=tmp_index;
            }
            return true;
        }
        if(Bits[tmp_index][valid_bit]==0 && !aviable_swap_find) {
            aviable_swap_index = tmp_index;  
            aviable_swap_find = true;
        }
        tmp_index = HashKey(dat, ++prob_index); jumps++;
    }while(!Bits[tmp_index].none());
    return false;
}

template <typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(const Data &dat, ulong& prob_index) noexcept {
    ulong tmp_index = HashKey(dat, prob_index);
    while(Bits[tmp_index].all() && Elements[tmp_index]!=dat) {
        tmp_index = HashKey(dat, ++prob_index);
    }
    return tmp_index;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data &dat, ulong& prob_index) {
    ulong tmp_index;
    if(Find(tmp_index, dat, prob_index)){
        Bits[tmp_index][valid_bit]=0;
        holes++;
        size--;
        prob_index = 0;
        if(size<vecSize/5 && vecSize>HASHTABLE_INIT_SIZE) Resize(vecSize/2);
        if(holes>vecSize/3) Resize(vecSize);
        return true;
    }
    prob_index = 0;
    return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::CheckDirtyBit() {
    bool result = true;
    for(ulong i{0}; i<vecSize; i++) result&=Bits[i][full_bit] == 1;
    return result;
}

template <typename Data>
void HashTableOpnAdr<Data>::printTable() const {
    std::cout<<std::endl;
    for(ulong i{0}; i<vecSize; i++){
        std::cout<<"Bits["<<i<<"][0]="<<Bits[i][0]<<"\t["<<i<<"][0]="<<Bits[i][1]<<"\tElements: "<<Elements[i]<<std::endl;
    }
}

/* ************************************************************************** */
}
