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
	当 Result 不等于 0 时, 说明有错误.
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
		@brief 初始化 Log 
		@param LogPath 指定Log目录, 默认为空
		@param LogFileName Log 文件名, 默认是空
		@return 错误代码, 由 GetLastError, ios_base::iostate, 自定错误码 组成.
	*/
	LOG_RESULT InitLog(std::wstring& LogPath = std::wstring(), std::wstring& LogFileName = std::wstring());

	/*
		@brief 写入 Log
		@param LogType Log 类型
		@param LogMsg Log 消息
	*/
	LOG_RESULT WriteLog(LOG_TYPE LogType, std::wstring LogMsg);
	LOG_RESULT WriteLog(LOG_TYPE LogType, std::string LogMsg);

private:
	// 私有成员变量
	std::wstring			m_LogPath;
	std::wstring			m_LogFileName;
	std::ofstream			m_LogStream;

private:
	// 私有成员函数
	friend class SingletonFactory<CEasyLog>;
	CEasyLog();
};

#define WriteEasyLog(Type, Msg) CEasyLog::GetInstance()->WriteLog(Type, Msg);

