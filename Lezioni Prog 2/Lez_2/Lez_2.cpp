/*
OBBIETTIVI DI OGGI:
- EREDITARIETA';
- POLIMORFISMO;
- OVERLOADING;

BONUS: TEMPLATE;
*/
#include <iostream>
#include <typeinfo>
#include <vector>

#include "Lez_2_Classe_Madre.h"
#include "Lez_2_Overloading.h"

int main(int argc, char **argv)
{
    Cat cat{"fuffy", 20};
    Dog dog{"bobby"};

    Animal **zoo = new Animal *[2];
    zoo[0] = &dog;
    zoo[1] = &cat;

    for (int i = 0; i < 2; i++)
    {
        std::cout << zoo[i]->m_Nome << std::endl; // accedo a m_Nome come se fosse un Animal*
        zoo[i]->faiUnVerso();                     // accedo a faiUnVerso come se fosse un Animal*
        std::cout << typeid(zoo[i]).name() << "\n";

        if (typeid(*zoo[i]) == typeid(Dog)) // mi assicuro che zoo[i] sia di tipo cane prima di fare il casting
        {
            Dog *asDog = dynamic_cast<Dog *>(zoo[i]);
            asDog->ulula(); // Accedo a ulula() come se fosse un Dog*
        }
    }

    print(3);
    print("ciao");

    Vettore v1 = {-2, 0};
    Vettore v2 = {1.5, 2}; // v3 = v1 + v2 = {-0.5, 2}

    Vettore v3 = v1 + v2;
    std::cout << v3;

    std::vector<int> vettore;
    vettore.push_back(3); // [3]
    vettore.push_back(5); // [3, 5]
    vettore[1] == 5;
    return 0;
}
