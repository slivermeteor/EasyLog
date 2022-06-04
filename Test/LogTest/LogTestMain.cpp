#include <iostream>
#include <string>
#include <format>
#include "include/easylog.hpp"

using namespace std;

int main()
{
	ezlog::EzlogConfig config;
	config.log_dir = "Z:/123/";
	config.log_fname = "ezlog";

	ezlog::init_ezlog(config);
	ezlog::formatter::ezlog_formatter(ezlog::EzlogLevel::kDebugLog, __FILE__, __LINE__, __FUNCTION__, "main", "{}", 123);
	return 0;
}