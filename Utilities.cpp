/**************************************************************************************************************************
// Name: Bruno Pinto
// Date of completion: 2020/04/10
**************************************************************************************************************************/


#include <iostream>
#include <string>
#include "Utilities.h"

namespace std {

	// initializing static variable
	char Utilities::m_delimiter = '\0';

	// sets the field width of the current object to the value of the parameter
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	// returns the field width of the current object
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	// extracts tokens from the first parameter
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string tempField{};

		// matches next_pos against the last character of the file
		// next_pos - 1 because it's always position + 1
		if (next_pos - 1 != str.length()) {

			try {

				// reasoning behind the 2nd argument:
				// 1. find the delimiter starting at next_pos -> this is the position the delimiter is
				// 2. subtract that position from next_pos to get the length
				tempField = str.substr(next_pos, str.find(m_delimiter, next_pos) - next_pos);


				if (tempField == "") {
					more = false;
					throw "ERROR: Two delimiters with no tokens between them!";
				}
				else {
					more = true;
					if (m_widthField < tempField.length()) {
						setFieldWidth(tempField.length());
					}
				}
			}

			catch (const char* errorMsg) {
				std::cout << errorMsg << std::endl;
			}

		}
		else {
			more = false;
		}

		return tempField;
	}

	// sets the delimiter for this class to the character received
	void Utilities::setDelimiter(const char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	// returns the delimiter character
	char Utilities::getDelimiter() {
		return m_delimiter;
	}

	// destructor
	Utilities::~Utilities() {
	}
	
}