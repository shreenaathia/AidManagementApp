#include<iostream>
#include<cstring>
#include "ErrorMessage.h"

using namespace std;

namespace sict
{

	ErrorMessage::ErrorMessage(const char* errorMessage)
	{
		if (nullptr == errorMessage)
		{
			this->m_errMsg = nullptr;
		}
		else
		{
			this->m_errMsg = new char[strlen(errorMessage) + 1];
			strcpy(m_errMsg, errorMessage);
		}
	}

	ErrorMessage::~ErrorMessage()
	{
		delete[] m_errMsg;
		m_errMsg = nullptr;
	}

	void ErrorMessage::clear()
	{
		if (m_errMsg != nullptr)
		{
			delete[] m_errMsg;
			m_errMsg = nullptr;
		}
	}

	bool ErrorMessage::isClear() const
	{
		return (m_errMsg == nullptr);
	}

	void ErrorMessage::message(const char* str)
	{
		if (nullptr != str)
		{
			delete[] m_errMsg;
			m_errMsg = new char[strlen(str) + 1];
			strcpy(m_errMsg, str);
		}
	}

	const char* ErrorMessage::message() const
	{
		return m_errMsg;
	}


	std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& em)
	{
		if (!em.isClear())
		{
			ostr << em.message();
		}
		return ostr;
	}

}
