#include <mysql.h>
#include <iostream>
#include <string>
#include "baza_danych.h"
#include <conio.h>
	
void zamiana(std::string*);

int main()
{
	SetConsoleOutputCP(CP_UTF8);
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