#include "binarytreelnk.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
    delete rChild;
    delete lChild;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& other) : elem(other.elem) {
    lChild = (other.lChild != nullptr) ? new NodeLnk(*other.lChild) : nullptr;
    rChild = (other.rChild != nullptr) ? new NodeLnk(*other.rChild) : nullptr;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk&& other) noexcept {
    std::swap(elem, other.elem);
    std::swap(lChild, other.lChild);
    std::swap(rChild, other.rChild);
}

// template <typename Data>
// BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& other) {
//     elem = other.elem;
//     delete lChild;
//     lChild = (other.lChild != nullptr) ? new NodeLnk(*other.lChild) : nullptr;
//     delete rChild;
//     rChild = (other.rChild != nullptr) ? new NodeLnk(*other.rChild) : nullptr;
//     return *this;
// }

// template <typename Data>
// BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& other) noexcept {
//     std::swap(elem, other.elem);
//     std::swap(lChild, other.lChild);
//     std::swap(rChild, other.rChild);
//     return *this;
// }

/* ************************************************************************** */

template<typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
    delete root;
}

// template <typename Data>
// void BinaryTreeLnk<Data>::DeleteSubTree(NodeLnk* node) {
//   if (node->HasLeftChild()) DeleteSubTree(node->lChild);
//   if (node->HasRightChild()) DeleteSubTree(node->rChild);

//   delete node;
//   node = nullptr;
//   BinaryTree<Data>::size--;
// }

template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
    if(root != nullptr) return *root; 
    else throw std::length_error("BinaryTreeLnk<Data>::Root(): Empty tree");
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() {
    if(root != nullptr) return *root; 
    else throw std::length_error("BinaryTreeLnk<Data>::Root(): Empty tree");
}

// template <typename Data>
// void BinaryTreeLnk<Data>::InsertBreadth(const Data &dat) {
//     if (root==nullptr) {
//         root = new NodeLnk(dat);
//         size++;
//     }else{
//         QueueVec<BinaryTreeLnk<Data>::NodeLnk*> coda;
//         coda.Enqueue(root);
//         while(!coda.Empty()){
//             NodeLnk* current = coda.HeadNDequeue();
//             if (!(current->HasLeftChild())) {
//                 current->lChild = new NodeLnk(dat);
//                 size++;
//                 break;
//             }
//             else coda.Enqueue(current->lChild);

//             if (!(current->HasRightChild())){
//                 current->rChild = new NodeLnk(dat);
//                 size++;
//                 break;
//             }
//             else coda.Enqueue(current->rChild);
//         }
//     }
// }

// template <typename Data>
// void BinaryTreeLnk<Data>::InsertBreadth(Data&& dat) {
//     if (root==nullptr) root = new NodeLnk(std::move(dat));
//     else {
//         QueueVec<BinaryTreeLnk<Data>::NodeLnk*> coda;
//         coda.Enqueue(root);
//         while(!coda.Empty()){
//             NodeLnk* current = coda.HeadNDequeue();
//             if (!(current->HasLeftChild())) {
//                 current->lChild = new NodeLnk(std::move(dat));
//                 size++;
//                 break;
//             }
//             else coda.Enqueue(current->lChild);

//             if (!(current->HasRightChild())){
//                 current->rChild = new NodeLnk(std::move(dat));
//                 size++;
//                 break;
//             }
//             else coda.Enqueue(current->rChild);
//         }
//     }
// }

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const MappableContainer<Data> &other) {
    size = other.Size();
    QueueVec<NodeLnk * *> coda;
    coda.Enqueue(&root);
    other.Map(
        [&coda](const Data& dat){
            NodeLnk *& cur = *coda.HeadNDequeue();
            cur = new NodeLnk(dat);
            coda.Enqueue(&cur->lChild);
            coda.Enqueue(&cur->rChild);
        }
    );
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(MutableMappableContainer<Data> &&other) noexcept {
    size = other.Size();
    QueueVec<NodeLnk * *> coda;
    coda.Enqueue(&root);
    other.Map(
        [&coda](const Data& dat){
            NodeLnk *& cur = *coda.HeadNDequeue();
            cur = new NodeLnk(std::move(dat));
            coda.Enqueue(&cur->lChild);
            coda.Enqueue(&cur->rChild);
        }
    );
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk &other) {
    // for(BTBreadthIterator i(other); !i.Terminated(); ++i) InsertBreadth(*i);
    size = other.Size();
    root = (other.root!=nullptr) ? new NodeLnk(*other.root) : nullptr;
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& other) noexcept {
    // Clear();
    // size = other.Size();
    // QueueVec<NodeLnk * *> coda;
    // coda.Enqueue(&root);
    // other.Map(
    //     [&coda](const Data& dat){
    //         NodeLnk *& cur = *coda.HeadNDequeue();
    //         cur = new NodeLnk(std::move(dat));
    //         coda.Enqueue(&cur->lChild);
    //         coda.Enqueue(&cur->rChild);
    //     }
    // );
    std::swap(root, other.root);
    std::swap(size, other.size);
}

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk& other) {
    // Clear();
    // size = other.Size();
    // QueueVec<NodeLnk * *> coda;
    // coda.Enqueue(&root);
    // for(BTBreadthIterator i(other); !i.Terminated(); ++i) {
    //     NodeLnk *& cur = *coda.HeadNDequeue();
    //     cur = new NodeLnk(*i);
    //     coda.Enqueue(&cur->lChild);
    //     coda.Enqueue(&cur->rChild);
    // }
    Clear();
    size = other.Size();
    root = (other.root!=nullptr) ? new NodeLnk(*other.root) : nullptr;
    return *this;
}


template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk&& other) noexcept {
    // Clear();
    std::swap(root, other.root); //NOTE: root=move(root);
    std::swap(size, other.size);
    return *this;
}


/* ************************************************************************** */
}
