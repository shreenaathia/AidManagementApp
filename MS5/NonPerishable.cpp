#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include "NonPerishable.h"
#include"Product.h"

using namespace std;

namespace sict
{

	void NonPerishable::name(const char* prodName)
	{
		if (prodName != nullptr)
		{
			if (m_prodName != nullptr)
			{
				delete[] m_prodName;
				m_prodName = nullptr;
			}

			m_prodName = new char[strlen(prodName) + 1];
			strcpy(m_prodName, prodName);

		}
		else
		{
			delete[] m_prodName;
			m_prodName = nullptr;
		}
	}


	const char* NonPerishable::name() const
	{
		return this->m_prodName;
	}


	double NonPerishable::cost() const
	{
		if (m_isTaxable)
		{
			return this->m_price * tax_rate;
		}
		else
		{
			return this->m_price;
		}
	}


	void NonPerishable::message(const char* msg)
	{
		error.message(msg);
	}


	bool NonPerishable::isClear() const
	{
		return error.isClear();
	}

	NonPerishable::NonPerishable(const char recordName) 
	{
		m_prodType = recordName;
		m_prodSku[0] = '\0';
		m_prodName = nullptr;
		m_prodUnit[0] = '\0';
		m_currentQty = 0;
		m_neededQty = 0;
		m_price = 0;
		m_isTaxable = true;

	}

	NonPerishable::NonPerishable(const char* prodSku, const char* prodName, const char* prodUnit, int prodQty,
		bool isTax, double prodPrice, int qtyNeeded)
	{
		this->m_prodName = nullptr;
		if (prodSku != nullptr && prodName != nullptr && prodUnit != nullptr)
		{
			strcpy(m_prodSku, prodSku);
			strcpy(m_prodUnit, prodUnit);
			name(prodName);
			m_currentQty = prodQty;
			m_isTaxable = isTax;
			m_price = prodPrice;
			m_neededQty = qtyNeeded;
		}

	}


	NonPerishable::NonPerishable(const NonPerishable& np)
	{
		this->m_prodName = nullptr;
		*this = np;
	}

	NonPerishable& NonPerishable::operator=(const NonPerishable& np)
	{
		if (this != &np)
		{

			m_prodType = np.m_prodType;
			strcpy(m_prodSku, np.m_prodSku);
			name(np.m_prodName);
			strcpy(m_prodUnit, np.m_prodUnit);
			m_currentQty = np.m_currentQty;
			m_neededQty = np.m_neededQty;
			m_price = np.m_price;
			m_isTaxable = np.m_isTaxable;

		}
		return *this;
	}

	NonPerishable::~NonPerishable()
	{
		delete[] m_prodName;
		m_prodName = nullptr;
	}


	std::fstream& NonPerishable::store(std::fstream& file, bool newLine) const
	{
		file << m_prodType << ","
			<< m_prodSku << ","
			<< name() << ","
			<< m_price << ","
			<< m_isTaxable << ","
			<< m_currentQty << ","
			<< m_prodUnit << ","
			<< m_neededQty;

		if (newLine)
		{
			file << endl;
		}

		return file;
	}


	std::fstream& NonPerishable::load(std::fstream& file)
	{
		char sku[max_sku_length];   //stores sku
		char name[max_name_length];  //stores name
		char unit[max_unit_length];
		double price;    //stores price
		bool taxed;      //stores tax
		int qty;    //stores quantity
		int qtyNeed;
		

		file.getline(sku, max_sku_length, ',');
		file.getline(name, max_name_length, ',');
		file >> price;
		file.ignore();
		file >> taxed;
		file.ignore();
		file >> qty;
		file.ignore();
		file.getline(unit, max_unit_length, ',');
		file >> qtyNeed;

		
		strcpy(m_prodSku, sku);           
		this->name(name);         
		m_price = price;        
		m_isTaxable = taxed;        
		m_currentQty = qty;  
		m_neededQty = qtyNeed;
		strcpy(m_prodUnit, unit);

		return file;
	}



