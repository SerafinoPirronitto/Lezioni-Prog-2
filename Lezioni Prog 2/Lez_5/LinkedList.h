#pragma once
#include "Container.h"
#include <iostream>
#include <string>

// Nodo<T>
template <typename T>
struct Nodo
{
    T value;
    Nodo<T> *next;
};

// Lista Collegata
template <typename T>
class Lista : public IContainer<T>
{
public:
    Lista() : m_Head(nullptr), m_Count(0) {}
    // avendo definito il costruttore, dovrei definire anche i costruttori copia e move ed operatori di asssegnazione
    // per rispettare la rule of 5:
    Lista(const Lista &other) : m_Head(nullptr), m_Count(0)
    {
        Nodo<T> *curr = other.m_Head;
        while (curr != nullptr)
        {
            // O(n) * O(n) = O(n^2)
            insert(curr->value, m_Count); // inserimento in coda. [5] -> [6] -> [1] -> NIL. [5] -> [6]-> [1] ->NIL
            curr = curr->next;
        }
    }
    Lista(Lista &&other) : m_Head(other.m_Head), m_Count(other.m_Count)
    {
        other.m_Head = nullptr;
        other.m_Count = 0;
    }
    Lista &operator=(const Lista &other)
    {
        if (this != &other)
        {
            // libero la memoria allocata
            Nodo<T> *curr = m_Head;
            while (curr != nullptr)
            {
                auto temp = curr;
                curr = curr->next;
                delete temp;
            }

            // copio la lista (inserimenti in coda)
            curr = other.m_Head;
            while (curr != nullptr)
            {
                insert(curr->value, m_Count);
                curr = curr->next;
            }
        }
    }
    Lista &operator=(Lista &&other)
    {
        if (this != other)
        {
            // libero la memoria allocata
            Nodo<T> *curr = m_Head;
            while (curr != nullptr)
            {
                auto temp = curr;
                curr = curr->next;
                delete temp;
            }

            m_Head = other.m_Head;
            m_Count = other.m_Count;
            other.m_Head = nullptr;
            other.m_Count = 0;
        }
    }
    ~Lista()
    {
        // libero la memoria allocata
        Nodo<T> *curr = m_Head;
        while (curr != nullptr)
        {
            auto temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    size_t size() const { return m_Count; }

    void insert(const T &element) // inserimento in testa
    {
        // crare un Nodo<T>
        Nodo<T> *new_node = new Nodo<T>{element, m_Head}; // da c++ 17 si può fare: new_node{.value = element, .next = nullptr};
        // Nuova Testa:
        m_Head = new_node;
        m_Count++;
    }

    void insert(const T &element, size_t index)
    {
        if (index > m_Count)
            exit_with_msg("Index out of range");

        if (index == 0)
            return insert(element); // fallback all'inserimento in testa

        Nodo<T> *prev = m_Head;
        Nodo<T> *curr = m_Head->next;

        size_t i = 0;
        while (curr != nullptr && i < index) // finché non raggiungo la fine della lista o arrivo all'indice desiderato
        {
            i++;
            prev = curr;
            curr = curr->next;
        } // O(n)
        // tecnicamente non serve perché controlliamo all'entrata nella funzione se l'indice è corretto
        // exit_if_null(curr, "Index out of range");

        Nodo<T> *new_node = new Nodo<T>{element, nullptr};
        prev->next = new_node;
        new_node->next = curr;

        m_Count++;
    }

    T remove(const T &element)
    {
        // Le operazioni in testa sono "speciali" perché devo cambiare il valore di m_Head
        if (m_Head->value == element)
        {
            Nodo<T> *temp = m_Head;
            m_Head = m_Head->next;
            delete temp;
            m_Count--;
            return element;
        }

        // altrimenti mi basta cambiare i collegamenti tra i nodi precedenti e successivi
        Nodo<T> *prev = m_Head;
        Nodo<T> *curr = m_Head->next;

        while (curr != nullptr && curr->value != element) // finché non raggiungo la fine della lista o arrivo all'elemento desiderato
        {
            prev = curr;
            curr = curr->next;
        }
        exit_if_null(curr, "Element not found");

        prev->next = curr->next;
        delete curr;
        m_Count--;
        return element;
    }

    T remove(size_t index)
    {
        if (index >= m_Count)
            exit_with_msg("Index out of range");

        if (index == 0)
            return remove(m_Head->value);

        Nodo<T> *prev = m_Head;
        Nodo<T> *curr = m_Head->next;

        size_t i = 1;
        while (curr != nullptr && i < index) // finché non raggiungo la fine della lista o arrivo all'indice desiderato
        {
            i++;
            prev = curr;
            curr = curr->next;
        }
        // exit_if_null(curr, "Index out of range");
        // preferisco fare un controllo prima di scorrere tutta la lista (principio Fail-Fast).

        T element = curr->value;
        prev->next = curr->next;
        delete curr;
        m_Count--;
        return element;
    }

    void clear()
    {
        Nodo<T> *curr = m_Head;

        while (curr != nullptr)
        {
            Nodo<T> *temp = curr;
            curr = curr->next;
            delete temp;
        }

        m_Head = nullptr;
        m_Count = 0;
    }

    const T &operator[](size_t index) const // operatore [] valido solo in lettura, non posso fare assegnazioni tipo 'lista[3] = 5;'
    {
        if (index >= m_Count)
            exit_with_msg("Index out of range");

        if (index == 0)
            return m_Head->value;

        Nodo<T> *prev = m_Head;
        Nodo<T> *curr = m_Head->next;

        size_t i = 1;
        while (curr != nullptr && i < index) // finché non raggiungo la fine della lista o arrivo all'indice desiderato
        {
            i++;
            prev = curr;
            curr = curr->next;
        }
        // se ho raggiunto la fine esco.
        exit_if_null(curr, "Index out of range: reached end of list");
        return curr->value;
    }

    friend std::ostream &operator<<(std::ostream &out, const Lista &l)
    {
        out << "Head: ";
        for (size_t i = 0; i < l.m_Count; i++)
        {
            out << "[" << l[i] << "] -> ";
        }
        out << "NIL" << std::endl;
        return out;
    }

private:
    inline void exit_if_null(const void *ptr, const std::string &msg = "") const
    {
        if (!ptr)
        {
            std::cerr << msg << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    inline void exit_with_msg(const std::string &msg) const
    {
        std::cerr << msg << std::endl;
        exit(EXIT_FAILURE);
    }

    Node<T> *m_Tail;
    Nodo<T> *m_Head;
    size_t m_Count;
};
