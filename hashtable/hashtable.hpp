
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>
#include <string>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

protected:

  uint HashByte(unsigned char* val) const noexcept;

public:

  uint operator()(std::string val) const noexcept; // (concrete function should not throw exceptions)
  uint operator()(int val) const noexcept; // (concrete function should not throw exceptions)
  uint operator()(double val) const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public ResizableContainer,
                  virtual public DictionaryContainer<Data> {

private:

  // ...

protected:

  using DictionaryContainer<Data>::size;

  uint a = 3;
  uint b = 5;

public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable& operator=(const HashTable& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable& other) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.
  inline bool operator!=(HashTable&& other) const noexcept { return !(operator==(other)); }; // Comparison of abstract hashtable is possible but not required.

protected:

  // Auxiliary member functions

  uint HashKey(uint key) const noexcept;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
