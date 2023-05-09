
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public MutablePreOrderMappableContainer<Data>,
                        virtual public MutablePostOrderMappableContainer<Data> {

private:

protected:

  using Container::size;

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */


  // Copy assignment
  LinearContainer& operator=(const LinearContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  LinearContainer& operator=(LinearContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.


  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer& other) const noexcept; // Comparison of abstract types is possible.
  inline bool operator!=(const LinearContainer& other) const noexcept { return !operator==(other); }; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& operator[](ulong index) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)
  virtual Data& operator[](ulong index) = 0; // (mutable version; concrete function must throw std::out_of_range when out of range)

  virtual const Data& Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Front(); // (mutable version; concrete function must throw std::length_error when empty)

  virtual const Data& Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Back();  // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  inline void Fold(FoldFunctor func, void* acc) const override { PreOrderMappableContainer<Data>::Fold(func, acc); }; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  virtual void Map(MapFunctor func) const override { PreOrderMap(func); }; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  virtual void PreOrderMap(MapFunctor func) const override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  virtual void PostOrderMap(const MapFunctor func) const override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutableMappableContainer)

  using typename MutableMappableContainer<Data>::MutableMapFunctor;

  virtual void Map(MutableMapFunctor func) override { PreOrderMap(func); }; // Override MutableMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePreOrderMappableContainer)

  virtual void PreOrderMap(MutableMapFunctor func) override; // Override MutablePreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePostOrderMappableContainer)

  virtual void PostOrderMap(MutableMapFunctor func) override;// Override MutablePostOrderMappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class SortableLinearContainer : virtual public LinearContainer<Data> {

private:

protected:

  using Container::size;

public:

  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer& operator=(const SortableLinearContainer& other) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  SortableLinearContainer& operator=(SortableLinearContainer&& other) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(SortableLinearContainer& other) const noexcept { return LinearContainer<Data>::operator==(other); }; // Comparison of abstract types is possible.
  inline bool operator!=(SortableLinearContainer& other) const noexcept { return LinearContainer<Data>::operator!=(other); }; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member function

  inline virtual void Sort() noexcept { if(!(this->Empty())) QuickSort(0, size-1); };

protected:

  void QuickSort(ulong p, ulong r) noexcept;
  ulong Partition(ulong p, ulong r) noexcept;

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
