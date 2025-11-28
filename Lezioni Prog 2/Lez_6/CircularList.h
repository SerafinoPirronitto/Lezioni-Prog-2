#pragma once
#include "DoublyLinkedList.h"

#define SNETINEL_VAL 0

template <typename T>
class CircularList
{
    using Node = Node<T>;

    CircularList() : m_Head(nullptr) {}
    // altri costruttori

    void insert(const T &element)
    {
        Nodo *new_Node = new Node{element, nullptr, m_Head};

        if (m_Head == nullptr) // caso 1: Ho una lista vuota, inserisco il primo elemento
        {
            new_Node->next = new_Node;
            new_Node->prev = new_Node;
        }
        else // caso 2: ho già, almeno un elemento
        {
            new_Node->next = m_Head;       // 2
            new_Node->prev = m_Head->prev; // 1
            m_Head->prev->next = new_Node; // 1
            m_Head->prev = new_Node;       // 2
        }
        m_Head = new_Node;
    }

    void remove(Node *to_delete)
    {
        assert(to_delete != nullptr);
        if (to_delete->next == to_delete) // se c'è un solo elemento
        {
            m_Head = nullptr;
        }
        else if (m_Head == to_delete) // se elimino la testa
        {
            m_Head = to_delete->next;
        }

        to_delete->next->prev = to_delete->prev;
        to_delete->prev->next = to_delete->next;

        delete to_delete;
        to_delete = nullptr;
    }

    Node *search(const T &element)
    {
        if (m_Head == nullptr)
            return nullptr;

        Node *curr = m_Head;
        while (curr->next != curr && curr->val != element && curr->next != m_Head)
        {
            curr = curr->next;
        }

        if (curr->val == element)
            return curr; // nota che potrbbe ritornare nullptr
        else
            return nullptr;
    }

private:
    Node *m_Head;
};