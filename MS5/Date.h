#ifndef SICT_DATE_H
#define SICT_DATE_H


#define NO_ERROR   0  //--No error - the date is valid
#define CIN_FAILED 1  // --istream failed on information entry
#define YEAR_ERROR 2  //--Year value is invalid
#define MON_ERROR  3  //--Month value is invalid
#define DAY_ERROR  4  // --Day value is invalid


namespace sict {

	const int min_year = 2000;
	const int max_year = 2030;


	class Date {

		int m_year;
		int m_month;
		int m_day;
		int m_dateCheck;
		int m_errorState;

		int mdays(int, int)const;
		void errCode(int errorCode);



	public:

		Date();
		Date(int, int, int);

		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& is);
		std::ostream& write(std::ostream& os) const;

	};

	std::istream& operator>>(std::istream& is, Date& date);
	std::ostream& operator<<(std::ostream& os, const Date& date);





}
#endif
