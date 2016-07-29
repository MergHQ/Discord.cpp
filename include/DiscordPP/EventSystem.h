#pragma once
#include <DiscordPP\IEventListener.h>
#include <DiscordPP\EventParams.h>
#include <vector>

class CEventSystem
{
public:
	CEventSystem();
	~CEventSystem();

	void RegisterEventListener(IEventListener*);
	void OnEvent(SEventParams& params);
private:
	std::vector<IEventListener*> m_listeners;
};

