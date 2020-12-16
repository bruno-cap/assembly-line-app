/**************************************************************************************************************************
// Name: Bruno Pinto
// Date of completion: 2020/04/10
**************************************************************************************************************************/


#include <iostream>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
#include "Workstation.h"

namespace std {

	// custom constructor
	LineManager::LineManager(const std::string& filename, std::vector<Workstation*>& addressesOfWorkstationObjects,
		std::vector<CustomerOrder>& CustomerOrderObjectsToBeFilled) {

			Utilities tempUtilitiesObject;

			std::string startingStation;
			std::string nextStation;

			std::string stringLine;
			size_t pos{ 0 };
			bool success{ true };
			std::string tempString;

			Utilities::setDelimiter('|');
			std::ifstream file(filename);
			if (!file)
			{
				std::cerr << "ERROR: Cannot open file [" << filename << "].\n";
				return;
			}
			do
			{
				std::getline(file, stringLine);

				// if the previous operation failed, the "file" object is
				//   in error mode
				if (file)
				{
					pos = 0;
					// read station / next station pairs from the file
					startingStation = tempUtilitiesObject.extractToken(stringLine, pos, success);
					pos += (startingStation.length() + 1);
					// nextStation will be blank if there are no next stations
					nextStation = tempUtilitiesObject.extractToken(stringLine, pos, success);
					bool foundCurrent = false;
					bool foundNext = false;

					// traverse the addressesOfWorkshopObjects vector to try to find a name match
					for (size_t i = 0; i < addressesOfWorkstationObjects.size() && !foundCurrent; i++) {
						if (addressesOfWorkstationObjects.at(i)->getItemName() == startingStation) {	// found current
							foundCurrent = true;
							// if next station is not empty (meaning it's not the last element - we have to setup the nextStation pointer)
							// if nextStation is empty, we're not doing anything - m_pNextStation will remain nullptr as per initialization
							if (!nextStation.empty()) {
								for (size_t j = 0; j < addressesOfWorkstationObjects.size() && !foundNext; j++) {
									if (addressesOfWorkstationObjects.at(j)->getItemName() == nextStation) {	// found next
										foundNext = true;
										addressesOfWorkstationObjects.at(i)->setNextStation(*addressesOfWorkstationObjects.at(j));
									}
								}
							}
						}
					}
				}
			} while (file);
			file.close();


			// moves all the CustomerOrder objects onto the back of the ToBeFilled queue
			for (size_t i = 0; i < CustomerOrderObjectsToBeFilled.size(); i++) {
				ToBeFilled.push_back(std::move(CustomerOrderObjectsToBeFilled.at(i)));
				m_cntCustomerOrder++;
			}

			// copies all Workstation objects to the Assembly Line container
			for (Workstation* i : addressesOfWorkstationObjects) {
				AssemblyLine.push_back(i);
			}
	}

	// performs one cycle of operations on the assembly line
	bool LineManager::run(std::ostream& os) {
		static size_t iterationNo{ 1 };

		os << "Line Manager Iteration: " << iterationNo << std::endl;

		bool foundFirstStation = false;
		bool isMentionedInNextPos = false;
		int indexStartingPos{ -1 };			// safe state - as we're referring to indexes, -1 is an impossible value

		for (size_t i = 0; i < AssemblyLine.size() && !foundFirstStation; i++) {

			for (size_t j = 0; j < AssemblyLine.size() && !isMentionedInNextPos; j++) {

				if (AssemblyLine.at(j)->getNextStation() == nullptr) {
					isMentionedInNextPos = false;
				}
				else if (AssemblyLine.at(j)->getNextStation()->getItemName() == AssemblyLine.at(i)->getItemName()) {
					isMentionedInNextPos = true;
				}
				else {
					isMentionedInNextPos = false;
				}

			}

			if (!isMentionedInNextPos) {
				foundFirstStation = true;
				indexStartingPos = i;
			}
			else {
				isMentionedInNextPos = false;
			}
		}


		// moves order to the starting point of the process line
		if (!ToBeFilled.empty()) {
			*AssemblyLine.at(indexStartingPos) += std::move(ToBeFilled.front());
			ToBeFilled.pop_front();
		}

		// loops through all stations on the assembly line and run one cycle of the Station's process
		for (Workstation* i : AssemblyLine) {
			i->runProcess(os);
		}

		// checks if CustomerOrder is complete. Is so, move to Completed. Otherwise, move further down AssemblyLine
		CustomerOrder tempCustomerOrder;
		for (Workstation* i : AssemblyLine) {
			if (i->getIfCompleted(tempCustomerOrder)) {
				Completed.push_back(std::move(tempCustomerOrder));
			}
			else {
				i->moveOrder();
			}
		}

		iterationNo++;

		return Completed.size() == m_cntCustomerOrder;
	}

	// displays all the orders that were completed
	void LineManager::displayCompletedOrders(std::ostream& os) const {
		for (size_t i = 0; i < Completed.size(); i++) {
			Completed.at(i).display(os);
		}
	}

	// displays all stations on the assembly line in the order they were received from the client
	void LineManager::displayStations() const {
		for (Workstation* i : AssemblyLine) {
			i->display(std::cout);
		}
	}

	// displays all stations on the assembly line in the order they are linked
	void LineManager::displayStationsSorted() const {

		bool foundFirstStation = false;
		bool isMentionedInNextPos = false;
		int indexStartingPos{ -1 };

		for (size_t i = 0; i < AssemblyLine.size() && !foundFirstStation; i++) {

			for (size_t j = 0; j < AssemblyLine.size() && !isMentionedInNextPos; j++) {

				if (AssemblyLine.at(j)->getNextStation() == nullptr) {
					isMentionedInNextPos = false;
				}
				else if (AssemblyLine.at(j)->getNextStation()->getItemName() == AssemblyLine.at(i)->getItemName()) {
					isMentionedInNextPos = true;
				}
				else {
					isMentionedInNextPos = false;
				}

			}

			if (!isMentionedInNextPos) {
				foundFirstStation = true;
				indexStartingPos = i;
			}
			else {
				isMentionedInNextPos = false;
			}
		}

		// prints first workstation
		AssemblyLine.at(indexStartingPos)->display(std::cout);
		Workstation* printNext = const_cast <Workstation*>(AssemblyLine.at(indexStartingPos)->getNextStation());

		// we start at 1 because we printed the 1st record (pos 0) already
		for (size_t i = 1; i < AssemblyLine.size(); i++) {
			if (i != 1)		// we already have printNext setup for the first iteration
				printNext = const_cast<Workstation*>(printNext->getNextStation());
			printNext->display(std::cout);
		}
	}
}