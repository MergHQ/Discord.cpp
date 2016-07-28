#include "stdafx.h"
#include <DiscordPP\DiscordCpp.h>

CDiscordCpp::CDiscordCpp(IStartParams& params)
{
	m_pGateway = new CGateway("wss://gateway.discord.gg/?encoding=json&v=5", params);
}

CDiscordCpp::~CDiscordCpp()
{
	delete m_pGateway;
}
