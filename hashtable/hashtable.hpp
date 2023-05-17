
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

#ifndef HASHABLE_HPP
#define HASHABLE_HPP

template <typename Data>
class Hashable {

protected:

  ulong HashByte(const unsigned char* val) const noexcept;

public:

  ulong operator()(const std::string val) const noexcept; // (concrete function should not throw exceptions)
  ulong operator()(const int val) const noexcept; // (concrete function should not throw exceptions)
  ulong operator()(const double val) const noexcept; // (concrete function should not throw exceptions)

};

#endif

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public ResizableContainer,
                  virtual public DictionaryContainer<Data> {

private:

  // ...

protected:

  using DictionaryContainer<Data>::Insert;
  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::Remove;

  ulong a = 3;
  ulong b = 5;

  ulong vecSize = 0;

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

  ulong HashKey(const ulong key) const noexcept;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif