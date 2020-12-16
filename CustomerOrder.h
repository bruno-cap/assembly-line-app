/**************************************************************************************************************************
// Name: Bruno Pinto
// Date of completion: 2020/04/10
**************************************************************************************************************************/


#ifndef SDDS_CUSTOMERORDER_H__
#define SDDS_CUSTOMERORDER_H__

#include <string>
#include "Station.h"

namespace std {

	struct Item;

	class CustomerOrder {
		//attributes
		std::string m_name{};
		std::string m_product{};
		unsigned int m_cntItem{ 0 };
		Item** m_lstItem{ nullptr };
		static size_t m_widthField;

	public:
		// methods
		// default constructor
		CustomerOrder();
		// custom constructor that takes the name of a file as a parameter
		CustomerOrder(const std::string& str);
		// copy constructor - throws an exception when called
		CustomerOrder(const CustomerOrder& src);
		// assignment overload - deleted
		CustomerOrder& operator=(CustomerOrder& src) = delete;
		// move constructor - promises it doesn't throw an exception
		CustomerOrder(CustomerOrder&& src) noexcept;
		// move assignment - promises it doesn't throw an exception
		CustomerOrder& operator=(CustomerOrder&& src) noexcept;
		// returns m_name
		const std::string getName() const;
		// destructor
		virtual ~CustomerOrder();
		// returns true if all the items in the order have been filled; false otherwise
		bool isOrderFilled() const;
		// returns the ItemInfo::m_fillState of the item specified as a parameter.
		// If the item doesn't exist in the order, return true.
		bool isItemFilled(const std::string& itemName) const;
		// fills the item in the current order that corresponds to the station passed into the function.
		void fillItem(Station& station, std::ostream& os);
		// displays the state of the current object in the specified format
		void display(std::ostream& os) const;

	};

	struct Item
	{
		std::string m_itemName;
		unsigned int m_serialNumber = 0;
		bool m_isFilled = false;

		Item(const std::string& src) : m_itemName(src) {};
	};

}

#endif