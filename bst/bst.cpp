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

template<typename Data>
BST<Data>::BST(const BST<Data>& other): BinaryTreeLnk<Data>::BinaryTreeLnk(other) {}

template<typename Data>
BST<Data>::BST(BST<Data>&& other) noexcept: BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(other)) {}


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
inline bool BST<Data>::operator==(const BST<Data>& other) const noexcept{

    // std::cout<<"\nsize: "<<size<<"\t other.size: "<<other.size<<"\n";
    // std::cout<<"\n\nthis: ";
    // this->BreadthMap(
    //     [](const Data& dat){
    //         std::cout<<"\t"<<dat;
    //     }
    // );
    // std::cout<<"\n\nother: ";
    // other.BreadthMap(
    //     [](const Data& dat){
    //         std::cout<<"\t"<<dat;
    //     }
    // );

  // std::cout<<"\n\nthis: ";
  // for(BTInOrderIterator i(*this); !(i.Terminated()); ++i) std::cout<<"\t"<<*i;

  
  // std::cout<<"\n\nother: ";
  // for(BTInOrderIterator i(other); !(i.Terminated()); ++i) std::cout<<"\t"<<*i;

  // std::cout<<"\n";


  if (size == other.Size()) {
    BTInOrderIterator<Data> IterThis(*this);
    BTInOrderIterator<Data> IterOther(other);
    for (; !IterThis.Terminated(); ++IterThis, ++IterOther) {
      // std::cout<<(*IterThis)<<"=="<<(*IterOther)<<"\t";
      if((*IterThis) != (*IterOther)) return false;
    }
    return true;
  }
  return false;
}


template <typename Data>
bool BST<Data>::Insert(const Data& dat){
  NodeLnk*& puntatore=FindPointerTo(root, dat); //NOTE: da verificare il funzionamento di FindPointerTo
  if(puntatore==nullptr){
    puntatore=new NodeLnk(dat);
    // std::cout<<"\nInserito: "<<puntatore
    size++;
    return true;
  }
  return false;
}

template <typename Data>
bool BST<Data>::Remove(const Data& dat) { //NOTE: da verificare il funzionamento e cosa ritornare
  // delete Detach(FindPointerTo(root, dat));
  // return true;

  NodeLnk*& puntatore=FindPointerTo(root, dat);
  if(puntatore!=nullptr){
    delete Detach(puntatore);
    return true;
  }
  return false;
}

template <typename Data>
bool BST<Data>::Insert(Data && dat){ //NOTE: Da verificare il funzionamento e cosa ritornare
  NodeLnk*& puntatore=FindPointerTo(root, dat);
  if(puntatore==nullptr){
    puntatore=new NodeLnk(std::move(dat));
    size++;
    return true;
  }
  return false;
}

template<typename Data>
const Data& BST<Data>::Min() const {
  if (root != nullptr) return FindPointerToMin(root)->elem;
  else throw std::length_error("BST<Data>::Min(): Empty tree");
}

template <typename Data>
const Data& BST<Data>::Max()const{
  if (root != nullptr) return FindPointerToMax(root)->elem;
  else throw std::length_error("BST<Data>::Max(): Empty tree");
}
template <typename Data>
Data BST<Data>::MinNRemove(){
  if (root != nullptr) return DataNDelete(DetachMin(root));
  else throw std::length_error("BST<Data>::MinNRemove(): Empty tree");
}

template <typename Data>
Data BST<Data>::MaxNRemove(){
  if (root != nullptr) return DataNDelete(DetachMax(root));
  else throw std::length_error("BST<Data>::MaxNRemove(): Empty tree");
}
template<typename Data>
void BST<Data>::RemoveMin(){
  if (root != nullptr) delete DetachMin(root);
  else throw std::length_error("BST<Data>::RemoveMin(): Empty tree");
}
template<typename Data>
void BST<Data>::RemoveMax(){
  if (root != nullptr) delete DetachMax(root);
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
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk* const& Nodo)const noexcept{
  NodeLnk* const* puntatore=&Nodo;
  NodeLnk* corrente=Nodo;
  if(corrente!=nullptr){
    while(corrente->rChild!=nullptr){
      puntatore=&corrente->rChild;
      corrente=corrente->rChild;
    }
  }
  return *puntatore;
}
template <typename Data>
const Data& BST<Data>::Predecessor(const Data& valore) const{
  NodeLnk* const* puntatore=&FindPointerToPredecessor(root,valore);
  if (puntatore != nullptr) return (*puntatore)->elem;
  else throw std::length_error("BST<Data>::Predecessor(): Predecessor not found");
}

