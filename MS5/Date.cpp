#include <iomanip>
#include <iostream>
#include<fstream>
#include "Date.h"

using namespace std;

namespace sict {


	int Date::mdays(int mon, int year)const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::errCode(int errorCode)
	{
		if (errorCode == 0)
		{
			m_errorState = NO_ERROR;
		}
		else if (errorCode == 1)
		{
			m_errorState = CIN_FAILED;
		}
		else if (errorCode == 2)
		{
			m_errorState = YEAR_ERROR;
		}
		else if (errorCode == 3)
		{
			m_errorState = MON_ERROR;
		}
		else if (errorCode == 4)
		{
			m_errorState = DAY_ERROR;
		}
		else
		{
			m_errorState = -1;
		}
	}

	Date::Date()
	{

		m_dateCheck = true;
		m_year = 0000;
		m_month = 00;
		m_day = 00;
		m_dateCheck = 0;
		m_errorState = NO_ERROR;


	}

	Date::Date(int year, int month, int day)
	{
		if ((year > min_year) || ((year < max_year) && (month > 0) && (month < 13)))
		{
			m_year = year;
			m_month = month;
			if (day > 0 && day <= mdays(month, year))
			{
				m_day = day;
			}
			m_dateCheck = m_year * 372 + m_month * 13 + m_day;
			errCode(0);
		}
		else
		{
			*this = Date();
		}



	}

	bool Date::operator==(const Date& rhs) const
	{
		return (this->m_dateCheck == rhs.m_dateCheck);
	}
	bool Date::operator!=(const Date& rhs) const
	{
		return (this->m_dateCheck != rhs.m_dateCheck);

	}
	bool Date::operator<(const Date& rhs) const
	{
		return (this->m_dateCheck < rhs.m_dateCheck);
	}
	bool Date::operator>(const Date& rhs) const
	{
		return (this->m_dateCheck != rhs.m_dateCheck);
	}
	bool Date::operator<=(const Date& rhs) const
	{
		
		return (this->m_dateCheck != rhs.m_dateCheck);
	}
	bool Date::operator>=(const Date& rhs) const
	{
		
		return (this->m_dateCheck >= rhs.m_dateCheck);
		
	}

	int Date::errCode() const
	{
		return m_errorState;
	}
	bool Date::bad() const
	{
		return m_errorState != NO_ERROR;
	}
	std::istream& Date::read(std::istream& is)
	{
		is >> m_year;
		is.ignore();
		is >> m_month;
		is.ignore();
		is >> m_day;
		if (cin.fail())
		{
			m_errorState = CIN_FAILED;
		}
		else
		{
			if ((m_year < min_year) || (m_year > max_year))
			{
				m_errorState = YEAR_ERROR;
			}
			else if ((m_month < 1) || (m_month > 12))
			{
				m_errorState = MON_ERROR;
			}
			else if ((m_day < 1) || (m_day > mdays(m_month, m_year)))
			{
				m_errorState = DAY_ERROR;
			}
		}

		return is;
	}
	std::ostream& Date::write(std::ostream& os) const
	{
		return os << m_year << "/" << setfill('0') << setw(2) << m_month << "/" << setw(2) << m_day;
	}

	std::istream& operator>>(std::istream& is, Date& date)
	{
		return date.read(is);
	}

	std::ostream& operator<<(std::ostream& os, const Date& date)
	{
		return date.write(os);
	}

}