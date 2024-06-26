
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer : virtual public TestableContainer<Data>{


private:

protected:

public:

  // Destructor
  virtual ~DictionaryContainer() = default; // Utilizzo del distruttore di default (Virtual)

  /* ************************************************************************ */

  // Copy assignment
  DictionaryContainer& operator=(const DictionaryContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  DictionaryContainer& operator=(DictionaryContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const DictionaryContainer& other) const noexcept = delete; // Non utilizzabile
  bool operator!=(const DictionaryContainer& other) const noexcept = delete; // Non utilizzabile

  /* ************************************************************************ */

  // Specific member functions

  virtual bool Insert(const Data& val) = 0; // Copy of the value
  virtual bool Insert(Data&& val) = 0; // Move of the value
  virtual bool Remove(const Data& val) = 0;

  bool InsertAll(const MappableContainer<Data>& cont); // Copy of the value; From MappableContainer; True if all are inserted
  bool InsertAll(MutableMappableContainer<Data>&& cont); // Move of the value; From MutableMappableContainer; True if all are inserted
  bool RemoveAll(const MappableContainer<Data>& cont); // From MappableContainer; True if all are removed

  bool InsertSome(const MappableContainer<Data>& cont); // Copy of the value; From MappableContainer; True if some is inserted
  bool InsertSome(MutableMappableContainer<Data>&& cont); // Move of the value; From MutableMappableContainer; True if some is inserted
  bool RemoveSome(const MappableContainer<Data>& cont); // From MappableContainer; True if some is removed

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif
