
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

#define const_init_queue_size 10 

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

#include <cmath>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : virtual public Queue<Data>,
                 virtual protected Vector<Data> {

private:

protected:


  
  using Vector<Data>::Elements; //Eh bisogna sempre chiedere
  
  ulong head = 0;
  ulong tail = 0;
  

  // const double const_exp_check = 0.75;
  const double const_exp_set = 2;
  const double const_red_check = 0.5;
  const double const_red_set = 0.6;

public:

  using Container::size;

  // Default constructor
  QueueVec();

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const MappableContainer<Data>& cont); // A queue obtained from a MappableContainer
  QueueVec(MutableMappableContainer<Data>&& cont) noexcept; // A queue obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec& other);

  // Move constructor
  QueueVec(QueueVec&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec<Data>& operator=(const QueueVec& other);

  // Move assignment
  QueueVec<Data>& operator=(QueueVec&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec& other) const noexcept;
  inline bool operator!=(const QueueVec& other) const noexcept { return !(this->operator==(other)); };

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data& Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data& Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data& elem) override; // Override Queue member (copy of the value)
  void Enqueue(Data&& elem) override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  bool Empty() const noexcept override { return head==tail; } // Override Container member

  ulong Size() const noexcept override { return (size==0) ? 0 : ((tail+size-head)%size); } // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary member functions

  void CheckNExpand();
  void CheckNReduce();

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
