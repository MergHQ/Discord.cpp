#include "stdafx.h"
#include <DiscordPP\EventSystem.h>


CEventSystem::CEventSystem()
{
}


CEventSystem::~CEventSystem()
{
}

void CEventSystem::RegisterEventListener(IEventListener* pListener)
{
	m_listeners.push_back(pListener);
}

void CEventSystem::OnEvent(SEventParams& params)
{
	// Emit to all listeners
	for (IEventListener* pListener : m_listeners) 
	{
		pListener->OnEvent(params);
	}
}
