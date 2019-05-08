#include <mysql.h>
#include <iostream>
#include <string>
#include "baza_danych.h"
#include <conio.h>
	
void zamiana(std::string*);

int main()
{
	baza_danych baza;
	if (baza.connect())
	{
		MYSQL_ROW row;
		std::string query;
		for (int i = 0; i < 3; i++)
		{
			query = baza.gen_query(1);
			//std::cout << std::endl << query << std::endl;
			//std::cout << "\nTEST: " << i << std::endl;
			query = baza.choice(query);
			//std::cout << std::endl << query << std::endl;
			baza.answers[0][i] = query;
			query = "SELECT pytanie FROM question WHERE id = " + query;
			//std::cout << std::endl << query << std::endl;
			row = mysql_fetch_row(baza.zapytanie(query));
			std::cout << std::endl << row[0] << std::endl;
			do {
				std::cout << "Tak(y/Y) Nie(n/N)";
				baza.answers[1][i] = _getch();
			} while (baza.answers[1][i] != "y" && baza.answers[1][i] != "n" && baza.answers[1][i] != "Y" && baza.answers[1][i] != "N");
			zamiana(&baza.answers[1][i]);
			baza.count_answers++;
			std::cout << std::endl << baza.answers[0][i] << "  " << baza.answers[1][i];
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
		*znak = "1";
	if (*znak == "n" || *znak == "N")
		*znak = "0";
}