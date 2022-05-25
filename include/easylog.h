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
 * <tr><th>Date        <th>Version  <th>Author    <th>Description
 * <tr><td>2022Äê5ÔÂ15ÈÕ  <td>1.0      <td>slivermteor  <td>create
 * </table>
 */
#pragma once
#include <string>

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

	bool init_ezlog(const EzlogConfig& init_config);

};
