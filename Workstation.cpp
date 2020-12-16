/**************************************************************************************************************************
// Name: Bruno Pinto
// Date of completion: 2020/04/10
**************************************************************************************************************************/


#include <iostream>
#include "Workstation.h"


namespace std {

	// custom constructor
	Workstation::Workstation(const std::string& str) : Station(str) {
		m_pNextStation = nullptr;
	}

	// runs a single cycle of the assembly line for the current station
	void Workstation::runProcess(std::ostream& os) {
		if (!m_order.empty()) {
			m_order.front().fillItem(*this, os);
		}
	}

	// manipulates the order at the front of the queue whether it needs service or not
	bool Workstation::moveOrder() {
		bool requiresMoving = false;

			if (!m_order.empty() && m_order.front().isItemFilled(getItemName())) {
				*m_pNextStation += std::move(m_order.front());
				m_order.pop_front();
				requiresMoving = true;
			}

		return requiresMoving;
	}

	// stores the provided Station object's reference into the m_pNextStation pointer
	void Workstation::setNextStation(Station& station) {
		m_pNextStation = dynamic_cast<Workstation*>(&station);
	}

	// returns the next station on the assembly line
	const Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}

	// manipulates the order at the front of the queue whether it's completed or not
	bool Workstation::getIfCompleted(CustomerOrder& order) {

		bool success = false;

		// if order is empty or item at the front is not filled, returns false
		// otherwise, move item at the front to order and returns true
		if (!m_order.empty() && m_order.front().isOrderFilled()) {
			order = std::move(m_order.front());
			m_order.pop_front();
			success = true;
		}

		return success;
	}

	// writes the name of the Item this Workstation is responsible for into the parameter
	void Workstation::display(std::ostream& os) {

		os << this->getItemName() << " --> ";

		// if m_pNextStation exists
		if (m_pNextStation != nullptr) {
			os << m_pNextStation->getItemName();
		}
		// otherwise, if it doesn't
		else {
			os << "END OF LINE";
		}

		os << std::endl;
	}

	// moves the parameter onto the back of the CustomerOrder queue
	Workstation& Workstation::operator+=(CustomerOrder&& src) {
		m_order.push_back(std::move(src));
		return *this;
	}
}