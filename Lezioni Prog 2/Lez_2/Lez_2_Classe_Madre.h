#pragma once
#include <iostream>
#include <string>

class Animal // classe astratta o interfaccia
{
public:
    Animal(const std::string &nome, const std::string &specie) : m_Nome(nome), m_Specie(specie) {}

    virtual void faiUnVerso() = 0; // funzione virtuale pura
    void presentati()
    {
        std::cout << "Il mio nome è: " << m_Nome << " e sono un " << m_Specie << "\n";
    }

    virtual ~Animal() {}

    std::string m_Nome;
    std::string m_Specie;
};

class Dog : public Animal
{
public:
    Dog(const std::string &nome) : Animal(nome, "cane") {}

    void faiUnVerso() override
    {
        presentati();
        std::cout << "woof!\n";
    }

    void ulula()
    {
        std::cout << ululato;
    }

    const char *ululato = "uuuuuu\n";
};

class Cat : public Animal
{
public:
    Cat(const std::string &nome, int num_artigli) : Animal(nome, "gatto"), m_NumeroArtigli(num_artigli) {}

    void faiUnVerso() override
    {
        std::cout << "miao!\n";
    }

private:
    int m_NumeroArtigli;
};

// class Rectangle
// {
// public:
//     Rectangle(int base, int altezza) {}
// };

// class Square : public Rectangle
// {
// public:
//     Square(int lato) : Rectangle(lato, lato) {}
// };
