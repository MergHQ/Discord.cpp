#include "stdafx.h"
#include <DiscordPP/Gateway.h>
#include "JSON.hpp"

void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) 
{
	printf("%s \n", msg->get_payload().c_str());
}


CGateway::CGateway(std::string uri, IStartParams& params)
{
	m_startParams = params;
	m_client.init_asio();

	websocketpp::lib::error_code ec;

	m_client.set_tls_init_handler(bind(&CGateway::onTlsInit, this, ::_1));
	m_client.set_message_handler(bind(&CGateway::onMessage, this, &m_client, ::_1, ::_2));
	m_client.set_socket_init_handler(bind(&CGateway::onSocketInit, this, ::_1));
	m_client.set_open_handler(bind(&CGateway::onOpen, this, ::_1));
	m_client.set_close_handler(bind(&CGateway::onClose, this, ::_1));

	client::connection_ptr con = m_client.get_connection(uri, ec);
	if (ec) 
		printf("error");

	m_client.set_tls_init_handler(bind(&CGateway::onTlsInit, this, ::_1));

	m_client.connect(con);
	m_client.run();
}

CGateway::~CGateway()
{
}

context_ptr CGateway::onTlsInit(websocketpp::connection_hdl hdl)
{
	context_ptr ctx(new boost::asio::ssl::context(boost::asio::ssl::context::tlsv1));

	try {
		ctx->set_options(boost::asio::ssl::context::default_workarounds |
			boost::asio::ssl::context::no_sslv2 |
			boost::asio::ssl::context::single_dh_use);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return ctx;
}

void CGateway::onMessage(client* c, websocketpp::connection_hdl hdl, message_ptr msg)
{
	nlohmann::json j = nlohmann::json::parse(msg->get_payload());
	if (j["op"].is_number_unsigned() && j["op"].get<int>() == 0)
	{
		if (j["t"] == "MESSAGE_CREATE") {
			printf("%s \n", std::string(j["d"]["author"]["username"].dump() + ": " + j["d"]["content"].dump()).c_str());
		}
	}
}

void CGateway::onOpen(websocketpp::connection_hdl hdl)
{
	nlohmann::json j = { 
		{ "op", 2 },
		{ "d",{
			{ "token", m_startParams.token },
			{ "v", 5 },
			{ "compress", false },
			{ "large_threshold", 100 },
			{ "properties",{
				{ "$os","linux" },
				{ "$browser","discord.cpp" },
				{ "$device","discord.cpp" },
				{ "referrer", "" },
				{ "$referring_domain", "" }
			} }
		}},
	};
	std::string handshake = j.dump();
	printf("%s \n", handshake.c_str());
	m_client.send(hdl, handshake, websocketpp::frame::opcode::text);
}

void CGateway::onClose(websocketpp::connection_hdl hd)
{
}

void CGateway::onSocketInit(websocketpp::connection_hdl hdl)
{
}