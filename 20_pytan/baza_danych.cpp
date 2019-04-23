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
		return  false;
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
int baza_danych::choice(std::string query) {
	MYSQL_ROW row, all;
	MYSQL_RES* res = zapytanie(query);
	float  stosunek = 0.0, t_w = 0.0, f_w = 0.0, t_all = 0.0, f_all = 0.0, pom, pom_wystapienia, pom_ilo_true, all_wyrazy;
	int wynik;
	std::string query_all = "SELECT COUNT(id) FROM words";
	//-----------KONIEC DEKLARACJI ZMIENNYCH------------
	all = mysql_fetch_row(zapytanie(query_all)); //Strukture zawierajaca informacje o iloci wszystkich slow pasujacych
	std::istringstream bss((std::string)all[0]);
	bss >> all_wyrazy;
	while (row = mysql_fetch_row(res)) // 0 - id 1 - ilosc odpowiedzi 2 - ilosc odpowiedzi tak
	{
		std::istringstream iss((std::string)row[1]);
		iss >> pom_wystapienia;
		std::istringstream ass((std::string)row[2]);
		ass >> pom_ilo_true;
		t_w = pom_ilo_true / pom_wystapienia; //Stosunek prawdziwych do wystapien
		f_w = (pom_wystapienia - pom_ilo_true) / pom_wystapienia; //Stosunek fa³szywych do wystapien
		t_all = pom_ilo_true / all_wyrazy; //Stosunek prawdziwych do wszystkich
		f_all = (pom_wystapienia - pom_ilo_true) / all_wyrazy;//Stosunek fa³szywych do wszystkich
		pom = t_w * f_w * t_all * f_all; //Schemat oceny 
		if (stosunek < pom)
		{
			std::istringstream css((std::string)row[0]);
			css >> wynik;
		}
	}
	return wynik;
}
