#include <string>

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