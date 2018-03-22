#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>
#include <ctime>

std::wstring str2wstr(std::string& str)
{	
	// ??? 
	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>  Convert;
	std::wstring wstr = Convert.from_bytes(str);
	
	if (!wstr.empty())
	{
		return wstr;
	}
	else
	{
		return std::wstring();
	}
}

std::string wstr2str(std::wstring& wstr)
{
	// ??? 
	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>  Convert;
	std::string str = Convert.to_bytes(wstr);

	if (!str.empty())
	{
		return str;
	}
	else
	{
		return std::string();
	}
}


bool IsFileExists(std::wstring& FilePath)
{
	if (FilePath.empty())
	{
		return false;
	}

	std::fstream fs(FilePath);

	if (!fs)
	{
		return false;
	}

	return true;
}

std::wstring GetTimeWStr()
{
	time_t CurTime = time(0);

	wchar_t TimeWStr[100] = { 0 };
	tm _tm = { 0 };
	localtime_s(&_tm, &CurTime);
	wcsftime(TimeWStr, 100, L"%Y-%m-%d %H:%M:%S", &_tm);

	return std::wstring(TimeWStr);
}

std::string GetTimeStr()
{
	time_t CurTime = time(0);

	char TimeStr[100] = { 0 };
	tm _tm = { 0 };
	localtime_s(&_tm, &CurTime);
	strftime(TimeStr, 100, "%Y-%m-%d %H:%M:%S", &_tm);

	return std::string(TimeStr);
}

std::string GetTimeStamp()
{
	time_t CurTime = time(0);

	char TimeStr[100] = { 0 };
	tm _tm = { 0 };
	localtime_s(&_tm, &CurTime);
	strftime(TimeStr, 100, "%Y-%m-%d", &_tm);
	
	return std::string(TimeStr) + '_' + 
		std::to_string(3600 * _tm.tm_hour + 60 * _tm.tm_min + _tm.tm_sec);
}
