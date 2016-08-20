#pragma once
#include <DiscordPP/StartParams.h>
#include <DiscordPP/Gateway.h>
#include <DiscordPP/EventSystem.h>
#include <thread>
#include <DiscordPP/APIRequest.h>

class CDiscordCpp
{
public:
	CDiscordCpp(SStartParams& params);
	~CDiscordCpp();

	CEventSystem* pEventSystem;
	CGateway* pGateway;
	SStartParams startParams;
	CAPIRequest* pAPIRequest;

	void CreateMessage(std::string chanId, std::string content);
	void CreateDm(std::string uid, std::string content);
	nlohmann::json GetUser(std::string uid);
	nlohmann::json GetChannel(std::string chid);
	void ModifyChannel(std::string chid, std::string name, int position, std::string topic, int bitrate, int userlimit);
	void DeleteChannel(std::string chid);
	nlohmann::json GetChannelMessages(std::string chid, std::string around, std::string before, std::string after, int limit);
	nlohmann::json GetChannelMessage(std::string chid, std::string msgid);
	// Upload file
	void EditMessage(std::string chid, std::string msgid, std::string contents);
	void DeleteMesssage(std::string chid, std::string msgid);
	void BulkDeleteMessages(std::string chid, std::string messages);
	//void EditChannelPermission
	nlohmann::json GetChannelInvites(std::string chid);
	nlohmann::json CreateChannelInvite(std::string chid, int maxAge, int duration, int temporary);
	void TriggerTypingIndicator(std::string chid);
	nlohmann::json GetPinnedMessages(std::string chid);
	void AddPinnedChannelMessage(std::string chid, std::string msgid);
	void DeletePinnedChannelMessage(std::string chid, std::string msgid);
private:
	std::thread m_gatewayThread;
};
