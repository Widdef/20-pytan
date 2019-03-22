#include "baza_danych.h"
#include <mysql.h>

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
	if (conn) {
		return true;
	}
	else {
		return false;
	}
}

