#pragma once
#include <string>
#include <DiscordPP\JSON.hpp>

enum EEventType
{
	MESSAGE_CREATE,
	MESSAGE_UPDATE,
	MESSAGE_DELETE,
	PRESENCE_UPDATE,
	READY,
	RESUMED,
	CHANNEL_CREATE,
	CHANNEL_UPDATE,
	CHANNEL_DELETE
};

enum EPayloadType
{
	HANDSHAKE,
	CREATE_MESSAGE
};

struct SEventParams
{
	EEventType type;
	std::string raw;
	int opCode;
	nlohmann::json object;
};