template <typename Data>
const Data& BST<Data>::Successor(const Data& valore) const{
  NodeLnk* const* puntatore=&FindPointerToSuccessor(root,valore);
  if(puntatore !=nullptr) return (*puntatore)->elem;
  else throw std::length_error("BST<Data>::Successor(): Successor not found");
}
template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& valore){
  NodeLnk** puntatore=&FindPointerToPredecessor(root,valore);
  if (puntatore != nullptr) return DataNDelete(Detach(*puntatore));
  else throw std::length_error("BST<Data>::PredecessorNRemove(): Predecessor not found");
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& valore){
  NodeLnk** puntatore=&FindPointerToSuccessor(root,valore);
  if (puntatore != nullptr) return DataNDelete(Detach(*puntatore));
  else throw std::length_error("BST<Data>::SuccessorNRemove(): Successor not found");
}
template <typename Data>
void BST<Data>::RemovePredecessor(const Data& valore){
  NodeLnk** puntatore=&FindPointerToPredecessor(root,valore);
  if (puntatore != nullptr) delete Detach(*puntatore);
  else throw std::length_error("BST<Data>::RemovePredecessor(): Predecessor not found");
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& valore){
  NodeLnk **puntatore = &FindPointerToSuccessor(root, valore);
  if (puntatore != nullptr) delete Detach(*puntatore);
  else throw std::length_error("BST<Data>::RemoveSuccessor(): Successor not found");
}
template <typename Data>
bool BST<Data>::Exists(const Data& valore)const noexcept{
  return (FindPointerTo(root,valore) !=nullptr);
}

// template <typename Data>
// void BST<Data>::printBT() const {
//   std::cout<<"\n\n\tStampa di un BST non disponibile...\n\n";
// }

template <typename Data>
Data BST<Data>::DataNDelete(NodeLnk *puntatore)
{
  Data valore = puntatore->elem;
  delete puntatore;
  return valore;
}
template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(typename BST<Data>::NodeLnk*& node) noexcept{
  if (node != nullptr) {
    if (node->lChild == nullptr) return Skip2Right(node);
    else if (node->rChild == nullptr) return Skip2Left(node);
    else {
      NodeLnk *max = DetachMax(node->lChild);
      std::swap(node->elem, max->elem);
      return max;
    }
  }
  return nullptr;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(typename BST<Data>::NodeLnk*& node)noexcept{
  return Skip2Left(FindPointerToMax(node));
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
template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(typename BST<Data>::NodeLnk*& node)noexcept{
  return Skip2Right(FindPointerToMin(node));
}
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(typename BST<Data>::NodeLnk*& node) noexcept{
  NodeLnk *new_rChild = nullptr;
  if (node != nullptr) {
    std::swap(new_rChild, node->rChild);
    std::swap(new_rChild, node);
    size--;
  }
  return new_rChild;
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnk*& Nodo) noexcept{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(Nodo));
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk*& Nodo) noexcept{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(Nodo));
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(typename BST<Data>::NodeLnk* const& Nodo, Data valore) const noexcept{
  NodeLnk *const *puntatore = &Nodo;
  NodeLnk *corrente = Nodo;

  while (corrente != nullptr) {
    if (valore > corrente->elem) {
      puntatore = &corrente->rChild;
      corrente = corrente->rChild;
    } else if (valore < corrente->elem) {
      puntatore = &corrente->lChild;
      corrente = corrente->lChild;
    } else {
      break;
    }
  }
  return *puntatore;
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(typename BST<Data>::NodeLnk*& Nodo, Data valore) noexcept{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(Nodo,valore));
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(typename BST<Data>::NodeLnk* const& Nodo, Data valore) const noexcept{
  NodeLnk *const *predecessor = nullptr;
  NodeLnk *const *corrente = &Nodo;

  while ((*corrente) != nullptr && (*corrente)->elem != valore) {
    if ((*corrente)->elem > valore) {
      corrente = &(*corrente)->lChild;
    } else if ((*corrente)->elem < valore) {
      predecessor = corrente;
      corrente = &(*corrente)->rChild;
    }
  }
  if ((*corrente) != nullptr && (*corrente)->lChild != nullptr) predecessor = &FindPointerToMax((*corrente)->lChild);

  return *predecessor;
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(typename BST<Data>::NodeLnk* const& node, Data valore) const noexcept{
  typename BST<Data>::NodeLnk *const *successor = nullptr;
  typename BST<Data>::NodeLnk *const *current = &node;

  while ((*current) != nullptr && (*current)->elem != valore) {
    if ((*current)->elem < valore) current = &(*current)->rChild;
    else if ((*current)->elem > valore) {
      successor = current;
      current = &(*current)->lChild;
    }
  }
  if ((*current) != nullptr && (*current)->rChild != nullptr) successor = &FindPointerToMin((*current)->rChild);

  return *successor;
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(typename BST<Data>::NodeLnk*& Nodo, Data valore) noexcept{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(Nodo,valore));
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(typename BST<Data>::NodeLnk*& Nodo, Data valore) noexcept{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(Nodo,valore));
}

};
