
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Stack : virtual public ClearableContainer {
              // Must extend ClearableContainer

private:

  // ...

protected:

  using Container::size;

public:

  // Destructor
  virtual ~Stack() = default;

  /* ************************************************************************ */

  // Copy assignment
  Stack& operator=(const Stack& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  Stack& operator=(Stack&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Stack& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Stack& other) const noexcept = delete; // Comparison of abstract types might not be possible.


  /* ************************************************************************ */

  // Specific member functions

  // type Top() specifiers; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual const Data& Top() const = 0;
  
  // type Top() specifiers; // (mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Top() = 0;
  
  // type Pop() specifiers; // (concrete function must throw std::length_error when empty)
  virtual void Pop() = 0;
  
  // type TopNPop() specifiers; // (concrete function must throw std::length_error when empty)
  virtual Data TopNPop() = 0;
  
  // type Push(argument) specifiers; // Copy of the value
  virtual void Push(const Data& elem) = 0;
  
  // type Push(argument) specifiers; // Move of the value
  virtual void Push(Data&& elem) = 0;


};

/* ************************************************************************** */

}

#endif
