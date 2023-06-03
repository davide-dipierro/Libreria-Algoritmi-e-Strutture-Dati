
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#define HASHTABLE_INIT_SIZE 16

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

public:

  ulong operator()(const Data& dat) const noexcept; // (concrete function should not throw exceptions)

};

#endif

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public ResizableContainer,
                  virtual public DictionaryContainer<Data>,
                  virtual protected MappableContainer<Data> {

private:

  // ...

protected:

  using Container::size;
  ulong max = 127;

  std::default_random_engine gen = std::default_random_engine(std::random_device{}());
  std::uniform_int_distribution<ulong> genA = std::uniform_int_distribution<ulong>(1, max);
  std::uniform_int_distribution<ulong> genB = std::uniform_int_distribution<ulong>(0, max);

  ulong a = 1;
  ulong b = 0;



public:

  
  using DictionaryContainer<Data>::Exists; 
  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::InsertSome;
  using DictionaryContainer<Data>::RemoveAll;
  using DictionaryContainer<Data>::RemoveSome;
  
  ulong vecSize = HASHTABLE_INIT_SIZE;

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
  bool operator==(const HashTable& other) const noexcept; // Comparison of abstract hashtable is possible but not required.
  inline bool operator!=(const HashTable& other) const noexcept { return !(operator==(other)); }; // Comparison of abstract hashtable is possible but not required.

  // Just for testing
  virtual void printTable() const = 0;

protected:

  // Auxiliary member functions

  ulong HashKey(const ulong key) const noexcept;
  ulong nextPow(ulong num);

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
