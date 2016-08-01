#include "stdafx.h"
#include <DiscordPP/WebRequest.h>
#include <cpr/cpr.h>

void CWebRequest::Get(std::string url, std::string token, std::string& res)
{
	auto r = cpr::Get(cpr::Url{ "https://discordapp.com/api" + url },
		cpr::Header({{"Authorization", token }}));
	res = r.text;                     
}

void CWebRequest::Post(std::string url, std::string token, std::string content, std::string& res)
{
	auto r = cpr::Post(cpr::Url{ "https://discordapp.com/api" + url },
		cpr::Body{ content },
		cpr::Header{ { "Content-Type", "application/json" },{ "Authorization", token }});
	res = r.text;
}