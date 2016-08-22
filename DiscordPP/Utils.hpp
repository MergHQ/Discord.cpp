#include <string>
#include <iostream>
#include <cstdarg>

template <class T>
static std::string ArrayToList(T* arr) 
{
	std::string s = "";
	for (T o : arr)
	{
		s += std::to_string(o) + ",";
	}

	return s;
}

static void Log(const char* payload, ...)
{
	printf(payload);
	va_list args;
	va_start(args, payload);
	vprintf(payload, args);
	va_end(args);
	std::cout << std::endl;
}