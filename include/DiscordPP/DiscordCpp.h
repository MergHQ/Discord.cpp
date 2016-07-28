#pragma once
#include <DiscordPP\IStartParams.h>
#include <DiscordPP\Gateway.h>

class CDiscordCpp
{
public:
	CDiscordCpp(IStartParams& params);
	~CDiscordCpp();
private:
	CGateway* m_pGateway;

};