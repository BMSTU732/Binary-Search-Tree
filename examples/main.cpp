#include "../include/BinarySearchTree.h"
int main()
{
	BinarySearchTree<int> tree= { 8,10,3,6,7,14,13 }; 
	//Checking "insert" function
	tree.insert(5);
	//Checking "find" function
	tree.find(10);

	BinarySearchTree<int> tree3;
	//Checking ">>" operator
	std::cin >> tree3;
	std::ofstream file1("C:\\tree.txt");
	//Cheking "<<" file operator
	file1 << tree; 
	//Cheking copy assignment operator
	tree = tree3;
	//Checking ">>" operator
	std::cout << tree<<std::endl;
	
    auto a = tree.find(1);
	std::cout << (*a) << std:: endl;
	//Cheking comparison operator
	if (tree == tree3) 
	{
		std::cout << "Trees are equal!" << std::endl;
	}
	else { std::cout << "Trees aren't equal :( " << std::endl; }
	BinarySearchTree<int> tree2 = {1,2,3,4,5,6};

	std::ifstream file2("C:\\tree33.txt");
	//Checking ">>" file operator
	file2 >> tree2;
	//Checking move assignment operator
	tree2 = std::move(tree);
	std::cout << tree2 << std::endl;
        BinarySearchTree<int> tree4 = { 6,3,8,7,2,9};
	if (tree4.remove(3) == true)
	{
		std::cout << "After removing the element: " << tree4 << std::endl;
	}
}
