#pragma once
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <DiscordPP/StartParams.h>
#include <vector>
#include <DiscordPP/EventParams.h>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::config::asio_tls_client::message_type::ptr message_ptr;
typedef websocketpp::lib::shared_ptr<boost::asio::ssl::context> context_ptr;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

class CGateway
{
public:
	CGateway(std::string uri, SStartParams& params);
	~CGateway();
	client m_client;
	SStartParams m_startParams;
	std::thread m_keepAliveThread;
	client::connection_ptr m_connection;
	std::string m_lastSequence = "null";
	void WsSend(std::string payload);
private:
	std::vector<SEventParams> events;
	context_ptr OnTlsInit(websocketpp::connection_hdl hdl);
	void Keepalive(uint32_t ms);
	void OnMessage(client* c, websocketpp::connection_hdl hdl, message_ptr msg);
	void OnOpen(websocketpp::connection_hdl hdl);
	void OnClose(websocketpp::connection_hdl hd);
	void OnSocketInit(websocketpp::connection_hdl hdl);
};