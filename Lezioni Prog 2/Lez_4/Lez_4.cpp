/*Algoritmi di ordinamento*/
#include <iostream>
#include <limits>
#include <random>

template <typename T>
void swap(T &a, T &b)
{
    T temp = b;
    b = a;
    a = temp;
}

template <typename T>
size_t Partition(T *array, size_t start, size_t end)
{
    T pivot = array[end]; // scelgo come pivot l'ultimo elemento della partizione

    size_t j = start;
    for (size_t i = start; i <= end; i++)
    {
        if (array[i] <= pivot)
        {
            swap(array[j], array[i]);
            j++;
        }
    }

    return j - 1;
}

template <typename T>
void QuickSort(T *array, size_t start, size_t end)
{
    if (start >= end)
        return;
    /*
        size_t rand_index = rand() % (end - start) + start;
        swap(array[end], array[rand_index]); */
    // OTTIMIZZAZIONE RANDOMICA

    size_t p = Partition(array, start, end);

    QuickSort(array, start, p - 1);
    QuickSort(array, p + 1, end);
}

template <typename T>
void Merge(T *array, size_t start, size_t half, size_t end) // [0, 1, 2, 3, 4, 5, 6]
{
    std::cout << "Chiamato Merge, con start=" << start << " half=" << half << " end=" << end << '\n';
    size_t l = half - start + 1; // dimensione array sinistro
    size_t r = end - half;       // dimensione array destro

    T *L = new T[l + 1];
    T *R = new T[r + 1];

    for (size_t i = 0; i <= l; i++)
    {
        L[i] = array[start + i];
    }
    for (size_t i = 0; i <= r; i++)
    {
        R[i] = array[half + 1 + i];
    }

    L[l] = std::numeric_limits<T>::max(); // infinito
    R[r] = std::numeric_limits<T>::max(); // infinito

    size_t j = 0;
    size_t k = 0;
    for (size_t i = start; i <= end; i++)
    {
        if (L[j] < R[k])
        {
            array[i] = L[j];
            j++;
        }
        else
        {
            array[i] = R[k];
            k++;
        }
    }

    delete[] L;
    delete[] R;
}

template <typename T>
void MergeSort(T *array, size_t start, size_t end)
{
    if (start >= end)
        return;

    size_t half = (start + end) / 2;

    MergeSort(array, start, half - 1);
    MergeSort(array, half, end);
    Merge(array, start, half, end);
}

int main(int agrc, char **argv)
{

    int array[] = {0, 9, -3, 7, -2, 1, 12, 4};

    std::cout << sizeof(array) << '\n';
    QuickSort<int>(array, 0, 7);

    for (size_t i = 0; i < 8; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    int array2[] = {-15, 7, 4, -2, 3, 0, 9, -5, 6, 10};
    size_t dim = sizeof(array2) / sizeof(int);
    std::cout << dim;
    MergeSort(array2, 0, dim - 1);
    for (size_t i = 0; i < dim; i++)
    {
        std::cout << array2[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}