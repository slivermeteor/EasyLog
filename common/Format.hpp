#pragma  once

#include <iostream>
#include <string>
#include "LogUtil.hpp"

std::wstring FormatLog()
{
	return std::wstring();
}

// wchar_t жиди
template <typename ... Ts>
std::wstring FormatLog(const wchar_t* Arg, Ts... Args)
{
	wstring wstr(Arg);
	return wstr + FormatLog(Args...);
}

template <typename ... Ts>
std::wstring FormatLog(const char* Arg, Ts... Args)
{
	wstring wstr(str2wstr(std::string(Arg)));
	return wstr + FormatLog(Args...);
}

template <typename T, typename ... Ts>
std::wstring FormatLog(T Arg, Ts... Args)
{
	wstring wstr = to_wstring(Arg);
	return wstr + FormatLog(Args...);
}