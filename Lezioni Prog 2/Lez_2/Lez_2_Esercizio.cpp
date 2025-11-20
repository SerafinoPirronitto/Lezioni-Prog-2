/*
SCRIVI UNA CLASSE PER UN ARRAY DINAMICO CHE EMULI IL COMPORTAMENTO
DI std::vector<T>. IN PARTICOLARE, L'ARRAY DOVRA':
- ALLOCARE NUOVA MEMORIA QUANDO NECESSARIO AD OSPITARE NUOVI ELEMENTI;
- OCCUPARE, SEMPRE E COMUNQUE, LA MINIMA MEMORIA NECESSARIA AD OSPITARE
  GLI ELEMENTI ATTUALEMTE INSERITI;
- DARE ACCESSO AGLI ELEMENTI TRAMITE USO DELL'OPERATORE [];
- IMPLEMENTARE UN METODO CHE PERMETTA DI OTTENERE IL NUMERO DI ELEMENTI;

INOLTRE DOVRA' ANCHE:
- SUPPORTARE INSERIMENTO TRAMITE USO DELL'OPERATORE +
  (ES: MyArray + 3, dovrà contenere tutti gli elementi che conteneva MyArray
   ed anche l'elemento '3')
- SUPPORTARE CANCELLAZIONE TRAMITE USO DELL'OPERATORE -;
- SUPPORTARE STAMPA TRAMITE USO DELL'OPERATORE <<;
*/
#include <cstdlib>
#include <iostream>

class Vector
{
public:
    // metodi
    Vector(size_t n = 1) : N(n), contatore(0) // [5], insert(10) --> [5, 10]
    {
        array = new int[N];
    }
    ~Vector()
    {
        delete[] array;
    }

    void insert(int elemento)
    {
        if (contatore == N)
        {
            int *temp = array;
            N = N * 2;
            array = new int[N]; // [ , ]
            for (size_t i = 0; i < contatore; i++)
            {
                array[i] = temp[i];
            }
            // [5 , 10]
            delete[] temp;
        }
        array[contatore++] = elemento;
    }

    void remove(int elemento) // cerco elemento e rimuovo
    {
        for (size_t i = 0; i < contatore; i++)
        {
            if (array[i] == elemento)
            {
                removeAtIndex(i);
                return;
            }
        }
        // non abbiamo trovato nulla
        std::cerr << "Elemento " << elemento << " non trovato\n";
    }

    void removeAtIndex(size_t index) // [1,2,3,4,5,6,7], removeAtIndex(3) ---> [1,2,3,5,6,7,7]---> [1,2,3,5,6,7]
    {
        for (size_t i = index; i < contatore; i++)
        {
            array[i] = array[i + 1];
        }
        contatore--;
        if (contatore <= N / 2) // [1,2,3,4, 0, 0, 0, 0]
        {
            int *temp = array;
            N = N / 2;
            array = new int[N];
            for (size_t i = 0; i < contatore; i++)
            {
                array[i] = temp[i];
            }
            delete[] temp;
        }
    }

    size_t size() const { return contatore; }

    int operator[](size_t index) { return array[index]; }

    // attributi
private:
    // metodi
    // attributi
    int *array;
    size_t contatore; // elementi attualmente contenuti
    size_t N;         // capacità massima
};

/*
BONUS: SCRIVERE UN INTERFACCIA PER UNA STRUTTURA DATI "CONTAINER",
       CHE CHIEDE ALLE CLASSI FIGLIE DI IMPLEMENTARE TUTTI I METODI
       DESCRITTI SOPRA E FARE IN MODO CHE L'ARRAY IMPLEMENTI SEMPLICEMENTE
       QUESTA INTERFACCIA. CI SERVIRA' PIU' AVANTI...
*/