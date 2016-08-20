#pragma once
#include <DiscordPP/IDiscordObject.h>
#include <DiscordPP/EventParams.h>

struct IEventListener
{
	virtual ~IEventListener() {};
	virtual void OnRawEvent(SEventParams&) = 0;
};