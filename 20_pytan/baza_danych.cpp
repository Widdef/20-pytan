#include "baza_danych.h"
#include <mysql.h>
#include <string>
#include <iostream>

baza_danych::baza_danych()
{
	host = "localhost";
	login = "root";
	pass = "DonQnei199&MDon!QAZUMK";
	database = "ask_20";
	port = 3306;
	unix_socket = 0;
	client_flag = 0;
}
baza_danych::~baza_danych()
{
}
bool baza_danych::connect()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, host, login, pass, database, port, unix_socket, client_flag);
	//std::cout << "test_polaczenia";
	if (conn) {
		std::cout << "Polaczenie dziala";
		return true;
	}
	else {
		std::cout << "Polaczenie nie dziala";
		return false;
	}
}
MYSQL_RES* baza_danych::zapytanie(std::string query, char* tab[])
{
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		return mysql_store_result(conn);
	}
	else
	{
		std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		return false;
	}
}
void baza_danych::wynik(MYSQL_RES * res)
{
	MYSQL_ROW row;
	char row2 = 'a';
	//std::string tab[20];
	int i = 0;
	while (row = mysql_fetch_row(res))
	{
		//row2 = *row[0];
		//tab[i] = row[i];
		printf("\n%s", row[0]);
		i++;
		//std::cout << "TEST" << row[0] << std::endl;
	}
	//return row2;
}



