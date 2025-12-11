#include "BST.h"

int main(int argc, char **argv)
{
    BST<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(17);
    tree.insert(22);
    tree.insert(8);
    tree.insert(1);

    std::cout << "inorder:";
    tree.inorder(tree.getRoot());
    std::cout << "\npreorder:";
    tree.preorder(tree.getRoot());
    std::cout << "\npostorder:";
    tree.postorder(tree.getRoot());

    std::cout << "\nRemove(10)\n";
    tree.remove(tree.search(10));

    std::cout << "inorder:";
    tree.inorder(tree.getRoot());
    std::cout << "\npreorder:";
    tree.preorder(tree.getRoot());
    std::cout << "\npostorder:";
    tree.postorder(tree.getRoot());
}
