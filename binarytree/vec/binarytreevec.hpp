
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

  protected:

    const ulong Index() const { return i; } //{ return (this)-(bt->Nodes->Elements); }

  public:

    BinaryTreeVec<Data>* bt;
    Data dat {};
    int i;


    NodeVec(const Data &dat, int i, BinaryTreeVec<Data>* bt);
    NodeVec(Data&& dat, int i, BinaryTreeVec<Data>* bt);
    ~NodeVec() { if(!(bt->Nodes.Empty())) bt->Nodes[Index()]=nullptr; };

    NodeVec& operator=(const NodeVec& other);
    NodeVec& operator=(NodeVec&& other) noexcept;

    virtual bool HasLeftChild() const noexcept override;
    virtual bool HasRightChild() const noexcept override;

    virtual NodeVec& RightChild() override;
    virtual const NodeVec& RightChild() const override;

    virtual NodeVec& LeftChild() override;
    virtual const NodeVec& LeftChild() const override;


    virtual inline Data& Element() noexcept override { return dat; }
    virtual inline const Data& Element() const noexcept override { return dat; }

  };

  // Vector<Data> Elements;// = Vector<Data>(0);
  Vector<NodeVec*> Nodes;// = Vector<NodeVec*>(0);

public:

  // Default constructor
  BinaryTreeVec() : Nodes(0) {;};

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
  bool operator==(const BinaryTreeVec& other) const noexcept { return BinaryTree<Data>::operator==(other); };
  bool operator!=(const BinaryTreeVec& other) const noexcept { return !(this->operator==(other)); };

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  virtual const NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  virtual NodeVec& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() override; // Override ClearableContainer member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;
  void BreadthFold(FoldFunctor func, void* acc) const override { for(int i{0}; i<Nodes.Size(); i++) func(Nodes[i]->Element(), acc); }; // Override BreadthFoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)

  using typename MappableContainer<Data>::MapFunctor;
  void BreadthMap(MapFunctor func) const override { for(int i{0}; i<Nodes.Size(); i++) func(Nodes[i]->Element()); }; // Override BreadthMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableBreadthMappableContainer)

  using typename MutableMappableContainer<Data>::MutableMapFunctor;
  void BreadthMap(MutableMapFunctor func) override { for(int i{0}; i<Nodes.Size(); i++) func(Nodes[i]->Element()); }; // Override MutableBreadthMappableContainer member

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
