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

void CDiscordCpp::CreateMessage(string chanId, string content)
{
	if (content.length() > 2000) return;

	json j;
	j["content"] = content;

	string res;
	pAPIRequest->Post("/channels/" + chanId + "/messages", startParams.token, j.dump());
}

json CDiscordCpp::GetUser(string uid)
{
	string res;
	pAPIRequest->Get("/users/" + uid, startParams.token, "", res);
	if (res == "") return 0;
	return json::parse(res);
}

json CDiscordCpp::GetChannel(string chid)
{
	string res;
	pAPIRequest->Get("/channels/" + chid, startParams.token, "", res);
	return json::parse(res);
}

void CDiscordCpp::ModifyChannel(string chid, string name, int position, string topic, int bitrate, int userlimit)
{
	if (name.length() > 100) return;
	if (topic.length() > 1024) return;

	json j;
	j["name"] = name == "" ? "null" : name;
	j["position"] = position;
	j["topic"] = topic == "" ? "null" : name;
	j["bitrate"] = bitrate;
	j["user_limit"] = userlimit;
	pAPIRequest->Put("/channels/" + chid, startParams.token, j.dump());
}

void CDiscordCpp::DeleteChannel(string chid)
{
	pAPIRequest->Delete("/channels/" + chid, startParams.token);
}

json CDiscordCpp::GetChannelMessages(string chid, string around, string before, string after, int limit)
{
	json j;
	j["around"] = around;
	j["before"] = before;
	j["after"] = after;
	j["limit"] = limit;

	string res;
	pAPIRequest->Get("/channels/" + chid + "/messages", startParams.token, j.dump(), res);
	return json::parse(res);
}

json CDiscordCpp::GetChannelMessage(string chid, string msgid)
{
	string res;
	pAPIRequest->Get("/channels/" + chid + "/message/" + msgid, "", res);
	return json::parse(res);
}

void CDiscordCpp::EditMessage(string chid, string msgid, string contents)
{
	json j;
	j["content"] = contents;
	pAPIRequest->Patch("/channels/" + chid + "/messages/" + msgid, startParams.token, j.dump());
}

void CDiscordCpp::DeleteMesssage(string chid, string msgid)
{
	pAPIRequest->Delete("/channels/" + chid + "/messages/" + msgid, startParams.token);
}

void CDiscordCpp::BulkDeleteMessages(string chid, string messages)
{
	pAPIRequest->Post("/channels/" + chid + "/messages/bulk_delete", startParams.token, messages);
}

json CDiscordCpp::GetChannelInvites(string chid)
{
	string res;
	pAPIRequest->Get("/channels/" + chid + "/invites", startParams.token, "", res);
	return json::parse(res);
}

json CDiscordCpp::CreateChannelInvite(string chid, int maxAge, int duration, int temporary)
{
	json j;
	j["max_age"] = maxAge;
	j["max_uses"] = duration;
	j["temporary"] = temporary;

	string res;
	pAPIRequest->Post("/channels/" + chid + "/invites", startParams.token, j.dump(), res);
	return json::parse(res);
}

void CDiscordCpp::TriggerTypingIndicator(string chid)
{
	pAPIRequest->Post("/channels/" + chid + "/typing", startParams.token, "");
}

json CDiscordCpp::GetPinnedMessages(string chid)
{
	string res;
	pAPIRequest->Get("/channels/" + chid + "/pins", startParams.token, "", res);
	return json::parse(res);
}

void CDiscordCpp::AddPinnedChannelMessage(string chid, string msgid)
{
	pAPIRequest->Put("/channels/" + chid +"/pins/" + msgid, startParams.token, "");
}

void CDiscordCpp::DeletePinnedChannelMessage(string chid, string msgid)
{
	pAPIRequest->Delete("/channels/" + chid + "/pins/" + msgid, startParams.token);
}

void CDiscordCpp::CreateGuild(string name, string region, string icon)
{
	json j;
	j["name"] = name;
	j["region"] = region;
	j["icon"] = icon;

	pAPIRequest->Post("/guilds", startParams.token, j.dump());
}

json CDiscordCpp::GetGuild(string gid)
{
	string res;
	pAPIRequest->Get("/guilds/" + gid, startParams.token, "", res);
	return json::parse(res);
}

void CDiscordCpp::ModifyGuild(string gid, string name, string region, int verification_level, string afk_channel_id, int afkTimeout, string icon, string ownerId, string splash)
{
	json j;
	j["name"] = name;
	j["region"] = region;
	j["verification_level"] = verification_level;
	j["afk_channel_id"] = afk_channel_id;
	j["afk_timeout"] = afkTimeout;
	j["icon"] = icon;
	j["owner_id"] = ownerId;
	j["splash"] = splash;

	pAPIRequest->Patch("/guilds/" + gid, startParams.token, j.dump());
}

void CDiscordCpp::DeleteGuild(string gid)
{
	pAPIRequest->Delete("/guilds/" + gid, startParams.token);
}

json CDiscordCpp::GetGuildChannels(string gid)
{
	string res;
	pAPIRequest->Get("/guilds/" + gid + "/channels", startParams.token, "", res);
	return json::parse(res);
}

void CDiscordCpp::CreateGuildChannel(string gid, string name, string type, int bitrate, int userLimit)
{	
	json j;
	j["name"] = name;
	j["type"] = type;
	j["bitrate"] = bitrate;
	j["user_limit"] = userLimit;

	pAPIRequest->Post("/guilds/" + gid + "/channels", startParams.token, j.dump());
}

void CDiscordCpp::ModifyGuildChannel(string gid, string id, int position)
{
	json j;
	j["id"] = id;
	j["position"] = position;

	pAPIRequest->Patch("/guilds/" + gid + "/channels", startParams.token, j.dump());
}

json CDiscordCpp::GetGuildMember(string gid, string uid)
{
	string res;
	pAPIRequest->Get("/guilds" + gid + "members" + uid, startParams.token, "", res);
	return json::parse(res);
}




