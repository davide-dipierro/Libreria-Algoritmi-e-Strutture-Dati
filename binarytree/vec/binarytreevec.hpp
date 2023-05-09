
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data>,
                      virtual protected Vector<Data> {

private:

  // ...

protected:

  struct NodeVec : virtual public MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode

  friend class BinaryTreeVec<Data>;

  private:

    Vector<Data>* punt;

  protected:

    const ulong Index() const { return (this)-(Nodes); }

  public:

    virtual inline Data& Element() noexcept override { return Elements[Index()]; }
    virtual inline const Data& Element() const noexcept override { return Elements[Index()]; }

  };

  using Vector<Data>::Elements;
  Vector<NodeVec*> Nodes;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const MappableContainer<Data>& other); // A binary tree obtained from a MappableContainer
  BinaryTreeVec(MutableMappableContainer<Data>&& other) noexcept; // A binary tree obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data>& other);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data>&& other) noexcept;
  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec& other);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BinaryTreeVec& other) const noexcept { return Vector<Data>::operator==(other); };
  inline bool operator!=(const BinaryTreeVec& other) const noexcept { return Vector<Data>::operator!=(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  virtual const NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  virtual NodeVec& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual inline void Clear() override { Vector<Data>::Clear(); }; // Override ClearableContainer member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)

  // type BreadthFold(arguments) specifiers; // Override BreadthFoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)

  // type BreadthMap(arguments) specifiers; // Override BreadthMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableBreadthMappableContainer)

  // type BreadthMap(arguments) specifiers; // Override MutableBreadthMappableContainer member

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
