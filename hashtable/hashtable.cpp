
namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline uint HashTable<Data>::HashKey(uint key) const noexcept {
    return (a*key+b)%this->size;
}

/* ************************************************************************** */

template <>
uint Hashable<int>::operator()(int val) const noexcept {        
    unsigned char* byteData = reinterpret_cast<unsigned char*>(&val);
    return HashByte(byteData);
}

template <>
uint Hashable<std::string>::operator()(std::string val) const noexcept {
    unsigned int hashValue = 0;
    // unsigned int prime = 31;

    // for (char ch : val) {
    //     hashValue = hashValue * prime + ch;
    // }

    for(int i{0}; i<val.size(); i++) hashValue = hashValue + (i*val[i]);

    return hashValue;
}

template <>
uint Hashable<double>::operator()(double val) const noexcept {
    unsigned long long intValue = *reinterpret_cast<unsigned long long*>(&val);
    unsigned char* byteData = reinterpret_cast<unsigned char*>(&intValue);

    return HashByte(byteData);
}

template <typename Data>
uint Hashable<Data>::HashByte(unsigned char *byteData) const noexcept {
    unsigned int hashValue = 0;
    unsigned int prime = 31;
    for (size_t i = 0; i < sizeof(unsigned long long); ++i) {
        hashValue = hashValue * prime + byteData[i];
    }
    return uint();
}

/* ************************************************************************** */

}
