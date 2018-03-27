#include "EasyLog.h"
#include "LogUtil.h"
#ifdef _WIN32
#include <windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi")
#include <imagehlp.h>
#pragma comment(lib, "imagehlp.lib")
#endif

using namespace std;

CEasyLog::CEasyLog()
{
}

CEasyLog::~CEasyLog()
{
}

LOG_RESULT CEasyLog::InitLog(std::wstring& LogPath, std::wstring& LogFileName)
{
	m_LogPath = LogPath;
	m_LogFileName = LogFileName;
	LOG_RESULT LogResult = {};
	// 没有指定 Log 目录, 得到当前执行目录, 创建 Log 目录.
	if (m_LogPath.empty())
	{
#ifdef _WIN32

		wchar_t ExecutePath[MAX_PATH] = { 0 };
		wchar_t FileName[MAX_PATH] = { 0 };
		GetModuleFileNameW(NULL, ExecutePath, MAX_PATH);
		if (m_LogFileName.empty())
		{
			_wsplitpath_s(ExecutePath, 
				NULL, 0,
				NULL, 0,
				FileName, MAX_PATH, 
				NULL, 0);
			m_LogFileName = std::move(wstring(FileName));
		}

		PathRemoveFileSpecW(ExecutePath);
		m_LogPath = std::move(wstring(ExecutePath) + L"\\Log\\");

#else
	// Linux


		if (m_LogFileName.empty())
		{

		}

#endif
	}
	
	// 判断目录是否存在
#ifdef _WIN32

	if (!MakeSureDirectoryPathExists((wstr2str(m_LogPath) + '\\').c_str()))
	{
		LogResult.ResultType = WINDOWS_ERROR;
		LogResult.Result = GetLastError();
		return LogResult;
	}
#else
	// Linux - 保证目录

#endif

	// 打开 / 创建 Log 文件
	std::wstring LogFileFullPath = m_LogPath + L'/' + 
		m_LogFileName + L'_' + str2wstr(GetTimeStamp()) 
		+ L".log";
	m_LogStream.open(LogFileFullPath, ofstream::out | ofstream::app);
	int StreamState = m_LogStream.rdstate();
	if (StreamState != ofstream::goodbit)
	{
		// 打开 / 创建 文件有错误
		LogResult.ResultType = IO_ERROR;
		LogResult.Result = StreamState;
		return LogResult;
	}

	// 写入初始化完成
	LogResult = WriteLog(LOG_INFO, wstring(L"Log Init Complete"));

	return LogResult;
}

LOG_RESULT CEasyLog::WriteLog(LOG_TYPE LogType, string LogMsg)
{
	return WriteLog(LogType, str2wstr(LogMsg));
}

LOG_RESULT CEasyLog::WriteLog(LOG_TYPE LogType, wstring LogMsg)
{
	LOG_RESULT LogResult = {};
	// LogStream 未初始化
	if (m_LogStream.rdstate() != ofstream::goodbit)
	{
		LogResult.ResultType = EASYLOG_ERROR;
		LogResult.Result = LOG_FILE_UNINIT;
		return LogResult;
	}

	m_LogStream << "[" << GetTimeStr().c_str() << "] ";

	switch (LogType)
	{
		case LOG_INFO:
		{
			m_LogStream << "[INFO]" << " ";
			break;
		}
		case LOG_WARNING:
		{
			m_LogStream << "[WARNING]" << " ";
			break;
		}
		case LOG_ERROR:
		{
			m_LogStream << "[ERRPR]" << " ";
			break;
		}
		default:
		{
			m_LogStream << "[UNKNOWN]" << " ";
			break;
		}
	}

	m_LogStream << wstr2str(LogMsg).c_str() << endl;

	return LogResult;
}


