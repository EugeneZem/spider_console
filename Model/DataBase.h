#pragma once

#include <pqxx/pqxx>
#include <string>
#include <tuple>

using namespace std;

class Transactions
{
	tuple<string, string, string, string, string> connectData_ = 
		{ "localhost", "5432", "Spider", "postgres", "392260" };
	string error_;

public:
	Transactions() {};
	~Transactions() {};

	void CreateTables();
	void AddDocument(string link_to_document);
	//void AddWord(string word, string link_to_document, int quantity);
	int CheckWord(string word);

private:
	string SQLQuery_;

	int id_;

	int connectForTransaction();

	int connectForQuery();



};
