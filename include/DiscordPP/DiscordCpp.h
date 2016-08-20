#pragma once
#include <DiscordPP/StartParams.h>
#include <DiscordPP/Gateway.h>
#include <DiscordPP/EventSystem.h>
#include <thread>
#include <DiscordPP/APIRequest.h>

typedef nlohmann::json json;
typedef std::string string;

class CDiscordCpp
{
public:
	CDiscordCpp(SStartParams& params);
	~CDiscordCpp();

	CEventSystem* pEventSystem;
	CGateway* pGateway;
	SStartParams startParams;
	CAPIRequest* pAPIRequest;

	// Channel
	void CreateMessage(string chanId, string content);
	void CreateDm(string uid, string content);
	json GetUser(string uid);
	json GetChannel(string chid);
	void ModifyChannel(string chid, string name, int position, string topic, int bitrate, int userlimit);
	void DeleteChannel(string chid);
	json GetChannelMessages(string chid, string around, string before, string after, int limit);
	json GetChannelMessage(string chid, string msgid);
	// Upload file
	void EditMessage(string chid, string msgid, string contents);
	void DeleteMesssage(string chid, string msgid);
	void BulkDeleteMessages(string chid, string messages);
	//void EditChannelPermission
	json GetChannelInvites(string chid);
	json CreateChannelInvite(string chid, int maxAge, int duration, int temporary);
	void TriggerTypingIndicator(string chid);
	json GetPinnedMessages(string chid);
	void AddPinnedChannelMessage(string chid, string msgid);
	void DeletePinnedChannelMessage(string chid, string msgid);

	// Guild
	void CreateGuild(string name, string region, string icon);
	json GetGuild(string gid);
	void ModifyGuild(string gid, string name, string region, int verification_level, string afk_channel_id, int afkTimeout, string icon, string ownerId, string splash);
	void DeleteGuild(string gid);
	json GetGuildChannels(string gid);
	void CreateGuildChannel(string gid, string name, string type, int bitrate, int userLimit);
	void ModifyGuildChannel(string gid, string id, int position);
	json GetGuildMember(string gid, string uid);

private:
	std::thread m_gatewayThread;
};
