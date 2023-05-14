
namespace lasd {

/* ************************************************************************** */

template <typename Data>
const Data& QueueVec<Data>::Head() const {
    if(Empty()) throw std::length_error("QueueVec: the stack is empty in Head()");
    return Vector<Data>::operator[](head);
}

template <typename Data>
Data& QueueVec<Data>::Head() {
    if(Empty()) throw std::length_error("QueueVec: the stack is empty in Head()");
    return Vector<Data>::operator[](head);
}

template <typename Data>
void QueueVec<Data>::Dequeue() {
    if(Empty()) throw std::length_error("QueueVec: the stack is empty in Dequeue()");
    CheckNReduce();
    head=(head+1)%size;
}

template <typename Data>
Data QueueVec<Data>::HeadNDequeue() {
    if(Empty()) throw std::length_error("QueueVec: the stack is empty in HeadNDequeue()");
    CheckNReduce();
    head=(head+1)%size;
    return Vector<Data>::operator[]((head-1+size)%size);
}

template <typename Data>
void QueueVec<Data>::Enqueue(const Data& elem) {
    Vector<Data>::operator[](tail) = elem;
    CheckNExpand();
    tail=(tail+1)%size;
}

template <typename Data>
void QueueVec<Data>::Enqueue(Data&& elem) {
    std::swap(Vector<Data>::operator[](tail), elem);
    CheckNExpand();
    tail=(tail+1)%size;
}

template <typename Data>
void QueueVec<Data>::Clear() {
    Vector<Data>::Resize(const_init_queue_size);
    head = tail = 0;    
}

/* ************************************************************************** */

template <typename Data>
void QueueVec<Data>::CheckNExpand() {
    if((tail + 1) % size == head) {
        ulong new_size = size * const_exp_set;
        Data* nuovo = new Data[new_size] {};
        for(ulong i = 0; i < size; ++i) {
            nuovo[i] = Elements[(i+head)%size];
        }
        std::swap(Elements, nuovo);
        delete[] nuovo;
        tail = Size();
        head = 0;
        size = new_size;
    }
}

template <typename Data>
void QueueVec<Data>::CheckNReduce() {  
    if(Size() <= size * const_red_check && Size() >= const_init_queue_size) {
        ulong new_size = size * const_red_set;
        Data* nuovo = new Data[new_size] {};
        for(ulong i = 0; i < Size(); ++i) {
            nuovo[i] = Elements[(i+head)%size];
        }
        delete[] Elements;
        Elements = nuovo;
        tail = Size();
        head = 0;
        size = new_size;
    }
}


template <typename Data>
QueueVec<Data>::QueueVec() {
    Vector<Data>::Resize(const_init_queue_size);
}

template <typename Data>
QueueVec<Data>::QueueVec(const MappableContainer<Data>& cont) {
    size = cont.Size() + 1;
    Elements = new Data[size] {};
    ulong index = 0;
    cont.Map(
        [this, &index](const Data& dat) {
            Elements[index++] = dat;
        }
    );
    tail = cont.Size();
    head = 0;
}

template <typename Data>
QueueVec<Data>::QueueVec(MutableMappableContainer<Data>&& cont) noexcept {
    size = cont.Size() + 1;
    Elements = new Data[size] {};
    ulong index = 0;
    cont.Map(
        [this, &index](Data& dat) {
            // Elements[index++] = std::move(dat);
            std::swap(Elements[index++], dat);
        }
    );
    tail = cont.Size();
    head = 0;
}

template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec& other) : Vector<Data>::Vector(other) {
    head=other.head;
    tail=other.tail;
}

template <typename Data>
QueueVec<Data>::QueueVec(QueueVec&& other) noexcept : Vector<Data>::Vector(std::move(other)) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    other.Clear();
}

template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec& other) {
    this->Clear();
    Vector<Data>::Resize(other.size);
    for(ulong i{0}; i<other.Size(); i++){
        Vector<Data>::operator[](i)=other.operator[]((i+other.head)%other.size);
    }
    head=0;
    tail=other.Size();
    return *this;
}

template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec&& other) noexcept {
    this->Vector<Data>::operator=(std::move(other));
    std::swap(other.head, head);
    std::swap(other.tail, tail);
    return *this;
}

template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec& other) const noexcept {
    if(Size()!=other.Size()) return false;
    for(ulong i=0; i<Size(); i++) {
        if(this->operator[]((i+head)%size)!=other[(i+other.head)%other.size]) return false;
    }
    return true;
}

}
