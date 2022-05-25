#pragma once
#include <string>
#ifdef WIN32
#include <Windows.h>
#else
#include <iconv.h>
#endif

std::string toUtf8(std::wstring_view wstr) {
	std::string str;
	int bytesNeed =
		WideCharToMultiByte(CP_UTF8, NULL, wstr.data(), static_cast<int>(wstr.size()), NULL, 0, NULL, FALSE);
	str.resize(bytesNeed);
	WideCharToMultiByte(CP_UTF8, NULL, wstr.data(), static_cast<int>(wstr.size()), const_cast<char*>(str.c_str()),
		bytesNeed, NULL, FALSE);
	return str;
}

std::wstring fromUtf8(std::string_view str) {
	std::wstring wstr;
	int bytesNeed = MultiByteToWideChar(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), 0, 0);
	wstr.resize(bytesNeed);
	MultiByteToWideChar(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), const_cast<wchar_t*>(wstr.c_str()),
		bytesNeed);
	return wstr;
}

// todo linux convert function