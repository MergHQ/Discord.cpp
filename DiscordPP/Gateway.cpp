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

	m_client.set_tls_init_handler(bind(&CGateway::OnTlsInit, this, ::_1));
	m_client.set_message_handler(bind(&CGateway::OnMessage, this, &m_client, ::_1, ::_2));
	m_client.set_socket_init_handler(bind(&CGateway::OnSocketInit, this, ::_1));
	m_client.set_open_handler(bind(&CGateway::OnOpen, this, ::_1));
	m_client.set_close_handler(bind(&CGateway::OnClose, this, ::_1));

	m_connection = m_client.get_connection(uri, ec);
	if (ec) 
		printf("error");

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

context_ptr CGateway::OnTlsInit(websocketpp::connection_hdl hdl)
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

void CGateway::OnMessage(client* c, websocketpp::connection_hdl hdl, message_ptr msg)
{
	nlohmann::json j = nlohmann::json::parse(msg->get_payload());

	SEventParams p;
	p.opCode = j["op"].get<int>();
	p.raw = msg->get_payload();
	gApp->pEventSystem->OnRawEvent(p);

	if (j["s"].is_null())
		m_lastSequence = "null";
	else
		m_lastSequence = j["s"].dump();

	if(j["op"].get<int>() == 10) 
	{
		uint32_t ms = j["d"]["heartbeat_interval"].get<int>();
		Keepalive(ms);
	}

	if (j["op"].get<int>() == 0) {
		SEventParams p;
		if (j["t"] == "MESSAGE_CREATE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.raw = msg->get_payload();
			p.type = EPayloadType::MESSAGE_CREATE;
		}
		else if (j["t"] == "READY")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::READY;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "CHANNEL_CREATE") 
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::CHANNEL_CREATE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "CHANNEL_UPDATE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::CHANNEL_UPDATE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "CHANNEL_DELETE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::CHANNEL_DELETE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_CREATE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_CREATE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_DELETE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_DELETE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_BAN_ADD")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_BAN_ADD;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_BAN_REMOVE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_BAN_REMOVE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_EMOJI_UPDATE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_EMOJI_UPDATE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_INTEGRATIONS_UPDATE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_INTEGRATIONS_UPDATE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_MEMBER_ADD")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_MEMBER_ADD;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_MEMBER_REMOVE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_MEMBER_ADD;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_MEMBER_UPDATE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_MEMBER_UPDATE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_MEMBERS_CHUNK")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_MEMBERS_CHUNK;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_ROLE_CREATE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_ROLE_CREATE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_ROLE_UPDATE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_ROLE_UPDATE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "GUILD_ROLE_DELETE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::GUILD_ROLE_DELETE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "MESSAGE_UPDATE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::MESSAGE_UPDATE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "MESSAGE_DELETE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::MESSAGE_DELETE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "PRECENSE_UPDATE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::PRECENSE_UPDATE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "TYPING_START")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::TYPING_START;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "VOICE_STATE_UPDATE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::VOICE_STATE_UPDATE;
			p.raw = msg->get_payload();
		}
		else if (j["t"] == "VOICE_SERVER_UPDATE")
		{
			p.object = j["d"];
			p.opCode = 0;
			p.type = EPayloadType::VOICE_SERVER_UPDATE;
			p.raw = msg->get_payload();
		}

		gApp->pEventSystem->OnRawEvent(p); // TODO: Queue gateway events on main thread. Don't slow down the gateway thead with requests and shit.
	}
}

void CGateway::OnOpen(websocketpp::connection_hdl hdl)
{
	WsSend(GetHandshakePacket(m_startParams.token));
}

void CGateway::OnClose(websocketpp::connection_hdl hd)
{
}

void CGateway::OnSocketInit(websocketpp::connection_hdl hdl)
{
}