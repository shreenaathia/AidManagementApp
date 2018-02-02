#ifndef SICT_ERRORMESSAGE_H
#define SICT_ERRORMESSAGE_H

#include"ErrorMessage.h"

namespace sict
{

	class ErrorMessage
	{
		char* m_errMsg;

	public:
		explicit ErrorMessage(const char* errorMessage = nullptr);
		ErrorMessage(const ErrorMessage& em) = delete;
		ErrorMessage& operator=(const ErrorMessage& em) = delete;
		virtual ~ErrorMessage();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;

	};

	std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& em);
}

#endif 