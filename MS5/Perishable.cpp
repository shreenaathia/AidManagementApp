#include<fstream>
#include "Perishable.h"


using namespace std;

namespace sict
{


	Perishable::Perishable() : NonPerishable('P')
	{
		
	}

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{
		NonPerishable::store(file, false);
		file << "," << m_expiryDate;
		if (newLine)
		{
			file << '\n';
		}
		else
		{
			file << ',';
		}

		return file;
	}


	std::fstream& Perishable::load(std::fstream& file)
	{
		NonPerishable::load(file);
		char c;
		file >> c;
		file >> this->m_expiryDate;
		return file;
	}


	std::ostream& Perishable::write(std::ostream& os, bool linear) const
	{
		NonPerishable::write(os, linear);

		if (this->name() != nullptr && this->isClear())
		{

			if (linear)
			{
				os << this->m_expiryDate;
			}
			else
			{
				os << std::endl << "Expiry date: " << this->m_expiryDate;
				
			}
			
		}
		return os;
	}


	std::istream& Perishable::read(std::istream& is)
	{
		Date temp;

		NonPerishable::read(is);


		if ( this->name() != nullptr && this->isClear())
		{
			cout << "Expiry date (YYYY/MM/DD): ";

			is >> temp;

			if (temp.errCode() == CIN_FAILED)
			{
				is.setstate(ios::failbit);
				message("Invalid Year in Date Entry");
			}
			else if (temp.errCode() == YEAR_ERROR)
			{
				is.setstate(ios::failbit);
				message("Invalid Year in Date Entry");
			}
			else if (temp.errCode() == MON_ERROR)
			{
				message("Invalid Month in Date Entry");

			}
			else if (temp.errCode() == DAY_ERROR)
			{
				message("Invalid Day in Date Entry");
			}
			else if (!cin.fail())
			{
				m_expiryDate = temp;
			}
		}
		return is;
	}

	const Date& Perishable::expiry() const
	{
		return this->m_expiryDate;
	}

	Product* CreatePerishable()
	{
		Product* item = nullptr;
		item = new Perishable();
		return item;
	}
}
