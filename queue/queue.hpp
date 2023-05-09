
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Queue : virtual public ClearableContainer {

private:

protected:

public:

  // Destructor
  virtual ~Queue() = default;

  /* ************************************************************************ */

  // Copy assignment
  Queue<Data>& operator=(const Queue& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  Queue<Data>& operator=(Queue&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Queue& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Queue& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  // type Head() specifiers; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual const Data& Head() const = 0;

  // type Head() specifiers; // (mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Head() = 0;

  // type Dequeue() specifiers; // (concrete function must throw std::length_error when empty)
  virtual void Dequeue() = 0;

  // type HeadNDequeue() specifiers; // (concrete function must throw std::length_error when empty)
  virtual Data HeadNDequeue() = 0;

  // type Enqueue(argument) specifiers; // Copy of the value
  virtual void Enqueue(const Data& elem) = 0;

  // type Enqueue(argument) specifiers; // Move of the value
  virtual void Enqueue(Data&& elem) = 0;

};

/* ************************************************************************** */

}

#endif
