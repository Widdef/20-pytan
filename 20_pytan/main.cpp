#include <mysql.h>
#include <iostream>
#include <string>
#include "baza_danych.h"

int main()
{
	baza_danych baza;
	if (baza.connect())
	{
		MYSQL_ROW row;
		std::string query;
		for (int i = 0; i<20; i++)
		{
			query = baza.gen_query(1);
			//std::cout << "TEST: " << baza.choice(query);
			query = baza.choice(query);
			query = "SELECT pytanie FROM question WHERE id = " + query;
			row = mysql_fetch_row(baza.zapytanie(query));
			std::cout << std::endl << row[0]; 
			/* BY NIE ZAPOMNIEÆ ZNOWU I MYŒLEÆ PO RAZ 5 NAD TYM SAMYM JAK IDIOTA NOTKA:
					
					SELECT * FROM relacje WHERE id_question = 4 AND stan = 1;
				I TO CO ZAPISA£EM W ZESZYCIE
					SELECT * FROM (SELECT * FROM relacje {WHERE [WYNIK ZAPYTANIA POWY¯EJ]) AS wynik} WHERE id_question = 4 AND stan = 1;
				DLA 1 KROKU NIE MA BYÆ TEGO W {...}
			*/
			break;
		}
	}
	else
	{
		puts("Po³¹czenie nie udane");
	}
	baza.~baza_danych();
	std::cin.get();
	std::cin.get();
	return 0;
}