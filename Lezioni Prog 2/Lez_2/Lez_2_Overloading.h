#pragma once
#include <iostream>
#include <string>

// esempio di overload di una funzione
void print(int a)
{
    std::cout << "Questo e' un intero: " << a << '\n';
}

void print(std::string s)
{
    std::cout << "Questo e' un string: " << s << '\n';
}

// std::endl === << '\n' << std::flush

struct Vettore
{
    float x;
    float y;

    Vettore operator+(const Vettore &other)
    {
        return Vettore{this->x + other.x, this->y + other.y};
    }

    friend std::ostream &operator<<(std::ostream &out, const Vettore &v)
    {
        out << "{ x: " << v.x << ", y: " << v.y << "}";
        return out;
    }
};
