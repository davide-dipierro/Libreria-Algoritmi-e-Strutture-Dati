
namespace lasd {

/* ************************************************************************** */

// Copy constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec& other) {
    size = other.size;
    riempimento=other.riempimento;
    Elements = new Data[size] {};
    std::copy(other.Elements, other.Elements+riempimento, Elements);
}

// Move constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec&& other) noexcept : Vector<Data>::Vector(std::move(other)) {
    std::swap(other.riempimento, riempimento);
    other.Clear();
}

/* ************************************************************************** */

// Operators

template <typename Data>
bool StackVec<Data>::operator==(const StackVec& other) const noexcept {
    if(riempimento!=other.riempimento) return false;
    for(ulong i=0; i<riempimento; i++) {
        if(this->operator[](i)!=other[i]) return false;
    }
    return true;
}

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec& other) {
    Vector<Data>::operator=(other);
    riempimento=other.riempimento;
    return *this;
}

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec&& other) noexcept {
    Vector<Data>::operator=(std::move(other));
    std::swap(riempimento, other.riempimento);
    return *this;
}

/* ************************************************************************** */

template <typename Data>
const Data& StackVec<Data>::Top() const {
    if(Empty()) throw std::length_error("StackVec: the stack is empty in Top()");
    return Vector<Data>::operator[](riempimento-1);
}

template <typename Data>
Data& StackVec<Data>::Top() {
    if(Empty()) throw std::length_error("StackVec: the stack is empty in Top()");
    return Vector<Data>::operator[](riempimento-1);
}

template <typename Data>
void StackVec<Data>::Pop() {
    if(Empty()) throw std::length_error("StackVec: the stack is empty in Pop()");
    CheckNReduce();
    riempimento--;
}

template <typename Data>
Data StackVec<Data>::TopNPop() {
    if(Empty()) throw std::length_error("StackVec: the stack is empty in TopNPop()");
    CheckNReduce();
    return Vector<Data>::operator[](--riempimento);
}

template <typename Data>
void StackVec<Data>::Push(const Data& elem) {
    CheckNExpand();
    Vector<Data>::operator[](riempimento++) = elem;
}

template <typename Data>
void StackVec<Data>::Push(Data&& elem) {
    CheckNExpand();
    Vector<Data>::operator[](riempimento++) = std::move(elem);
}

/* ************************************************************************** */

template <typename Data>
bool StackVec<Data>::CheckNExpand() {
    if (riempimento < size) return false;
    else Vector<Data>::Resize(size*const_exp_set);
    return true;
}


template <typename Data>
bool StackVec<Data>::CheckNReduce() {
    if(size*const_red_check < riempimento) return false;
    if(riempimento<=const_init_stack_size*const_red_check) Vector<Data>::Resize((ulong)const_init_stack_size);
    else Vector<Data>::Resize((ulong)size*const_red_set);
    return true;
}




template <typename Data>
void StackVec<Data>::Clear() {
    riempimento=0;
    CheckNReduce();
}

/* ************************************************************************** */

template <typename Data>
StackVec<Data>::StackVec() : Vector<Data>(const_init_stack_size) {
    // size = const_init_stack_size;
    // Elements = new Data[const_init_stack_size] {};
    riempimento = 0;
}

template <typename Data>
StackVec<Data>::StackVec(const MappableContainer<Data>& cont) : Vector<Data>::Vector(cont) {
    riempimento = cont.Size();
    CheckNExpand(); 
}

template <typename Data>
StackVec<Data>::StackVec(MutableMappableContainer<Data>&& cont) noexcept : Vector<Data>::Vector(std::move(cont)) {
    riempimento = cont.Size();
    CheckNExpand(); 
}

}
