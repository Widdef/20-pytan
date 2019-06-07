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
	unix_socket = NULL;
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
		//std::cout << "\nPolaczenie dziala\n";
		return true;
	}
	else {
		std::cout << "\nPolaczenie nie dziala\n";
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
std::string baza_danych::choice(std::string &query) {
	MYSQL_ROW row, all;
	MYSQL_RES* res;
	if (res = zapytanie(query))
	{
		float  stosunek = 0.0, t_w = 0.0, f_w = 0.0, t_all = 0.0, f_all = 0.0, pom, pom_ilo_true, wystapienia;
		std::string wynik;
		std::string query_all = gen_query(2);
		//-----------KONIEC DEKLARACJI ZMIENNYCH------------
		all = mysql_fetch_row(zapytanie(query_all)); //Strukture zawierajaca informacje o iloci wszystkich slow pasujacych
		std::istringstream bss((std::string)all[0]);
		bss >> all_wyrazy;
		while (row = mysql_fetch_row(res)) // 0 - id 1 - ilosc odpowiedzi 2 - ilosc odpowiedzi tak
		{
			std::istringstream iss((std::string)row[1]);
			iss >> wystapienia;
			std::istringstream ass((std::string)row[2]);
			ass >> pom_ilo_true;
			t_w = pom_ilo_true / wystapienia; //Stosunek prawdziwych do wystapien
			f_w = (wystapienia - pom_ilo_true) / wystapienia; //Stosunek fa³szywych do wystapien
			t_all = pom_ilo_true / all_wyrazy; //Stosunek prawdziwych do wszystkich
			f_all = (wystapienia - pom_ilo_true) / all_wyrazy;//Stosunek fa³szywych do wszystkich
			pom = t_w * f_w * t_all * f_all; //Schemat oceny 
			if (stosunek <= pom)
			{
				stosunek = pom;
				wynik = (std::string)row[0];
				if (stosunek == 0)
				{
					wynik = "stop";
					break;
				}
				if (pom == 0.0625)
				{
					break;
				}
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
		query = query + gen_baza_query(3);
		query = query + ",(SELECT id_question, COUNT(id_question)AS ilosc FROM";
		query = query + gen_baza_query(3);
		query = query + "WHERE stan=1 GROUP BY id_question)AS liczba WHERE relacje.id_question=liczba.id_question GROUP BY id_question ORDER BY wystapienia DESC";
		break;
	case 2:
		query = "SELECT COUNT(id) FROM ";
		query = query + gen_baza_query(2);
		break;
	}
	return query;
}

std::string baza_danych::gen_baza_query(int tabela, int numer)
{
	std::string wynik = "";
	switch (tabela)
	{
	case 1:  // 
		if (count_answers == 0)
			wynik = " relacje ";
		else
		{
			wynik = "SELECT words.* FROM relacje";
			wynik += gen_baza_query(5, count_answers - 2);
			wynik += " WHERE (words.id = relacje.id_words) AND ";
			/*if (count_answers > 1)
			{
				wynik += "words.id = relacje.id_words AND ";
			}*/
			wynik = wynik + "(id_question=" + answers[0][count_answers - 1] + " AND stan !=" + answers[1][count_answers - 1] + ") GROUP BY id_words";
		}
		break;
	case 2:
		if (count_answers == 0)
			wynik = " words ";
		else
		{
			wynik = " (SELECT relacje.id_words AS id FROM relacje," + gen_baza_query(4, count_answers - 1) + " WHERE wyrazy.id_words = relacje.id_words GROUP BY relacje.id_words";
			wynik = wynik + ") AS all_elementy";
		}
		break;
	case 3:
		if (count_answers == 0)
			wynik = " relacje ";
		else
		{
			MYSQL_ROW row;
			wynik = " (SELECT * FROM relacje WHERE(";
			MYSQL_RES* zmien = zapytanie(gen_baza_query(1));
			while (row = mysql_fetch_row(zmien))
			{
				wynik += " id_words=" + (std::string)row[0] + " OR";
			}
			wynik.pop_back();
			wynik.pop_back();
			wynik += ") AND (";
			for (int i = 0; i < count_answers; i++)
			{
				wynik += " id_question!=" + answers[0][i] + " AND";
			}
			wynik.pop_back();
			wynik.pop_back();
			wynik.pop_back();
			wynik += ")) AS relacje ";
		}
		break;
	case 4:
		if (numer == -1)
			wynik = "delete";
		else
		{
			std::string in_if = "";
			wynik = "(SELECT relacje.id_words FROM relacje,";
			in_if = gen_baza_query(4, numer - 1);
			if (in_if == "delete")
			{
				in_if = "";
				wynik.pop_back();
			}
			wynik += in_if;
			wynik += " WHERE relacje.id_question=" + answers[0][numer] + " AND stan != " + answers[1][numer] + " GROUP BY relacje.id_words) AS wyrazy";
			numer--;
		}
		break;
	case 5:
		if (numer < 0)
		{
			wynik = ", words ";
		}
		else
		{
			if (numer <= count_answers - 3)
			{
				wynik = " relacje ";
			}
			wynik += ",(SELECT words.* FROM ";
			if (numer != 0)
			{
				wynik += gen_baza_query(5, numer - 1);
				if (numer - (count_answers - 1) == 0)
					wynik += " AS words ";
			}
			else
				wynik += " words, relacje ";
			wynik += " WHERE (words.id = relacje.id_words) AND (id_question = ";
			wynik += answers[0][numer];
			wynik += " AND stan !=" + answers[1][numer];
			wynik += ")) AS words";
		}
		break;
	}
	return wynik;
}
