
#ifndef FOLDABLE_HPP
#define FOLDABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class FoldableContainer : virtual public TestableContainer<Data>{

private:

protected:

public:

  //Destructor
  virtual ~FoldableContainer() = default; // Utilizzo del distruttore di default (Virtual)

  /* ************************************************************************ */

  // Copy assignment
  virtual FoldableContainer& operator=(const FoldableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual FoldableContainer& operator=(const FoldableContainer&& other) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const FoldableContainer& other) const noexcept = delete; // Non utilizzabile
  bool operator!=(const FoldableContainer& other) const noexcept = delete; // Non utilizzabile

  /* ************************************************************************ */

  // Specific member function
  
  using FoldFunctor = std::function<void(const Data&, void*)>; // Definizione della FoldFunctor void func(dato, accumulatore)

  virtual void Fold(FoldFunctor func, void* acc) const = 0; // Virtuale pura

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)

  virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PreOrderFoldableContainer : virtual public FoldableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PreOrderFoldableContainer() = default; // Utilizzo del distruttore di default (Virtual)

  /* ************************************************************************ */

  // Copy assignment
  PreOrderFoldableContainer& operator=(const PreOrderFoldableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  PreOrderFoldableContainer& operator=(PreOrderFoldableContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.


  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderFoldableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const PreOrderFoldableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void PreOrderFold(FoldFunctor func, void* acc) const = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)

  virtual void inline Fold(FoldFunctor func, void* acc) const override { // Override FoldableContainer member
    PreOrderFold(func, acc);
  }

};

/* ************************************************************************** */

template <typename Data>
class PostOrderFoldableContainer : virtual public FoldableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PostOrderFoldableContainer() = default; // Utilizzo del distruttore di default (Virtual)

  /* ************************************************************************ */

  // Copy assignment
  PostOrderFoldableContainer& operator=(const PostOrderFoldableContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  PostOrderFoldableContainer& operator=(PostOrderFoldableContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.


  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderFoldableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const PostOrderFoldableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void PostOrderFold(FoldFunctor func, void* acc) const = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)

  virtual void inline Fold(FoldFunctor func, void* acc) const override { // Override FoldableContainer member
    PostOrderFold(func, acc);
  }  

};

/* ************************************************************************** */


template <typename Data>
class InOrderFoldableContainer : virtual public FoldableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~InOrderFoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  InOrderFoldableContainer& operator=(const InOrderFoldableContainer& other) = delete;

  // Move assignment
  InOrderFoldableContainer& operator=(InOrderFoldableContainer&& other) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderFoldableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const InOrderFoldableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.


  /* ************************************************************************ */

  // Specific member function
  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void InOrderFold(FoldFunctor func, void* acc) const = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)
  inline virtual void Fold(FoldFunctor func, void* acc) const override { InOrderFold(func, acc); }  

};

/* ************************************************************************** */

template <typename Data>
class BreadthFoldableContainer : virtual public FoldableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~BreadthFoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthFoldableContainer& operator=(const BreadthFoldableContainer& other) = delete;

  // Move assignment
  BreadthFoldableContainer& operator=(BreadthFoldableContainer&& other) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthFoldableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BreadthFoldableContainer& other) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member function
  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void BreadthFold(FoldFunctor func, void* acc) const = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)
  inline virtual void Fold(FoldFunctor func, void* acc) const override { BreadthFold(func, acc); }  

};

/* ************************************************************************** */

}

#include "foldable.cpp"

#endif
