
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include <bitset>

/* ************************************************************************** */

#define full_bit 0
#define valid_bit 1

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> {

private:

  // ...

protected:
  // using DictionaryContainer<Data>::InsertAll;

  // using HashTable<Data>::vecSize;
  using HashTable<Data>::nextPow;
  using HashTable<Data>::HashKey;
  using Container::size;

  Data* Elements;
  std::bitset<2>* Bits; //Vector of 2 bits  -(00) Empty/Deleted -(01) Empty/Valid (Inconsistente)
//                                          -(10) Full/Deleted  -(11) Full/Valid

public:

  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::InsertSome;
  using DictionaryContainer<Data>::RemoveAll;
  using DictionaryContainer<Data>::RemoveSome;
  

  using HashTable<Data>::vecSize;

  // Default constructor
  HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const ulong newSize); // A hash table of a given size
  HashTableOpnAdr(const MappableContainer<Data>& other); // A hash table obtained from a MappableContainer
  HashTableOpnAdr(const ulong newSize, const MappableContainer<Data>& other); // A hash table of a given size obtained from a MappableContainer
  HashTableOpnAdr(MutableMappableContainer<Data>&& other) noexcept; // A hash table obtained from a MutableMappableContainer
  HashTableOpnAdr(const ulong newSize, MutableMappableContainer<Data>&& other) noexcept; // A hash table of a given size obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr<Data>& other);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HashTableOpnAdr();

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr& other);

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr& other) const noexcept;
  bool operator!=(const HashTableOpnAdr& other) const noexcept { return !(operator==(other)); };

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual bool Insert(const Data& dat) override; // Override DictionaryContainer member (Copy of the value)
  virtual bool Insert(Data&& dat) override; // Override DictionaryContainer member (Move of the value)
  virtual bool Remove(const Data& dat) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  virtual bool Exists(const Data& dat) const noexcept;  // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  virtual void Resize(const ulong n);  // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  virtual void Clear() override; // Override Container member

  /* ************************************************************************ */  //FUNZIONI SOLO PER TEST
  bool CheckDirtyBit();
  void printTable();

protected:

  // Auxiliary member functions

  ulong HashKey2(const ulong index, ulong& prob_index) const noexcept;
  bool Find(ulong& index, const Data& dat, ulong& prob_index) const noexcept;
  ulong FindEmpty(const ulong index, const Data& dat, ulong& prob_index) noexcept;
  bool Remove(const ulong& index, const Data& dat, ulong& prob_index);

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
