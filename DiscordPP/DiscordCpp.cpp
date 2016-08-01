#include "stdafx.h"
#include <DiscordPP/DiscordCpp.h>
#include <thread>
#include <DiscordPP/WebRequest.h>

CDiscordCpp* gApp;

CDiscordCpp::CDiscordCpp(SStartParams& params)
{
	gApp = this;
	startParams = params;
	pEventSystem = new CEventSystem;

	// Run gateway on separate thread
	m_gatewayThread = std::thread([](SStartParams& params) 
	{
		gApp->pGateway = new CGateway("wss://gateway.discord.gg/?encoding=json&v=6", params);
	}, params);
}

CDiscordCpp::~CDiscordCpp()
{
	delete pGateway;
	delete pEventSystem;
}

void CDiscordCpp::CreateMessage(std::string chanId, std::string content)
{
	if (content.length() > 2000) return;

	nlohmann::json j;
	j["content"] = content;

	CWebRequest wr;
	std::string res;
	wr.Post("/channels/" + chanId + "/messages", startParams.token, j.dump());
}
