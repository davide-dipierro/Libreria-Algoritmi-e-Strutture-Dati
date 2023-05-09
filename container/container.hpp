#ifndef CONTAINER_HPP
#define CONTAINER_HPP

typedef unsigned long int ulong;

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

private:

protected:

  ulong size = 0; //Dimensione della struttura

public:

  // Destructor
  virtual ~Container() = default; //Utilizzo del distruttore di default (Virtuale)

  /* ************************************************************************ */

  // Copy assignmen //Non utilizzabile
  Container& operator=(const Container& other) = delete;

  // Move assignment //Non utilizzabile
  Container& operator=(Container&& other) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container& other) const noexcept = delete; //Non utilizzabile
  bool operator!=(const Container& other) const noexcept = delete; //Non utilizzabile

  /* ************************************************************************ */

  // Specific member functions
  inline virtual bool Empty() const noexcept { return size==0; }; // Virtuale inline

  inline virtual ulong Size() const noexcept { return size; }; // Virtuale inline

};

/* ************************************************************************** */

class ClearableContainer : virtual public Container {

private:

protected:

public:

  // Destructor
  virtual ~ClearableContainer() = default; //Utilizzo del distruttore di default

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer& operator=(const ClearableContainer& other) = delete; //Non utilizzabile

  // Move assignment
  ClearableContainer& operator=(ClearableContainer&& other) noexcept = delete; //Non utilizzabile

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer& other) const noexcept = delete; //Non utilizzabile
  bool operator!=(const ClearableContainer& other) const noexcept = delete; //Non utilizzabile

  /* ************************************************************************ */

  // Specific member function

  virtual void Clear() = 0; // Virtuale pura

};

/* ************************************************************************** */

class ResizableContainer : virtual public ClearableContainer {

private:

protected:

public:

  // Destructor
  virtual ~ResizableContainer() = default; // Utilizzo del distruttor di default (Virtuale)

  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer& operator=(const ResizableContainer& other) = delete; // Non utilizzabile

  // Move assignment
  ResizableContainer& operator=(ResizableContainer&& other) noexcept = delete; // Non utilizzabile

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResizableContainer& other) const noexcept = delete; // Non utilizzabile
  bool operator!=(const ResizableContainer& other) const noexcept = delete; // Non utilizzabile

  /* ************************************************************************ */

  // Specific member function

  virtual void Resize(const ulong n) = 0; // Virtuale pura
 
  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  virtual void Clear() override { Resize(0); } // Override della funzione Clear() ereditata

};

/* ************************************************************************** */

}

#endif
