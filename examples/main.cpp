#include "../include/BinarySearchTree.h"
int main()
{
    setlocale(LC_ALL,"Russian");
    BinarySearchTree<int> tree= { 8,10,3,6,7,14,13 };
    tree.insert(5);
    tree.find(10);

    BinarySearchTree<int> tree3;
    std::cin >> tree3;
    std::ofstream file1("C:\\tree.txt");
    file1 << tree;
    tree = tree3;
    std::cout << tree<<std::endl;

    auto a = tree.find(1);
    std::cout << (*a) << std:: endl;
    if (tree == tree3)
    {
        std::cout << "Деревья равны!" << std::endl;
    }
    else { std::cout << "Деревья не равны!" << std::endl; }
    BinarySearchTree<int> tree2 = {1,2,3,4,5,6};
    std::ifstream file2("C:\\tree2.txt");
    file2 >> tree2;
    tree2 = std::move(tree);
    std::cout << tree2 << std::endl;
}
