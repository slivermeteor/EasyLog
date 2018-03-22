#include <iostream>
#include <string>
#include "EasyLog.h"

using namespace std;

int main()
{
	
	LOG_RESULT LogResult = {};
	LogResult = CEasyLog::GetInstance()->InitLog();
	if (LogResult.Result != 0)
	{
		cout << "Result Type:" << LogResult.ResultType << " Code:" << LogResult.Result << endl;
		return -1;
	}
	while (true)
	{
		wstring LogStr;
		LogStr.clear();
		cout << "Input the test log information: " << endl;
		wcin >> LogStr;
		
		//CEasyLog::GetInstance()->WriteLog(LOG_INFO, LogStr);
		WriteEasyLog(LOG_INFO, LogStr);
	}	

	return 0;
}