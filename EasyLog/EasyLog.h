#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Singleton.hpp"


enum LOG_TYPE
{
	LOG_INFO = 0,
	LOG_WARNING,
	LOG_ERROR
};

enum LOG_ERROR_CODE
{
	LOG_SUCCESS = 0,
	LOG_FILE_UNINIT 
};

enum LOG_RESULT_TYPE
{
	WINDOWS_ERROR = 0,
	IO_ERROR,
	EASYLOG_ERROR
};

/*
	�� Result ������ 0 ʱ, ˵���д���.
*/
struct LOG_RESULT
{
	LOG_RESULT_TYPE ResultType;
	unsigned long Result;

	LOG_RESULT()
	{
		ResultType = WINDOWS_ERROR;
		Result = 0;
	}
};

class CEasyLog :
	public SingletonFactory<CEasyLog>
{
public:

	~CEasyLog();

	/*
		@brief ��ʼ�� Log 
		@param LogPath ָ��LogĿ¼, Ĭ��Ϊ��
		@param LogFileName Log �ļ���, Ĭ���ǿ�
		@return �������, �� GetLastError, ios_base::iostate, �Զ������� ���.
	*/
	LOG_RESULT InitLog(std::wstring& LogPath = std::wstring(), std::wstring& LogFileName = std::wstring());

	/*
		@brief д�� Log
		@param LogType Log ����
		@param LogMsg Log ��Ϣ
	*/
	LOG_RESULT WriteLog(LOG_TYPE LogType, std::wstring LogMsg);
	LOG_RESULT WriteLog(LOG_TYPE LogType, std::string LogMsg);

private:
	// ˽�г�Ա����
	std::wstring			m_LogPath;
	std::wstring			m_LogFileName;
	std::ofstream			m_LogStream;

private:
	// ˽�г�Ա����
	friend class SingletonFactory<CEasyLog>;
	CEasyLog();
};

#define WriteEasyLog(Type, Msg) CEasyLog::GetInstance()->WriteLog(Type, Msg);

