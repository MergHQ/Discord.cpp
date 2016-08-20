#pragma once
#include <string>

class CAPIRequest
{
public:
	CAPIRequest() {};
	~CAPIRequest() {};
	void Get(std::string endpoint, std::string token, std::string content = "", std::string& res = std::string());
	void Post(std::string endpoint, std::string token, std::string content, std::string& res = std::string());
	void Delete(std::string endpoint, std::string token, std::string& res = std::string());
	void Patch(std::string endpoint, std::string token, std::string content, std::string& res = std::string());
	void Put(std::string endpoint, std::string token, std::string content, std::string& res = std::string());
};