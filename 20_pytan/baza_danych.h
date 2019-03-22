#pragma once
#include <mysql.h>
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
public:
	MYSQL* conn;
	baza_danych();
	bool connect();
	~baza_danych();
};

