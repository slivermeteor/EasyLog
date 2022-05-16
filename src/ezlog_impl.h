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

namespace ezlog {
	struct EzlogConfig {
		std::wstring log_dir;
		std::wstring log_fname;
		// todo: encrypt config
	};

	enum class EzlogError {
		success = 0,
		create_log_path_failed,
		open_log_file_failed,
	};

	namespace std_fs = std::filesystem;
	namespace std_time = std::chrono;

	class EzLog
	{

	public:
		~EzLog();
		bool InitLog(const EzlogConfig& ezlog_config);
	protected:
		void set_error(EzlogError e);

	private:

		EzlogError last_error_ = EzlogError::success;
		std_fs::path			log_path_;
		std_fs::path			log_full_path_;
		std::ofstream			log_stream;

	private:
		EzLog();
	};
};
