
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
// #include ...

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> {

private:

  // ...

protected:

  // using HashTable<Data>::???;

  // ...

public:

  // Default constructor
  HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const ulong size); // A hash table of a given size
  HashTableOpnAdr(const MappableContainer<Data>& other); // A hash table obtained from a MappableContainer
  HashTableOpnAdr(const ulong size, const MappableContainer<Data>& other); // A hash table of a given size obtained from a MappableContainer
  HashTableOpnAdr(MutableMappableContainer<Data>&& other) noexcept; // A hash table obtained from a MutableMappableContainer
  HashTableOpnAdr(const ulong size, MutableMappableContainer<Data>&& other) noexcept; // A hash table of a given size obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr<Data>& other);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr& other);

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr& other) const noexcept;
  bool operator!=(HashTableOpnAdr&& other) const noexcept { return !(operator==(other)); };

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual bool Insert(const Data& val) override; // Override DictionaryContainer member (Copy of the value)
  virtual bool Insert(Data&& val) override; // Override DictionaryContainer member (Move of the value)
  virtual bool Remove(const Data& val) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  virtual bool Exists(const Data& val) const noexcept;  // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  virtual void Resize(const ulong n);  // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  virtual void Clear() override; // Override Container member

public:

  // Auxiliary member functions

  // type HashKey(argument) specifiers;
  // type Find(argument) specifiers;
  // type FindEmpty(argument) specifiers;
  // type Remove(argument) specifiers;

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
