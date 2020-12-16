/**************************************************************************************************************************
// Name: Bruno Pinto
// Date of completion: 2020/04/10
**************************************************************************************************************************/


#ifndef SDDS_STATION_H__
#define SDDS_STATION_H__

#include <string>

namespace std {

	class Station {
		// attributes
		int m_id;
		std::string m_name{};
		std::string m_description{};
		unsigned int m_serial{ 0 };
		unsigned int m_quantity{ 0 };
		static size_t m_widthField;
		static size_t id_generator;

	public:
		// methods
		// custom constructor
		Station(const std::string& str);
		// returns the name of the current Station object
		const std::string& getItemName() const;
		// returns the next serial number to be used on the assembly line and increments m_serialNumber
		unsigned int getNextSerialNumber();
		// returns the remaining quantity of the current Station object
		unsigned int getQuantity() const;
		// subtracts 1 from the available quantity and doesn't go below 0
		void updateQuantity();
		// inserts the content of the current object into first parameter
		void display(std::ostream& os, bool full) const;
		// destructor
		virtual ~Station();
	};
}

#endif