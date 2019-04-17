#include "baza_danych.h"
#include <mysql.h>
#include <string>
#include <iostream>
#include <sstream>

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
MYSQL_RES* baza_danych::zapytanie(std::string query)
{
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		MYSQL_RES* res = mysql_store_result(conn);
		return res;
	}
	else
	{
		std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		return false;
	}
}
float baza_danych::choice(std::string query) {
	MYSQL_ROW row, all;
	float  stosunek = 0.0, pom = 0.0;
	int max = 0, ilosc = 0, pom_wys, pom_ilo, all_wyrazy;
	std::string query_all = "SELECT COUNT(id) FROM words";
	all = mysql_fetch_row(zapytanie(query_all));
	std::istringstream bss((std::string)all[0]);
	bss >> all_wyrazy;
	while (row = mysql_fetch_row(zapytanie(query)))
	{
		std::istringstream iss((std::string)row[1]);
		iss >> pom_wys;
		std::istringstream ass((std::string)row[2]);
		ass >> pom_ilo;
		pom = (float)pom_ilo / (float)all_wyrazy;
		return pom;
	}

	return stosunek;
}