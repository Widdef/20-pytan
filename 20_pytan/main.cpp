#include <mysql.h>
#include <iostream>
#include <string>
#include "baza_danych.h"
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <sstream>

#define CHAR_IN_LINE  60

void zamiana(std::string*);
void referencja(int &);

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	int zmienna = 5;
	std::cout << "Referencja!!!!\nPrzed wprowadzeniem do funkcji: " << zmienna << "\nPo wprowadzeniu do funkcji: ";
	referencja(zmienna);
	std::cout << zmienna << "\nWciœnij klawisz by przejœæ do 20 pytañ";
	std::cin.get();
	system("cls");
	std::fstream  pytania;
	pytania.open("pytania.txt",std::ios::in);
	if (pytania.good() == true)
	{
		std::string li;
		char *question_linie;
		int linie = 0;
		while(getline(pytania, li))
		{
			linie++;
		}
		question_linie = (char *)malloc(linie * CHAR_IN_LINE * sizeof(char*));
		pytania.close();
		pytania.open("pytania.txt", std::ios::in);
		for (int i = 0; i < linie; i++)
		{
			for (int j = 0; j < CHAR_IN_LINE; j++)
			{
				pytania >> std::noskipws >> question_linie[i*CHAR_IN_LINE+j];
				if (question_linie[i*CHAR_IN_LINE + j] == '\n' || question_linie[i*CHAR_IN_LINE + j] == EOF)
				{
					break;
				}
			}
		}
		pytania.close();
		baza_danych baza;
		if (baza.connect())
		{
			MYSQL_ROW row;
			std::string query;
			int numer;
			for (int i = 0; i < 20; i++)
			{
				query = baza.gen_query(1);
				query = baza.choice(query);
				if (query == "stop")
				{
					break;
				}
				baza.answers[0][i] = query;
				if (baza.answers[0][i] == "")
				{
					break;
				}
				query = "SELECT * FROM question WHERE id = " + query;
				row = mysql_fetch_row(baza.zapytanie(query));
				if (baza.all_wyrazy == 1)
				{
					break;
				}
				std::cout << std::endl;
				//std::cout << std::endl << row[1] << std::endl; // Wypisanie pytania
				std::istringstream iss((std::string)row[0]);
				iss >> numer;
				for (int j = 0; j < CHAR_IN_LINE; j++)
				{
					std::cout << question_linie[(numer - 1)*CHAR_IN_LINE + j];
				}
				std::cout << std::endl;
				do {
					std::cout << "Tak(y/Y) Nie(n/N)";
					baza.answers[1][i] = _getch();
				} while (baza.answers[1][i] != "y" && baza.answers[1][i] != "n" && baza.answers[1][i] != "Y" && baza.answers[1][i] != "N");
				zamiana(&baza.answers[1][i]);
				baza.count_answers++;
			}
			query = "SELECT slowo FROM relacje,(";
			query += baza.gen_baza_query(1);
			query += ") AS words WHERE words.id = relacje.id_words";
			row = mysql_fetch_row(baza.zapytanie(query));
			std::cout << "\n\nCzy twoje s³owo to:  " << row[0] << "\n\n";
			std::cout << "Tak(y/Y) Nie(n/N)";
			std::string ostateczna;
			ostateczna = _getch();
			zamiana(&ostateczna);
			system("cls");
			if (ostateczna == "0")
			{
				std::cout << "Dziekuje za gre!\n";
			}
			else
			{
				/*std::cout << "O jakim slowie myslales?\n";
				std::string slowo;
				std::cin >> slowo;
				query = "INSERT INTO words (slowo) VALUES (\""+slowo+"\")";
				mysql_fetch_row(baza.zapytanie(query));
				query = "SELECT COUNT(id) FROM question";
				row = mysql_fetch_row(baza.zapytanie(query));
				std::istringstream iss((std::string)row[0]);
				iss >> numer;
				row = mysql_fetch_row(baza.zapytanie("SELECT id FROM words WHERE slowo = \""+slowo+"\""));
				std::string id_word = row[0];
				std::string stan;
				for (int i = 0; i < numer; i++)
				{
					stan = "-1";
					for (int j = 0; j < 20; j++)
					{
						if (baza.answers[0][j] == std::to_string(i))
						{
							stan = baza.answers[1][j];
							break;
						}
					}
					query = "INSERT INTO relacje VALUES (\"" + std::to_string(i) + "\",\"" + id_word + "\",\"" + stan + "\")";
					mysql_fetch_row(baza.zapytanie(query));
				}*/
			}

		}
		else
		{
			puts("Po³¹czenie nie udane");
		}
		free(question_linie);
		baza.~baza_danych();
		system("PAUSE");
		std::cin.get();
		std::cin.get();
	}
	else
	{
		std::cout << "B³¹d odczytywania pytañ";
	}
	return 0;
}

void zamiana(std::string* znak)
{
	if (*znak == "y" || *znak == "Y")
		*znak = "0"; // W zapytaniu negujemy wartoœci dlatgo zamienione odpowiedzi by uniknac dodatkowych funkcji
	if (*znak == "n" || *znak == "N")
		*znak = "1"; // W zapytaniu negujemy wartoœci dlatgo zamienione odpowiedzi by uniknac dodatkowych funkcji
}

void referencja(int &zmienna)
{
	zmienna*=zmienna;
}