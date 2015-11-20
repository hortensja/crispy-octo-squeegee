#include <iostream>

#include "wczytywanieitp.h"
#include <stdlib.h>

int main() {


	Dane dane = wczytajDane("SZABLON.tex");

	int liczbaPakietow = 25;
	wypiszDane(dane);

	std::cout << std::endl;

	
	Pakiet ** pakiety = podzielNaPakiety(dane, liczbaPakietow);
	pomieszejPakity(pakiety, liczbaPakietow, 0.5);

	Dane wynik = odmieszajPakity(pakiety);
	wypiszDane(wynik);

	system("pause");
	return 0;
}