#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include "units/plane.hpp"
#include "units/crew_members.hpp"
#include "units/passengers.hpp"

int main() {

    int maxEconomyLuggage = 0;
    int maxBusinessLuggage = 0;
    int maxFirstClassLuggage = 0;

    Plane plane(maxEconomyLuggage, maxBusinessLuggage, maxFirstClassLuggage);

    int unitId = 0;

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "STOP") {
            break;
        }

        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type != "FIRST_CLASS_SEGMENT" && type != "BUSINESS_CLASS_SEGMENT" &&
            type != "ECONOMY_CLASS_SEGMENT" && type != "PILOT" &&
            type != "FLIGHT_ATTENDANT" && type != "ECONOMY" &&
            type != "BUSINESS" && type != "FIRST_CLASS") {
            std::cout << "Invalid input: " << line << std::endl;
            continue;
        }

        if (type == "FIRST_CLASS_SEGMENT") {
            iss >> maxFirstClassLuggage;
            plane = Plane(maxEconomyLuggage, maxBusinessLuggage, maxFirstClassLuggage);
        }
        else if (type == "BUSINESS_CLASS_SEGMENT") {
            iss >> maxBusinessLuggage;
            plane = Plane(maxEconomyLuggage, maxBusinessLuggage, maxFirstClassLuggage);
        }
        else if (type == "ECONOMY_CLASS_SEGMENT") {
            iss >> maxEconomyLuggage;
            plane = Plane(maxEconomyLuggage, maxBusinessLuggage, maxFirstClassLuggage);
        }
        else {
            int handLuggage1 = 0, handLuggage2 = 0, luggage1 = 0, luggage2 = 0;

            if (type == "PILOT") {
                std::shared_ptr<Unit> pilot = std::make_shared<Pilot>(unitId++);
                plane.addUnit(pilot);
            }
            else if (type == "FLIGHT_ATTENDANT") {
                std::shared_ptr<Unit> attendant = std::make_shared<FlightAttendant>(unitId++);
                plane.addUnit(attendant);
            }
            else if (type == "ECONOMY") {
                iss >> handLuggage1 >> luggage1;
                std::shared_ptr<Unit> economyPassenger = std::make_shared<EconomyPassenger>(unitId++, handLuggage1, luggage1);
                if (!plane.addUnit(economyPassenger)) {
                    std::cout << "!!CANT REGISTER ECONOMY PASSENGER, ID = " << economyPassenger->getId() << "!!\n";
                }
            }
            else if (type == "BUSINESS") {
                iss >> handLuggage1 >> handLuggage2 >> luggage1;
                std::shared_ptr<Unit> businessPassenger = std::make_shared<BusinessPassenger>(unitId++, handLuggage1, handLuggage2, luggage1, 0);
                if (!plane.addUnit(businessPassenger)) {
                    std::cout << "!!CANT REGISTER BUSINESS PASSENGER, ID = " << businessPassenger->getId() << "!!\n";
                }
            }
            else if (type == "FIRST_CLASS") {
                iss >> handLuggage1 >> handLuggage2 >> luggage1 >> luggage2;
                std::shared_ptr<Unit> firstClassPassenger = std::make_shared<FirstClassPassenger>(unitId++, handLuggage1, handLuggage2, luggage1, luggage2);
                if (!plane.addUnit(firstClassPassenger)) {
                    std::cout << "!!CANT REGISTER FIRST CLASS PASSENGER, ID = " << firstClassPassenger->getId() << "!!\n";
                }
            }
        }
    }

    std::cout << "Total luggage weight: " << plane.getTotalLuggageWeight() << " kg\n";
    return 0;
}
