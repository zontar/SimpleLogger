#include "SimpleLogger.h"

//#include <iostream>

SimpleLogger *SimpleLogger::m_this = NULL;
bool SimpleLogger::isInit = false;

SimpleLogger::SimpleLogger(const std::wstring &fileName)
{
	tabCount=0;
	isInit = true;
	sDebug.open(fileName,std::ios::app);
	sDebug << "[session started on " << __TIME__ << "]" << std::endl << std::endl;
}


SimpleLogger::~SimpleLogger(void)
{
	sDebug << "[session closed on " << __TIME__ << "]" << std::endl << std::endl;
	isInit = false;
	sDebug.close();
}

SimpleLogger *SimpleLogger::instance(const std::wstring &fileName)
{
	if(m_this == NULL)
	{
		m_this = new SimpleLogger(fileName);
	}
	return m_this;
}

void SimpleLogger::freeInstance()
{
	if(m_this) delete m_this;
	m_this = NULL;
}

void SimpleLogger::makeTabs()
{
	for(int i=0;i<tabCount;++i) sDebug << "\t";
}

void SimpleLogger::log(const std::wstring &text)
{	
	makeTabs();
	sDebug << text << std::endl;
}

void SimpleLogger::incTabs()
{
	tabCount++;
}

void SimpleLogger::decTabs()
{
	tabCount--;
}

TabLogger::TabLogger(const std::wstring &name)
{
	dbg = SimpleLogger::instance();
	m_name = name;
	if(dbg->isInit)
	{
		dbg->log(L"<"+m_name+L">");
		dbg->incTabs();
	}
}

TabLogger::~TabLogger()
{
	if(dbg->isInit)
	{
		dbg->decTabs();
		dbg->log(L"</"+m_name+L">");
	}
}

Logger::Logger()
{
	dbg = SimpleLogger::instance();
}

Logger::~Logger()
{
	
	while(!m_stream.eof())m_buf += m_stream.get();
	if(dbg->isInit)	dbg->log(m_buf);	
}

Logger &Logger::operator<<(const std::wstring &val)
{
	m_stream << val;
	return *this;
}

Logger &Logger::operator<<(DWORD val)	
{
	m_stream << val;
	return *this;
}

Logger &Logger::operator<<(__int64 val)	
{
	m_stream << val;
	return *this;
}

Logger &Logger::operator<<(int val)	
{
	m_stream << val;
	return *this;
}

