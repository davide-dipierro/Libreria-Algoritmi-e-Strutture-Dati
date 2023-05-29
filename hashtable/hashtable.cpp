#include <functional>
#include "hashtable.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTable<Data>::HashTable(const HashTable &other) {
    vecSize = other.vecSize;
    size = other.size;
    a = other.a;
    b = other.b;
}

template <typename Data>
HashTable<Data>::HashTable(HashTable &&other) noexcept{
    std::swap(vecSize, other.vecSize);
    std::swap(size, other.size);
    std::swap(a, other.a);
    std::swap(b, other.b);
}

template <typename Data>
HashTable<Data>& HashTable<Data>::operator=(const HashTable &other) {
    vecSize = other.vecSize;
    size = other.size;
    a = other.a;
    b = other.b;
    return *this;
}

template <typename Data>
HashTable<Data>& HashTable<Data>::operator=(HashTable &&other) noexcept {
    std::swap(vecSize, other.vecSize);
    std::swap(size, other.size);
    std::swap(a, other.a);
    std::swap(b, other.b);
    return *this;
}

template <typename Data>
ulong HashTable<Data>::HashKey(const ulong key) const noexcept {
    return (a*key+b)%vecSize;
}

template <typename Data>
ulong HashTable<Data>::nextPow(ulong num) {
    if(num<HASHTABLE_INIT_SIZE) return HASHTABLE_INIT_SIZE;
    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num |= num >> 32;
    return num + 1;

    // return std::pow(2, ceil(log2(num)));
}

/* ************************************************************************** */

// template <typename Data>
// long Hashable<Data>::operator()(const Data& dat) const noexcept {        
//     // const unsigned char* byteData = reinterpret_cast<const unsigned char*>(&dat);
//     // return HashByte(byteData, sizeof(dat));
//     // return static_cast<long>(std::hash<Data>{}(dat));
// }

template <>
class Hashable<int>{
    public:
        ulong operator()(int val) const noexcept {      
            // return val;
            // return static_cast<long>(std::hash<Data>{}(dat));
            val = (val + 0x7ed55d16) + (val << 12);        // MurmurHash      
            val = (val ^ 0xc761c23c) ^ (val >> 19);
            val = (val + 0x165667b1) + (val << 5);
            val = (val + 0xd3a2646c) ^ (val << 9);
            val = (val + 0xfd7046c5) + (val << 3);
            val = (val ^ 0xb55a4f09) ^ (val >> 16);
            return static_cast<ulong>(val);
        }
};

template <>
class Hashable<std::string>{
    public:
        ulong operator()(std::string val) const noexcept {
            // return static_cast<long>(std::hash<Data>{}(dat));
            ulong hash = 5381;
            for (char c : val) hash = ((hash << 5) + hash) + c; // hash * 33 + c
            return hash;
        }
};

template <>
class Hashable<double>{
    public:
        ulong operator()(double val) const noexcept {
            // return static_cast<long>(std::hash<Data>{}(dat));
            ulong longVal = *reinterpret_cast<ulong*>(&val);  // Converte il double in un ulong
            ulong hash = 5381;
            hash ^= longVal;
            return hash;
        }
};

/* ************************************************************************** */

}
