#include "bst.hpp"

namespace lasd {

template <typename Data>
BST<Data>::BST(const MappableContainer<Data>& other){
  other.Map(
    [this](const Data& dat){
        Insert(dat);
    }
  );
}

template <typename Data>
BST<Data>::BST(MutableMappableContainer<Data>&& other) noexcept{
  other.Map(
    [this](Data& dat){
        Insert(std::move(dat));
    }
  );
}

template <typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& other){
  BinaryTreeLnk<Data>::operator=(other);
  return *this;
}
template <typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& other)noexcept{
  BinaryTreeLnk<Data>::operator=(std::move(other));
  return *this;
}

template <typename Data>
bool BST<Data>::operator==(const BST<Data>& other) const noexcept{
  if (size != other.Size()) return false;
  BTInOrderIterator<Data> IterThis(*this);
  BTInOrderIterator<Data> IterOther(other);
  while( !IterThis.Terminated() ) {
    if((*IterThis) != (*IterOther)) return false;
    ++IterThis; ++IterOther;
  }
  return true;
}


template <typename Data>
bool BST<Data>::Insert(const Data& dat){
  NodeLnk*& punt = FindPointerTo(root, dat);
  if(punt!=nullptr) return false;
  punt=new NodeLnk(dat);
  size++;
  return true;
}

template <typename Data>
bool BST<Data>::Remove(const Data& dat) { 
  NodeLnk*& punt=FindPointerTo(root, dat);
  if(punt==nullptr) return false;
  delete Detach(punt);
  return true;
}

template <typename Data>
bool BST<Data>::Insert(Data&& dat) {
  NodeLnk*& punt=FindPointerTo(root, dat);
  if(punt!=nullptr) return false;
  punt=new NodeLnk(std::move(dat));
  size++;
  return true;
}

template<typename Data>
const Data& BST<Data>::Min() const {
  if(root!=nullptr) return FindPointerToMin(root)->elem;
  else throw std::length_error("BST<Data>::Min(): Empty tree");
}

template <typename Data>
const Data& BST<Data>::Max()const{
  if(root!=nullptr) return FindPointerToMax(root)->elem;
  else throw std::length_error("BST<Data>::Max(): Empty tree");
}
template <typename Data>
Data BST<Data>::MinNRemove(){
  if(root!=nullptr) return DataNDelete(DetachMin(root));
  else throw std::length_error("BST<Data>::MinNRemove(): Empty tree");
}

template <typename Data>
Data BST<Data>::MaxNRemove(){
  if(root!=nullptr) return DataNDelete(DetachMax(root));
  else throw std::length_error("BST<Data>::MaxNRemove(): Empty tree");
}
template<typename Data>
void BST<Data>::RemoveMin(){
  if(root!=nullptr) delete DetachMin(root);
  else throw std::length_error("BST<Data>::RemoveMin(): Empty tree");
}
template<typename Data>
void BST<Data>::RemoveMax(){
  if(root!=nullptr) delete DetachMax(root);
  else throw std::length_error("BST<Data>::RemoveMax(): Empty tree");
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnk* const& node)const noexcept{
  NodeLnk* const* punt=&node;
  NodeLnk* corrente=node;
  if(corrente!=nullptr){
    while(corrente->lChild!=nullptr){
      punt=&corrente->lChild;
      corrente=corrente->lChild;
    }
  }
  return *punt;
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk* const& node)const noexcept{
  NodeLnk* const* punt = &node;
  NodeLnk* current=node;
  if(current!=nullptr){
    while(current->rChild!=nullptr){
      punt=&current->rChild;
      current=current->rChild;
    }
  }
  return *punt;
}

