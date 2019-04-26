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
	count_answers = 0;
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
std::string baza_danych::choice(std::string query) {
	MYSQL_ROW row, all;
	MYSQL_RES* res;
	if (res = zapytanie(query))
	{
		float  stosunek = 0.0, t_w = 0.0, f_w = 0.0, t_all = 0.0, f_all = 0.0, pom, pom_wystapienia, pom_ilo_true, all_wyrazy;
		std::string wynik;
		std::string query_all = gen_query(2);
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
			//std::cout <<  std::endl << stosunek << pom << std::endl;
			if (stosunek < pom)
			{
				stosunek = pom;
				wynik = (std::string)row[0];
			}
		}
		return wynik;
	}
	else
	{
		return false;
	}
}

std::string baza_danych::gen_query(int rodzaj)
{
	std::string query;
	std::string inside_query = "";
	switch (rodzaj)
	{
	case 1: 
		query = "SELECT relacje.id_question, COUNT(relacje.id_question)AS wystapienia, liczba.ilosc FROM ";
		query += gen_baza_query(3);
		//std::cout <<std::endl << query << std::endl;
		query += ",(SELECT id_question, COUNT(id_question)AS ilosc FROM";
		query += gen_baza_query(3);
		query += "WHERE stan=1 GROUP BY id_question)AS liczba WHERE relacje.id_question=liczba.id_question GROUP BY id_question ORDER BY wystapienia DESC";
		//std::cout << std::endl << query << std::endl; 
		break;
	case 2: inside_query = gen_baza_query(2); 
		query = "SELECT COUNT(id) FROM ";
		query += inside_query; 
		break;
	case 3:
		query = "";
		break;
	}
	return query;
}

std::string baza_danych::gen_baza_query(int tabela)
{
	std::string wynik = "";
	switch (tabela)
	{
	case 1:
		if (count_answers == 0)
			wynik = " relacje ";
		else
		{
			wynik = " (SELECT * FROM relacje WHERE ";
			for (int i = 0; i < count_answers; i++)
			{
				wynik += "(id_question=" + answers[0][i] + " AND stan=" + answers[1][i] + ")";
				if (i < count_answers - 1)
				{
					wynik += " OR ";
				}
			}
			wynik += ") AS relacje ";
		}
		break;
	case 2:
		if (count_answers == 0)
			wynik = " words ";
		else
		{
			wynik = " (SELECT words.id FROM words, relacje WHERE words.id=relacje.id_words AND ";
			for (int i = 0; i < count_answers; i++)
			{
				wynik += "(id_question=" + answers[0][i] + " AND stan=" + answers[1][i] + ")";
				if (i < count_answers - 1)
				{
					wynik += " OR ";
				}
			}
			wynik += ") AS all_elementy";
		}
		break;
	case 3:
		if (count_answers == 0)
			wynik = " relacje ";
		else
		{
			MYSQL_ROW row;
			wynik = " (SELECT * FROM relacje WHERE(";
			while (row = mysql_fetch_row(zapytanie(gen_baza_query(1))))
			{
				wynik += " id_words=" + (std::string)row[1] + " OR";
			}
			wynik.pop_back();
			wynik.pop_back();
			wynik += ") AND (";
			for (int i = 0; i < count_answers; i++)
			{
				wynik += " id_question!=" + answers[0][i] + " OR";
			}
			wynik.pop_back();
			wynik.pop_back();
			wynik += ")) AS relacje ";
			break;
		}
		return wynik;
	}
}
