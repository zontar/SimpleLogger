#include <stdafx.h>
#include "SimpleLogger.h"

//#include <iostream>

SimpleLogger *SimpleLogger::m_this = NULL;
bool SimpleLogger::isInit = false;

SimpleLogger::SimpleLogger(const std::wstring &fileName)
{
	tabCount=0;
	isInit = true;
	m_fileName = fileName;
	log(L"[session started ]\n\n");
}


SimpleLogger::~SimpleLogger(void)
{
	log(L"[session closed]\n\n");
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
	sDebug.open(m_fileName,std::ios::app);
	makeTabs();
	sDebug << text << std::endl;
	sDebug.close();
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
	if(dbg && dbg->isInit)
	{
		dbg->log(L"<"+m_name+L">");
		dbg->incTabs();
	}
}

TabLogger::~TabLogger()
{
	if(dbg && dbg->isInit)
	{
		dbg->decTabs();
		dbg->log(L"</"+m_name+L">");
	}
}

Logger::Logger()
{
#ifndef _SIMPLE_NO_DEBUG
	dbg = SimpleLogger::instance();
#endif
}

Logger::~Logger()
{
#ifndef _SIMPLE_NO_DEBUG	
	while(!m_stream.eof())m_buf += m_stream.get();
	if(dbg->isInit)	dbg->log(m_buf);	
#endif
}

Logger &Logger::operator<<(const std::wstring &val)
{
#ifndef _SIMPLE_NO_DEBUG
	m_stream << val;
#endif
	return *this;

}

Logger &Logger::operator<<(DWORD val)	
{
#ifndef _SIMPLE_NO_DEBUG
	m_stream << val;
#endif
	return *this;
}

Logger &Logger::operator<<(__int64 val)	
{
#ifndef _SIMPLE_NO_DEBUG
	m_stream << val;
#endif
	return *this;
}

Logger &Logger::operator<<(int val)	
{
#ifndef _SIMPLE_NO_DEBUG
	m_stream << val;
#endif
	return *this;
}

Logger &Logger::operator<<(size_t val)	
{
#ifndef _SIMPLE_NO_DEBUG
	m_stream << val;
#endif
	return *this;
}
