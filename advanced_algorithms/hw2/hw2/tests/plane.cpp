#include <iostream>
#include <cassert>
#include "../units/plane.hpp"
#include "../units/crew_members.hpp"
#include "../units/passengers.hpp"

int main() {
    Plane plane(50, 50, 50);

    // ���������� ���������� ���������� ������ �������
    std::shared_ptr<Unit> economyPassenger1 = std::make_shared<EconomyPassenger>(1, 5, 25);
    std::shared_ptr<Unit> economyPassenger2 = std::make_shared<EconomyPassenger>(2, 10, 20);
    std::shared_ptr<Unit> businessPassenger = std::make_shared<BusinessPassenger>(3, 7, 8, 15, 0);
    std::shared_ptr<Unit> firstClassPassenger = std::make_shared<FirstClassPassenger>(4, 10, 10, 15, 15);

    plane.addUnit(economyPassenger1);
    plane.addUnit(economyPassenger2);
    plane.addUnit(businessPassenger);
    plane.addUnit(firstClassPassenger);

    // �������� ���������� ������ ������ ��� Economy
    std::shared_ptr<Unit> extraEconomyPassenger = std::make_shared<EconomyPassenger>(5, 5, 35);
    std::cout << ((!plane.addUnit(extraEconomyPassenger))
        ? "Exceeded economy luggage limit test passed.\n"
        : "Exceeded economy luggage limit test failed.\n");

    // ���������� ��������� � ����������� ���������� ������ ��� ���� �������
    Plane overloadedPlane(30, 30, 30);
    std::shared_ptr<Unit> heavyEconomy = std::make_shared<EconomyPassenger>(8, 15, 30);
    std::shared_ptr<Unit> heavyBusiness = std::make_shared<BusinessPassenger>(9, 10, 10, 25, 0);
    std::shared_ptr<Unit> heavyFirstClass = std::make_shared<FirstClassPassenger>(10, 10, 15, 20, 20);
    overloadedPlane.addUnit(heavyEconomy);
    overloadedPlane.addUnit(heavyBusiness);
    std::cout << ((!overloadedPlane.addUnit(heavyFirstClass))
        ? "Exceeded total plane luggage limit test passed.\n"
        : "Exceeded total plane luggage limit test failed.\n");

    // ����������� �� ���������� ������� (����. 2 ������)
    Plane testPlane1(100, 100, 100);
    std::shared_ptr<Unit> pilot1 = std::make_shared<Pilot>(15);
    std::shared_ptr<Unit> pilot2 = std::make_shared<Pilot>(16);
    std::shared_ptr<Unit> pilot3 = std::make_shared<Pilot>(17);

    testPlane1.addUnit(pilot1);
    testPlane1.addUnit(pilot2);
    std::cout << ((!testPlane1.addUnit(pilot3))
        ? "Pilot limit test passed.\n"
        : "Pilot limit test failed.\n");

    // ����������� �� ���������� ��������������� (����. 6 ���������������)
    Plane testPlane2(100, 100, 100);
    bool flightAttendantLimitPassed = true;
    for (int i = 0; i < 6; ++i) {
        if (!testPlane2.addUnit(std::make_shared<FlightAttendant>(20 + i))) {
            flightAttendantLimitPassed = false;
            break;
        }
    }
    flightAttendantLimitPassed = flightAttendantLimitPassed && !testPlane2.addUnit(std::make_shared<FlightAttendant>(26));
    std::cout << (flightAttendantLimitPassed ? "Flight attendant limit test passed.\n" : "Flight attendant limit test failed.\n");

    // ����������� �� ���������� ���������� ������-������ (����. 200 ����������)
    Plane testPlane3(1000, 1000, 1000);
    bool economyPassengerLimitPassed = true;
    for (int i = 0; i < 200; ++i) {
        if (!testPlane3.addUnit(std::make_shared<EconomyPassenger>(100 + i, 5, 5))) {
            economyPassengerLimitPassed = false;
            break;
        }
    }
    economyPassengerLimitPassed = economyPassengerLimitPassed && !testPlane3.addUnit(std::make_shared<EconomyPassenger>(300, 5, 5));
    std::cout << (economyPassengerLimitPassed ? "Economy passenger limit test passed.\n" : "Economy passenger limit test failed.\n");

    // ����������� �� ���������� ���������� ������-������ (����. 10 ����������)
    Plane testPlane4(1000, 1000, 1000);
    bool businessPassengerLimitPassed = true;
    for (int i = 0; i < 10; ++i) {
        if (!testPlane4.addUnit(std::make_shared<BusinessPassenger>(400 + i, 5, 5, 10, 10))) {
            businessPassengerLimitPassed = false;
            break;
        }
    }
    businessPassengerLimitPassed = businessPassengerLimitPassed && !testPlane4.addUnit(std::make_shared<BusinessPassenger>(410, 5, 5, 10, 10));
    std::cout << (businessPassengerLimitPassed ? "Business passenger limit test passed.\n" : "Business passenger limit test failed.\n");

    // ����������� �� ���������� ���������� ������� ������ (����. 4 ���������)
    Plane testPlane5(100, 100, 100);
    bool firstClassPassengerLimitPassed = true;
    for (int i = 0; i < 4; ++i) {
        if (!testPlane5.addUnit(std::make_shared<FirstClassPassenger>(500 + i, 5, 5, 10, 10))) {
            firstClassPassengerLimitPassed = false;
            break;
        }
    }
    firstClassPassengerLimitPassed = firstClassPassengerLimitPassed && !testPlane5.addUnit(std::make_shared<FirstClassPassenger>(504, 5, 5, 10, 10));
    std::cout << (firstClassPassengerLimitPassed ? "First class passenger limit test passed.\n" : "First class passenger limit test failed.\n");

    // ���������� ������ � ������-�����, ����� �������� ����� ������-������ ��������
    Plane planeWithLimitedBusinessLuggage(50, 20, 50);
    std::shared_ptr<Unit> businessPassenger1 = std::make_shared<BusinessPassenger>(18, 10, 8, 15, 0);
    std::shared_ptr<Unit> businessPassenger2 = std::make_shared<BusinessPassenger>(19, 10, 8, 10, 0);
    std::shared_ptr<Unit> economyPassenger = std::make_shared<EconomyPassenger>(20, 5, 10);

    // ���������� ������� ��������� ������-������, ������� ������ ������ ��������� ����� � ����� ������
    planeWithLimitedBusinessLuggage.addUnit(businessPassenger1);

    // ���������� ������� ��������� ������-������, ��� ����� ������ ���� ��������� � ����� ������-������
    bool movedToEconomy = planeWithLimitedBusinessLuggage.addUnit(businessPassenger2);

    // ��������, ��� �� ����� ������� ��������� � ������-�����
    std::cout << (movedToEconomy ? "Business luggage moved to economy test passed.\n" : "Business luggage moved to economy test failed.\n");

    // ��������, ��� ����� ��������� ������-������ ����������� ��������� ����� �������� ������ ������-������
    bool economyAdded = planeWithLimitedBusinessLuggage.addUnit(economyPassenger);
    std::cout << (economyAdded ? "Economy luggage added after business moved test passed.\n" : "Economy luggage added after business moved test failed.\n");

    // ���������� ������, ����� ����� � ������-������ ������������ ��� ����� ������ ������-������
    Plane fullEconomyLuggagePlane(10, 10, 50);
    std::shared_ptr<Unit> fullEconomyPassenger = std::make_shared<EconomyPassenger>(21, 5, 10);
    std::shared_ptr<Unit> overflowBusinessPassenger = std::make_shared<BusinessPassenger>(22, 5, 5, 20, 0);

    // ������-����� ����������� ������ ����������
    fullEconomyLuggagePlane.addUnit(fullEconomyPassenger);

    // ���������� ��������� ������-������, ������� ��������� ����� ������-������
    bool overflowBusinessRejected = !fullEconomyLuggagePlane.addUnit(overflowBusinessPassenger);
    std::cout << (overflowBusinessRejected ? "Business luggage rejected due to full economy test passed.\n" : "Business luggage rejected due to full economy test failed.\n");

    // ���������� ��������� � ������ ������, �� ��� ������
    Plane handLuggageOnlyPlane(100, 100, 100);
    std::shared_ptr<Unit> handLuggageOnlyPassenger = std::make_shared<EconomyPassenger>(25, 5, 0);

    // �������� � ������ ������ ������ ���� �������� ��� ���������� ������ ���� ������
    handLuggageOnlyPlane.addUnit(handLuggageOnlyPassenger);
    int weightAfterHandLuggage = handLuggageOnlyPlane.getTotalLuggageWeight();
    std::cout << ((weightAfterHandLuggage == 0) ? "Hand luggage only test passed.\n" : "Hand luggage only test failed.\n");

    // �������� ���������� ������ ��� ��������� ������� ������, ����� ��� ����� ��������� ����� ������������ ��������
    Plane firstClassOverflowTestPlane(100, 100, 20);
    std::shared_ptr<Unit> largeFirstClassPassenger = std::make_shared<FirstClassPassenger>(26, 10, 10, 25, 0);

    // ��������, ��� ����� ������������ � ������-�����
    bool firstClassMovedToEconomy = firstClassOverflowTestPlane.addUnit(largeFirstClassPassenger);
    std::cout << (firstClassMovedToEconomy ? "First class luggage moved to economy test passed.\n" : "First class luggage moved to economy test failed.\n");

    Plane plane11(100, 50, 30);

    // �������� ���������� ������-������ � �������.
    std::shared_ptr<Unit> passenger1 = std::make_shared<EconomyPassenger>(1, 20, 10);
    std::shared_ptr<Unit> passenger2 = std::make_shared<EconomyPassenger>(2, 15, 5);
    std::shared_ptr<Unit> passenger3 = std::make_shared<EconomyPassenger>(3, 25, 8);

    plane11.addUnit(passenger1);
    plane11.addUnit(passenger2);
    plane11.addUnit(passenger3);

    // ������� ������� ������ ����, ��� ����.
    assert(!plane11.removeLuggageForWeight(50) && "Should not be able to remove more weight than available!");

    std::cout << "All removeLuggageForWeight tests passed.\n";
    return 0;
}