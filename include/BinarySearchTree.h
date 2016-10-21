#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include <iostream>
#include <fstream>
#include <memory>

template <typename T>
class BinarySearchTree;

template <typename T>
std::ofstream& operator << (std::ofstream& fout, const BinarySearchTree<T>& tree);

template <typename T>
std::ostream& operator << (std::ostream& out, const BinarySearchTree<T>& tree);

template <typename T>
std::istream& operator >> (std::istream& in, BinarySearchTree<T>& tree);

template <typename T>
std::ifstream& operator >> (std::ifstream& fin, BinarySearchTree<T>& tree);

template <typename T>
class BinarySearchTree {
    class Node {
    public:
        T value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        Node(T val):value(val), left(nullptr), right(nullptr) {}
        ~Node() {
            right = nullptr;
            left = nullptr;
        }
    };

    std::shared_ptr<Node> Root;
    size_t Size;

public:
    BinarySearchTree() : Root(nullptr), Size(0) {};
    BinarySearchTree(const std::initializer_list<T>& list);
    BinarySearchTree(const BinarySearchTree<T>& tree);
    BinarySearchTree(BinarySearchTree<T>&& tree);
    ~BinarySearchTree();

    bool Insert(const T& val) noexcept;
    bool Compare(std::shared_ptr<Node> ptr1, std::shared_ptr<Node> ptr2) const noexcept;
    bool Remove(const T& value, std::shared_ptr<Node>& ptr) noexcept;
    bool Remove(const T& value) noexcept;

    void Direct(std::ostream& out, std::shared_ptr<Node> root) const noexcept;
    void Symmetric(std::ostream& out, std::shared_ptr<Node> root) const noexcept;
    void Copy(std::shared_ptr<Node> root, std::shared_ptr<Node> ptr) noexcept;

    std::shared_ptr<T> Find(const T& val) const noexcept;
    std::shared_ptr<Node> ReturnRoot() const noexcept {return Root;}

    size_t ReturnSize() const noexcept { return Size;}

    BinarySearchTree<T>& operator= (const BinarySearchTree<T>& tree) noexcept;
    BinarySearchTree<T>& operator= (BinarySearchTree<T>&& tree) noexcept;
    bool operator== (const BinarySearchTree<T>& tree) const noexcept;
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const std::initializer_list<T>& list):BinarySearchTree(){
    for (auto& it : list)
        Insert(it);
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& tree){
    *this = tree;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& tree):Size(tree.Size), Root(tree.Root){
    tree.Root = nullptr;
}

template <typename T>
bool BinarySearchTree<T>::Insert(const T& val) noexcept {
    if (!Size) {
        Root = std::make_shared <Node> (val);
        Size++;
        return true;
    }
    std::shared_ptr<Node> CurPtr = Root;
    std::shared_ptr<Node> PrevPtr = Root;
    while (CurPtr)
    {
        PrevPtr = CurPtr;
        if (CurPtr->value > val)
            CurPtr = CurPtr->left;
        else if (CurPtr->value < val)
            CurPtr = CurPtr->right;
        else if (CurPtr->value == val)
            return false;
    }
    if (PrevPtr->value > val)
        PrevPtr->left = std::make_shared<Node> (val);
    else
        PrevPtr->right = std::make_shared<Node> (val);
    Size++;
    return true;
}

template <typename T>
std::shared_ptr<T> BinarySearchTree<T>::Find(const T& val) const noexcept {
    std::shared_ptr<Node> tmp(Root);
    while (tmp) {
        if (tmp->value > val)
            tmp = tmp->left;
        else if (tmp->value < val)
            tmp = tmp->right;
        else return std::make_shared<T> (tmp->value);
    }
    return nullptr;
}

