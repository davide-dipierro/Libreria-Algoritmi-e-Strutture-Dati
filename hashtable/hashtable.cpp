
namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline ulong HashTable<Data>::HashKey(const ulong key) const noexcept {
    return (a*key+b)%vecSize;
}

/* ************************************************************************** */

template <>
inline ulong Hashable<int>::operator()(const int val) const noexcept {        
    // const unsigned char* byteData = reinterpret_cast<const unsigned char*>(&val);
    // return HashByte(byteData);
    return val+1;
}

template <>
inline ulong Hashable<std::string>::operator()(const std::string val) const noexcept {
    unsigned int hashValue = 0;
    // unsigned int prime = 31;

    // for (char ch : val) {
    //     hashValue = hashValue * prime + ch;
    // }

    for(int i{0}; i<val.size(); i++) hashValue = hashValue + (i*val[i]);

    return hashValue;
}

template <>
inline ulong Hashable<double>::operator()(const double val) const noexcept {
    // long long intValue = *reinterpret_cast<const unsigned long long*>(&val);
    // unsigned char* byteData = reinterpret_cast<unsigned char*>(&intValue);

    // return HashByte(byteData);
    return val+1;
}

template <typename Data>
ulong Hashable<Data>::HashByte(const unsigned char *byteData) const noexcept {
    unsigned int hashValue = 0;
    unsigned int prime = 31;
    for (size_t i = 0; i < sizeof(unsigned long long); ++i) {
        hashValue = hashValue * prime + byteData[i];
    }
    return hashValue;
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

}
