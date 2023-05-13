
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public ClearableContainer,
             virtual public DictionaryContainer<Data>,
             virtual public LinearContainer<Data> {

private:

protected:

  
/* ********************************************************************** */
  struct Node {

    // Data
    Data elem {};
    Node* next = nullptr;

    // Specific constructors
    Node(const Data& new_elem);
    Node(Data&& new_elem) noexcept;

    // Copy constructor
    Node(const Node& new_node);
    // Move constructor
    Node(Node&& new_node) noexcept;

    // Destructor
    virtual ~Node() = default;

    // Comparison operators
    inline bool operator==(const Node& other) { return (other.elem == elem); }
    inline bool operator!=(const Node& other) { return (other.elem != elem); }

    /* ********************************************************************** */

  };

  Node* head = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const MappableContainer<Data>& cont); // A list obtained from a MappableContainer
  List(MutableMappableContainer<Data>&& cont) noexcept;// A list obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List& other);

  // Move constructor
  List(List&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List() {
    while(!Empty()) RemoveFromFront();
  }

  /* ************************************************************************ */

  // Copy assignment
  List<Data>& operator=(const List& other);

  // Move assignment
  List<Data>& operator=(List&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List& other) const noexcept;
  bool operator!=(const List& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual void InsertAtFront(const Data& new_elem); // Copy of the value
  virtual void InsertAtFront(Data&& new_elem); // Move of the value
  virtual void RemoveFromFront(); // (must throw std::length_error when empty)
  virtual Data FrontNRemove(); // (must throw std::length_error when empty)

  virtual void InsertAtBack(const Data& new_elem); // Copy of the value
  virtual void InsertAtBack(Data&& new_elem); // Move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual bool Insert(const Data& elem) override; // Copy of the value //Solo se l'elemento non è già presente
  virtual bool Insert(Data&& elem) override;  // Move of the value
  virtual bool Remove(const Data& elem) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data & operator[](const ulong index) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](const ulong index) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  const inline Data& Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  inline Data& Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  const Data& Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;
  virtual void Fold(FoldFunctor func, void* acc) const override { PreOrderFold(func, acc); }; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderFoldableContainer)
  virtual void inline PreOrderFold(FoldFunctor func, void* acc) const;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderFoldableContainer)
  virtual void PostOrderFold(FoldFunctor func, void* acc) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;
  virtual void Map(MapFunctor func) const override { PreOrderMap(func); }; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  virtual void PreOrderMap(MapFunctor func) const override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  virtual void PostOrderMap(MapFunctor func) const override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutableMappableContainer)

  using typename MutableMappableContainer<Data>::MutableMapFunctor;
  virtual void Map(MutableMapFunctor func) override { PreOrderMap(func); }; // Override MutableMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePreOrderMappableContainer)

  virtual inline void PreOrderMap(MutableMapFunctor func) override; // Override MutablePreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePostOrderMappableContainer)

  virtual void PostOrderMap(MutableMapFunctor func) override; // Override MutablePostOrderMappableContainer member

protected:

  void AuxPostOrderFold(const Node* nodo, FoldFunctor func, void* acc) const;
  void AuxPreOrderFold(const Node* nodo, FoldFunctor func, void* acc) const;
  
  void AuxPostOrderMap(const Node* nodo, MapFunctor func) const;
  void AuxPreOrderMap(const Node* nodo, MapFunctor func) const;
  
  void AuxPostOrderMap(Node* nodo, MutableMapFunctor func);
  void AuxPreOrderMap(Node* nodo, MutableMapFunctor func);
  
  /* ************************************************************************ */

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
