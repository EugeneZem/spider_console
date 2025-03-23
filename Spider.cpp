//#include <boost/beast/core.hpp>
//#include <boost/beast/http.hpp>
//#include <boost/beast/version.hpp>
//#include <boost/asio/connect.hpp>
//#include <boost/asio/ip/tcp.hpp>
//
//#include <boost/lexical_cast.hpp>

#include "Model/NetClient.h"

#include "Model/Indexer.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <Windows.h>
#include <map>
#include "Model/DataBase.h"

#pragma execution_character_set("utf-8")

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>


using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	Transactions tr;
	tr.CreateTables();
	tr.AddDocument("https://netology.ru/profil");

    NetClient nc("80", 10);

    string page = nc.getPage("fizika.ru", "/");

	Indexer ind;

	ind.setIndexerData(page);

	return 0;
}