template <typename T>
void BinarySearchTree<T>::Copy(std::shared_ptr<Node> root, std::shared_ptr<Node> ptr) noexcept {
    if (!root && ptr) {
        Insert(ptr->value);
        Copy(Root, ptr);
        return;
    }
    if (!ptr) {
        Root = nullptr;
        return;
    }
    if (ptr->value != root->value) root->value = ptr->value;
    if (root->left && !ptr->left) {
        root->left = nullptr;
    }
    if (root->right && !ptr->right) {
        root->right = nullptr;
    }
    if (ptr->left && !root->left) {
        root->left = std::make_shared<Node>(ptr->left->value);
        Size++;
    }
    if (ptr->right && !root->right) {
        root->right = std::make_shared<Node>(ptr->right->value);
        Size++;
    }
    if (ptr->right && root->right)
        Copy(root->right, ptr->right);
    if (ptr->left && root->left)
        Copy(root->left, ptr->left);

}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator= (const BinarySearchTree<T>& tree) noexcept {
    if (this == &tree)
        return *this;
    this->Size = 0;
    this->Root = nullptr;
    Copy(Root, tree.Root);
    return *this;
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator= (BinarySearchTree<T>&& tree) noexcept {
    if (this == &tree)
        return *this;

    Root = nullptr;
    Size = tree.Size;
    Root = tree.Root;
    tree.Root = nullptr;

    return *this;
}

template <typename T>
bool BinarySearchTree<T>::Compare(std::shared_ptr<Node> ptr1, std::shared_ptr<Node> ptr2) const noexcept {
    if (ptr1 && !ptr2) return false;
    if (!ptr1 && ptr2) return false;
    if (!ptr1 && !ptr2) return true;
    if (ptr1->value == ptr2->value) {
        Compare(ptr1->left, ptr2->left);
        Compare(ptr1->right, ptr2->right);
    }
    else return false;
    return true;
}

template <typename T>
bool BinarySearchTree<T>::operator== (const BinarySearchTree<T>& tree) const noexcept {
    if (Size != tree.Size) return false;
    return Compare(Root, tree.Root);
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    Root = nullptr;
    Size = 0;
}

template <typename T>
void BinarySearchTree<T>::Direct(std::ostream& out, std::shared_ptr<Node> root) const noexcept{
    if (!root) return;

    out << root->value << ' ';
    Direct(out, root->left);
    Direct(out, root->right);
}

template <typename T>
void BinarySearchTree<T>::Symmetric(std::ostream& out, std::shared_ptr<Node> root) const noexcept {
    if (!root) return;

    Symmetric(out, root->left);
    out << root->value << ' ';
    Symmetric(out, root->right);
}

template <typename T>
bool BinarySearchTree<T>::Remove(const T& value) noexcept{
    return this->Remove(value, Root);
}


template <typename T>
bool BinarySearchTree<T>::Remove(const T& value, std::shared_ptr<Node>& ptr) noexcept{

    if (!ptr) return false;
    if (value > ptr->value)
        Remove(value, ptr->right);
    else if (value < ptr->value)
        Remove(value, ptr->left);

    else {
        if (!ptr->right && !ptr->left) {
            ptr = nullptr;
        }
        else if (!ptr->right) {
            ptr = ptr->left;
        }
        else if (!ptr->left) {
            ptr = ptr->right;
        }
        else if (!ptr->right->left) {
            auto LeftSide = ptr->left;
            ptr = ptr->right;
            ptr->left = LeftSide;
        } else {
            auto bottom = ptr->right;
            while (bottom)
                bottom = bottom->left;
            bottom = ptr->left;
            ptr = ptr->right;
        }
        Size--;
        return true;
    }
}




template <typename T>
std::ostream& operator << (std::ostream& out, const BinarySearchTree<T>& tree) {
    tree.Symmetric(out, tree.ReturnRoot());
    return out;
}

template <typename T>
std::ofstream& operator << (std::ofstream& fout, const BinarySearchTree<T>& tree) {
    tree.Direct(fout, tree.ReturnRoot());
    return fout;
}

template <typename T>
std::istream& note(std::istream& in, BinarySearchTree<T>& tree) {
    T value;
    while (in >> value)
        tree.Insert(value);
    return in;
}

template <typename T>
std::istream& operator >> (std::istream& in, BinarySearchTree<T>& tree) {
    note(in, tree);
    return in;
}

template <typename T>
std::ifstream& operator >> (std::ifstream& fin, BinarySearchTree<T>& tree) {
    note(fin, tree);
    return fin;
}

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
