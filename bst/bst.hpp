
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public ClearableContainer,
            virtual public DictionaryContainer<Data>,
            virtual public BinaryTree<Data>,
            virtual protected BinaryTreeLnk<Data> {

private:

protected:

  using Container::size;
  using BinaryTreeLnk<Data>::root;
  using typename BinaryTreeLnk<Data>::NodeLnk;

public:

  using BinaryTree<Data>::Map;
  using BinaryTree<Data>::PreOrderMap;
  using BinaryTree<Data>::PostOrderMap;
  using BinaryTree<Data>::InOrderMap;
  using BinaryTree<Data>::BreadthMap;
  using BinaryTree<Data>::Root;

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const MappableContainer<Data>& other); // A bst obtained from a MutableContainer
  BST(MutableMappableContainer<Data>&& other) noexcept; // A bst obtained from a MappableMutableContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST& other) : BinaryTreeLnk<Data>::BinaryTreeLnk(other) {;}

  // Move constructor
  BST(BST&& other) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(other)) {;}

  /* ************************************************************************ */

  // Destructor
  ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST& operator=(const BST& other);

  // Move assignment
  BST& operator=(BST&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST& other) const noexcept;
  inline bool operator!=(const BST& other) const noexcept { return (!(operator==(other))); };

  /* ************************************************************************ */

  // Specific member functions

  const Data& Min() const; // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data& Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data& dat) const; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data& dat); // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data& dat); // (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data& dat) const; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data& dat); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data& dat); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data& dat) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&& dat) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data& dat) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  inline bool Exists(const Data& val) const noexcept override { return (FindPointerTo(root,val) !=nullptr); }; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() override { BinaryTreeLnk<Data>::Clear(); }; // Override ClearableContainer member

  /* ************************************************************************ */
  // const NodeLnk& Root() const override { return BinaryTreeLnk<Data>::Root(); };

  //Non funziona
  // virtual void printBT() const override;

protected:

  // Auxiliary member functions

  Data DataNDelete(NodeLnk* node);

  NodeLnk* Detach(NodeLnk*& node) noexcept;

  NodeLnk* DetachMin(NodeLnk*& node) noexcept { return Skip2Right(FindPointerToMin(node)); };
  NodeLnk* DetachMax(NodeLnk*& node) noexcept { return Skip2Left(FindPointerToMax(node)); };

  NodeLnk* Skip2Left(NodeLnk*& node) noexcept;
  NodeLnk* Skip2Right(NodeLnk*& node) noexcept;

  NodeLnk* const& FindPointerToMin(NodeLnk* const& node) const noexcept;
  NodeLnk*& FindPointerToMin(NodeLnk*& node) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(node));
  };

  NodeLnk* const& FindPointerToMax(NodeLnk* const& node) const noexcept;
  NodeLnk*& FindPointerToMax(NodeLnk*& node) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
  };

  NodeLnk* const& FindPointerTo(NodeLnk* const& node, Data val) const noexcept;
  inline NodeLnk*& FindPointerTo(NodeLnk*& node, Data val) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(node,val));
  };

  NodeLnk* const& FindPointerToPredecessor(NodeLnk* const &node, Data val) const noexcept;
  inline NodeLnk*& FindPointerToPredecessor(NodeLnk*& node, Data val) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(node,val));
  };
  
  NodeLnk* const& FindPointerToSuccessor(NodeLnk* const &node, Data val) const noexcept;
  inline NodeLnk*& FindPointerToSuccessor(NodeLnk*& node, Data val) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(node,val));
  };

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
