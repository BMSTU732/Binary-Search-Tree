#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H
#include <initializer_list>
#include <iostream>
#include <fstream>
#include <memory>
template<typename T>
class BinarySearchTree;

template <typename T>
std::ostream & operator << (std::ostream & out, const BinarySearchTree<T> & tree)//вывод
{
	tree.SWalk(out, tree.GetRoot());
	return out;
};
template <typename T>
std::istream & operator >> (std::istream & in, BinarySearchTree<T> & tree)//ввод
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
template <typename T>
std::ofstream & operator << (std::ofstream & out, const BinarySearchTree<T> & tree)//вывод в файл
{
	tree.PWalk(out, tree.GetRoot());
	return out;
};
template <typename T>
std:: ifstream & operator >> (std::ifstream& in, BinarySearchTree<T>& tree)//ввод в файл
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
		Node * left_;
		Node * right_; 
		T value_; //значение

		
		Node(T value) : value_(value), left_(nullptr), right_(nullptr) {};
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
	size_t size_; 

public:

	BinarySearchTree() : size_(0), root_(nullptr) {};
	BinarySearchTree(const std::initializer_list<T> & list) : size_(0), root_(nullptr)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			insert(*it);
		};

	};
	BinarySearchTree(const BinarySearchTree& tree) 
	{
		root_ = tree.root_->memcpy();
	};
	BinarySearchTree(BinarySearchTree&& tree) 
	{
		size_ = tree.size_;
		tree.size_ = 0;
		root_ = tree.root_;
		tree.root_ = nullptr;
	};
	void PWalk(std::ostream & str, std::shared_ptr<Node> this_node) const noexcept 
	{
		if (!this_node) { return; }
		str << this_node->value_ << " ";
		PWalk(str, this_node->left_);
		PWalk(str, this_node->right_);
	}
	void SWalk(std::ostream &str, std::shared_ptr<Node> this_node) const noexcept 
	{
		if (!this_node) { return;  }
		SWalk(str, this_node->right_);
		str << this_node->value_ << " ";
		SWalk(str, this_node->left_);
	}
	auto GetRoot() const -> std::shared_ptr<Node>
	{
		return root_;
	}
	auto compare(const std::shared_ptr<Node>node1,const std::shared_ptr<Node> node2) const noexcept -> bool {

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
		return false;
	};
	auto deletenode(std::shared_ptr<Node> &node, const T& value) ->bool
	{
		if (node == nullptr) { return false; }
		if (value < node->value_)
		{
			deletenode(node->left_, value); 
		}
		else if (value> node->value_) 
		{
			deletenode(node->right_, value); 
		}
		else 
		{
			if (node->left_ == nullptr && node->right_ == nullptr) //удаляем лист
			{
				node=nullptr;
				return true;
			}
			if (node->left_!=nullptr && node->right_==nullptr) //существует левый потомок
			{
				node = node->right_;
				return true;
			}
			else if (node->right_!= nullptr && node->left_ == nullptr) //существует правый потомок
			{
				node = node->left_;
				return true;
			}
			else if (node->left_ != nullptr && node->right_ != nullptr)  //оба потомка существуют
			{
				std::shared_ptr<Node> my_node1 = node->right_;
				std::shared_ptr<Node> my_node2 =node;
				while (my_node1->left_ != nullptr) 
				{
					my_node2 = my_node1;
					my_node1= my_node1->left_;
				}
				node->value_ = my_node1->value_;
				my_node2->left_ = nullptr;
			}

		}
		return true;
	}
	
	auto operator = (const BinarySearchTree& tree)->BinarySearchTree& 
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
	auto operator = (BinarySearchTree&& tree)->BinarySearchTree& 
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
	auto operator == (const BinarySearchTree& tree) -> bool 
	{
		if (size_ != tree.size_) { return false; }
		else
		{
			compare(root_, tree.root_);
		}
	};
	
};
#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
