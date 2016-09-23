#include <initializer_list>
#include <iostream>
#include <fstream>

template <typename T>
class BinarySearchTree;

template <typename T>
std::ofstream& operator << (std::ofstream& fout, const BinarySearchTree<T>& tree);
template <typename T>
std::ostream& operator << (std::ostream& out, const BinarySearchTree<T>& tree);
template <typename T>
std::istream& operator >> (std::istream& in, BinarySearchTree<T>& tree);

template <typename T>
class BinarySearchTree
{
    class Node
    {
    public:
        T value;
        Node* right;
        Node* left;
        Node(T val):value(val), right(nullptr) left(nullptr) {}
        ~Node()
        {
            delete right;
            delete left;
            left = right = nullptr;
        }
    };
    Node* Child;
    size_t size;

public:
    BinarySearchTree() : Child(nullptr), size(0) {};
    BinarySearchTree(BinarySearchTree<T>&& tree);
    BinarySearchTree(const std::initializer_list<T>& list);
    bool add(T& val) noexcept;
    const T* getTree(const T& val) const noexcept;
    void inorder_walk(std::ostream& out, Node* child) const noexcept;
    Node* ReturnChild() const noexcept {return Child;}
    BinarySearchTree<T>& operator= (BinarySearchTree<T>&& tree);
    ~BinarySearchTree();
};

template <typename T>
std::ostream& operator << (std::ostream& out, const BinarySearchTree<T>& tree)
{
	tree.inorder_walk(out, tree.ReturnChild());
	return out;
}

template <typename T>
std::ofstream& operator << (std::ofstream& fout, const BinarySearchTree<T>& tree)
{
	tree.inorder_walk(fout, tree.ReturnChild());
	return fout;
}

template <typename T>
std::istream& operator >> (std::istream& in, BinarySearchTree<T>& tree)
{
	setlocale(LC_ALL, "Russian");
	size_t size = 0;
	cout << "Введите колличество: ";
	cin >> size;
	cout << '\n';
	for (size_t i = 0; i < size; i++)
	{
		T value;
		in >> value;
		tree.add(value);
		cout << ' ';
	}
	return in;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const std::initializer_list<T>& list):size(0), Child(nullptr)
{
    for (auto it : list)
	{
        add(it);
    }
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& tree):size(tree.size), Child(tree.Child)
{
    tree.Child = nullptr;
}

template <typename T>
bool BinarySearchTree<T>::add(T& val) noexcept //Фукция добавления звена в дерево
{
    if (!size) 
	{
		Child = new Node(val);
        size++;
        return true;
    }
    Node* Q_Link = Child;
    Node* P_Link = Child;
    while (Q_Link)
    {
		P_Link = Q_Link;
        if (Q_Link->value > val)
			Q_Link = Q_Link->left;
        else if (Q_Link->value < val)
			Q_Link = Q_Link->right;
        else if (Q_Link->value == val)
            return false;
    }
    if (P_Link->value > val)
		P_Link->left = new Node(val);
    else
		P_Link->right = new Node(val);
    size++;
    return true;
}

template <typename T>
const T* BinarySearchTree<T>::getTree(const T& val) const noexcept
{
    const Node* tmp = Child;
    while (tmp) 
	{
        if (tmp->value > val)
            tmp = tmp->left;
        else if (tmp->value < val)
            tmp = tmp->right;
        else return &tmp->value;
    }
    return nullptr;
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator= (BinarySearchTree<T>&& tree)
{
    if (this == &tree)
        return *this;

    delete Child;
    size = tree.size;
	Child = tree.Child;
    tree.Child = nullptr;

    return *this;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    delete Child;
    Child = nullptr;
    size = 0;
}

template <typename T>
void BinarySearchTree<T>::inorder_walk(std::ostream& out, Node* child) const noexcept
{
    if (!child) return;

    out << child->value << ' ';
    inorder_walke(out, child->left);
    inorder_walk(out, child->right);
}
