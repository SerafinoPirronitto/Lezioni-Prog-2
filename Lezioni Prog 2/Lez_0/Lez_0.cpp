#include <iostream>
#include <fstream>
#include <string>

void increment(int &a)
{
	a++;
}

int main(int argc, const char **argv)
{
	// c-style string
	const char *stringa = "Hello World\n";
	strlen(stringa);
	strcmp(stringa, "hello");

	// c++ style
	std::string stringa2 = "Hello World\n";
	stringa2.compare(stringa);
	stringa2 = stringa2 + "ciao";

	std::cout << sizeof(std::string) << std::endl;

	// c-style
	int i = 0;
	int *p = &i; // p->i
	int j = 5;
	int &r = i;
	p = &j;
	j++;
	std::cout << *p << std::endl;

	// c++ style
	increment(i);
	std::string &stringa3 = stringa2;
	stringa3 = std::string("ciao");

	std::cin >> i;
	if (!std::cin)
	{
		std::cerr << "Errore di input\n";
		exit(1);
	}
	std::cout << i << std::endl;

	return 0;
}