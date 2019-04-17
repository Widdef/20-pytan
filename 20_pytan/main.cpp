// MySqlTest.cpp : Defines the entry point for the console application.
//
#include <mysql.h>
#include <iostream>
#include <string>
#include "baza_danych.h"



int main()
{
	baza_danych baza;
	baza_danych* wsk_baza = &baza;
	if (baza.connect())
	{
		MYSQL_ROW row = NULL;
		char* tab = NULL;
		tab = '\0';
		std::string query = "SELECT relacje.id_question, COUNT(relacje.id_question) AS `wystapienia`, liczba.ilosc FROM relacje, (SELECT `id_question`, COUNT(id_question) AS `ilosc` FROM relacje WHERE `stan` = 1 GROUP BY id_question) AS `liczba` WHERE relacje.id_question = liczba.id_question GROUP BY id_question ORDER BY `wystapienia` DESC";
		std::cout << "TEST: " << baza.choice(query);
		
		//res = zapytanie(query, baza, &tab);
		//printf("Numer pytania %s\n", wynik(res));
		//query = std::string("SELECT pytanie FROM question WHERE id = ") + row[0];
		/*q = query.c_str();
		qstate = mysql_query(baza.conn, q);

		if (!qstate)
		{
			res = mysql_store_result(baza.conn);
			while (row = mysql_fetch_row(res))
			{
				printf("\n%s\nTAK/NIE\n", row[0]);
			}
		}*/
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