#include "binarytreevec.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data &dat2, int i2, BinaryTreeVec<Data>* bt2) {
    this->bt = bt2;
    this->i = i2;
    this->dat=dat2;  
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& dat2, int i2, BinaryTreeVec<Data>* bt2) {
    this->bt = bt2;
    this->i = i2;
    std::swap(dat, dat2);  
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec &other) {
    this->dat=other.dat;  
    this->bt = other.bt;
    this->i=other.i;
    return *this;
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(NodeVec&& other) noexcept {
    std::swap(this->dat, other.dat);  
    std::swap(this->bt, other.bt);
    std::swap(this->i, other.i);
    return *this;
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return (Index()*2+1<(bt->Nodes).Size()) && ((bt->Nodes)[Index()*2+1] != nullptr);
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    return Index()*2+2<(bt->Nodes).Size() && (bt->Nodes)[Index()*2+2] != nullptr;
}

template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if(HasLeftChild()) return *(bt->Nodes).operator[](Index()*2+1);
    else throw std::out_of_range("BinaryTreeVec<Data>::NodeVec::LeftChild(): Not found!");
}

template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if(HasRightChild()) return *(bt->Nodes).operator[](Index()*2+2);//[Index()*2+2];
    else throw std::out_of_range("BinaryTreeVec<Data>::NodeVec::RightChild(): Not found!");
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() {
    if(HasLeftChild()) return *(bt->Nodes).operator[](Index()*2+1);
    else throw std::out_of_range("BinaryTreeVec<Data>::NodeVec::LeftChild(): Not found!");
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() {
    if(HasRightChild()) return *(bt->Nodes).operator[](Index()*2+2);
    else throw std::out_of_range("BinaryTreeVec<Data>::NodeVec::RightChild(): Not found!");
}

/* ************************************************************************** */

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const MappableContainer<Data>& other) : Nodes(other.Size()){
    int i = 0;
    other.Map(
        [this, &i](const Data& dat){
            this->Nodes[i] = new NodeVec(dat, i, this); i++;
        }
    );
    this->size=other.Size();
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MutableMappableContainer<Data> &&other) noexcept : Nodes(other.Size()) {
    int i = 0;
    other.Map(
        [this, &i](Data& dat){
            this->Nodes[i] = new NodeVec(std::move(dat), i, this); i++;
        }
    );
    this->size = other.Size();
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> &other) : Nodes(other.Size()) {
    this->size=other.Size();
    for(ulong i{0}; i<this->Size(); i++) this->Nodes[i] = new NodeVec(other.Nodes[i]->Element(), i, this);
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> &&other) noexcept  { //, Nodes(std::move(other.Nodes)) {
    std::swap(Nodes, other.Nodes);
    std::swap(this->size, other.size);
    for(int i=0; i<this->Size(); i++) Nodes[i]->bt = this;
    for(int i=0; i<other.Size(); i++) other.Nodes[i]->bt = &other;
}

template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec(){
    Clear();
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec& other) {
    Clear();
    Nodes.Resize(other.Size());
    this->size=other.Size();
    for(ulong i{0}; i<this->Size(); i++) this->Nodes[i] = new NodeVec(other.Nodes[i]->Element(), i, this);
    return *this;
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec &&other) noexcept {
    std::swap(this->Nodes, other.Nodes);
    std::swap(this->size, other.size);
    for(int i=0; i<this->Size(); i++) Nodes[i]->bt = this;
    for(int i=0; i<other.Size(); i++) other.Nodes[i]->bt = &other;
    return *this;
}

template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    if(!this->Empty()) return *Nodes[0];
    else throw std::length_error("BinaryTreeVec<Data>::Root(): Empty tree");
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() {
    if(!this->Empty()) return *Nodes[0];
    else throw std::length_error("BinaryTreeVec<Data>::Root(): Empty tree");
}

template <typename Data>
void BinaryTreeVec<Data>::Clear() {
    for(ulong i{0}; i<Nodes.Size(); i++) {
        if(Nodes[i]!=nullptr){
            delete Nodes[i];
            Nodes[i]=nullptr;
        }
    }
    Nodes.Clear();
    this->size=0;
}

/* ************************************************************************** */

}
