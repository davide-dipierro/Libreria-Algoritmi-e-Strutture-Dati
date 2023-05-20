#include <functional>

namespace lasd {

/* ************************************************************************** */

template <typename Data>
ulong HashTable<Data>::HashKey(const ulong key) const noexcept {
    return (a*key+b)%vecSize;
}

template <typename Data>
ulong HashTable<Data>::nextPow(ulong num) {
    if(num<4) return 4;
    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num |= num >> 32;
    return num + 1;
}

/* ************************************************************************** */

template <typename Data>
long Hashable<Data>::operator()(const Data& dat) const noexcept {        
    // const unsigned char* byteData = reinterpret_cast<const unsigned char*>(&dat);
    // return HashByte(byteData, sizeof(dat));
    // return dat+1;
    return static_cast<long>(std::hash<Data>{}(dat));
}

template <typename Data>
long Hashable<Data>::HashByte(const unsigned char* byteData, size_t siz) const noexcept {
    ulong hashValue = 0;
    for (size_t i = 0; i < siz; ++i) hashValue = hashValue * prime + byteData[i];
    return hashValue;
}

/* ************************************************************************** */

}
