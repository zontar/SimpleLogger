#ifndef __SIMPLELOGGER_H
#define __SIMPLELOGGER_H

#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>

#ifndef _SIMPLE_NO_DEBUG
	//определяет блок вида <name> </name>, содержимое сдвигает на 1 таб. Закрывает блок в конце области видимости текущего блока кода
	#define DeclareFunction(name) TabLogger __m_debugger(L#name);
	//Инициализация логгера. Создает синглтон. Определяет файл для записи лога, начинает сессию логирования
	#define InitDebug(fileName) SimpleLogger::instance(fileName);
	//Закрывает сессию логирования, удаляет синглтон
	#define ReleaseDebug SimpleLogger::freeInstance();
	//Непосредвенно запись лога: представляет собой поток, в конце вывода вставляет std::endl
	
#else
	#define DeclareFunction(name) //TabLogger __m_debugger(L#name);
	#define InitDebug(fileName) //SimpleLogger::instance(fileName);
	#define ReleaseDebug //SimpleLogger::freeInstance();
#endif

#define LOG Logger()
#define PARAM(name) L#name<<L"="<<name<<L"; " 

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
	Logger &operator<<(unsigned __int64 val);
	Logger &operator<<(int val);
	Logger &operator<<(size_t val);
	Logger &operator<<(std::string &val);

private:
	std::wstring widen(const std::string& in, std::locale loc  = std::locale());
	SimpleLogger *dbg;
	std::wstring m_buf;
	std::wstringstream m_stream;
};

#endif //__SIMPLEDEBUGGER_H

