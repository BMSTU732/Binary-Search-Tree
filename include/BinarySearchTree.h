#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H
#pragma once
// BinarySearchTree.cpp: определяет точку входа для консольного приложения.
//Реализовать класс "", имеющий интерфейс:
//вставка элемента в дерево
//поиск элемента в дереве
//файловый потоковый ввод/вывод
//потоковый вывод

#include <initializer_list>
#include <iostream>
#include <fstream>
template<typename T>
class BinarySearchTree;


template <typename T>
std::ofstream & operator << (std::ofstream & out, const BinarySearchTree<T> & tree)
{
    tree.DoPreorderWalk(out, tree.GetRoot());
    return out;
};

template <typename T>
std::ostream & operator << (std::ostream & out, const BinarySearchTree<T> & tree)
{
    tree.DoPreorderWalk(out, tree.GetRoot());
    return out;
};

template <typename T>
std::istream & operator >> (std::istream & in, BinarySearchTree<T> & tree)
{
    T value;
    int size;
    std::cout << "Size: ";
    if (in >> size) {
        for (int i = 0; i < size; i++)
        {
            if (in >> value) {
                tree.insert(value);
            }
        }
    }
    return in;
};

template<typename T>
class BinarySearchTree
{
private:
    struct Node {
        Node * left_; //указатель на левого сына
        Node * right_; //указатель на правого сына
        T value_; //значение

        Node(T value) : value_(value), left_(nullptr), right_(nullptr) {}; //конструктор, инициализирующий узел
        ~Node()
        {
            delete left_;
            delete right_;
        }
    };

    Node* root_; //указатель на корень
    size_t size_; //размер дерева

public:
    BinarySearchTree()
    {
        size_ = 0;
        root_ = nullptr;
    };
    BinarySearchTree(const std::initializer_list<T> & list)
    {
        size_ = 0;
        root_ = nullptr;
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            insert(*it);
        };

    };
    void DoPreorderWalk(std::ostream & str, Node *this_node) const noexcept //Прямой обход дерева
    {
        if (!this_node) { return; }
        str << this_node->value_ << " ";
        DoPreorderWalk(str, this_node->left_);
        DoPreorderWalk(str, this_node->right_);
    }
    Node* GetRoot() const
    {
        return root_;
    }
    ~BinarySearchTree()
    {
        delete root_;
    };


    auto size() noexcept -> size_t
    {
        return size_;
    };


    auto insert(const T & value) noexcept -> bool
    {

        Node* this_node = root_;
        Node* my_node = nullptr;
        if (root_ == nullptr)
        {
            root_ = new Node(value);
            size_++;
            return true;
        }
        while (this_node)
        {
            my_node = this_node;
            if (value == my_node->value_)
            {
                return false;
            }
            else if (value < my_node->value_)
            {
                this_node = my_node->left_;
            }
            else if (value > my_node->value_)
            {
                this_node = my_node->right_;
            }
        }
        if (value < my_node->value_)
        {
            my_node->left_ = new Node(value);
        }
        else
        {
            my_node->right_ = new Node(value);
        };
        size_++;
        return true;
    };

    auto find(const T & value) const noexcept -> const T *
    {
        Node *this_node = root_;
        if (size_== 0)
        {
            return nullptr;
        };
        while (this_node)
        {
            if (value < this_node->value_)
            {
                this_node = this_node->left_;
            }
            else if (value > this_node->value_)
            {
                this_node = this_node->right_;
            }
            else if (value == this_node->value_)
            {
                return &this_node->value_;
            }
        }
        return nullptr;
    };
};

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
