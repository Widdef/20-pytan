// MySqlTest.cpp : Defines the entry point for the console application.
//
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
		MYSQL_RES *res = NULL;
		char* tab = NULL;
		tab = '\0';
		char* test[20];
		std::string query = "SELECT `id_question`, COUNT(id_question) AS `wystapienia` FROM relacje GROUP BY id_question ORDER BY `wystapienia` DESC LIMIT 1";
		res = baza.zapytanie(query,test);
		row = baza.wynik(res);
		std::cout << row;
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
	
	std::cin.get();
	std::cin.get();
	return 0;
}