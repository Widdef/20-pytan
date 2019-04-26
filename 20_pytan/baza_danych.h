#pragma once
#include <mysql.h>
#include <string>
class baza_danych
{
private:
	const char *host;
	const char *login;
	const char *pass;
	const char *database;
	unsigned int port;
	const char *unix_socket;
	unsigned long client_flag;
	MYSQL* conn;
	std::string gen_baza_query(int tabela);
public:
	int count_answers;
	std::string answers[2][20];
	baza_danych();
	~baza_danych();
	bool connect();
	MYSQL_RES* zapytanie(std::string query);
	std::string choice(std::string query);
	std::string gen_query(int rodzaj);
};

