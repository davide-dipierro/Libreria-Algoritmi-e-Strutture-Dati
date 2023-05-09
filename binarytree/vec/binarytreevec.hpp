
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data> {

private:

  // ...

protected:

  struct NodeVec : virtual public MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode

  // friend class BinaryTreeVec<Data>;

  private:

    BinaryTreeVec<Data>* bt;
    int i;


  protected:

    const ulong Index() const { return i; }//{ return (this)-(bt->Nodes->Elements); }

  public:

    NodeVec(const Data &dat, int i, BinaryTreeVec<Data>* bt);
    NodeVec(Data&& dat, int i, BinaryTreeVec<Data>* bt);

    virtual bool HasLeftChild() const noexcept override;
    virtual bool HasRightChild() const noexcept override;

    virtual NodeVec& RightChild() override;
    virtual const NodeVec& RightChild() const override;

    virtual NodeVec& LeftChild() override;
    virtual const NodeVec& LeftChild() const override;


    virtual inline Data& Element() noexcept override { return bt->Elements[Index()]; }
    virtual inline const Data& Element() const noexcept override { return bt->Elements[Index()]; }

  };

  Vector<Data> Elements = Vector<Data>(0);
  Vector<NodeVec*> Nodes = Vector<NodeVec*>(0);

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
  virtual ~BinaryTreeVec() = default;

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

  virtual inline void Clear() override { Elements.Clear(); Nodes.Clear(); }; // Override ClearableContainer member (throw std::length_error when empty)

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
