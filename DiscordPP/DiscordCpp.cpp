#include "stdafx.h"
#include <DiscordPP/DiscordCpp.h>
#include <thread>

CDiscordCpp* gApp;

CDiscordCpp::CDiscordCpp(SStartParams& params)
{
	gApp = this;
	startParams = params;
	pEventSystem = new CEventSystem;
	pWebRequest = new CWebRequest;

	// Run gateway on separate thread
	m_gatewayThread = std::thread([](SStartParams& params) 
	{
		gApp->pGateway = new CGateway("wss://gateway.discord.gg/?encoding=json&v=6", params);
	}, params);
}

CDiscordCpp::~CDiscordCpp()
{
	if (pGateway)
		delete pGateway;
	if (pEventSystem)
		delete pEventSystem;
	if (pWebRequest)
		delete pWebRequest;
}

void CDiscordCpp::CreateMessage(std::string chanId, std::string content)
{
	if (content.length() > 2000) return;

	nlohmann::json j;
	j["content"] = content;

	std::string res;
	pWebRequest->Post("/channels/" + chanId + "/messages", startParams.token, j.dump());
}

nlohmann::json CDiscordCpp::GetUser(std::string uid)
{
	std::string res;
	pWebRequest->Get("/users/" + uid, startParams.token, res);
	return nlohmann::json::parse(res);
}
