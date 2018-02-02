#ifndef SICT_NONPERISHABLE_H
#define SICT_NONPERISHABLE_H

#include"Product.h"
#include "ErrorMessage.h"

namespace sict
{
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 1.13;

	class NonPerishable : public Product
	{
		char m_prodType;
		char m_prodSku[max_sku_length + 1];
		char* m_prodName;
		char m_prodUnit[max_unit_length + 1];
		int m_currentQty;
		int m_neededQty;
		double m_price;
		bool m_isTaxable;
		ErrorMessage error;
	

	protected:
		void name(const char*);
		const char* name() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;


	public:
		NonPerishable(const char recordName = 'N');
		NonPerishable(const char* prodSku, const char* prodName, const char* prodUnit, int prodQty = 0, bool isTax = true,
			double prodPrice = 0, int qtyNeeded = 0);
		NonPerishable(const NonPerishable&);
		NonPerishable& operator=(const NonPerishable&);
		~NonPerishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		int operator+=(int);
		bool operator>(const Product&) const;

	};

	std::ostream& operator<<(std::ostream&, const Product&);
	std::istream& operator>>(std::istream&, Product&);
	double operator+=(double&, const Product&);
	Product* CreateProduct();
}
#endif
