
namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline ulong HashTable<Data>::HashKey(const ulong key) const noexcept {
    return (a*key+b)%vecSize;
}

/* ************************************************************************** */

template <>
ulong Hashable<int>::operator()(const int val) const noexcept {        
    // const unsigned char* byteData = reinterpret_cast<const unsigned char*>(&val);
    // return HashByte(byteData);
    return val+1;
}

template <>
ulong Hashable<std::string>::operator()(const std::string val) const noexcept {
    unsigned int hashValue = 0;
    // unsigned int prime = 31;

    // for (char ch : val) {
    //     hashValue = hashValue * prime + ch;
    // }

    for(int i{0}; i<val.size(); i++) hashValue = hashValue + (i*val[i]);

    return hashValue;
}

template <>
ulong Hashable<double>::operator()(const double val) const noexcept {
    long long intValue = *reinterpret_cast<const unsigned long long*>(&val);
    unsigned char* byteData = reinterpret_cast<unsigned char*>(&intValue);

    return HashByte(byteData);
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

/* ************************************************************************** */

}
