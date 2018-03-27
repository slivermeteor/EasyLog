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
	// û��ָ�� Log Ŀ¼, �õ���ǰִ��Ŀ¼, ���� Log Ŀ¼.
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
	
	// �ж�Ŀ¼�Ƿ����
#ifdef _WIN32

	if (!MakeSureDirectoryPathExists((wstr2str(m_LogPath) + '\\').c_str()))
	{
		LogResult.ResultType = WINDOWS_ERROR;
		LogResult.Result = GetLastError();
		return LogResult;
	}
#else
	// Linux - ��֤Ŀ¼

#endif

	// �� / ���� Log �ļ�
	std::wstring LogFileFullPath = m_LogPath + L'/' + 
		m_LogFileName + L'_' + str2wstr(GetTimeStamp()) 
		+ L".log";
	m_LogStream.open(LogFileFullPath, ofstream::out | ofstream::app);
	int StreamState = m_LogStream.rdstate();
	if (StreamState != ofstream::goodbit)
	{
		// �� / ���� �ļ��д���
		LogResult.ResultType = IO_ERROR;
		LogResult.Result = StreamState;
		return LogResult;
	}

	// д���ʼ�����
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
	// LogStream δ��ʼ��
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


