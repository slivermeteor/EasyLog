/**
 * @copyright slivermteor
 * @file ezlog_impl.h
 * @brief easylog implment
 * @author slivermteor
 * @mail: slivermeteor@gmail.com
 * @version 1.0
 *
 * @par change_log:
 * <table>
 * <tr><th>Date        <th>Version  <th>Author    <th>Description
 * <tr><td>2022Äê5ÔÂ16ÈÕ  <td>1.0      <td>slivermteor  <td>create
 * </table>
 */
#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "include/easylog.h"

namespace ezlog {
	namespace std_fs = std::filesystem;
	namespace std_time = std::chrono;

	class EzLog
	{

	public:
		~EzLog();
		static EzLog* inst();
		bool InitLog(const EzlogConfig& ezlog_config);
		void SetLogLevel(EzlogLevel _log_level);

		template <typename S, typename... Args>
		bool log(const S& format_str, Args&&... args);

	protected:
		void set_error(EzlogError e);
		EzLog();
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

	template<typename S, typename ...Args>
	inline bool EzLog::log(const S& format_str, Args && ...args)
	{
		return false;
	}
};
