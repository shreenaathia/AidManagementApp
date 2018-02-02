#ifndef SICT_PERISHABLE_H
#define SICT_PERISHABLE_H

#include<iostream>
#include<fstream>
#include"Date.h"
#include"NonPerishable.h"
#include"Product.h"

namespace sict 
{

	class Perishable: public NonPerishable
	{
		Date m_expiryDate;

	public:
		Perishable();

		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);

		const Date& expiry() const;

	};


	Product* CreatePerishable();

}

#endif

