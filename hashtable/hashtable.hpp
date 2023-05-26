
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
  ulong vecSize = 8;


public:

  //Constructor
  HashTable() {
    a = genA(gen)*2+1;
    b = nextPow(genB(gen));
  }
  
  //Copy constructor
  HashTable(const HashTable& other);

  //Move constructor
  HashTable(HashTable&& other) noexcept;

  //Copy assignament
  HashTable& operator=(const HashTable& other);

  //Move assignament
  HashTable& operator=(HashTable&& other) noexcept;


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
