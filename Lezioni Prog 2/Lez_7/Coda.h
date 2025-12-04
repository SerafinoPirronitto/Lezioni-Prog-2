#pragma once
#include <iostream>

template <typename T>
class Coda
{
public:
    Coda(size_t capacity = 32);
    // Coda(const Coda &other);
    // Coda(Coda &&other);
    // Coda &operator=(const Coda &other);
    // Coda &operator=(Coda &&other);
    //~Coda();

    void enqueue(const T &element);
    T dequeue();

    template <typename U>
    friend std::ostream &operator<<(std::ostream &out, const Coda<U> &coda);

private:
    T *m_Data;
    size_t m_Count;
    size_t m_Head;
    size_t m_Capacity;
};

template <typename T>
Coda<T>::Coda(size_t capacity) : m_Capacity(capacity), m_Count(0), m_Head(0)
{
    m_Data = new T[m_Capacity];
}

template <typename T>
void Coda<T>::enqueue(const T &element) // [1,2,3,4,5,...]
{
    size_t index = (m_Head + m_Count) % m_Capacity; // O(1)
    m_Data[index] = element;
    m_Count++;

    if (m_Count >= m_Capacity) // alloco nuovo memoria O(n)
    {
        T *oldData = m_Data;
        m_Data = new T[m_Capacity * 2];

        for (size_t i = 0; i < m_Count; i++)
        {
            m_Data[i] = oldData[(m_Head + i) % m_Capacity];
        }
        m_Head = 0;
        m_Capacity *= 2;
        delete[] oldData;
    }
}

template <typename T> // H  C+H                   H         C+H
T Coda<T>::dequeue()  //[1,2,3,4,5,6,7,8,9,10]    // [7,8,9,10, 0]
{

    --m_Count;
    if (m_Count < m_Capacity / 2 && m_Count > 32) // O(n)
    {
        T *oldData = m_Data;
        m_Data = new T[m_Capacity / 2];

        for (size_t i = 1; i < m_Count - 1; i++)
        {
            m_Data[i] = oldData[(m_Head + i) % m_Capacity];
        }

        m_Capacity /= 2;
        T out = oldData[m_Head];
        m_Head = 0;
        delete[] oldData;
        return out;
    }

    T out = m_Data[m_Head];
    m_Head = (m_Head + 1) % m_Capacity; // O(1)
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Coda<T> &coda)
{
    for (size_t i = 0; i < coda.m_Count; i++)
    {
        out << coda.m_Data[i + coda.m_Head] << " ";
    }
    return out;
}
