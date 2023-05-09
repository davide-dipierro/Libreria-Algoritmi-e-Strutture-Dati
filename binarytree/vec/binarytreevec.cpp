
namespace lasd {

/* ************************************************************************** */

template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    if(Elements != nullptr) return Nodes[0]; 
    else throw std::length_error("BinaryTreeVec<Data>::Root(): Empty tree");
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() {
    if(Elements != nullptr) return Nodes[0]; 
    else throw std::length_error("BinaryTreeVec<Data>::Root(): Empty tree");
}

/* ************************************************************************** */

}
