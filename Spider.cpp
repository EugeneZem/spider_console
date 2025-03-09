#include <pqxx/pqxx>
#include <Windows.h>
#include <map>
#include "Model/DataBase.h"

#pragma execution_character_set("utf-8")

using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	Transactions tr;
//	tr.CreateTables();
	tr.AddDocument("https://netology.ru/profil");


/*

	CREATE TABLE public.documents (
	id_document serial NOT NULL, 
	document_name NOT NULL, 
	CONSTRAIN documents_pk PRIMARY KEY (id_document)
	);

*/


	return 0;
}
