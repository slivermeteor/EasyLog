#include "ezlog_impl.h"
#include <format>
#include <chrono>
#ifdef _WIN32
#include <windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi")
#include <imagehlp.h>
#pragma comment(lib, "imagehlp.lib")
#endif

using namespace std;

namespace ezlog {
	EzLog::EzLog()
	{
	}

	EzLog::~EzLog()
	{
	}

	bool EzLog::InitLog(const EzlogConfig& ezlog_config)
	{
		log_path_ = ezlog_config.log_dir;
		// check log path exits
		if (!std_fs::exists(log_path_)) {
			// create log path
			if (!std_fs::create_directories(log_path_)) {
				set_error(EzlogError::create_log_path_failed);
				return false;
			}
		}

		log_full_path_ = log_path_ / std::format(L"{0}_{:%Y%m%d}.ezlog", ezlog_config.log_fname, std_time::system_clock::now());

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

	void EzLog::set_error(EzlogError e)
	{
		last_error_ = e;
	}
};
