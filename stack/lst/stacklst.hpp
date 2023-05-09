
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst :  virtual public Stack<Data>,
                  virtual public List<Data> {

private:

protected:

  using Container::size;

public:


  // Default constructor
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const MappableContainer<Data>& cont) : List<Data>::List(cont) { ; } // A queue obtained from a MappableContainer
  StackLst(MutableMappableContainer<Data>&& cont) noexcept : List<Data>::List(std::move(cont)) { ; }// A queue obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const StackLst& other) : List<Data>::List(other) { ; }

  // Move constructor
  StackLst(StackLst&& other) noexcept : List<Data>::List(std::move(other)) { ; }


  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst() {
    while(!(List<Data>::Empty())) List<Data>::RemoveFromFront(); //Forse può essere tolto
  }

  /* ************************************************************************ */

  // Copy assignment
  StackLst<Data>& operator=(const StackLst& other);

  // Move assignment
  StackLst<Data>& operator=(StackLst&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackLst& other) const noexcept { return this->List<Data>::operator==(other); }
  bool operator!=(const StackLst& other) const noexcept { return this->List<Data>::operator!=(other); }

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data& Top() const override;
  Data& Top() override;
  void Pop() override;
  Data TopNPop() override;
  void Push(const Data& elem) override;
  void Push(Data&& elem) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
