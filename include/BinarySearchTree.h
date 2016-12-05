#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include <initializer_list>
#include <iostream>
#include <fstream>
#include <memory>

template<typename T>
class BinarySearchTree;

//вывод
template <typename T>
std::ostream & operator << (std::ostream & out, const BinarySearchTree<T> & tree)
{
	tree.DoInorderWalk(out, tree.GetRoot());
	return out;
};
//ввод
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
//вывод в файл
template <typename T>
std::ofstream & operator << (std::ofstream & out, const BinarySearchTree<T> & tree)
{
	tree.DoPreorderWalk(out, tree.GetRoot());
	return out;
};
//ввод в файл
template <typename T>
std:: ifstream & operator >> (std::ifstream& in, BinarySearchTree<T>& tree)
{
	T value;
		while (in >> value) {
				tree.insert(value);
		};
	return in;
};


template<typename T>
class BinarySearchTree
{

private:
	struct Node {
		std::shared_ptr<Node> left_;
		std::shared_ptr<Node> right_;
		//Node * left_; //указатель на левого сына
		//Node * right_; //указатель на правого сына
		T value_; //значение

		
		Node(T value) : value_(value), left_(nullptr), right_(nullptr) {}; //конструктор, инициализирующий узел
		auto memcpy() ->std::shared_ptr<Node>
		{
			std::shared_ptr<Node> node = std::make_shared <Node>(value_);
			if (right_ != nullptr) 
			{
				node->right_ = right_->memcpy();
			}
			if (left_ != nullptr) 
			{
				node->left_ = left_->memcpy();
			}
			return node;
		}
		~Node()
		{
			left_=nullptr;
			right_=nullptr;
		}

	};
	
	std::shared_ptr<Node>root_; //указатель на корень
	size_t size_; //размер дерева

public:

	BinarySearchTree() : size_(0), root_(nullptr) {};
	BinarySearchTree(const std::initializer_list<T> & list) : size_(0), root_(nullptr)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			insert(*it);
		};

	};
	BinarySearchTree(const BinarySearchTree& tree) //Конструктор копирования
	{
		root_ = tree.root_->memcpy();
	};
	BinarySearchTree(BinarySearchTree&& tree) //Конструктор перемещения
	{
		size_ = tree.size_;
		tree.size_ = 0;
		root_ = tree.root_;
		tree.root_ = nullptr;
	};
	void DoPreorderWalk(std::ostream & str, std::shared_ptr<Node> this_node) const noexcept //Прямой обход дерева
	{
		if (!this_node) { return; }
		str << this_node->value_ << " ";
		DoPreorderWalk(str, this_node->left_);
		DoPreorderWalk(str, this_node->right_);
	}
	void DoInorderWalk(std::ostream &str, std::shared_ptr<Node> this_node) const noexcept //Симметричный обход дерева
	{
		if (!this_node) { return;  }
		DoInorderWalk(str, this_node->right_);
		str << this_node->value_ << " ";
		DoInorderWalk(str, this_node->left_);
	}
	auto GetRoot() const -> std::shared_ptr<Node>
	{
		return root_;
	}
	auto compare(std::shared_ptr<Node>node1, std::shared_ptr<Node> node2) const noexcept -> bool {

		if (node1 == nullptr && node2 == nullptr) return(true);
		else if (node1 != nullptr && node2 != nullptr)
		{
			return(
				node1->value_ == node2->value_ &&
				compare(node1->left_, node2->left_) &&
				compare(node1->right_, node2->right_)
				);
		}
		else return(false);
	}
	auto size() const noexcept -> size_t
	{
		return size_;
	};

	~BinarySearchTree()
	{
		root_ = nullptr;
	};

	auto insert(const T & value) noexcept -> bool
	{

		std::shared_ptr<Node>this_node= root_;
		std::shared_ptr<Node> my_node = nullptr;
		if (root_ == nullptr)
		{
			root_ = std::make_shared <Node>(value);
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
			my_node->left_ = std::make_shared <Node>(value);
		}
		else
		{
			my_node->right_ = std::make_shared <Node>(value);
		};
		size_++;
		return true;
	};

	auto find(const T & value) const noexcept -> const T *
	{
		auto this_node = root_;
	if (size_ == 0)
	{
		return nullptr;
	};
	while (this_node)
	{
		if (value < this_node->value_)
		{
			this_node =this_node->left_;
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
	auto remove(const T value) -> bool 
	{
		if (deletenode(root_, value)) 
		{
			size_--;
			return true;
		}
		else if (size_==0) { return false; }
	};
	auto deletenode(std::shared_ptr<Node> &node, const T& value)->std::shared_ptr<Node>
	{
		if (node == nullptr) return node;
		else if (value < node->value_)
		{
			node->left_=deletenode(node->left_, value); 
		}
		else if (value> node->value_) 
		{
			node->right_=deletenode(node->right_, value); 
		}
		else 
		{
			if (node->left_ == nullptr && node->right_ == nullptr) //удаляем лист
			{
				node=nullptr;
				return node;
			}
			if (node->right_!=nullptr && node->left_==nullptr) //существует левый потомок
			{
				std::shared_ptr<Node> n1 = node;
				node = node->right_;
				n1 = nullptr;
			}
			else if (node->left_!= nullptr && node->right_ == nullptr) //существует правый потомок
			{
				std::shared_ptr<Node> n2 = node;
				node = node->left_;
				n2 = nullptr;
			}
			else if (node->left_ != nullptr && node->right_ != nullptr)  //оба потомка существуют
			{
				auto curr = minimum(node->right_);
				node->value_ = curr->value_; 
				node->right_ = deletenode(node->right_, curr->value_);
			}
		}
		return node;
	}
	auto minimum(std::shared_ptr<Node> node)->std::shared_ptr<Node>
	{
		while (node->left_ != nullptr) 
		{
			node = node->left_;
		}
		return node;

	}
	auto operator = (const BinarySearchTree& tree)->BinarySearchTree& //оператор копирования
	{
		if (this == &tree)
		{
			return *this;
		}
		root_ = nullptr;
		size_ = tree.size_;
		root_ = tree.root_->memcpy();
		return *this;
	};
	auto operator = (BinarySearchTree&& tree)->BinarySearchTree& //оператор перемещения
	{
		if (this == &tree)
		{
			return *this;
		}
		root_ = nullptr;
		size_ = tree.size_;
		size_ = 0;
		root_ = tree.root_;
		tree.root_ = nullptr;

		return *this;
	};
	auto operator == (const BinarySearchTree& tree) -> bool //оператор сравнения
	{
		if (size_ != tree.size_) { return false; }
		else
		{
			return compare(root_, tree.root_);
		}
	};
	
};

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
