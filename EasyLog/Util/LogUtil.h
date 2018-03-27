#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>
#include <ctime>

std::wstring str2wstr(std::string& str);
std::string wstr2str(std::wstring& wstr);

bool IsFileExists(std::wstring& FilePath);

std::wstring GetTimeWStr();
std::string GetTimeStr();
std::string GetTimeStamp();