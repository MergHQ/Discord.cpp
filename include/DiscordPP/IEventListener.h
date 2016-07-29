#pragma once
#include <DiscordPP\EventParams.h>

struct IEventListener
{
	virtual ~IEventListener() {};
	virtual void OnEvent(SEventParams&) = 0;
};