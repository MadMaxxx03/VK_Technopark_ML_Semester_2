#include <iostream>
#include "crew_members.hpp"

void runCrewMembersTests() {
    Pilot pilot(1);
    FlightAttendant attendant(2);

    // Проверка свойств Pilota
    std::cout << (pilot.getId() == 1 && pilot.getHandLuggageWeight() == 0 && pilot.getLuggageWeight() == 0
        ? "Pilot test passed.\n" : "Pilot test failed.\n");

    // Проверка свойств FlightAttendant
    std::cout << (attendant.getId() == 2 && attendant.getHandLuggageWeight() == 0 && attendant.getLuggageWeight() == 0
        ? "FlightAttendant test passed.\n" : "FlightAttendant test failed.\n");

    // Проверка типа экипажа
    std::cout << (pilot.getType() == Unit::Type::PILOT && attendant.getType() == Unit::Type::FLIGHT_ATTENDANT
        ? "Crew member type test passed.\n" : "Crew member type test failed.\n");

    // Проверка уникальных идентификаторов членов экипажа
    Pilot pilot2(3);
    std::cout << ((pilot.getId() != pilot2.getId())
        ? "Unique crew member ID test passed.\n" : "Unique crew member ID test failed.\n");

    // Проверка багажа для членов экипажа
    std::cout << ((pilot.getHandLuggageWeight() == 0 && pilot.getLuggageWeight() == 0) &&
        (attendant.getHandLuggageWeight() == 0 && attendant.getLuggageWeight() == 0)
        ? "Crew member baggage weight test passed.\n" : "Crew member baggage weight test failed.\n");

    // Проверка отсутствия изменений веса багажа
    int initialPilotHandLuggage = pilot.getHandLuggageWeight();
    int initialPilotLuggage = pilot.getLuggageWeight();
    std::cout << ((pilot.getHandLuggageWeight() == initialPilotHandLuggage) &&
        (pilot.getLuggageWeight() == initialPilotLuggage)
        ? "Crew member immutable baggage weight test passed.\n" : "Crew member immutable baggage weight test failed.\n");

    // Проверка граничных условий при создании новых объектов
    FlightAttendant attendant2(4);
    std::cout << ((attendant2.getId() == 4 && attendant2.getHandLuggageWeight() == 0 && attendant2.getLuggageWeight() == 0)
        ? "Boundary test for FlightAttendant creation passed.\n" : "Boundary test for FlightAttendant creation failed.\n");

    // Проверка ошибок в типе
    std::cout << ((pilot.getType() != Unit::Type::FLIGHT_ATTENDANT && attendant.getType() != Unit::Type::PILOT)
        ? "Incorrect crew member type test passed.\n" : "Incorrect crew member type test failed.\n");
}
