/**************************************************************************************************************************
// Name: Bruno Pinto
// Date of completion: 2020/04/10
**************************************************************************************************************************/


#ifndef SDDS_LINEMANAGER_H__
#define SDDS_LINEMANAGER_H__

#include <vector>
#include "Workstation.h"

namespace std {

	class LineManager {
		// attributes
		std::vector<Workstation*> AssemblyLine{};
		std::deque<CustomerOrder> ToBeFilled{};
		std::deque<CustomerOrder> Completed{};
		unsigned int m_cntCustomerOrder{ 0 };

	public:
		// methods
		// custom constructor
		LineManager(const std::string& filename, std::vector<Workstation*>& addressesOfWorkshopObjects,
			std::vector<CustomerOrder>& CustomerOrderObjectsToBeFilled);
		// performs one cycle of operations on the assembly line
		bool run(std::ostream& os);
		// displays all the orders that were completed
		void displayCompletedOrders(std::ostream& os) const;
		// displays all stations on the assembly line in the order they were received from the client
		void displayStations() const;
		// displays all stations on the assembly line in the order they are linked
		void displayStationsSorted() const;
	};
}

#endif