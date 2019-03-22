// MySqlTest.cpp : Defines the entry point for the console application.
//
#include <mysql.h>
#include <iostream>
#include <string>
#include "baza_danych.h"

MYSQL_RES *zapytanie(std::string query, baza_danych baza)
{
	MYSQL_RES *res;
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

int main()
{
	baza_danych baza;
	if (baza.connect())
	{
		int qstate;
		MYSQL_ROW row;
		MYSQL_RES *res;
		std::string query = "SELECT `id_question`, COUNT(id_question) AS `wystapienia` FROM relacje GROUP BY id_question ORDER BY `wystapienia` DESC LIMIT 1";
		res = zapytanie(query, baza);
		while (row = mysql_fetch_row(res))
		{
			printf("Numer pytania %s\n", row[0]);
			int wystapienia = std::stoi(row[1]);
			std::cout << wystapienia;
			query = std::string("SELECT pytanie FROM question WHERE id = ") + row[0];
			std::cout << std::endl << query;
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
	}
	else
	{
		puts("Po³¹czenie nie udane");
	}
	
	std::cin.get();
	std::cin.get();
	return 0;
}