#include <iostream>
#include "DataBase.h"

using namespace std;

void Transactions::CreateTables()
{
	SQLQuery_ = 
		"CREATE TABLE IF NOT EXISTS public.words ("
		"id_word serial NOT NULL, "
		"word text NOT NULL, "
		"CONSTRAINT words_pk PRIMARY KEY (id_word)); ";
	if (connectForTransaction()) cout << error_;

	SQLQuery_ =
		"CREATE TABLE IF NOT EXISTS public.documents ("
		"id_document serial NOT NULL, "
		"link_to_document text NOT NULL, "
		"CONSTRAINT document_pk PRIMARY KEY (id_document)); ";
	if (connectForTransaction()) cout << error_;

	SQLQuery_ = 
		"CREATE TABLE IF NOT EXISTS public.documents_words ("
		"id_word int NOT NULL, "
		"id_document int NOT NULL, "
		"quantity_word_in_document int NOT NULL, "
		"CONSTRAINT fk1 FOREIGN KEY "
		"(id_word) REFERENCES public.words(id_word), "
		"CONSTRAINT fk2 FOREIGN KEY "
		"(id_document) REFERENCES public.documents(id_document));";
	if (connectForTransaction()) cout << error_;
}

void Transactions::AddDocument(string link_to_document)
{
	SQLQuery_.clear();
	SQLQuery_ =
		"INSERT INTO documents "
		"(link_to_document) "
		"VALUES('" + link_to_document + "');";
	connectForTransaction();
}

int Transactions::connectForTransaction()
{
	try
	{
		pqxx::connection connect(
			"host=" + get<0>(connectData_) + " port=" + get<1>(connectData_) +
			" dbname=" + get<2>(connectData_) + " user=" + get<3>(connectData_) +
			" password=" + get<4>(connectData_));

		pqxx::work transaction{ connect };
		transaction.exec(SQLQuery_);
		transaction.commit();
	}
	catch (const exception& e)
	{
		error_ = e.what();
		return  1;
	}

	return 0;
}

int Transactions::connectForQuery()
{
	try
	{
		pqxx::connection connect(
			"host=" + get<0>(connectData_) + " port=" + get<1>(connectData_) +
			" dbname=" + get<2>(connectData_) + " user=" + get<3>(connectData_) +
			" password=" + get<4>(connectData_));

		pqxx::work transaction{ connect };
		
		id_ = transaction.query_value<int>(SQLQuery_);
	}
	catch (const exception& e)
	{
		error_ = e.what();
		return  1;
	}

	return 0;
}

int Transactions::CheckWord(string word)
{
	SQLQuery_ =
		"SELECT id_word FROM words WHERE word='" + word + "';";

	cout << SQLQuery_ << '\n';
	if (connectForQuery())
	{
		cout << error_;
		return 0;
	}

	cout << "SQL result " << id_ ;
	return id_;
}

