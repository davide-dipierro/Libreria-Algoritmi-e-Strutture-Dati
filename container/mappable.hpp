
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "foldable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MappableContainer : virtual public FoldableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~MappableContainer() = default; // Utilizzo del distruttore di default (Virtual)

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer& operator=(const MappableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  MappableContainer& operator=(MappableContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const MappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member function

  using MapFunctor = std::function<void(const Data &)>; // Definzione della MapFunctor void func(dato)
  virtual void Map(MapFunctor func) const = 0; // Virtuale pura

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;
  virtual void inline Fold(FoldFunctor func, void* acc) const override; // Override FoldableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer : virtual public PreOrderFoldableContainer<Data>,
                                  virtual public MappableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderMappableContainer& operator=(const PreOrderMappableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  PreOrderMappableContainer& operator=(PreOrderMappableContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const PreOrderMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFunctor;

  virtual void PreOrderMap(MapFunctor func) const = 0;
  virtual void inline Map(MapFunctor func) const override { PreOrderMap(func); } // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;
  virtual void inline Fold(FoldFunctor func, void* acc) const override { MappableContainer<Data>::Fold(func, acc); }; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderFoldableContainer)

  virtual void inline PreOrderFold(FoldFunctor func, void* acc) const override; // Override PreOrderFoldableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer : virtual public PostOrderFoldableContainer<Data>,
                                  virtual public MappableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PostOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  virtual PostOrderMappableContainer& operator=(const PostOrderMappableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual PostOrderMappableContainer& operator=(PostOrderMappableContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const PostOrderMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFunctor;

  virtual void PostOrderMap(MapFunctor func) const = 0;
  virtual void Map(MapFunctor func) const override { PostOrderMap(func); } // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)
  using typename FoldableContainer<Data>::FoldFunctor;

  void inline Fold(FoldFunctor func, void* acc) const override { MappableContainer<Data>::Fold(func, acc); }; // Override FoldableContainer member
  void inline PostOrderFold(FoldFunctor func, void* acc) const override; // Override PostOrderFold member

};

/* ************************************************************************** */

template <typename Data>
class InOrderMappableContainer : virtual public MappableContainer<Data>, 
                                 virtual public InOrderFoldableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~InOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  virtual InOrderMappableContainer& operator=(const InOrderMappableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual InOrderMappableContainer& operator=(InOrderMappableContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const InOrderMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member function
  using typename MappableContainer<Data>::MapFunctor;
  virtual void InOrderMap(MapFunctor func) const = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  inline virtual void Map(MapFunctor func) const override { InOrderMap(func); } // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)
  using typename FoldableContainer<Data>::FoldFunctor;
  inline void Fold(FoldFunctor func, void* acc) const override { MappableContainer<Data>::Fold(func, acc); }; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderFoldableContainer)
  void InOrderFold(FoldFunctor func, void* acc) const override; // Override InOrderFold member

};

/* ************************************************************************** */

template <typename Data>
class BreadthMappableContainer : virtual public MappableContainer<Data>,
                                 virtual public BreadthFoldableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~BreadthMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  virtual BreadthMappableContainer& operator=(const BreadthMappableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual BreadthMappableContainer& operator=(BreadthMappableContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BreadthMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member function
  using typename MappableContainer<Data>::MapFunctor;
  virtual void BreadthMap(MapFunctor func) const = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  inline virtual void Map(MapFunctor func) const override { BreadthMap(func); } // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)
  using typename FoldableContainer<Data>::FoldFunctor;
  inline void Fold(FoldFunctor func, void* acc) const override { MappableContainer<Data>::Fold(func, acc); }; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthFoldableContainer)
  void BreadthFold(FoldFunctor func, void* acc) const override; // Override BreadthFold member

};

/* ************************************************************************** */

template <typename Data>
class MutableMappableContainer : virtual public MappableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~MutableMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableMappableContainer& operator=(const MutableMappableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  MutableMappableContainer& operator=(MutableMappableContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MutableMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const MutableMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member function

  using MutableMapFunctor = std::function<void(Data &)>;
  
  virtual void Map(MutableMapFunctor func) = 0;

};

/* ************************************************************************** */

template <typename Data>
class MutablePreOrderMappableContainer : virtual public MutableMappableContainer<Data>,
                                          virtual public PreOrderMappableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~MutablePreOrderMappableContainer() = default;

  /* ************************************************************************ */

  
  // Copy assignment
  MutablePreOrderMappableContainer& operator=(const MutablePreOrderMappableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  MutablePreOrderMappableContainer& operator=(MutablePreOrderMappableContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MutablePreOrderMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const MutablePreOrderMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MutableMappableContainer<Data>::MutableMapFunctor;

  virtual void PreOrderMap(MutableMapFunctor func) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableMappableContainer)

  virtual void inline Map(MutableMapFunctor func) override { PreOrderMap(func); };

};

/* ************************************************************************** */

template <typename Data>
class MutablePostOrderMappableContainer : virtual public MutableMappableContainer<Data>,
                                          virtual public PostOrderMappableContainer<Data> {
private:

protected:

public:

  // Destructor
  virtual ~MutablePostOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutablePostOrderMappableContainer& operator=(const MutablePostOrderMappableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  MutablePostOrderMappableContainer& operator=(MutablePostOrderMappableContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MutablePostOrderMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const MutablePostOrderMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.


  /* ************************************************************************ */

  // Specific member function

  using typename MutableMappableContainer<Data>::MutableMapFunctor;

  virtual void PostOrderMap(MutableMapFunctor func) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableMappableContainer)

  virtual void inline Map(MutableMapFunctor func) override { PostOrderMap(func); }; // Override MutableMappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class MutableInOrderMappableContainer : virtual public MutableMappableContainer<Data>,
                                        virtual public InOrderMappableContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~MutableInOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableInOrderMappableContainer& operator=(const MutableInOrderMappableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  MutableInOrderMappableContainer& operator=(MutableInOrderMappableContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MutableInOrderMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const MutableInOrderMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member function
  using typename MutableMappableContainer<Data>::MutableMapFunctor;

  virtual void InOrderMap(MutableMapFunctor func) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableMappableContainer)
  inline virtual void Map(MutableMapFunctor func) override { InOrderMap(func); }; // Override MutableMappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class MutableBreadthMappableContainer : virtual public MutableMappableContainer<Data>,
                                        virtual public BreadthMappableContainer<Data>{
private:

protected:

public:

  // Destructor
  virtual ~MutableBreadthMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableBreadthMappableContainer& operator=(const MutableBreadthMappableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  MutableBreadthMappableContainer& operator=(MutableBreadthMappableContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MutableBreadthMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const MutableBreadthMappableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member function
  using typename MutableMappableContainer<Data>::MutableMapFunctor;

  virtual void BreadthMap(MutableMapFunctor func) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableMappableContainer)
  inline virtual void Map(MutableMapFunctor func) override { BreadthMap(func); }; // Override MutableMappableContainer member

};

/* ************************************************************************** */

}

#include "mappable.cpp"

#endif
