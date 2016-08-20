#include "stdafx.h"
#include <DiscordPP/DiscordCpp.h>
#include "Utils.hpp"
#include <thread>

CDiscordCpp* gApp;

CDiscordCpp::CDiscordCpp(SStartParams& params)
{
	gApp = this;
	startParams = params;
	pEventSystem = new CEventSystem;
	pAPIRequest = new CAPIRequest;

	// Run gateway on separate thread
	m_gatewayThread = std::thread([](SStartParams& params) 
	{
		gApp->pGateway = new CGateway("wss://gateway.discord.gg/?encoding=json&v=6", params);
	}, params);
}

CDiscordCpp::~CDiscordCpp()
{
	if (pGateway)
		delete pGateway;
	if (pEventSystem)
		delete pEventSystem;
	if (pAPIRequest)
		delete pAPIRequest;
}

void CDiscordCpp::CreateMessage(std::string chanId, std::string content)
{
	if (content.length() > 2000) return;

	nlohmann::json j;
	j["content"] = content;

	std::string res;
	pAPIRequest->Post("/channels/" + chanId + "/messages", startParams.token, j.dump());
}

nlohmann::json CDiscordCpp::GetUser(std::string uid)
{
	std::string res;
	pAPIRequest->Get("/users/" + uid, startParams.token, res);
	return nlohmann::json::parse(res);
}

nlohmann::json CDiscordCpp::GetChannel(std::string chid)
{
	std::string res;
	pAPIRequest->Get("/channels/" + chid, startParams.token);
	return nlohmann::json::parse(res);
}

void CDiscordCpp::ModifyChannel(std::string chid, std::string name, int position, std::string topic, int bitrate, int userlimit)
{
	if (name.length() > 100) return;
	if (topic.length() > 1024) return;

	nlohmann::json j;
	j["name"] = name == "" ? "null" : name;
	j["position"] = position;
	j["topic"] = topic == "" ? "null" : name;
	j["bitrate"] = bitrate;
	j["user_limit"] = userlimit;
	pAPIRequest->Put("/channels/" + chid, startParams.token, j.dump());
}

void CDiscordCpp::DeleteChannel(std::string chid)
{
	pAPIRequest->Delete("/channels/" + chid, startParams.token);
}

nlohmann::json CDiscordCpp::GetChannelMessages(std::string chid, std::string around, std::string before, std::string after, int limit)
{
	nlohmann::json j;
	j["around"] = around;
	j["before"] = before;
	j["after"] = after;
	j["limit"] = limit;

	std::string res;
	pAPIRequest->Get("/channels/" + chid + "/messages", startParams.token, j.dump(), res);
	return nlohmann::json::parse(res);
}

nlohmann::json CDiscordCpp::GetChannelMessage(std::string chid, std::string msgid)
{
	std::string res;
	pAPIRequest->Get("/channels/" + chid + "/message/" + msgid, res);
	return nlohmann::json::parse(res);
}

void CDiscordCpp::EditMessage(std::string chid, std::string msgid, std::string contents)
{
	nlohmann::json j;
	j["content"] = contents;
	pAPIRequest->Patch("/channels/" + chid + "/messages/" + msgid, startParams.token, j.dump());
}

void CDiscordCpp::DeleteMesssage(std::string chid, std::string msgid)
{
	pAPIRequest->Delete("/channels/" + chid + "/messages/" + msgid, startParams.token);
}

void CDiscordCpp::BulkDeleteMessages(std::string chid, std::string messages)
{
	pAPIRequest->Post("/channels/" + chid + "/messages/bulk_delete", startParams.token, messages);
}

nlohmann::json CDiscordCpp::GetChannelInvites(std::string chid)
{
	std::string res;
	pAPIRequest->Get("/channels/" + chid + "/invites", startParams.token, "", res);
	return nlohmann::json::parse(res);
}

nlohmann::json CDiscordCpp::CreateChannelInvite(std::string chid, int maxAge, int duration, int temporary)
{
	nlohmann::json j;
	j["max_age"] = maxAge;
	j["max_uses"] = duration;
	j["temporary"] = temporary;

	std::string res;
	pAPIRequest->Post("/channels/" + chid + "/invites", startParams.token, j.dump(), res);
	return nlohmann::json::parse(res);
}

void CDiscordCpp::TriggerTypingIndicator(std::string chid)
{
}

nlohmann::json CDiscordCpp::GetPinnedMessages(std::string chid)
{
	return nlohmann::json();
}

void CDiscordCpp::AddPinnedChannelMessage(std::string chid, std::string msgid)
{
}

void CDiscordCpp::DeletePinnedChannelMessage(std::string chid, std::string msgid)
{
}




