#include <mysql.h>
#include <iostream>
#include <string>
#include "baza_danych.h"

int main()
{
	baza_danych baza;
	if (baza.connect())
	{
		MYSQL_ROW row = NULL;
		std::string query = "SELECT relacje.id_question, COUNT(relacje.id_question) AS `wystapienia`, liczba.ilosc FROM relacje, (SELECT `id_question`, COUNT(id_question) AS `ilosc` FROM relacje WHERE `stan` = 1 GROUP BY id_question) AS `liczba` WHERE relacje.id_question = liczba.id_question GROUP BY id_question ORDER BY `wystapienia` DESC";
		std::cout << "TEST: " << baza.choice(query);
	}
	else
	{
		puts("Po³¹czenie nie udane");
	}
	baza.~baza_danych();
	std::cin.get();
	std::cin.get();
	return 0;
}