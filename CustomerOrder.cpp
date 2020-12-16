/**************************************************************************************************************************
// Name: Bruno Pinto
// Date of completion: 2020/04/10
**************************************************************************************************************************/

#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace std {

	size_t CustomerOrder::m_widthField = 0;

	// default constructor
	CustomerOrder::CustomerOrder() {
	}

	// custom constructor that takes the name of a file as a parameter
	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities tempUtilitiesObject;
		size_t pos{ 0 };
		size_t itemsPos{ 0 };
		bool success{ true };
		std::string tempString;

		// get attributes

		// name
		tempString = tempUtilitiesObject.extractToken(str, pos, success);
		if (success)
			m_name = tempString;
		pos += (tempString.length() + 1);

		// name of the product being assembled

		tempString = tempUtilitiesObject.extractToken(str, pos, success);
		if (success)
			m_product = tempString;
		pos += (tempString.length() + 1);

		// list of items
		// get number of items
		itemsPos = pos;
		do {
			tempString = tempUtilitiesObject.extractToken(str, itemsPos, success);
			itemsPos += (tempString.length() + 1);
			if (success)
				m_cntItem++;
		}  while (success);
		
		// dynamically allocates Items**
		m_lstItem = new Item * [m_cntItem];

		// copy items
		for (size_t i = 0; i < m_cntItem; i++) {
			tempString = tempUtilitiesObject.extractToken(str, pos, success);
			m_lstItem[i] = new Item(tempString);
			pos += (tempString.length() + 1);
		}

		// update m_widthField
		if (m_widthField < tempUtilitiesObject.getFieldWidth())
				m_widthField = tempUtilitiesObject.getFieldWidth();
	}

	// copy constructor - throws an exception when called
	CustomerOrder::CustomerOrder(const CustomerOrder& src) {
		throw "Error!";
	}

	// move constructor - promises it doesn't throw an exception
	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
		m_lstItem = src.m_lstItem;
		m_name = src.m_name;
		m_product = src.m_product;
		m_cntItem = src.m_cntItem;
		m_widthField = src.m_widthField;

		src.m_lstItem = nullptr;
		src.m_name = "";
		src.m_product = "";
		src.m_cntItem = 0;
		// as m_widthField is a static variable we don't assign it to 0 (zero)
	}

	// move assignment - promises it doesn't throw an exception
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {

			// delete m_lstItem
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			m_lstItem = src.m_lstItem;
			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_widthField = src.m_widthField;

			src.m_lstItem = nullptr;
			src.m_name = "";
			src.m_product = "";
			src.m_cntItem = 0;
			// as m_widthField is a static variable we don't assign it to 0 (zero)
		}
		return *this;
	}

	// returns m_name
	const std::string CustomerOrder::getName() const {
		return m_name;
	}

	// destructor
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}

		delete[] m_lstItem;
	}

	// returns true if all the items in the order have been filled; false otherwise
	bool CustomerOrder::isOrderFilled() const {

		bool allFilled{ true };

		for (size_t i = 0; i < m_cntItem && allFilled; i++) {
			if (!m_lstItem[i]->m_isFilled)
				allFilled = false;
		}

		return allFilled;
	}

	// returns the ItemInfo::m_fillState of the item specified as a parameter.
	// If the item doesn't exist in the order, return true.
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {

		bool toReturn{ true };
		
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName)
				toReturn = m_lstItem[i]->m_isFilled;
		}

		return toReturn;
	}

	// fills the item in the current order that corresponds to the station passed into the function.
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {

		for (size_t i = 0; i < m_cntItem; i++) {
			// checks if the current order has the item handled by the station
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity() >= 1) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled ";
				}
				else {
					os << "    Unable to fill ";
				}
				os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
		}
	}

	// displays the state of the current object in the specified format
	void CustomerOrder::display(std::ostream& os) const {

		os << m_name << " - " << m_product << std::endl;

		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << std::setfill(' ') << "] "
			   << std::setw(m_widthField) << std::left << m_lstItem[i]->m_itemName << std::right << " - ";

			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED";
			}
			else {
				os << "MISSING";
			}

			os << std::endl;
		}
	}
}