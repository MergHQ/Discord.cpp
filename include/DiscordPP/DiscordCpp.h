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
	SStartParams startParams;
	void CreateMessage(std::string chanId, std::string content);
	void CreateDm(std::string uid, std::string content);
private:
	std::thread m_gatewayThread;
};
