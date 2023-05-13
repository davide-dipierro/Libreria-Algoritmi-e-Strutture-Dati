
namespace lasd {

/* ************************************************************************** */

//Constructors
template <typename Data>
Vector<Data>::Vector(const ulong new_size) {
    size = new_size;
    Elements = new Data[size] {};
}

//Specific constructor
template <typename Data>
Vector<Data>::Vector(const MappableContainer<Data>& cont) {
    size = cont.Size();
    Elements = new Data[size] {};
    ulong index = 0;
    cont.Map(
        [this, &index](const Data& dat) {
            Elements[index++] = dat;
        }
    );
}

//Specific constructor
template <typename Data>
Vector<Data>::Vector(MutableMappableContainer<Data>&& cont) noexcept {
    size = cont.Size();
    Elements = new Data[size] {};
    ulong index = 0;
    cont.Map(
        [this, &index](Data& dat) {
            // Elements[index++] = std::move(dat);
            std::swap(Elements[index++], dat);
        }
    );
}

//Destructor
template <typename Data>
Vector<Data>::~Vector() {
    delete[] Elements; 
}

/* ************************************************************************** */

//Copy constructor
template <typename Data>
Vector<Data>::Vector(const Vector<Data>& other){
    size = other.size;
    Elements = new Data[size] {};
    std::copy(other.Elements, other.Elements+size, Elements);
}

//Move constructor
template <typename Data>
Vector<Data>::Vector(Vector<Data>&& other) noexcept {
    std::swap(size, other.size);
    std::swap(Elements, other.Elements);
}

/* ************************************************************************** */

//Copy assignement
template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector& other) {
    delete[] Elements;
    size = other.Size();
    Elements = new Data[size];
    std::copy(other.Elements, other.Elements+size, Elements);
    return *this;
}

// Move assignement
template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector&& other) noexcept {
    std::swap(Elements, other.Elements);
    std::swap(size, other.size);
    return *this;
}

/* ************************************************************************** */

//Operators

template <typename Data>
const Data& Vector<Data>::operator[](const ulong index) const {
    if (index<size) return Elements[index];
    else throw std::out_of_range("Vector: out of range index of operator[]");
}

template <typename Data>
Data& Vector<Data>::operator[](const ulong index) {
    if (index<size) return Elements[index];
    else throw std::out_of_range("Vector: out of range index of operator[]");
}

template <typename Data>
bool Vector<Data>::operator==(const Vector& other) const noexcept {
    return LinearContainer<Data>::operator==(other);
}

template <typename Data>
bool Vector<Data>::operator!=(const Vector& other) const noexcept {
    return LinearContainer<Data>::operator!=(other);
}

/* ************************************************************************** */

template <typename Data>
void Vector<Data>::Resize(const ulong new_size) {
    if(new_size==0) Clear();
    else if (size!=new_size) {
        Data* ptr = new Data[new_size] {};
        ulong min_size = (size<new_size) ?  size : new_size;
        for(ulong i{0}; i<min_size; ++i) std::swap(Elements[i], ptr[i]);
        std::swap(Elements, ptr);
        size = new_size;
        delete[] ptr;
    }
}

template <typename Data>
void Vector<Data>::Clear() {
    delete[] Elements;
    Elements=nullptr;
    size=0;
}

}
