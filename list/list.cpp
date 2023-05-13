
namespace lasd {

/* ************************************************************************** */        //CLASS NODE

// Specific constructors
template <typename Data>
List<Data>::Node::Node(const Data& new_elem) {
    elem = new_elem;
    next = nullptr;
}
template <typename Data>
List<Data>::Node::Node(Data&& new_elem) noexcept {
    std::swap(elem, new_elem);
    next = nullptr;
}

// Copy constructor
template <typename Data>
List<Data>::Node::Node(const Node& new_node){
    elem = new_node.elem;
    next = new_node.next;
}

// Move constructor
template <typename Data>
List<Data>::Node::Node(Node&& new_node) noexcept {
    std::swap(elem, new_node.elem);
    std::swap(next, new_node.next);
}

/* ************************************************************************** */

// Specific constructor
template <typename Data>
List<Data>::List(const MappableContainer<Data>& cont) {
    cont.Map(
        [this](const Data& dat) {
            InsertAtBack(dat);
        }
    );
}

// Specific constructor
template <typename Data>
List<Data>::List(MutableMappableContainer<Data>&& cont) noexcept {
    cont.Map(
        [this](Data& dat) {
            InsertAtBack(std::move(dat));
        }
    );
}

// Copy constructor
template <typename Data>
List<Data>::List(const List<Data>& other){
    for(ulong i{0}; i<other.size; i++) InsertAtBack(other[i]);
}

// Move constructor
template <typename Data>
List<Data>::List(List<Data>&& other) noexcept {
    std::swap(head,other.head);
    std::swap(size,other.size);
}

/* ************************************************************************** */        //CLASS LIST

template <typename Data>
void List<Data>::InsertAtFront(const Data& new_elem) {
    Node* nuovo = new Node(new_elem);
    nuovo->next=head;
    head=nuovo;
    size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& new_elem) {
    Node* nuovo = new Node(std::move(new_elem));
    nuovo->next=head;
    head=nuovo;
    size++;
}

template <typename Data>
void List<Data>::RemoveFromFront() {
    if(Empty()) throw std::length_error("List: the list is empty in RemoveFromFront()");
    Node* old = head;
    head = head->next;
    delete old;
    size--;
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& new_elem) {
    Node* punt = head;
    Node* nuovo = new Node(new_elem);
    if(!Empty()){ 
        while(punt->next!=nullptr) punt=punt->next;
        punt->next=nuovo;
    }
    else head = nuovo;
    size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& new_elem) {
    Node* punt = head;
    Node* nuovo = new Node(std::move(new_elem));
    if(!Empty()){ 
        while(punt->next!=nullptr) punt=punt->next;
        punt->next=nuovo;
    }
    else head = nuovo;
    size++;
}


/* ************************************************************************** */

template <typename Data>
const Data& List<Data>::Front() const {
    if(Empty())throw std::length_error("List: the list is empty in Front()");
    return head->elem; 
};

template <typename Data>
Data& List<Data>::Front() {
    if(Empty())throw std::length_error("List: the list is empty in Front()");
    return head->elem; 
};

template <typename Data>
Data List<Data>::FrontNRemove() {
    if(Empty())throw std::length_error("List: the list is empty in Front()");
    Data elem = Front();
    RemoveFromFront();
    return elem;
}

template <typename Data>
const Data& List<Data>::Back() const {
    if(Empty()) throw std::length_error("List: the list is empty in Back()");
    Node* punt = head;
    while((punt->next)!=nullptr) punt=punt->next;
    return punt->elem; 
};


template <typename Data>
Data& List<Data>::Back() {
    if(Empty()) throw std::length_error("List: the list is empty in Back()");
    Node* punt = head;
    while((punt->next)!=nullptr) punt=punt->next;
    return punt->elem; 
};

/* ************************************************************************** */

template <typename Data>
const Data& List<Data>::operator[](const ulong index) const {
    if (!Empty() && index<size) {
        Node* ptr = head;
        for(ulong i{0}; i<index; i++) ptr=ptr->next;
        return ptr->elem;
    }
    else throw std::out_of_range("List: out of range index of operator[]");
}

template <typename Data>
Data& List<Data>::operator[](const ulong index) {
    if (!Empty() && index<size) {
        Node* ptr = head;
        for(ulong i{0}; i<index; i++) ptr=ptr->next;
        return ptr->elem;
    }
    else throw std::out_of_range("List: out of range index of operator[]");
}

template <typename Data>
List<Data>& List<Data>::operator=(const List& other) {
    // Node* nodo = other.head;
    Clear();
    other.PostOrderMap(
        [this](const Data& dat) {
            InsertAtFront(dat);
        }
    );
    return *this;
}

template <typename Data>
List<Data>& List<Data>::operator=(List&& other) noexcept {
    std::swap(other.head, head);
    std::swap(other.size, size);
    return *this;
}

template <typename Data>
bool List<Data>::operator==(const List& other) const noexcept {
    if(size!=other.size) return false;
    Node* punt1 = head;
    Node* punt2 = other.head;
    for(ulong i{0}; i<size; i++){
        if(!(*punt1 == *punt2)) return false;
        punt1=punt1->next;
        punt2=punt2->next;
    }
    return true;
}

template <typename Data>
inline bool List<Data>::operator!=(const List& other) const noexcept {
    return !operator==(other);
}

/* ************************************************************************** */


template <typename Data>
void List<Data>::PreOrderFold(FoldFunctor func, void* acc) const {
    AuxPreOrderFold(head, func, acc);
}

template <typename Data>
void List<Data>::AuxPreOrderFold(const Node* nodo, FoldFunctor func, void* acc) const {
    const Node* punt = nodo;
    while(punt!=nullptr){
        func(punt->elem, acc);
        punt=punt->next;
    }
}

template <typename Data>
void List<Data>::PostOrderFold(FoldFunctor func, void* acc) const {
    if(!Empty()) AuxPostOrderFold(head, func, acc);
}

template <typename Data>
void List<Data>::AuxPostOrderFold(const Node* nodo, FoldFunctor func, void* acc) const {
    if(nodo!=nullptr){
        if(nodo->next!=nullptr) AuxPostOrderFold(nodo->next, func, acc);
        func(nodo->elem, acc);
    }
}

template <typename Data>
void List<Data>::PreOrderMap(MapFunctor func) const {
    AuxPreOrderMap(head, func);
}

template <typename Data>
void List<Data>::AuxPreOrderMap(const Node* nodo, MapFunctor func) const {
    const Node* punt = nodo;
    while(punt!=nullptr){
        func(punt->elem);
        punt=punt->next;
    }
}

template <typename Data>
void List<Data>::PostOrderMap(MapFunctor func) const {
    if(!Empty()) AuxPostOrderMap(head, func);
}

template <typename Data>
void List<Data>::AuxPostOrderMap(const Node* nodo, MapFunctor func) const {
    if(nodo!=nullptr){
        if(nodo->next!=nullptr) AuxPostOrderMap(nodo->next, func);
        func(nodo->elem);
    }
}

template <typename Data>
void List<Data>::PostOrderMap(const MutableMapFunctor func) {
    if(!Empty()) AuxPostOrderMap(head, func);
}

template <typename Data>
void List<Data>::AuxPostOrderMap(Node* nodo, MutableMapFunctor func) {
    if(nodo!=nullptr){
        if(nodo->next!=nullptr) AuxPostOrderMap(nodo->next, func);
        func(nodo->elem);
    }
}

template <typename Data>
void List<Data>::PreOrderMap(const MutableMapFunctor func) {
    AuxPreOrderMap(head, func);
}

template <typename Data>
void List<Data>::AuxPreOrderMap(Node* nodo, MutableMapFunctor func) {
    Node* punt = nodo;
    while(punt!=nullptr){
        func(punt->elem);
        punt=punt->next;
    }
}

template <typename Data>
bool List<Data>::Insert(const Data& elem) {
    if(FoldableContainer<Data>::Exists(elem)) return false;
    InsertAtBack(elem);
    return true;
}

template <typename Data>
bool List<Data>::Insert(Data&& elem) {
    if(FoldableContainer<Data>::Exists(elem)) return false;
    InsertAtBack(std::move(elem));
    return true;
}

template <typename Data>
bool List<Data>::Remove(const Data& chk_elem) {
    Node* punt = head;
    Node* prev = nullptr;
    for(ulong i{0}; i<size; i++){
        if((punt->elem)==(chk_elem)) {
            if(prev != nullptr) prev->next=punt->next;
            else head=punt->next;
            delete punt;
            size--;
            return true;
        }
        prev=punt;
        punt=punt->next;
    }
    return false;
}

template <typename Data>
void List<Data>::Clear() {
    while(!Empty()) RemoveFromFront();
}

/* ************************************************************************** */

}