#pragma once
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <DiscordPP\IStartParams.h>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::config::asio_tls_client::message_type::ptr message_ptr;
typedef websocketpp::lib::shared_ptr<boost::asio::ssl::context> context_ptr;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

class CGateway
{
public:
	CGateway(std::string uri, IStartParams& params);
	~CGateway();
	context_ptr onTlsInit(websocketpp::connection_hdl hdl);
	void onMessage(client* c, websocketpp::connection_hdl hdl, message_ptr msg);
	void onOpen(websocketpp::connection_hdl hdl);
	void onClose(websocketpp::connection_hdl hd);
	void onSocketInit(websocketpp::connection_hdl hdl);
private:
	client m_client;
	IStartParams m_startParams;
};