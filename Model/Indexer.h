#pragma once

#include <vector>
#include <string>
#include <regex>
#include <iostream>

using namespace std;

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

	//regex findMask

};
