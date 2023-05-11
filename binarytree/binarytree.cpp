#include "binarytree.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree& other) const noexcept {
    if(size!=other.size) return false;
    BTPreOrderIterator i(*this);
    BTPreOrderIterator j(other);
    while(!(i.Terminated()) && !(j.Terminated())){
        if((*i)!=(*j)) return false;
        ++i; ++j;
    }
    return true;
}

template <typename Data>
void BinaryTree<Data>::Fold(FoldFunctor func, void *acc) const {
    for(BTPreOrderIterator i(*this); !(i.Terminated()); ++i) func(*i, acc);
}

template <typename Data>
void BinaryTree<Data>::PreOrderMap(MapFunctor func) const {
    for(BTPreOrderIterator i(*this); !(i.Terminated()); ++i) func(*i);
}

template <typename Data>
void BinaryTree<Data>::PostOrderMap(MapFunctor func) const {
    for(BTPostOrderIterator i(*this); !(i.Terminated()); ++i) func(*i);
}

template <typename Data>
void BinaryTree<Data>::InOrderMap(MapFunctor func) const {
    for(BTInOrderIterator i(*this); !(i.Terminated()); ++i) func(*i);
}

template <typename Data>
void BinaryTree<Data>::BreadthMap(MapFunctor func) const {
    for(BTBreadthIterator i(*this); !(i.Terminated()); ++i) func(*i);
}

template <typename Data>
void BinaryTree<Data>::printBT(const std::string &prefix, const BinaryTree<Data>::Node* node, bool isLeft) const {
    if( node != nullptr ) {
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->Element() << std::endl;

        // enter the next tree level - left and right branch
        if(node->HasLeftChild())printBT( prefix + (isLeft ? "│   " : "    "), &node->LeftChild(), true);
        if(node->HasRightChild())printBT( prefix + (isLeft ? "│   " : "    "), &node->RightChild(), false);
    }
}

/* ************************************************************************** */


template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MutableMapFunctor func) {
    for(BTPreOrderMutableIterator<Data> i(*this); !(i.Terminated()); ++i) func(*i);
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MutableMapFunctor func) {
    for(BTPostOrderMutableIterator<Data> i(*this); !(i.Terminated()); ++i) func(*i);
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MutableMapFunctor func) {
    for(BTInOrderMutableIterator i(*this); !(i.Terminated()); ++i) func(*i);
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MutableMapFunctor func) {
    for(BTBreadthMutableIterator i(*this); !(i.Terminated()); ++i) func(*i);
}

/* ************************************************************************** */

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& other) {
    if(!other.Empty()) root=current=&other.Root();
}


template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator &other) : stack(other.stack) {
    root = other.root;
    current = other.current;
}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& other) noexcept : stack(std::move(other.stack)) {
    std::swap(root, other.root);
    std::swap(current, other.current); 
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& other) {
    // if(this == &other) return *this; penso mai messo, ma andrebbe messo ovunque
    current=other.current;
    root=other.root;
    stack=other.stack;
    return *this;
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& other) noexcept {
    current = std::move(other.current);
    root = std::move(other.root);
    stack = std::move(other.stack); //NOTE: si può fare? secondo me sì perché abbiamo fatto l'operatore && in stack
    return *this;
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator &other) const noexcept {
    return (current==other.current && root==root);
}

template <typename Data>
const Data& BTPreOrderIterator<Data>::operator*() const {
    if(Terminated()) throw std::out_of_range("Iterator is terminated.");
    else return current->Element();
}

template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    if(!Terminated()){
        if(current->HasLeftChild()){
            if(current->HasRightChild()) stack.Push(&current->RightChild());
            current=&(current->LeftChild());
        }else if(current->HasRightChild()) { 
            current=&(current->RightChild());
        } else if (!stack.Empty()) {
            current=stack.TopNPop();
        } else {
            current=nullptr;
        }
    } else throw std::out_of_range("BTPreOrderIterator<Data>::operator++: Iterator is terminated.");
    return *this;
}

template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept {
    current=root;
}

/* ************************************************************************** */

template <typename Data>
BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator& other) {
    // if(this == &other) return *this; penso mai messo, ma andrebbe messo ovunque
    this->current=other.current;
    this->root=other.root;
    this->stack=other.stack;
    return *this;
}

template <typename Data>
BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator&& other) noexcept {
    this->current = std::move(other.current);
    this->root = std::move(other.root);
    this->stack = std::move(other.stack); //NOTE: si può fare? secondo me sì perché abbiamo fatto l'operatore && in stack
    return *this;
}

/* ************************************************************************** */

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& other){
    root= (other.Empty()) ? nullptr : &other.Root();
    current=DeepestLeftLeaf(root);
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& other) {
    stack=other.stack;
    root=other.root;
    current=other.current;
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& other) noexcept : stack(std::move(other.stack)){
    std::swap(current, other.current);
    std::swap(root, other.root); 
}

template <typename Data>
const Data& BTPostOrderIterator<Data>::operator*() const {
    if(Terminated()) throw std::out_of_range("Iterator is terminated.");
    else return current->Element();
}

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++(){
    if(!Terminated()){
        if(!(stack.Empty())){
            if (stack.Top()->HasRightChild() && !(&(stack.Top()->RightChild()) == current)) {
                current = &(stack.Top()->RightChild());
                current = DeepestLeftLeaf(current);
            } else {
                current = stack.TopNPop();
            }
        } else current = nullptr;
    } else throw std::out_of_range("BTPostOrderIterator<Data>::operator++: Iterator is terminated.");

    return *this;
}

