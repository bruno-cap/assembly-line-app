/**************************************************************************************************************************
// Name: Bruno Pinto
// Date of completion: 2020/04/10
**************************************************************************************************************************/


#ifndef SDDS_UTILITIES_H__
#define SDDS_UTILITIES_H__

#include <string>

namespace std {

	class Utilities {
		// attributes
		size_t m_widthField = 1;
		static char m_delimiter;
	public:
		// methods
		// sets the field width of the current object to the value of the parameter
		void setFieldWidth(size_t newWidth);
		// returns the field width of the current object
		size_t getFieldWidth() const;
		// extracts tokens from the first parameter
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		// sets the delimiter for this class to the character received
		static void setDelimiter(char newDelimiter);
		// returns the delimiter character
		static char getDelimiter();
		// destructor
		virtual ~Utilities();
	};

}

#endif