	std::ostream& NonPerishable::write(std::ostream& os, bool linear) const
	{
		if (error.isClear())
		{
			if (linear)
			{
				os.setf(ios::left);
				os.setf(ios::fixed);
				os.precision(2);
				os.fill(' ');

				os << setw(max_sku_length) << m_prodSku << '|'
					<< setw(20) << m_prodName << '|';
				os.unsetf(ios::left);
				os << setw(7) << cost() << '|'
					<< setw(4) << m_currentQty << '|';
				os.setf(ios::left);
				os << setw(10) << m_prodUnit;
				os.unsetf(ios::left);
				os	<< '|' << setw(4) << m_neededQty << "|";
			}
			else
			{
				os << "Sku: " << m_prodSku << endl
					<< "Name: " << m_prodName << endl
					<< "Price: " << m_price << endl;

				if (m_isTaxable)
				{
					os.setf(ios::fixed);
					os.precision(2);

					os  << "Price after tax: " << cost() << endl;
				}
				else
				{
					os << "Price after tax: N/A" <<  endl;
				}


				os << "Quantity On Hand: " << quantity() << " " << m_prodUnit << endl
					<< "Quantity Needed: " << qtyNeeded();
			}

		}
		else
		{
			os << error.message();
		}

		

		
		return os;
	}



	std::istream& NonPerishable::read(std::istream& is)
	{
		char sku[max_sku_length];
		char name[max_name_length];
		char unit[max_unit_length];
		double price;
		char c;
		int qty;
		int qtyNeed;
		
		error.clear();
		
		if (!is.fail())
		{

			cout << " Sku: ";
			is >> sku;
			if (!is.fail())
			{
				strcpy(m_prodSku, sku);
			}


			cout << " Name: ";
			is >> name;
			if (!is.fail())
			{
				this->name(name);

			}

			cout << " Unit: ";
			is >> unit;
			if (!is.fail())
			{
				strcpy(m_prodUnit, unit);
			}


			cout << " Taxed? (y/n): ";
			is >> c;
			if (!is.fail())
			{

				if (c == 'y' || c == 'Y')
				{
					this->m_isTaxable = true;
				}
				 else if (c == 'n' || c == 'N')
				{
					this->m_isTaxable = false;
				}
			
				else
				{
					error.message("Only (Y)es or (N)o are acceptable");
					is.setstate(std::ios::failbit);
				}
		    }

			if (!is.fail())
			{
			cout << " Price: ";
			is >> price;
			
				 if(!is.fail())
				{
					m_price = price;
				}
				else
				{
					error.message("Invalid Price Entry");
				}
		    }
			

			if (!is.fail())
			{
				cout << "Quantity On hand: ";
				is >> qty;
				m_currentQty = qty;
				if (is.fail())
				{
					error.message("Invalid Quantity Entry");
				}
		
			}

			if (!is.fail())
			{
				cout << "Quantity Needed: ";
				is >> qtyNeed;
				m_neededQty = qtyNeed;
				if (is.fail())
				{
					error.message("Invalid Quantity Needed Entry");
				}
			}

		}

		return is;
	}


	bool NonPerishable::operator==(const char* sku) const
	{
		return (strcmp(m_prodSku, sku) == 0);

	}

	double NonPerishable::total_cost() const
	{
		return m_currentQty * cost();
	}

	void NonPerishable::quantity(int onHand)
	{
		m_currentQty = onHand;
	}

	bool NonPerishable::isEmpty() const
	{
		if (m_prodSku[0] == '\0' && m_prodName == nullptr && m_currentQty == 0 && m_neededQty == 0 && m_price == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	int NonPerishable::qtyNeeded() const
	{
		return m_neededQty;
	}


	int NonPerishable::quantity() const
	{
		return this->m_currentQty;
	}


	bool NonPerishable::operator>(const char* str) const
	{
		return (strcmp(str, m_prodSku) > 0);
	}


	int NonPerishable::operator+=(int numUnit)
	{
		if (numUnit > 0)
		{
			return this->m_currentQty += numUnit;
		}
		else
		{
			return this->m_currentQty;
		}
	}

	bool NonPerishable::operator>(const Product& prod) const
	{
		return (strcpy(this->m_prodName, prod.name()) > 0);
	}


	std::ostream& operator<<(std::ostream& os, const Product& prod)
	{
		return prod.write(os, true);
	}


	std::istream& operator>>(std::istream& is, Product& prod)
	{
		return prod.read(is);
	}


	double operator+=(double& cost, const Product& prod)
	{
		return cost += prod.total_cost();

	}

	Product* CreateProduct()
	{
		Product* item = nullptr;
		item = new NonPerishable();
		return item;
	}


}
