#include "stdafx.h"
#include <DiscordPP/EventSystem.h>
#include "Utils.hpp"

CEventSystem::CEventSystem()
{
}


CEventSystem::~CEventSystem()
{
}


uint16_t CEventSystem::RegisterEventListener(IEventListener* pListener)
{
	m_listeners[index++] = pListener;
	return index;
}

void CEventSystem::OnRawEvent(SEventParams& params)
{
	// Emit to all listeners
	for (std::pair<uint16_t, IEventListener*> o : m_listeners)
	{
		o.second->OnRawEvent(params);
	}
}

void CEventSystem::RemoveListener(uint16_t id)
{
	m_listeners.erase(id);
}

void CEventSystem::Update()
{
	size_t s = events.size();
	s = s > 100 ? 0 : s;

	for (int i = 0; i < s; ++i) 
	{
		isUsed = true;
		try 
		{
			OnRawEvent(events.at(i));
		}
		catch (std::out_of_range e)
		{
			Log(e.what());
		}
	}

	if (isUsed)
		events.clear(); // fucking std::vector<>().empty() always tricking me
	isUsed = false;
}
