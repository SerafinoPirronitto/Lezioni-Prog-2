#include "Pila.h"
#include "Coda.h"

int main(int argc, char **argv)
{
    Pila<int> p;
    Coda<int> c(1);

    p.push(20);
    p.push(25);
    p.push(12);
    p.push(3);

    std::cout << p << '\n';

    std::cout << "Popped: " << p.pop() << '\n';
    std::cout << p << '\n';

    c.enqueue(20);
    c.enqueue(25);
    c.enqueue(12);
    c.enqueue(3);
    std::cout << c << '\n';
    std::cout << "Dequeued: " << c.dequeue() << '\n';
    std::cout << c << '\n';
}