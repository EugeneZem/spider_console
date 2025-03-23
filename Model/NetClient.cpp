#include "NetClient.h"

NetClient::NetClient(boost::asio::string_view port, int version) :
	port_(port), version_(version)
{
}

NetClient::~NetClient()
{
}


string NetClient::getPage(boost::asio::string_view host, boost::asio::string_view target)
{
	host_ = host;
	target_ = target;

	if (requvest()) page_ = "";
	return page_;
}

int NetClient::requvest()
{

	try
	{
		net::io_context ioc;

		tcp::resolver resolver(ioc);
		beast::tcp_stream stream(ioc);

		auto const results = resolver.resolve(host_, port_);

		stream.connect(results);

		http::request<http::string_body> req{ http::verb::get, target_, version_ };
		req.set(http::field::host, host_);
		req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

		http::write(stream, req);

		beast::flat_buffer buffer;

		http::response<http::dynamic_body> res;

		http::read(stream, buffer, res);

		page_ = boost::lexical_cast<std::string>(res);

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