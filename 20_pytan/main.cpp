#include <mysql.h>
#include <iostream>
#include <string>
#include "baza_danych.h"
#include <conio.h>
#include <fstream>
#include <cstdlib>

#define CHAR_IN_LINE  60

void zamiana(std::string*);

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	std::fstream  pytania;
	pytania.open("pytania.txt",std::ios::in);
	if (pytania.good() == true)
	{
		std::string li;
		int linie = 0;
		
		while(getline(pytania, li))
		{
			std::cout << li << "\n\n";
			linie++;
		}
		char *question_linie = (char *)malloc(linie * CHAR_IN_LINE * sizeof(char));
		pytania.close();
		pytania.open("pytania.txt", std::ios::in);
		for (int i = 0; i < linie; i++)
		{
			for (int j = 0; j < CHAR_IN_LINE; j++)
			{
				pytania>>question_linie[i*CHAR_IN_LINE+j];
				if (question_linie[i*CHAR_IN_LINE + j] == '\n' || question_linie[i*CHAR_IN_LINE + j] == EOF)
				{
					break;
				}
			}
		}
		pytania.close();
	}
	else
	{
		std::cout << "B³¹d oczytywania pytañ";
	}
	baza_danych baza;
	if (baza.connect())
	{
		MYSQL_ROW row;
		std::string query;
		for (int i = 0; i < 20; i++)
		{
			query = baza.gen_query(1);
			query = baza.choice(query);
			baza.answers[0][i] = query;
			if (baza.answers[0][i] == "")
			{
				break;
			}
			query = "SELECT pytanie FROM question WHERE id = " + query;
			row = mysql_fetch_row(baza.zapytanie(query));
			if (baza.all_wyrazy == 1)
			{
				std::cout << "Znaleziono nie wyœwietlono !!!";
				break;
			}
			std::cout << std::endl<< row[0] << std::endl; // Wypisanie pytania
			do {
				std::cout << "Tak(y/Y) Nie(n/N)";
				baza.answers[1][i] = _getch();
			} while (baza.answers[1][i] != "y" && baza.answers[1][i] != "n" && baza.answers[1][i] != "Y" && baza.answers[1][i] != "N");
			zamiana(&baza.answers[1][i]);
			baza.count_answers++;
		}
		query = "SELECT slowo FROM relacje,(";
		query += baza.gen_baza_query(1);
		query += ") AS words WHERE words.id = relacje.id_words";
		row = mysql_fetch_row(baza.zapytanie(query));
		std::cout << "\n\nCzy twoje s³owo to:  " << row[0] << "\n\n";
		std::cout << "Tak(y/Y) Nie(n/N)";
		std::string ostateczna;
		ostateczna = _getch();
		zamiana(&ostateczna);
		system("cls");
		if (ostateczna == "0")
		{
			std::cout << "Dziekuje za gre!\n";
		}
		else
		{
			std::cout << "O jakim slowie myslales?\n";
			std::string slowo;
			std::cin >> slowo;
		}
			
	}
	else
	{
		puts("Po³¹czenie nie udane");
	}
	
	baza.~baza_danych();
	system("PAUSE");
	std::cin.get();
	std::cin.get();
	return 0;
}

void zamiana(std::string* znak)
{
	if (*znak == "y" || *znak == "Y")
		*znak = "0"; // W zapytaniu negujemy wartoœci dlatgo zamienione odpowiedzi by uniknac dodatkowych funkcji
	if (*znak == "n" || *znak == "N")
		*znak = "1"; // W zapytaniu negujemy wartoœci dlatgo zamienione odpowiedzi by uniknac dodatkowych funkcji
}