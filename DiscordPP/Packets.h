#pragma once
#include "JSON.hpp"

using nlohmann::json;

static std::string GetHandshakePacket(std::string token)
{
	json j = {
		{ "op", 2 },
		{ "d",{
			{ "token", token },
			{ "v", 5 },
			{ "compress", false },
			{ "large_threshold", 100 },
			{ "properties",{
				{ "$os","linux" },
				{ "$browser","discord.cpp" },
				{ "$device","discord.cpp" },
				{ "referrer", "" },
				{ "$referring_domain", "" }
			} }
		} },
	};

	return j.dump();
}

static std::string GetKeepalivePacket(std::string seq)
{
	json j = {
		{ "op", 1 },
		{ "d", seq }
	};

	return j.dump();
}
