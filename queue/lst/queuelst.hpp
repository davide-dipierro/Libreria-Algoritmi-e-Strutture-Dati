
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : virtual public Queue<Data>,
                 virtual protected List<Data> {

private:

protected:
  using List<Data>::head;
  using Container::size;

public:

  // Default constructor
  QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const MappableContainer<Data>& cont)  : List<Data>::List(cont) { ; } // A queue obtained from a MappableContainer
  QueueLst(MutableMappableContainer<Data>&& cont) noexcept  : List<Data>::List(std::move(cont)) { ; }// A queue obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst& other) : List<Data>::List(other) { ; } 

  // Move constructor
  QueueLst(QueueLst&& other) noexcept : List<Data>::List(std::move(other)) { ; }

  /* ************************************************************************ */

  // Destructor
  ~QueueLst() = default;
  
  /* ************************************************************************ */

  // Copy assignment
  QueueLst<Data>& operator=(const QueueLst& other);

  // Move assignment
  QueueLst<Data>& operator=(QueueLst&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueLst& other) const noexcept { return this->List<Data>::operator==(other); }
  bool operator!=(const QueueLst& other) const noexcept { return this->List<Data>::operator!=(other); }

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data& Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data& Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data& elem) override; // Override Queue member (copy of the value)
  void Enqueue(Data&& elem) override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
