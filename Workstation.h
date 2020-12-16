/**************************************************************************************************************************
// Name: Bruno Pinto
// Date of completion: 2020/04/10
**************************************************************************************************************************/


#ifndef SDDS_WORKSTATION_H__
#define SDDS_WORKSTATION_H__

#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace std {

	class Workstation : public Station {
		// attributes
		std::deque<CustomerOrder> m_order;
		Workstation *m_pNextStation{ nullptr };

	public:
		// methods
		// custom constructor
		Workstation(const std::string& str);
		// copy constructor - deleted
		Workstation(const Workstation& src) = delete;
		// assignment overload - deleted
		Workstation& operator=(Workstation& src) = delete;
		// move constructor - deleted
		Workstation(Workstation&& src) = delete;
		// move assignment - deleted
		Workstation& operator=(Workstation&& src) = delete;
		// runs a single cycle of the assembly line for the current station
		void runProcess(std::ostream& os);
		// manipulates the order at the front of the queue whether it needs service or not
		bool moveOrder();
		// stores the provided Station object's reference into the m_pNextStation pointer
		void setNextStation(Station& station);
		// returns the next station on the assembly line
		const Workstation* getNextStation() const;
		// manipulates the order at the front of the queue whether it's completed or not
		bool getIfCompleted(CustomerOrder& order);
		// writes the name of the Item this Workstation is responsible for into the parameter
		void display(std::ostream& os);
		// moves the parameter onto the back of the CustomerOrder queue
		Workstation& operator+=(CustomerOrder&& src);
	};
}

#endif
