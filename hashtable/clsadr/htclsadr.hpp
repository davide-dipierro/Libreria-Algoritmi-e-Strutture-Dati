
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

/// @brief Quella che usa le liste
/// @tparam Data 
template <typename Data>
class HashTableClsAdr : virtual public HashTable<Data> {

private:

  // ...

protected:

  
  using HashTable<Data>::nextPow;
  // using DictionaryContainer<Data>::Remove;
  using Container::size;

  List<Data>* vec = nullptr;


public:
  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::RemoveAll;
  using DictionaryContainer<Data>::InsertSome;
  using DictionaryContainer<Data>::RemoveSome;


  using HashTable<Data>::vecSize;

  // Default constructor
  HashTableClsAdr() : HashTableClsAdr(16) {};

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(const ulong size); // A hash table of a given size
  HashTableClsAdr(const MappableContainer<Data>& other); // A hash table obtained from a MappableContainer
  HashTableClsAdr(const ulong size, const MappableContainer<Data>& other); // A hash table of a given size obtained from a MappableContainer
  HashTableClsAdr(MutableMappableContainer<Data>&& other) noexcept; // A hash table obtained from a MutableMappableContainer
  HashTableClsAdr(const ulong size, MutableMappableContainer<Data>&& other) noexcept; // A hash table of a given size obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr<Data>& other);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableClsAdr();

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr& operator=(const HashTableClsAdr& other);

  // Move assignment
  HashTableClsAdr& operator=(HashTableClsAdr&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr& other) const noexcept;
  bool operator!=(const HashTableClsAdr& other) const noexcept { return !(operator==(other)); };

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

  /* ************************************************************************ */  //FUNZIONI SOLO PER TEST

  void printTable();

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
