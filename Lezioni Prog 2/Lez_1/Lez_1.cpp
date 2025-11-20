#include <fstream>
#include <iostream>
#include <cstring>
#include "Lez_1_classi.h"

Persona costruisciReference()
{
    return Persona{"Ciro", new int(3)};
}

int main(int argc, const char **argv)
{
    // std::fstream file{"prova.txt", std::ios::in};

    // char s[30] = {};     // s = {0,0,0,0,0,0,0,0,...,0}
    // file.getline(s, 30); // s={c, i, a, o, 0,0,0,0,0,0,0,0,0}
    // std::streampos cursore = file.tellg();
    // cursore += 5; // sposto il cursore in avanti di 5
    // file.seekg(cursore);
    // file.getline(s + 5, 30 - 4); // s = {c,i,a,o,0,s,t,a,i,0,0,...,0}
    // s[4] = '\n';
    // std::cout << s;

    int eta = 30;

    Persona p1{"Alfredo", &eta};
    Persona p2(costruisciReference());

    eta = 20;
    p1.presentati();
    p2.presentati();

    return 0;
}