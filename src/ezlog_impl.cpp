#include "ezlog_impl.h"
#include <format>
#include <chrono>
#include <mutex>
#ifdef _WIN32
#include <windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi")
#include <imagehlp.h>
#pragma comment(lib, "imagehlp.lib")
#endif

#include "utils/ezlog_utils.hpp"

using namespace std;

namespace ezlog {
	std::unique_ptr<EzLog> EzLog::s_instance;
	std::once_flag EzLog::s_init_flag;

	EzLog::EzLog()
	{
	}

	EzLog::~EzLog()
	{
	}

	EzLog* EzLog::inst()
	{
		std::call_once(s_init_flag, [] {
			s_instance.reset(new EzLog());
			});

		return s_instance.get();
	}

	bool EzLog::InitLog(const EzlogConfig& ezlog_config)
	{
		// ! remove last / \\ because of create_directories will return false 
		// ! even create success when the log_dir has \ // at last
		// 
		// ! string convert to wstring, because path use ansi encode for string
		if (ezlog_config.log_dir.ends_with('/') || ezlog_config.log_dir.ends_with('\\')) {
			log_path_ = fromUtf8(std::string(ezlog_config.log_dir, 0, ezlog_config.log_dir.size() - 1));
		}
		else {
			log_path_ = fromUtf8(ezlog_config.log_dir);
		}
		// check log path exits
		std::error_code ec;
		if (!std_fs::exists(log_path_, ec)) {
			// create log path
			// ! 
			if (!std_fs::create_directories(log_path_, ec)) {
				set_error(EzlogError::create_log_path_failed);
				return false;
			}
		}

		log_full_path_ = log_path_ / std::format("{}_{:%Y%m%d}.ezlog", ezlog_config.log_fname, std_time::system_clock::now());

		// open or create log file
		log_stream.open(log_full_path_.c_str(), ofstream::out | ofstream::app);
		int StreamState = log_stream.rdstate();
		if (StreamState != ofstream::goodbit)
		{
			set_error(EzlogError::open_log_file_failed);
			return false;
		}

		// log first line

		return true;
	}

	void EzLog::SetLogLevel(EzlogLevel _log_level)
	{
		log_level_ = _log_level;
	}

	void EzLog::set_error(EzlogError e)
	{
		last_error_ = e;
	}
};
