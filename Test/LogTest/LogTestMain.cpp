#include <iostream>
#include <string>
#include <format>
#include "include/easylog.h"

using namespace std;

int main()
{
	ezlog::EzlogConfig config;
	config.log_dir = "Z:/123/";
	config.log_fname = "ezlog";

	ezlog::init_ezlog(config);
	return 0;
}