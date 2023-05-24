#include <functional>

namespace lasd {

/* ************************************************************************** */

template <typename Data>
ulong HashTable<Data>::HashKey(const ulong key) const noexcept {
    return (a*key+b)%vecSize;
}

template <typename Data>
ulong HashTable<Data>::nextPow(ulong num) {
    if(num<8) return 8;
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
        ulong operator()(const int val) const noexcept {        
            // return (val+1)*val;
            return val;
            //return val+1; ////RITORNO PER TESTING
        }
};

template <>
class Hashable<std::string>{
    public:
        ulong operator()(const std::string val) const noexcept {
            unsigned int hashValue = 0;
            for(int i=0; i<val.size(); i++)
                hashValue += (i*val[i]);
            return hashValue;
        }
};

template <>
class Hashable<double>{
    public:
        ulong operator()(const double val) const noexcept {
            ulong int_part = floor(val);
            return (int_part*int_part + ((val-int_part)*(val-int_part))) - int_part;
            //return val+1; //RITORNO PER TESTING
        }
};

template <typename Data>
long Hashable<Data>::HashByte(const unsigned char* byteData, size_t siz) const noexcept {
    ulong hashValue = 0;
    for (size_t i = 0; i < siz; ++i) hashValue = hashValue * prime + byteData[i];
    return hashValue;
}

/* ************************************************************************** */

}
