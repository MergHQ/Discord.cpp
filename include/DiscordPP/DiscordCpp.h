#pragma once
#include <DiscordPP\StartParams.h>
#include <DiscordPP\Gateway.h>
#include <DiscordPP\EventSystem.h>
#include <thread>

class CDiscordCpp
{
public:
	CDiscordCpp(SStartParams& params);
	~CDiscordCpp();

	CEventSystem* pEventSystem;
	CGateway* pGateway;
private:
	std::thread m_gatewayThread;
};