template <typename Data>
const Data& BST<Data>::Predecessor(const Data& val) const{
  NodeLnk* const* punt=&FindPointerToPredecessor(root,val);
  if (punt != nullptr) return (*punt)->elem;
  else throw std::length_error("BST<Data>::Predecessor(): Predecessor not found");
}
template <typename Data>
const Data& BST<Data>::Successor(const Data& val) const{
  NodeLnk* const* punt=&FindPointerToSuccessor(root,val);
  if(punt !=nullptr) return (*punt)->elem;
  else throw std::length_error("BST<Data>::Successor(): Successor not found");
}
template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& val){
  NodeLnk** punt=&FindPointerToPredecessor(root,val);
  if (punt != nullptr) return DataNDelete(Detach(*punt));
  else throw std::length_error("BST<Data>::PredecessorNRemove(): Predecessor not found");
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& val){
  NodeLnk** punt=&FindPointerToSuccessor(root,val);
  if (punt != nullptr) return DataNDelete(Detach(*punt));
  else throw std::length_error("BST<Data>::SuccessorNRemove(): Successor not found");
}
template <typename Data>
void BST<Data>::RemovePredecessor(const Data& val){
  NodeLnk** punt=&FindPointerToPredecessor(root,val);
  if (punt != nullptr) delete Detach(*punt);
  else throw std::length_error("BST<Data>::RemovePredecessor(): Predecessor not found");
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& val){
  NodeLnk** punt = &FindPointerToSuccessor(root, val);
  if (punt != nullptr) delete Detach(*punt);
  else throw std::length_error("BST<Data>::RemoveSuccessor(): Successor not found");
}

// template <typename Data>
// void BST<Data>::printBT() const {
//   std::cout<<"\n\n\tStampa di un BST non disponibile...\n\n";
// }

template <typename Data>
Data BST<Data>::DataNDelete(NodeLnk *punt) {
  Data val = punt->elem;
  delete punt;
  return val;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(typename BST<Data>::NodeLnk*& node) noexcept{
  if(node==nullptr) return nullptr;
  if (node->lChild == nullptr) return Skip2Right(node);
  else if (node->rChild == nullptr) return Skip2Left(node);
  else {
    NodeLnk* max = DetachMax(node->lChild);
    std::swap(node->elem, max->elem);
    return max;
  }

}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(typename BST<Data>::NodeLnk*& node) noexcept{
  NodeLnk* new_lChild = nullptr;
  if (node != nullptr) {
    std::swap(new_lChild, node->lChild);
    std::swap(new_lChild, node);
    size--;
  }
  return new_lChild;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(typename BST<Data>::NodeLnk*& node) noexcept{
  NodeLnk* new_rChild = nullptr;
  if (node != nullptr) {
    std::swap(new_rChild, node->rChild);
    std::swap(new_rChild, node);
    size--;
  }
  return new_rChild;
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(typename BST<Data>::NodeLnk* const& Nodo, Data val) const noexcept{
  NodeLnk* const *punt = &Nodo;
  NodeLnk* current = Nodo;

  while (current != nullptr) {
    if (val > current->elem) {
      punt = &current->rChild;
      current = current->rChild;
    } else if (val < current->elem) {
      punt = &current->lChild;
      current = current->lChild;
    } else {
      break;
    }
  }
  return *punt;

}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(typename BST<Data>::NodeLnk* const& Nodo, Data val) const noexcept{
  NodeLnk* const* predecessor = nullptr;
  NodeLnk* const* corrente = &Nodo;

  while ((*corrente) != nullptr && (*corrente)->elem != val) {
    if ((*corrente)->elem > val) {
      corrente = &(*corrente)->lChild;
    } else if ((*corrente)->elem < val) {
      predecessor = corrente;
      corrente = &(*corrente)->rChild;
    }
  }
  if ((*corrente) != nullptr && (*corrente)->lChild != nullptr) predecessor = &FindPointerToMax((*corrente)->lChild);

  return *predecessor;
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(typename BST<Data>::NodeLnk* const& node, Data val) const noexcept{
  typename BST<Data>::NodeLnk *const *successor = nullptr;
  typename BST<Data>::NodeLnk *const *current = &node;

  while ((*current) != nullptr && (*current)->elem != val) {
    if ((*current)->elem < val) current = &(*current)->rChild;
    else if ((*current)->elem > val) {
      successor = current;
      current = &(*current)->lChild;
    }
  }
  if ((*current) != nullptr && (*current)->rChild != nullptr) successor = &FindPointerToMin((*current)->rChild);

  return *successor;
}


};
