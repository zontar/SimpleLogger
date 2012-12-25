#ifndef __SIMPLELOGGER_H
#define __SIMPLELOGGER_H

#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>

//���������� ���� ���� <name> </name>, ���������� �������� �� 1 ���. ��������� ���� � ����� ������� ��������� �������� ����� ����
#define DeclareFunction(name) TabLogger __m_debugger(L#name);
//������������� �������. ������� ��������. ���������� ���� ��� ������ ����, �������� ������ �����������
#define InitDebug(fileName) SimpleLogger::instance(fileName);
//��������� ������ �����������, ������� ��������
#define ReleaseDebug SimpleLogger::freeInstance();
//������������� ������ ����: ������������ ����� �����, � ����� ������ ��������� std::endl
#define LOG Logger()

class SimpleLogger
{
public:	
	void log(const std::wstring &text);
	static SimpleLogger *instance(const std::wstring &fileName=L"");
	static void freeInstance();
	static bool isInit;
	void incTabs();
	void decTabs();
private:
	SimpleLogger(const std::wstring &fileName);
	~SimpleLogger(void);
	void makeTabs();
	std::wstring m_fileName;
	int tabCount;
	std::wofstream sDebug;
	static SimpleLogger *m_this;
};

class TabLogger
{
public:
	TabLogger(const std::wstring &name);
	~TabLogger();
private:
	SimpleLogger *dbg;
	std::wstring m_name;
};

class Logger
{
public:
	Logger();
	~Logger();
	Logger &operator<<(const std::wstring &val);
	Logger &operator<<(DWORD val);
	Logger &operator<<(__int64 val);
	Logger &operator<<(int val);

private:
	SimpleLogger *dbg;
	std::wstring m_buf;
	std::wstringstream m_stream;
};

#endif //__SIMPLEDEBUGGER_H

