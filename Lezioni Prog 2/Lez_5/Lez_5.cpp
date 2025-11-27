#include <iostream>
#include "LinkedList.h"

int main(int argc, char **argv)
{
    Lista<int> l;

    std::cout << "Insert: 5, 6, 10 \n";
    l.insert(5);
    l.insert(6);
    l.insert(10);

    std::cout << l << std::endl;

    std::cout << "Remove: " << l.remove(6) << '\n';
    std::cout << l << std::endl;

    std::cout << "Insert: 9, 15\n";
    l.insert(9);
    l.insert(15);
    std::cout << l << std::endl;

    std::cout << "Size: " << l.size() << std::endl
              << std::endl;

    std::cout << "Remove: " << l.remove((size_t)3) << '\n';
    std::cout << l << std::endl;

    std::cout << "Clear: \n";
    l.clear();
    std::cout << l << std::endl;
}