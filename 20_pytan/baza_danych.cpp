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
	how_much = 0;
}
baza_danych::~baza_danych()
{
}
bool baza_danych::connect()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, host, login, pass, database, port, unix_socket, client_flag);
	if (conn) {
		std::cout << "Polaczenie dziala";
		return true;
	}
	else {
		std::cout << "Polaczenie nie dziala";
		return false;
	}
}
std::string baza_danych::zapytanie(std::string query)
{
	const char* q = query.c_str();
	int i = 0;
	std::string test = "";
	while ((tab[i] != NULL) && i < 20)
	{
		i++;
	}
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			//test += "" + row[0];
			return test;
		}
	}
	else
	{
		std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		return false;
	}
}