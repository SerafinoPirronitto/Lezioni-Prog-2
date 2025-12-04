#pragma once
#include <iostream>

template <typename T>
class Pila
{
public:
    Pila(size_t capacity = 32);
    // Pila(const Pila &other);
    // Pila(Pila &&other);
    // Pila &operator=(const Pila &other);
    // Pila &operator=(Pila &&other);
    ~Pila();

    void push(const T &element);
    T pop();

    template <typename U>
    friend std::ostream &operator<<(std::ostream &out, const Pila<U> &pila);

private:
    T *m_Data;
    size_t m_Count;
    size_t m_Capacity;
};

template <typename T>
Pila<T>::Pila(size_t capacity) : m_Capacity(capacity), m_Count(0)
{
    m_Data = new T[m_Capacity];
}

template <typename T>
Pila<T>::~Pila()
{
    delete[] m_Data;
}

template <typename T>
void Pila<T>::push(const T &element) // [1] -----> [1, 2] ------> [1,2,3] ------> [1,2,3,4]
{
    m_Data[m_Count++] = element; // O(1) anche nel caso medio,  costante ammortizato
    // se m_Count supera m_Capacity aumentare la memoria (copia di tutti gli elementi) ---> O(n)
}

template <typename T>
T Pila<T>::pop() // [1,2,3,4] -----> [1,2,3] 4
{
    if (m_Count == 0)
    {
        std::cerr << "Pila vuota";
        exit(1);
    }
    // se m_Count supera m_Capacity diminuire la memoria (copia di tutti gli elementi)
    if (--m_Count < m_Capacity / 2)
    {
        // diminuire la dimensione dell'array.
    }
    return m_Data[m_Count]; // O(1)
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Pila<T> &pila)
{
    for (int i = pila.m_Count - 1; i >= 0; i--)
    {
        out << pila.m_Data[i] << " ";
    }
    return out;
}