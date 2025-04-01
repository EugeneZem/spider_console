#pragma once

#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>
#include <regex>
#include <iostream>

#include "DataBase.h"

using namespace std;
using namespace boost::algorithm;


class Indexer
{
public:
	Indexer();
	~Indexer();

	void setIndexerData(const string& data);
	vector<string> getWorlds();
	vector<string> getLinks();

	void extractingWords();
private:
	string page_;
	vector<string> worlds_;
	vector<string> links_;

	Transactions tr;

	//regex findMask

};
