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
	MYSQL_ROW tab[20];
	int how_much;
public:
	MYSQL_RES* zapytanie(std::string query);
	baza_danych();
	bool connect();
	~baza_danych();
	int choice(std::string query);
};

