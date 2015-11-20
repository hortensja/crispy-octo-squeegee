#pragma once
#include <fstream>  
#include <string>


typedef struct {
	int numerPakietu;
	int rozmiarPakietu;
	int ileWszystkichPakietow;
	int ileWszystkichDanych;
} Pakiet;

typedef struct{
	int rozmiarDanych;
	char *trescDanych;
} Dane;



Dane wczytajDane(std::string nazwa);
void wypiszDane(Dane dane);
void wypiszPakit(Pakiet pakiet);
Pakiet ** podzielNaPakiety(Dane dane, int naIlePakitow);
Pakiet ** pomieszejPakity(Pakiet** niepomieszanePakity, int naIlePakitow, double jakaCzescPakitowRazy);
Dane odmieszajPakity(Pakiet** pomieszanePakity);