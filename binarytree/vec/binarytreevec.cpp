#include "binarytreevec.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data &dat, int i, BinaryTreeVec<Data>* bt) {
    this->bt = bt;
    this->i=i;
    Element()=dat;  
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& dat, int i, BinaryTreeVec<Data>* bt) {
    this->bt = bt;
    this->i=i;
    std::swap(Element(), dat);  
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec &other) {
    Element()=other.Element();  
    // this->bt = other.bt;
    // this->i=other.i;
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(NodeVec&& other) noexcept {
    std::swap(Element(), other.Element());  
    // std::swap(this->bt, other.bt);
    // std::swap(this->i, other.i);
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
BinaryTreeVec<Data>::BinaryTreeVec(const MappableContainer<Data>& other) : Elements(other.Size()), Nodes(other.Size()){
    int i = 0;
    this->size=other.Size();
    other.Map(
        [this, &i](const Data& dat){
            this->Nodes[i] = new NodeVec(dat, i, this); i++;
        }
    );
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MutableMappableContainer<Data> &&other) noexcept : Elements(other.Size()), Nodes(other.Size()) {
    int i = 0;
    other.Map(
        [this, &i](const Data& dat){
            this->Nodes[i] = new NodeVec(std::move(dat), i, this);
            i++;
        }
    );
    std::swap(this->size, other.size);
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> &other) : Elements(other.Elements), Nodes(other.Nodes) {
    this->size=other.size;
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> &&other) noexcept : Elements(std::move(other.Elements)), Nodes(std::move(other.Nodes)) {
    std::swap(this->size, other.size);
}

template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec(){
    for(ulong i{0}; i<Nodes.Size(); i++) if(Nodes[i]!=nullptr) delete Nodes[i];
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec& other) {
    Clear();
    Elements = other.Elements;
    Nodes=other.Nodes;
    this->size = other.size;
    return *this;
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec &&other) noexcept {
    Clear();
    Elements = std::move(other.Elements);
    Nodes = std::move(other.Nodes);
    std::swap(this->size, other.size);
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

/* ************************************************************************** */

}
