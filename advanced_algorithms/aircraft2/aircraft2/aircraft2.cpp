#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "plane.hpp"
#include "crew_members.hpp"
#include "passengers.hpp"

int main() {
    // Переменные для хранения максимального веса багажа
    int maxEconomyLuggage = 0;
    int maxBusinessLuggage = 0;
    int maxFirstClassLuggage = 0;

    // Создаем самолет
    Plane plane(maxEconomyLuggage, maxBusinessLuggage, maxFirstClassLuggage);

    // Читаем строки из ввода
    std::string line;
    int unitId = 0; // Уникальный идентификатор для каждого юнита

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        // Обработка сегментов самолета
        if (type == "FIRST_CLASS_SEGMENT") {
            iss >> maxFirstClassLuggage;
            plane = Plane(maxEconomyLuggage, maxBusinessLuggage, maxFirstClassLuggage); // обновляем самолет
        }
        else if (type == "BUSINESS_CLASS_SEGMENT") {
            iss >> maxBusinessLuggage;
            plane = Plane(maxEconomyLuggage, maxBusinessLuggage, maxFirstClassLuggage); // обновляем самолет
        }
        else if (type == "ECONOMY_CLASS_SEGMENT") {
            iss >> maxEconomyLuggage;
            plane = Plane(maxEconomyLuggage, maxBusinessLuggage, maxFirstClassLuggage); // обновляем самолет
        }
        else {
            // Обработка членов экипажа и пассажиров
            int handLuggage1 = 0, handLuggage2 = 0, luggage1 = 0, luggage2 = 0;

            // Для экипажа
            if (type == "PILOT") {
                std::shared_ptr<Unit> pilot = std::make_shared<Pilot>(unitId++);
                if (plane.addUnit(pilot)) {
                    std::cout << "Pilot with ID " << pilot->getId() << " successfully registered." << std::endl;
                }
                else {
                    std::cout << "!!CANT REGISTER PILOT, ID = " << pilot->getId() << "!!" << std::endl;
                }
            }
            else if (type == "FLIGHT_ATTENDANT") {
                std::shared_ptr<Unit> attendant = std::make_shared<FlightAttendant>(unitId++);
                if (plane.addUnit(attendant)) {
                    std::cout << "Flight attendant with ID " << attendant->getId() << " successfully registered." << std::endl;
                }
                else {
                    std::cout << "!!CANT REGISTER FLIGHT ATTENDANT, ID = " << attendant->getId() << "!!" << std::endl;
                }
            }
            // Для пассажиров
            else if (type == "ECONOMY") {
                iss >> handLuggage1 >> luggage1; // один ручной и один багаж
                std::shared_ptr<Unit> passenger = std::make_shared<EconomyPassenger>(unitId++, handLuggage1, luggage1);
                if (!plane.addUnit(passenger)) {
                    std::cout << "!!CANT REGISTER ECONOMY PASSENGER, ID = " << passenger->getId() << "!!" << std::endl;
                }
            }
            else if (type == "BUSINESS") {
                iss >> handLuggage1 >> handLuggage2 >> luggage1; // два ручных и один багаж
                std::shared_ptr<Unit> passenger = std::make_shared<BusinessPassenger>(unitId++, handLuggage1, handLuggage2, luggage1, 0);
                if (!plane.addUnit(passenger)) {
                    std::cout << "!!CANT REGISTER BUSINESS PASSENGER, ID = " << passenger->getId() << "!!" << std::endl;
                }
            }
            else if (type == "FIRST_CLASS") {
                iss >> handLuggage1 >> handLuggage2 >> luggage1 >> luggage2; // два ручных и два багажа
                std::shared_ptr<Unit> passenger = std::make_shared<FirstClassPassenger>(unitId++, handLuggage1, handLuggage2, luggage1, luggage2);
                if (!plane.addUnit(passenger)) {
                    std::cout << "!!CANT REGISTER FIRST CLASS PASSENGER, ID = " << passenger->getId() << "!!" << std::endl;
                }
            }
        }
    }

    // Выводим общий вес багажа на борту
    std::cout << "Total luggage weight on the plane: " << plane.getTotalLuggageWeight() << " kg" << std::endl;

    return 0;
}
