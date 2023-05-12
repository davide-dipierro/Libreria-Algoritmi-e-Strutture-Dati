
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

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const MappableContainer<Data>& other); // A bst obtained from a MutableContainer
  BST(MutableMappableContainer<Data>&& other) noexcept; // A bst obtained from a MappableMutableContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST& other);

  // Move constructor
  BST(BST&& other) noexcept;

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

  bool Exists(const Data& dat) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() override { BinaryTreeLnk<Data>::Clear(); }; // Override ClearableContainer member

  //Non funziona
  // virtual void printBT() const override;

protected:

  // Auxiliary member functions

  Data DataNDelete(NodeLnk* node);

  NodeLnk* Detach(NodeLnk*& node) noexcept;

  NodeLnk* DetachMin(NodeLnk *&) noexcept;
  NodeLnk* DetachMax(NodeLnk *&) noexcept;

  NodeLnk* Skip2Left(NodeLnk *&) noexcept;
  NodeLnk* Skip2Right(NodeLnk *&) noexcept;

  NodeLnk* const &FindPointerToMin(NodeLnk *const &nod) const noexcept;
  NodeLnk* const &FindPointerToMax(NodeLnk *const &nod) const noexcept;

  NodeLnk*& FindPointerToMin(NodeLnk *&nod) noexcept;
  NodeLnk*& FindPointerToMax(NodeLnk *&nod) noexcept;

  NodeLnk*const& FindPointerTo(NodeLnk *const &nod, Data dat) const noexcept;
  NodeLnk*& FindPointerTo(NodeLnk *&nod, Data dat) noexcept;

  NodeLnk* const& FindPointerToPredecessor(NodeLnk *const &nod, Data dat) const noexcept;
  NodeLnk* const& FindPointerToSuccessor(NodeLnk *const &nod, Data dat) const noexcept;

  NodeLnk*& FindPointerToPredecessor(NodeLnk *&nod, Data dat) noexcept;
  NodeLnk*& FindPointerToSuccessor(NodeLnk *&nod, Data dat) noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
