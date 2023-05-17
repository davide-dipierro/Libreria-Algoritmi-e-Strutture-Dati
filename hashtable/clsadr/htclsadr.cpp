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
    // vecSize = other.vecSize;
    // vec = new List<Data>*[vecSize] {};
    std::swap(this->size, other.size);
    std::swap(vec, other.vec);
    std::swap(vecSize, other.vecSize);
    // this->size = 0;
    // for(ulong i{0}; i<vecSize; i++) if(other.vec[i]!=nullptr) InsertAll(std::move(*other.vec[i]));
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
    delete [] vec;
    vecSize = other.vecSize;
    vec = new List<Data>*[vecSize] {};
    for(ulong i{0}; i<vecSize; i++) if(other.vec[i]!=nullptr) InsertAll(*other.vec[i]);
    return *this;
}

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr &&other) noexcept {
    std::swap(this->size, other.size);
    std::swap(vec, other.vec);
    std::swap(vecSize, other.vecSize);
    return *this;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr &other) const noexcept {
    if(other.size!=this->size) return false;
    for(int i{0}; i<this->vecSize; i++){
        if(vec[i]!=nullptr){
            bool result=true;
            vec[i]->Map(
                [&other, &result](const Data& dat){
                    ulong index = other.HashKey(Hashable<Data>()(dat));
                    if(!other.vec[index]->Exists(dat)){
                        result = false;
                        return;
                    }
                }
            );
            if(result = false) return false;
        }
    }
    return true;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data &val) {
    // std::cout<<"\nCHIAMA & \n";
    bool result = false;
    ulong index = this->HashKey(Hashable<Data>()(val));
    if(vec[index]==nullptr) vec[index] = new List<Data>();
    
    result = vec[index]->List<Data>::Insert(val);
    if(result) size++;

    return result;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data &&val) {
    // std::cout<<"\nCHIAMA && \n";
    bool result = false;
    ulong index = this->HashKey(Hashable<Data>()(std::move(val)));
    // std::cout<<"\nindex: "<<index<<"\t sizevec: "<<this->vecSize<<"\t size: "<<this->size<<"\n";
    
    if(vec[index]==nullptr) vec[index] = new List<Data>();
    
    result = vec[index]->List<Data>::Insert(std::move(val));
    if(result) size++;

    return result;
}


template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data &val) {
    bool result = false;
    ulong index = this->HashKey(Hashable<Data>()(val));
    if(vec[index]==nullptr) return false;
    
    result = vec[index]->List<Data>::Remove(val);
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
