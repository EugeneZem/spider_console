#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/lexical_cast.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

using namespace std;

class NetClient
{
public:
	NetClient(boost::asio::string_view port, int version);
	~NetClient();

	string getPage(boost::asio::string_view host, boost::asio::string_view target);

private:
	boost::asio::string_view host_;
	boost::asio::string_view port_;
	boost::asio::string_view target_;
	int version_;

	string page_;

	int requvest();
};

