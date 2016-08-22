#pragma once
#include <DiscordPP\IEventListener.h>
#include <DiscordPP\EventParams.h>
#include <map>
#include <vector>s

class CEventSystem
{
public:
	CEventSystem();
	~CEventSystem();

	uint16_t RegisterEventListener(IEventListener*);
	void OnRawEvent(SEventParams& params);
	void RemoveListener(uint16_t id);
	void Update();
	std::vector<SEventParams> events;
	bool isUsed = false;
private:
	uint16_t index;
	std::map<uint16_t, IEventListener*> m_listeners;
};

