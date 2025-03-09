#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
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

int boost();

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	Transactions tr;
	tr.CreateTables();
	tr.AddDocument("https://netology.ru/profil");

    boost();

	return 0;
}



int boost()
{
    try
    {
        //if (argc != 4 && argc != 5)
        //{
        //    std::cerr <<
        //        "Usage: http-client-sync <host> <port> <target> [<HTTP version: 1.0 or 1.1(default)>]\n" <<
        //        "Example:\n" <<
        //        "    http-client-sync www.example.com 80 /\n" <<
        //        "    http-client-sync www.example.com 80 / 1.0\n";
        //    return EXIT_FAILURE;
        //}
        auto const host = "www.example.com";
        auto const port = "80";
        auto const target = "/";
        //int version = argc == 5 && !std::strcmp("1.0", argv[4]) ? 10 : 11;
        int version = 10;

        net::io_context ioc;

        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        auto const results = resolver.resolve(host, port);

        stream.connect(results);

        http::request<http::string_body> req{ http::verb::get, target, version };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        http::write(stream, req);

        beast::flat_buffer buffer;

        http::response<http::dynamic_body> res;

        http::read(stream, buffer, res);

        std::cout << res << std::endl;

        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ ec };

    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}