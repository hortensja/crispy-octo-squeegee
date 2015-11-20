#include "wczytywanieitp.h"

#include <iostream>
#include <fstream>  
#include <string>
#include <random>

std::mt19937 jakisRnaodm;

Dane wczytajDane(std::string nazwaPliku)
{

	Dane d;

	std::ifstream is(nazwaPliku, std::ifstream::binary);
	if (is) {
		// get length of file:
		is.seekg(0, is.end);
		int rozmiarDanych = is.tellg();
		is.seekg(0, is.beg);

		char *zawartoscDanych = new char[rozmiarDanych];

		std::cout << "Reading " << rozmiarDanych << " characters... ";
		// read data as a block:
		is.read(zawartoscDanych, rozmiarDanych);

		if (is)
			std::cout << "all characters read successfully.";
		else
			std::cout << "error: only " << is.gcount() << " could be read";
		std::cout << std::endl;
		is.close();

		d.rozmiarDanych = rozmiarDanych;
		d.trescDanych = zawartoscDanych;

		return d;

		// ...buffer contains the entire file...

		//delete[] buffer;
	}
	else {
		std::cout << "Nie udalo sie otworzyc pliku\n";
		d.rozmiarDanych = 0;
		d.trescDanych = nullptr;
		return d;
	}
}

void wypiszDane(Dane dane) {
	for (int i = 0; i < dane.rozmiarDanych; i++)
		std::cout << dane.trescDanych[i];
	std::cout << std::endl;
}

void wypiszPakit(Pakiet *pakiet){
	std::cout << pakiet->numerPakietu << " ";
	std::cout << pakiet->rozmiarPakietu << " ";
	char * wsk = (char*) (pakiet+1);
	for (int i = 0; i < pakiet->rozmiarPakietu; i++)
		std::cout << *(wsk + i);
	std::cout << std::endl;
}

Pakiet ** podzielNaPakiety(Dane dane, int naIlePakitow){

	Pakiet ** tablicaWskaznikowNaPakiet = new Pakiet*[naIlePakitow];
		
	int rozmiarPakitu = dane.rozmiarDanych / naIlePakitow;
	int rozmiarOstatniegoPakitu = dane.rozmiarDanych - rozmiarPakitu*(naIlePakitow - 1);


	if (rozmiarOstatniegoPakitu > rozmiarPakitu){
		rozmiarPakitu++;
		rozmiarOstatniegoPakitu = dane.rozmiarDanych - rozmiarPakitu*(naIlePakitow - 1);
	}

	for (int i = 0; i < naIlePakitow; i++){

		char* pakiet = new char[sizeof(Pakiet) + rozmiarPakitu];
		tablicaWskaznikowNaPakiet[i] = (Pakiet *)pakiet;
		tablicaWskaznikowNaPakiet[i]->numerPakietu = i;
		tablicaWskaznikowNaPakiet[i]->ileWszystkichPakietow = naIlePakitow;
		tablicaWskaznikowNaPakiet[i]->ileWszystkichDanych = dane.rozmiarDanych;
		
		if (i == (naIlePakitow - 1)){
			tablicaWskaznikowNaPakiet[i]->rozmiarPakietu = rozmiarOstatniegoPakitu;
			memcpy(tablicaWskaznikowNaPakiet[i] + 1, dane.trescDanych + rozmiarPakitu*i, rozmiarOstatniegoPakitu);
		}
		else{
			tablicaWskaznikowNaPakiet[i]->rozmiarPakietu = rozmiarPakitu;
			memcpy(tablicaWskaznikowNaPakiet[i] + 1, dane.trescDanych + rozmiarPakitu*i, rozmiarPakitu);
		}
		//wypiszPakit(tablicaWskaznikowNaPakiet[i]);
	}


	return tablicaWskaznikowNaPakiet;


}

Pakiet ** pomieszejPakity(Pakiet** niepomieszanePakity, int naIlePakitow, double jakaCzescPakitowRazy){

	std::uniform_int_distribution<int> rozklad(0, naIlePakitow-1);

	for (size_t i = 0; i < naIlePakitow*jakaCzescPakitowRazy; i++)	{

		int miejsce1 = rozklad(jakisRnaodm);
		int miejsce2 = rozklad(jakisRnaodm);

		Pakiet * temp = niepomieszanePakity[miejsce1];
		niepomieszanePakity[miejsce1] = niepomieszanePakity[miejsce2];
		niepomieszanePakity[miejsce2] = temp;
	}
	return niepomieszanePakity;
}

Dane odmieszajPakity(Pakiet** pomieszanePakity){

	Dane dane;
	int ilePakitow = pomieszanePakity[0]->ileWszystkichPakietow;
	dane.rozmiarDanych = pomieszanePakity[0]->ileWszystkichDanych;

	dane.trescDanych = new char[dane.rozmiarDanych];

	for (int i = 0; i < ilePakitow; i++)	{

		int nrPakitu = pomieszanePakity[i]->numerPakietu;
		int rozmiarPakkitu = pomieszanePakity[i]->rozmiarPakietu;
		if (nrPakitu == (ilePakitow - 1)){
			memcpy(dane.trescDanych + nrPakitu*pomieszanePakity[(i-1)%ilePakitow]->rozmiarPakietu, pomieszanePakity[i] + 1, rozmiarPakkitu);
		}
		else {
			memcpy(dane.trescDanych + nrPakitu*rozmiarPakkitu, pomieszanePakity[i] + 1, rozmiarPakkitu);
		}
		wypiszPakit(pomieszanePakity[i]);
	}
	return dane;
}