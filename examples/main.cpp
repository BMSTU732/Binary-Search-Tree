#include "../include/BinarySearchTree.h"


int main() {
	BinarySearchTree<int> Tree{ 11, 12, 15, 9 };
	auto a = 8;
	Tree.Insert(a);

	std::ofstream file("C:/Users/Роман/Desktop/BinarySearchTree.txt");

	file << Tree;
	file.close();

	std::cin >> Tree;
	std::cout << Tree << std::endl;

	std::ifstream file2("C:/Users/Роман/Desktop/BinarySearchTree.txt");
	BinarySearchTree<int> Tree2;
	file2 >> Tree2;
	std::cout << Tree2 << std::endl;

	BinarySearchTree<int> Tree3(std::move(Tree));
	std::cout << Tree3 << std::endl;

	Tree = Tree3;
	std::cout << Tree << std::endl;
	
	std::cout << (Tree == Tree2) << std::endl;

	system("pause");
	return 0;
}
