#pragma once
#include <codecvt>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

std::wstring str2wstr(std::string &str);
std::string wstr2str(std::wstring &wstr);

bool IsFileExists(std::wstring &FilePath);

std::wstring GetTimeWStr();
std::string GetTimeStr();
std::string GetTimeStamp();