template <typename Data>
const typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::DeepestLeftLeaf(const typename BinaryTree<Data>::Node* actual){
    if(actual!=nullptr){
        while(actual->HasLeftChild()){
            stack.Push(actual);
            actual = &(actual->LeftChild());
        }
        if(actual->HasRightChild()){
            stack.Push(actual);
            actual = &(actual->RightChild());
            actual = DeepestLeftLeaf(actual);
        }
    }
    return actual;
}

template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept {
    current=DeepestLeftLeaf(root);
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& other) {
    current=other.current;
    root=other.root;
    stack=other.stack;
    return *this;
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& other) noexcept {
    std::swap(current, other.current);
    std::swap(root, other.root);
    std::swap(stack, other.stack); //NOTE: si può fare? secondo me sì perché abbiamo fatto l'operatore && in stack
    return *this;
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator &other) const noexcept {
    return (current==other.current && root==root);
}

/* ************************************************************************** */

template <typename Data>
BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator& other) {
    this->current=other.current;
    this->root=other.root;
    this->stack=other.stack;
    return *this;
}

template <typename Data>
BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator&& other) noexcept {
    std::swap(this->current, other.current);
    std::swap(this->root, other.root);
    std::swap(this->stack, other.stack);
    return *this;
}

/* ************************************************************************** */

template <typename Data>
const typename BinaryTree<Data>::Node *BTInOrderIterator<Data>::Min2(const typename BinaryTree<Data>::Node* actual) {
    while (actual != nullptr && (actual->HasLeftChild())) {
        stack.Push(actual);
        actual = &actual->LeftChild();
    }
    return actual;
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &other) {
    root = (other.Empty()) ? nullptr : &other.Root();
    current=Min2(root);
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator& other) {
    stack=other.stack;
    root=other.root;
    current=other.current;
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator&& other) noexcept : stack(std::move(other.stack)) {
    std::swap(current, other.current);
    std::swap(root, other.root); 
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& other) {
    current=other.current;
    root=other.root;
    stack=other.stack;
    return *this;
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& other) noexcept {
    std::swap(current, other.current);
    std::swap(root, other.root);
    std::swap(stack, other.stack);
    return *this;
}

template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator &other) const noexcept {
    return (current==other.current && root==root);
}

template <typename Data>
const Data& BTInOrderIterator<Data>::operator*() const {
    if(Terminated()) throw std::out_of_range("Iterator is terminated.");
    else return current->Element();
}

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

template <typename Data>
BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator++() {
    if(!Terminated()){
        if((stack.Empty()) && !(current->HasRightChild())) current=nullptr;
        else { 
            if(current->HasRightChild()){
                current = Min2(&current->RightChild());
            } else current = stack.TopNPop();
        }
    } else throw std::out_of_range("BTInOrderIterator<Data>::operator++: Iterator is terminated.");
    return *this;
}

template <typename Data>
void BTInOrderIterator<Data>::Reset() noexcept {
    current=Min2(root);
}

/* ************************************************************************** */

template <typename Data>
BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator& other) {
    this->current=other.current;
    this->root=other.root;
    this->stack=other.stack;
    return *this;
}

template <typename Data>
BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator&& other) noexcept {
    std::swap(this->current, other.current);
    std::swap(this->root, other.root);
    std::swap(this->stack, other.stack);
    return *this;
}

/* ************************************************************************** */

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& other) {
    root = current = (other.Empty()) ? nullptr : &other.Root();
}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator &other) {
    queue = other.queue;
    root = current = other.current;
}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator&& other) noexcept : queue(std::move(other.queue)){
    std::swap(root, other.root);
    std::swap(current, other.current); 
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator& other) {
    current=other.current;
    root=other.root;
    queue=other.queue;
    return *this;
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator&& other) noexcept {
    std::swap(current, other.current);
    std::swap(root, other.root);
    std::swap(queue, other.queue);
    return *this;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator &other) const noexcept {
    return (current==other.current && root==root);
}

template <typename Data>
const Data& BTBreadthIterator<Data>::operator*() const {
    if(Terminated()) throw std::out_of_range("Iterator is terminated.");
    else return current->Element();
}

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    if (!Terminated()) {
        if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild())); 
        if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));
        
        if (!queue.Empty()) current = queue.HeadNDequeue();
        else current = nullptr;
    }else throw std::out_of_range("BTBreadthIterator<Data>::operator++: Iterator is terminated.");
    return *this;
}

template <typename Data>
void BTBreadthIterator<Data>::Reset() noexcept {
    current=root;
}


/* ************************************************************************** */

template <typename Data>
BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator& other) {
    this->current=other.current;
    this->root=other.root;
    this->queue=other.queue;
    return *this;
}

template <typename Data>
BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator&& other) noexcept {
    std::swap(this->current, other.current);
    std::swap(this->root, other.root);
    std::swap(this->queue, other.queue);
    return *this;
}

/* ************************************************************************** */

}
