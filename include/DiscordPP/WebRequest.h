#pragma once
#include <string>

class CWebRequest
{
public:
	CWebRequest() {};
	~CWebRequest() {};
	void Get(std::string url, std::string token, std::string& res = std::string());
	void Post(std::string url, std::string token, std::string content, std::string& res = std::string());
};