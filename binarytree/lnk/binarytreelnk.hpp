
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public MutableBinaryTree<Data> {

private:

protected:

  using Container::size;

  // using BinaryTree<Data>::???;


  struct NodeLnk : virtual public MutableBinaryTree<Data>::MutableNode { 

    friend class BinaryTreeLnk<Data>;

  private:

  protected:

  public:

    Data elem {};
    NodeLnk* lChild = nullptr;
    NodeLnk* rChild = nullptr;

    // virtual ~NodeLnk() = default; // NOTE: Da decidere se cancellare i figli, penso di no
    virtual ~NodeLnk();

    NodeLnk(const NodeLnk& other);
    NodeLnk(NodeLnk&& other) noexcept;

    NodeLnk(const Data& newElem) { elem = newElem; }; //NOTE: Va bene dichiarare due costruttori? E se il dato è un NodeLnk??
    NodeLnk(Data&& newElem) noexcept { std::swap(elem, newElem); };

    // NodeLnk& operator=(const NodeLnk& other);
    // NodeLnk& operator=(NodeLnk&& other) noexcept;

    virtual inline Data& Element() noexcept override { return elem; }
    virtual inline const Data& Element() const noexcept override { return elem; }

    virtual inline bool IsLeaf() const noexcept override { return (!(HasLeftChild() || HasRightChild())); }; 
    
    virtual inline bool HasLeftChild() const noexcept override { return lChild!=nullptr; }
    virtual inline bool HasRightChild() const noexcept override { return rChild!=nullptr; }

    virtual inline NodeLnk& RightChild() override { if(HasRightChild()) return *rChild; else throw std::out_of_range("BinaryTreeLnk<Data>::NodeLnk::RightChild(): Not found!"); }
    virtual inline const NodeLnk& RightChild() const override { if(HasRightChild()) return *rChild; else throw std::out_of_range("BinaryTreeLnk<Data>::NodeLnk::RightChild(): Not found!"); }

    virtual inline NodeLnk& LeftChild() override { if(HasLeftChild()) return *lChild; else throw std::out_of_range("BinaryTreeLnk<Data>::NodeLnk::LeftChild(): Not found!"); }
    virtual inline const NodeLnk& LeftChild() const override { if(HasLeftChild()) return *lChild; else throw std::out_of_range("BinaryTreeLnk<Data>::NodeLnk::LeftChild(): Not found!"); }

  };

  NodeLnk* root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const MappableContainer<Data>& other); // A binary tree obtained from a MappableContainer
  BinaryTreeLnk(MutableMappableContainer<Data>&& other) noexcept; // A binary tree obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data>& other);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk& other);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk& other) const noexcept { return BinaryTree<Data>::operator==(other); };
  bool operator!=(const BinaryTreeLnk& other) const noexcept { return BinaryTree<Data>::operator!=(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  virtual const NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  virtual NodeLnk& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // virtual inline void Clear() override { if (root != nullptr) { DeleteSubTree(root); root=nullptr; } }; // Override ClearableContainer member
  virtual inline void Clear() override { if (root != nullptr) { delete root; root=nullptr; } size=0; }; // Override ClearableContainer member




protected:

  
  // void DeleteSubTree(NodeLnk* node);
  // void InsertBreadth(const Data& dat);
  // void InsertBreadth(Data&& dat);

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
