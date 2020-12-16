/**************************************************************************************************************************
// Name: Bruno Pinto
// Date of completion: 2020/04/10
**************************************************************************************************************************/


#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "Station.h"

namespace std {

	// initializing static variables
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	// custom constructor
	Station::Station(const std::string& str) {
		Utilities tempUtilitiesObject;
		size_t pos{ 0 };
		bool success{ true };
		std::string tempString;

		// get attributes

		// id
		id_generator++;
		m_id = id_generator;

		// name
		tempString = tempUtilitiesObject.extractToken(str, pos, success);
		if (success) 
			m_name = tempString;

		// serial
		pos += (tempString.length() + 1);
		tempString = tempUtilitiesObject.extractToken(str, pos, success);
		if (success)
			m_serial = stoi(tempString);

		// quantity in stock
		pos += (tempString.length() + 1);
		tempString = tempUtilitiesObject.extractToken(str, pos, success);
		if (success)
			m_quantity = stoi(tempString);

		// update m_widthField
		if (m_widthField < tempUtilitiesObject.getFieldWidth())
					m_widthField = tempUtilitiesObject.getFieldWidth();

		// description
		pos += (tempString.length() + 1);
		tempString = tempUtilitiesObject.extractToken(str, pos, success);
		if (success)
			m_description = tempString;
	}

	// returns the name of the current Station object
	const std::string& Station::getItemName() const {
		return m_name;
	}

	// returns the next serial number to be used on the assembly line and increments m_serialNumber
	unsigned int Station::getNextSerialNumber() {
		m_serial++;
		return m_serial - 1;
	}

	// returns the remaining quantity of the current Station object
	unsigned int Station::getQuantity() const {
		return m_quantity;
	}

	// subtracts 1 from the available quantity and doesn't go below 0
	void Station::updateQuantity() {
		if (m_quantity != 0)
					m_quantity--;
	}

	// inserts the content of the current object into first parameter
	void Station::display(std::ostream& os, bool full) const {

		std::cout
			<< "[" << std::setw(3) << std::setfill('0') << m_id << std::setfill(' ') << "] Item: " 
			<< std::setw(m_widthField) << std::left << m_name << std::right << " [" 
			<< std::setw(6) << std::setfill('0') << m_serial << std::setfill(' ') << "]";
			
		if (full) {
			std::cout << " Quantity: " << std::setw(m_widthField) << std::left << m_quantity << std::right
					  << " Description: " << m_description;
		}
			
		std::cout << std::endl;
	}

	// destructor
	Station::~Station() {
	}
}