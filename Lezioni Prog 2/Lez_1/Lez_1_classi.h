#ifndef CLASSI_H
#define CLASSI_H
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

class Persona
{
public:
    Persona() : nome("") {}

    Persona(const char *str, int *eta) : nome(str), eta(eta)
    {
    }
    Persona(const Persona &other) : nome(other.nome), eta(other.eta)
    {
        std::cout << "Usato costruttore di copia\n";
    }
    Persona(const Persona &&other) : nome(other.nome), eta(other.eta)
    {
        std::cout << "Usato costruttore di move\n";
    }

    void presentati() const
    {
        std::cout << "Ciao, io sono " << nome << " ed ho " << *eta << " anni" << std::endl;
    }

    void battezza(const char *nome)
    {
        this->nome = nome;
    }

    ~Persona()
    {
        std::cout << "Distruttore chiamato da " << nome << std::endl;
    }

private:
    const char *nome;
    const char *cognome;
    int *eta;
};

struct Libro
{
    const char *titolo;
    const char *autore;
    int annoPublicazione;
    float prezzo;
    char genere[20];
};

class Archivio
{
public:
    Archivio(size_t dimensione) : m_contatore(0)
    {
        m_Libri = new Libro[dimensione];
    }

    bool inserisciLibro(Libro &libro)
    {
        if (m_contatore == 100)
        {
            std::cerr << "Impossibile inserire il libro. Archivio Pieno\n";
            return false;
        }
        m_Libri[m_contatore++] = libro;
        return true;
    }

    void stampaArchivio() const
    {
        for (int i = 0; i < m_contatore; i++)
        {
            std::cout << "titolo: " << m_Libri[i].titolo << std::endl;
        }
    }

    Libro *cercaLibro(const char *titolo)
    {
        for (int i = 0; i < m_contatore; i++)
        {
            if (strncmp(m_Libri[i].titolo, titolo, 20) == 0)
            {
                return &m_Libri[i];
            }
        }
        return nullptr;
    }

    void salva(const char *path_to_file)
    {
        std::fstream file{path_to_file, std::ios::out}; // aprire un file in scrittura
        for (size_t i = 0; i < m_contatore; i++)
        {
            file << m_Libri[i].titolo << "\n"; // aggiunto le informazioni del libro allo ss
        }
        file.close();
    }

    void carica(const char *path_to_file)
    {
        std::fstream file{path_to_file, std::ios::in}; // aprire un file in scrittura
        char s[50];                                    // creato uno string stream
        for (size_t i = 0; i < m_contatore; i++)
        {
            file.getline(s, 50); // aggiunto le informazioni del libro allo ss
            strncpy(const_cast<char *>(m_Libri[i].titolo), s, 50);
        }
        file.close();
    }

    ~Archivio()
    {
        delete[] m_Libri;
    }

private:
    Libro *m_Libri;
    int m_contatore;
};

#endif