#pragma  once

#include <iostream>
#include <string>
#include <codecvt>

std::wstring FormatLog()
{
	return std::wstring();
}

// wchar_t ����
template <typename ... Ts>
std::wstring FormatLog(const wchar_t* Arg, Ts... Args)
{
	wstring wstr(Arg);
	return wstr + FormatLog(Args...);
}

template <typename ... Ts>
std::wstring FormatLog(const char* Arg, Ts... Args)
{
	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>  Convert;
	wstring wstr(Convert.from_bytes(std::string(Arg)));
	return wstr + FormatLog(Args...);
}

template <typename T, typename ... Ts>
std::wstring FormatLog(T Arg, Ts... Args)
{
	wstring wstr = to_wstring(Arg);
	return wstr + FormatLog(Args...);
}