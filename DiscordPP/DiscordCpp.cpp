#include "stdafx.h"
#include <DiscordPP\DiscordCpp.h>
#include <thread>

CDiscordCpp* gApp;

CDiscordCpp::CDiscordCpp(SStartParams& params)
{
	gApp = this;
	pEventSystem = new CEventSystem;

	// Run gateway on separate thread
	m_gatewayThread = std::thread([](SStartParams& params) 
	{
		gApp->pGateway = new CGateway("wss://gateway.discord.gg/?encoding=json&v=5", params);
	}, params);
}

CDiscordCpp::~CDiscordCpp()
{
	delete pGateway;
	m_gatewayThread.detach();
	delete pEventSystem;
}
