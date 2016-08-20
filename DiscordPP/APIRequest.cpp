#include "stdafx.h"
#include <DiscordPP/APIRequest.h>
#include <cpr/cpr.h>

void CAPIRequest::Get(std::string endpoint, std::string token, std::string content, std::string& res)
{
	if (content == "")
	{
		auto r = cpr::Get(cpr::Url{ "https://discordapp.com/api" + endpoint },
			cpr::Header({ { "Authorization", token } }));
		res = r.text;
		return;
	} 

	auto r = cpr::Get(cpr::Url{ "https://discordapp.com/api" + endpoint },
		cpr::Body{ content },
		cpr::Header({{"Authorization", token }}));
	res = r.text;                     
}

void CAPIRequest::Post(std::string endpoint, std::string token, std::string content, std::string& res)
{
	auto r = cpr::Post(cpr::Url{ "https://discordapp.com/api" + endpoint },
		cpr::Body{ content },
		cpr::Header{ { "Content-Type", "application/json" },{ "Authorization", token }});
	res = r.text;
}

void CAPIRequest::Delete(std::string endpoint, std::string token, std::string& res)
{
	auto r = cpr::Delete(cpr::Url{ "https://discordapp.com/api" + endpoint },
		cpr::Header({ { "Authorization", token } }));
	res = r.text;
}

void CAPIRequest::Patch(std::string endpoint, std::string token, std::string content, std::string& res)
{
	auto r = cpr::Patch(cpr::Url{ "https://discordapp.com/api" + endpoint },
		cpr::Body{ content },
		cpr::Header{ { "Content-Type", "application/json" },{ "Authorization", token } });
	res = r.text;
}

void CAPIRequest::Put(std::string endpoint, std::string token, std::string content, std::string& res)
{
	auto r = cpr::Put(cpr::Url{ "https://discordapp.com/api" + endpoint },
		cpr::Body{ content },
		cpr::Header{ { "Content-Type", "application/json" },{ "Authorization", token } });
	res = r.text;
}
