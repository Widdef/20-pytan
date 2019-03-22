// MySqlTest.cpp : Defines the entry point for the console application.
//
#include <mysql.h>
#include <iostream>
#include <string>
#include "baza_danych.h"

int main()
{
	using namespace std;
	baza_danych baza;
	if (baza.connect())
	{
		int qstate;
		MYSQL_ROW row;
		MYSQL_RES *res;
		string query = "SELECT `id_question`, COUNT(id_question) AS `wystapienia` FROM relacje GROUP BY id_question ORDER BY `wystapienia` DESC LIMIT 1";
		const char* q = query.c_str();
		qstate = mysql_query(baza.conn, q);
		if (!qstate)
		{
			res = mysql_store_result(baza.conn);
			while (row = mysql_fetch_row(res))
			{
				printf("Numer pytania %s\n", row[0]);
				int wystapienia = stoi(row[1]);
				cout << wystapienia;
				query = string("SELECT pytanie FROM question WHERE id = ") + row[0];
				cout << endl << query;
				q = query.c_str();
				qstate = mysql_query(baza.conn, q);
				if (!qstate)
				{
					res = mysql_store_result(baza.conn);
					while (row = mysql_fetch_row(res))
					{
						printf("\n%s\nTAK/NIE\n", row[0]);
					}
				}
			}
		}
		else
		{
			cout << "Query failed: " << mysql_error(baza.conn) << endl;
		}
	}
	else
	{
		puts("Po³¹czenie nie udane");
	}
	
	cin.get();
	cin.get();
	return 0;
}