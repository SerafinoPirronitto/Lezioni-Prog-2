#pragma once
#include <assert.h>

template <typename T>
class Node
{
    T val;
    Nodo *next;
    Node *prev;

    friend class ListaDoppiamenteCollegata<T>;
    friend class CircularList<T>;
};

template <typename T>
class ListaDoppiamenteCollegata
{
public:
    using Node = Node<T>;
    using LDC = ListaDoppiamenteCollegata;

    ListaDoppiamenteCollegata() : m_Head(nullptr), m_Tail(nullptr) {}
    ListaDoppiamenteCollegata(const LDC &other) : m_Head(nullptr), m_Tail(nullptr) // other:   [5] -> [6] -> [7] -> NIL
    {
        Nodo *curr = other.m_Tail;
        while (curr != m_Head)
        {
            insert_head(curr->val); // H-> [5] <-> [6] <-> [7]<-T
            curr = curr->prev;
        }

        /*
        Nodo *curr = other.m_Head;
        while (curr != nullptr)
        {
            insert_tail(curr->val); // H-> [5] <-> [6] <-> [7]<-T
            curr = curr->next;
        }
        */
    }
    // TODO: IMPLEMENTARE GLI ALTRI COSTRUTTORI/DISTRUTTORE

    void insert_head(const T &element)
    {
        Node *new_Node = new Node{element, nullptr, nullptr};
        new_Node->next = m_Head;
        if (m_Head)
            m_Head->prev = new_Node;
        m_Head = new_Node;
    }

    void insert_tail(const T &element)
    {
        Node *new_Node = new Node{element, nullptr, nullptr};
        new_Node->prev = m_Tail;
        if (m_Tail)
            m_Tail->next = new_Node;
        m_Tail = new_Node;
    }

    void remove(Node *to_delete)
    {
        assert(to_delete != nullptr);
        if (to_delete->next)                         // se esiste un elemento successivo
            to_delete->next->prev = to_delete->prev; // [5] <-> [6] <-> [7]
        if (to_delete->prev)
            to_delete->prev->next = to_delete->next;

        delete to_delete;
        to_delete = nullptr; // buona abitudine, ma tecincamente List ha la ownership del puntatore;
    }

    Node *search(const T &element)
    {
        Node *curr = m_Head;
        while (curr && curr->val != element)
        {
            curr = curr->next;
        }
        return curr; // nota che potrbbe ritornare nullptr
    } // lista.remove(lista.search(5))

    void clear()
    {
        Node *curr = m_Head;
        while (curr)
        {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }
        m_Head = nullptr;
    }

    Node *Head() const { return m_Head; }
    Node *Tail() const { return m_Tail; }

private:
    Node *m_Head;
    Node *m_Tail;
};
