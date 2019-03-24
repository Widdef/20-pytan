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
public:
	MYSQL_RES *zapytanie(std::string query, char* tab[]);
	baza_danych();
	bool connect();
	~baza_danych();
};

