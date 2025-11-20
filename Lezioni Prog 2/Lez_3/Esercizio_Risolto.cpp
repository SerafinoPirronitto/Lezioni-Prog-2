/*
SCRIVI UNA CLASSE PER UN ARRAY DINAMICO CHE EMULI IL COMPORTAMENTO
DI std::vector<T>. IN PARTICOLARE, L'ARRAY DOVRA':
- ALLOCARE NUOVA MEMORIA QUANDO NECESSARIO AD OSPITARE NUOVI ELEMENTI;
- OCCUPARE SOLO LA MEMORIA NECESSARIA AD OSPITARE GLI ELEMENTI ATTUALEMTE INSERITI;
- DARE ACCESSO AGLI ELEMENTI TRAMITE USO DELL'OPERATORE [];
- IMPLEMENTARE UN METODO CHE PERMETTA DI OTTENERE IL NUMERO DI ELEMENTI;
- IMPLEMENTARE UN METODO CHE PERMETTA DI SVUOTARE TUTTA LA STRUTTURA;

INOLTRE DOVRA' ANCHE:
- SUPPORTARE INSERIMENTO TRAMITE USO DELL'OPERATORE +
  (ES: MyArray + 3, dovrà contenere tutti gli elementi che conteneva MyArray
   ed anche l'elemento '3')
- SUPPORTARE CANCELLAZIONE TRAMITE USO DELL'OPERATORE -;
- SUPPORTARE STAMPA TRAMITE USO DELL'OPERATORE <<;
*/

/*
BONUS: SCRIVERE UN INTERFACCIA PER UNA STRUTTURA DATI "CONTAINER",
       CHE CHIEDE ALLE CLASSI FIGLIE DI IMPLEMENTARE TUTTI I METODI
       DESCRITTI SOPRA E FARE IN MODO CHE L'ARRAY IMPLEMENTI SEMPLICEMENTE
       QUESTA INTERFACCIA. CI SERVIRA' PIU' AVANTI...
*/

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <type_traits>

// L'interfaccia IContainer chiede di implementare tutte le operazioni tipiche di una struttura dati
template <typename T>
class IContainer
{
    static_assert(std::is_copy_constructible<T>::value && std::is_move_constructible<T>::value && std::is_copy_assignable<T>::value && std::is_move_assignable<T>::value);

public:
    virtual void insert(const T &element) = 0;
    virtual void insert(const T &element, size_t index) = 0;
    virtual T remove(const T &element) = 0;
    virtual T remove(size_t index) = 0;
    virtual void clear() = 0;
    virtual size_t size() const = 0;

    virtual ~IContainer() {};
};

// La classe vector implementa tutti i metodi di IContainer emulando il comportamento di std::vector<T>
template <typename T, size_t default_capacity = 64 / sizeof(T)>
class Vector : public IContainer<T>
{

public:
    inline size_t size() const override { return m_Size; }

