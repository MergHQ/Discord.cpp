#include "stdafx.h"
#include <DiscordPP/Gateway.h>
#include "JSON.hpp"
#include "Packets.h"

void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) 
{
	printf("%s \n", msg->get_payload().c_str());
}


CGateway::CGateway(std::string uri, SStartParams& params)
{
	m_startParams = params;
	m_client.init_asio();

	websocketpp::lib::error_code ec;

	m_client.set_tls_init_handler(bind(&CGateway::onTlsInit, this, ::_1));
	m_client.set_message_handler(bind(&CGateway::onMessage, this, &m_client, ::_1, ::_2));
	m_client.set_socket_init_handler(bind(&CGateway::onSocketInit, this, ::_1));
	m_client.set_open_handler(bind(&CGateway::onOpen, this, ::_1));
	m_client.set_close_handler(bind(&CGateway::onClose, this, ::_1));

	m_connection = m_client.get_connection(uri, ec);
	if (ec) 
		printf("error");

	m_client.set_tls_init_handler(bind(&CGateway::onTlsInit, this, ::_1));

	m_client.connect(m_connection);
	m_client.run();
}

CGateway::~CGateway()
{
	m_keepAliveThread.detach();
	m_client.stop();
}

void CGateway::WsSend(std::string payload)
{
	m_client.send(m_connection, payload, websocketpp::frame::opcode::text);
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

void CGateway::Keepalive(uint32_t ms)
{
	m_keepAliveThread = std::thread([](uint32_t ms, CGateway* pGw)
	{
		while (true)
		{
			pGw->WsSend(GetKeepalivePacket(pGw->m_lastSequence));
			Sleep(ms);
		}
	}, ms, this);
}

void CGateway::onMessage(client* c, websocketpp::connection_hdl hdl, message_ptr msg)
{
	nlohmann::json j = nlohmann::json::parse(msg->get_payload());

	if (j["s"].is_null())
		m_lastSequence = "null";
	else
		m_lastSequence = j["s"].dump();

	if(j["op"].get<int>() == 10) 
	{
		uint32_t ms = j["d"]["heartbeat_interval"].get<int>();
		Keepalive(ms);
	}

	SEventParams p;
	p.object = j;
	p.opCode = j["op"].get<int>();
	p.raw = msg->get_payload();

	gApp->pEventSystem->OnEvent(p);
}

void CGateway::onOpen(websocketpp::connection_hdl hdl)
{
	WsSend(GetHandshakePacket(m_startParams.token));
}

void CGateway::onClose(websocketpp::connection_hdl hd)
{
}

void CGateway::onSocketInit(websocketpp::connection_hdl hdl)
{
}