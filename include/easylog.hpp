/**
 * @copyright slivermteor
 * @file easylog.hpp
 * @brief easylog header file
 * @author slivermteor
 * @mail: slivermeteor@gmail.com
 * @version 1.0
 *
 * @par change_log:
 * <table>
 * <tr><th>Date          <th>Version  <th>Author    <th>Description
 * <tr><td>2022Äê5ÔÂ15ÈÕ  <td>1.0      <td>slivermteor  <td>create
 * </table>
 */
#pragma once
#include <mutex>
#include <chrono>
#include <string>
#include <fstream>
#include <filesystem>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace ezlog {
	struct EzlogConfig {
		std::string log_dir; // utf8
		std::string log_fname; // utf8
		// todo: encrypt config
	};

	enum class EzlogLevel {
		kAllLog,
		kDebugLog,
		kInfoLog,
		kWarnLog,
		kErrorLog,
		kNoneLog,
	};

	enum class EzlogError {
		success = 0,
		create_log_path_failed,
		open_log_file_failed,
	};

	namespace utils {
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
	};

	namespace formatter {
		template<typename... Args>
		void ezlog_formatter(EzlogLevel _level, const char* file, int line, const char* func, const char* tag, const char* fmt_str, Args&& ... args) {
			// ! todo: custom seperate char
			// time format %F = %Y-%m-%d %T = %H:%M:%S
			// see C++ time format: https://en.cppreference.com/w/cpp/chrono/c/strftime
			std::string time_str = std::format("[{0:%F}][{0:%T}]", std::chrono::system_clock::now());

			std::string content_str = std::vformat(fmt_str, std::make_format_args(args...));

			std::string proc_str = std::format("[][]");
		}
	};

	namespace details {

		namespace std_fs = std::filesystem;
		namespace std_time = std::chrono;

		class EzLog
		{

		public:
			~EzLog() {};

			static EzLog* inst()
			{
				std::call_once(s_init_flag, [] {
					s_instance.reset(new EzLog());
					});

				return s_instance.get();
			}


			bool InitLog(const EzlogConfig& ezlog_config)
			{
				// ! remove last / \\ because of create_directories will return false if the path has \ // at last
				// ! even the directories create success

				// ! string convert to wstring, because path use ansi encode for string
				if (ezlog_config.log_dir.ends_with('/') || ezlog_config.log_dir.ends_with('\\')) {
					log_path_ = utils::fromUtf8(std::string(ezlog_config.log_dir, 0, ezlog_config.log_dir.size() - 1));
				}
				else {
					log_path_ = utils::fromUtf8(ezlog_config.log_dir);
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
				log_stream.open(log_full_path_.c_str(), std::ofstream::out | std::ofstream::app);
				int StreamState = log_stream.rdstate();
				if (StreamState != std::ofstream::goodbit)
				{
					set_error(EzlogError::open_log_file_failed);
					return false;
				}

				// log first line

				return true;
			}

			void SetLogLevel(EzlogLevel _log_level)
			{
				log_level_ = _log_level;
			}

			template <typename S, typename... Args>
			bool log(const S& format_str, Args&&... args)
			{

			}

		protected:
			void set_error(EzlogError e)
			{
				last_error_ = e;
			}

			EzLog() = default;
			EzLog(const EzLog&) = delete;
			EzLog& operator=(const EzLog&) = delete;

		private:
			EzlogError last_error_ = EzlogError::success;
			EzlogLevel log_level_ = EzlogLevel::kDebugLog;
			std_fs::path			log_path_;
			std_fs::path			log_full_path_;
			std::ofstream			log_stream;

			static std::unique_ptr<EzLog> s_instance;
			static std::once_flag s_init_flag;
		};

		std::unique_ptr<EzLog> EzLog::s_instance = nullptr;
		std::once_flag EzLog::s_init_flag;
	};

	bool init_ezlog(const EzlogConfig& init_config)
	{
		return details::EzLog::inst()->InitLog(init_config);
	}
};