    Vector() : m_Size(0), m_Capacity(default_capacity) { m_Data = new T[m_Capacity]; }
    Vector(const Vector &other) : m_Size(other.m_Size), m_Capacity(other.m_Capacity)
    {
        m_Data = new T[m_Capacity]; // qui m_Data viene costruito per la prima volta
        for (size_t i = 0; i < m_Size; i++)
        {
            m_Data[i] = other[i];
        }
    }
    Vector(Vector &&other) : m_Size(other.m_Size), m_Capacity(other.m_Capacity)
    {
        m_Data = other.m_Data;  // rubo la memoria
        other.m_Data = nullptr; // cancello il puntatore dell'oggetto "derubato"
        other.m_Size = 0;
    }
    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            delete[] m_Data; // qui esista già, perciò cancelliamo la vecchia memoria
            m_Size = other.m_Size;
            m_Capacity = other.m_Capacity;
            m_Data = new T[m_Capacity];
            for (size_t i = 0; i < m_Size; i++)
            {
                m_Data[i] = other[i];
            }
        }

        return *this;
    }
    Vector &operator=(Vector &&other) // operatore di assegnazione move
    {
        if (this != &other)
        {
            delete[] m_Data; // m_Data esisteva già, quindi cancello la vecchia memoria
            m_Size = other.m_Size;
            m_Capacity = other.m_Capacity;
            m_Data = other.m_Data; // rubo il puntatore a m_Data
            other.m_Size = 0;
            other.m_Data = nullptr;
        }
        return *this;
    }

    ~Vector() override { delete[] m_Data; } // ricordo di liberare la memoria

    void insert(const T &new_element) override
    {
        if (m_Size >= m_Capacity)
            resize(m_Capacity * 2);
        m_Data[m_Size++] = new_element;
    }

    void insert(const T &element, size_t index) override
    {
        if (index >= m_Size)
        {
            std::cerr << "Index " << index << " is out of range. [0 - " << (m_Size - 1) << " ].\n";
            throw new std::invalid_argument("Index out of range");
        }

        if (++m_Size > m_Capacity)
            resize(m_Capacity * 2);

        for (size_t i = m_Size - 1; i > index; i--) // esempio: [1, 2, 4, 5] insert(3,2) -> [1, 2, 3, 4, 5]
        {
            m_Data[i] = m_Data[i - 1];
        }

        m_Data[index] = element;
    }

    T remove(size_t index) override
    {
        if (index >= m_Size)
        {
            std::cerr << "Index " << index << " is out of range. [0 - " << (m_Size - 1) << " ].\n";
            throw new std::invalid_argument("Index out of range");
        }

        T element = m_Data[index];
        for (size_t i = index; i < m_Size - 1; i++) // esempio [1,2,3,4,5] remove(2) -> [1, 2, 4, 5]
        {
            m_Data[i] = m_Data[i + 1];
        }

        if (--m_Size < m_Capacity / 2 && m_Size > default_capacity)
        {
            resize(m_Capacity / 2);
        }
        return element;
    }

    T remove(const T &element) override
    {
        for (size_t i = 0; i < m_Size; i++)
        {
            if (element == m_Data[i])
            {
                return remove(i);
            }
        }

        std::cerr << "Element " << element << " is not contained in the vector.\n";
        std::cerr << *this << '\n';
        throw new std::invalid_argument("Element not Found");
    }

    void clear() override
    {
        delete[] m_Data;
        m_Data = new T[default_capacity];
        m_Capacity = default_capacity;
        m_Size = 0;
    }

    T &operator[](size_t index) // non const per permettere l'assegnazione
    {
        if (index >= m_Size)
        {
            std::cerr << "Index " << index << " is out of range. [0 - " << (m_Size - 1) << " ].\n";
            throw new std::invalid_argument("Index out of range");
        }

        return m_Data[index];
    }

    const T &operator[](size_t index) const // const per permettere di essere usato SOLO IN LETTURA quando usato su un vettore const
    {
        if (index >= m_Size)
        {
            std::cerr << "Index " << index << " is out of range. [0 - " << (m_Size - 1) << " ].\n";
            throw new std::invalid_argument("Index out of range");
        }

        return m_Data[index];
    }

    Vector &operator+(const T &element)
    {
        this->insert(element);
        return *this; // this è tipo const Vector*
    }

    Vector &operator-(const T &element)
    {
        this->remove(element);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector<T> &v)
    {
        if (v.size() == 0)
            return out << "[]";

        out << "[";
        for (size_t i = 0; i < v.size() - 1; i++)
        {
            out << (v[i]) << ", ";
        }
        out << (v[v.size() - 1]) << "]";
        return out;
    }

private:
    // Metodi
    void resize(size_t new_capacity)
    {
        if (new_capacity == 0)
            throw new std::bad_array_new_length();

        T *oldData = m_Data;
        m_Data = new T[new_capacity];

        for (size_t i = 0; i < m_Size && i < new_capacity; i++)
        {
            m_Data[i] = std::move(oldData[i]); // verrà chiamato l'operatore di assegnazione move di T non di vector<T>
        }

        m_Capacity = new_capacity;
        if (m_Capacity < m_Size)
            m_Size = m_Capacity;
        delete[] oldData;
    }

    // Attributi
    T *m_Data;
    size_t m_Size;
    size_t m_Capacity;
};

int main(int argc, const char **argv)
{
    Vector<int> array;
    std::cout << array << std::endl;

    Vector << Vector

                      array +
                  3 + 4 + 5;
    std::cout << array << std::endl;

    array - 4;
    std::cout << array << std::endl;

    std::cout << array[1] << std::endl;
    array[1] = 10;
    std::cout << array << std::endl;

    Vector<int> array2;
    array2 + 1;
    array2 = array;

    std::cout << array2 << std::endl;

    return 0;
}
