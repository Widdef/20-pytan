// MySqlTest.cpp : Defines the entry point for the console application.
//
#include <mysql.h>
#include <iostream>
#include <string>
#include "baza_danych.h"

MYSQL_RES *zapytanie(std::string query, baza_danych baza, char* tab[])
{
	const char* q = query.c_str();
	int qstate = mysql_query(baza.conn, q);
	if (!qstate)
	{
		return mysql_store_result(baza.conn);
	}
	else
	{
		std::cout << "Query failed: " << mysql_error(baza.conn) << std::endl;
		return false;
	}
}
std::string wynik(MYSQL_RES* res)
{
	MYSQL_ROW row;
	std::string wynik;
	int i = 0;
	while (row = mysql_fetch_row(res))
	{
		//*wynik++ = row;
	}
	return wynik;
}

int main()
{
	baza_danych baza;
	if (baza.connect())
	{
		MYSQL_ROW *row;
		MYSQL_RES *res;
		char* tab;
		tab = '\0';
		std::string query = "SELECT `id_question`, COUNT(id_question) AS `wystapienia` FROM relacje GROUP BY id_question ORDER BY `wystapienia` DESC LIMIT 1";
		res = zapytanie(query, baza, &tab);
		printf("Numer pytania %s\n", wynik(res));
		//query = std::string("SELECT pytanie FROM question WHERE id = ") + row[0];
		/*q = query.c_str();
		qstate = mysql_query(baza.conn, q);1>c:\users\mzygo\source\repos\widdef\20-pytan\20_pytan\main.cpp(45): note: Wskazane typy nie s¹ powi¹zane; konwersja wymaga operatora reinterpret_cast, rzutowania w stylu jêzyka C lub rzutowania w stylu funkcji

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