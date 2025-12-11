#pragma once
#include <iostream>
#include <cassert>

template <typename T>
class BST; // dichiariamo BST qui, serve a dichiare la classe BST come friend in Node senza scrivere il corpo della classe

template <typename T>
class Node
{
public:
    const T &value() const { return val; }

private:
    Node(const T &value, Node *l, Node *r, Node *p) : val(value), left(l), right(r), parent(p) {}
    T val;
    Node *left;
    Node *right;
    Node *parent;
    friend class BST<T>;
};

template <typename T>
class BST
{
    using Node = Node<T>;

public:
    BST() : root(nullptr) {}

    Node *max(Node *start) const
    {
        while (start->right)
        {
            start = start->right;
        }
        return start;
    }

    Node *min(Node *start) const
    {
        while (start->left)
        {
            start = start->left;
        }
        return start;
    }

    Node *predecessor(const Node *node) const
    {
        if (!node)
            return nullptr;

        if (node->left)
        {
            return max(node->left);
        }

        Node *p = node->parent;
        while (p && node == node->parent->left)
        {
            node = p;
            p = node->parent;
        }
        return p;
    }
    Node *successor(const Node *node) const
    {
        if (!node)
            return nullptr;

        if (node->right == nullptr)
        {
            return min(node->right);
        }

        Node *p = node->parent;
        while (p && node == node->parent->right)
        {
            node = p;
            p = node->parent;
        }
        return p;
    }

    Node *search(const T &value) const
    {
        Node *curr = root;
        while (curr && curr->val != value)
        {
            if (value < curr->val)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return curr;
    }

    void insert(const T &value)
    {
        Node *newNode = new Node{value, nullptr, nullptr, nullptr};

        // se l'albero è vuoto, lo metto come root
        if (isEmpty())
        {
            root = newNode;
            return;
        }

        // cerco il posto in cui mettere il nuovo nodo
        Node *prev = nullptr;
        Node *curr = root;
        while (curr)
        {
            prev = curr;
            if (value < curr->val)
                curr = curr->left;
            else
                curr = curr->right;
        }
        assert(prev); // prev non può essere nullptr altrimenti sarei nel caso in cui è empty?
        newNode->parent = prev;
        if (value < prev->val)
        {
            prev->left = newNode;
        }
        else
        {
            prev->right = newNode;
        }
    }

    void remove(Node *toDelete)
    {
        if (toDelete == nullptr)
            return;

        if (toDelete->left == nullptr) // al più un figlio destro, ma anche 0
        {
            trasplant(toDelete->right, toDelete);
        }
        else if (toDelete->right == nullptr) // ha solo un figlio sinistro
        {
            trasplant(toDelete->left, toDelete);
        }
        else
        {
            Node *succ = min(toDelete->right);
            if (succ->parent != toDelete) // succ non è il figlio diretto di toDelete, deve "scalare" l'albero
            {
                trasplant(succ->right, succ);
                succ->right = toDelete->right;
                succ->right->parent = succ;
            }
            trasplant(succ, toDelete); // trapianto il successore al posto del nodo da cancellare
            succ->left = toDelete->left;
            succ->left->parent = succ;
        }

        delete toDelete;
    }

    void inorder(Node *node) const
    {
        if (node)
        {
            inorder(node->left);
            std::cout << " " << node->val << " ";
            inorder(node->right);
        }
    }

    void preorder(Node *node) const
    {
        if (node)
        {
            std::cout << " " << node->val << " ";
            inorder(node->left);
            inorder(node->right);
        }
    }

    void postorder(Node *node) const
    {
        if (node)
        {
            inorder(node->left);
            inorder(node->right);
            std::cout << " " << node->val << " ";
        }
    }

    bool isEmpty() const { return root == nullptr; }
    Node *getRoot() const { return root; }

private:
    void trasplant(Node *src, Node *dest)
    {
        if (dest->parent == nullptr)
        {
            root = src;
        }
        else if (dest == dest->parent->left)
        {
            dest->parent->left = src;
        }
        else
        {
            dest->parent->right = src;
        }

        if (src != nullptr)
        {
            src->parent = dest->parent;
        }
    }
    Node *root;
};