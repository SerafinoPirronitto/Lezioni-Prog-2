#include <iostream>
#include <string>
#include <stdint.h>

template <typename T>
void print(const T &c)
{
    std::cout << c << std::endl;
}

template <>
void print(const double &d)
{
    std::cout << "Il numero con la virgola è: " << d << std::endl;
}

template <int *p>
void print_pointed()
{
    print(*p);
}

template <>
void print_pointed<nullptr>()
{
    print("Impossible dereferenziare nullptr");
}
template <typename T>
T makeDefault()
{
    return T{};
}

template <typename T>
const T &maximum(const T &a, const T &b)
{
    return (a > b) ? a : b;
}

template <class TYPE_VOTO, class TYPE_DATA, int max_voto = 30>
struct Voto
{
    std::string nome_studente;
    TYPE_VOTO valore;
    TYPE_DATA data_esame;
};

template <class T, size_t MAX_SIZE = 256>
class Vector
{
    static_assert(MAX_SIZE != 0);

public:
    Vector()
    {
        m_Data = new T[MAX_SIZE];
    }
    T *m_Data;
};

main(int argc, const char **argv)
{

    Voto<int, std::string, 30> voto{"Fulvio", 18, "19/11/2025"};
    Vector<int, 256> v;

    int i = makeDefault<int>();
    print(i);
    char c = makeDefault<char>();
    print(c);
    print(maximum("albero", "ariete"));
    print(maximum(3, 6));
    print(5.0);

    int *g = new int{3};
    print_pointed<g>();
    int *f = nullptr;
    print_pointed<f>();

    return 0;
}