
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>
#include <string>

/* ************************************************************************** */

#include "../container/dictionary.hpp"
#include <random>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

#ifndef HASHABLE_HPP
#define HASHABLE_HPP

template <typename Data>
class Hashable {

protected:

  ulong prime = 31;
  long HashByte(const unsigned char* byteData, size_t siz) const noexcept;

public:

  ulong operator()(const Data& dat) const noexcept; // (concrete function should not throw exceptions)


};

#endif

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public ResizableContainer,
                  virtual public DictionaryContainer<Data> {

private:

  // ...

protected:

  using Container::size;
  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::InsertSome;
  using DictionaryContainer<Data>::RemoveAll;
  using DictionaryContainer<Data>::RemoveSome;

  ulong prime = 31;

  std::default_random_engine gen = std::default_random_engine(std::random_device{}());
  std::uniform_int_distribution<ulong> genA = std::uniform_int_distribution<ulong>(1, prime);
  std::uniform_int_distribution<ulong> genB = std::uniform_int_distribution<ulong>(0, prime);

  ulong a = 3;
  ulong b = 4;


public:


  ulong vecSize = 8;

  //Constructor
  HashTable() {
    a = 1;//genA(gen)*2+1;
    b = 0;//nextPow(genB(gen));
  }
  
  //Copy constructor
  HashTable(const HashTable& other) {
    vecSize = other.vecSize;
    size = other.size;
    a = other.a;
    b = other.b;
  }

  //Move constructor
  HashTable(HashTable&& other) noexcept {
    std::swap(vecSize, other.vecSize);
    std::swap(size, other.size);
    std::swap(a, other.a);
    std::swap(b, other.b);
  }

  //Copy assignament
  virtual HashTable& operator=(const HashTable& other) {
    vecSize = other.vecSize;
    size = other.size;
    a = other.a;
    b = other.b;
    return *this;
  }

  //Move assignament
  virtual HashTable& operator=(HashTable&& other) noexcept {
    std::swap(vecSize, other.vecSize);
    std::swap(size, other.size);
    std::swap(a, other.a);
    std::swap(b, other.b);
    return *this;
  }

  // Destructor
  virtual ~HashTable() = default;

/* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable& other) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.
  inline bool operator!=(const HashTable& other) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.

protected:

  // Auxiliary member functions

  ulong HashKey(const ulong key) const noexcept;
  ulong nextPow(ulong num);

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
