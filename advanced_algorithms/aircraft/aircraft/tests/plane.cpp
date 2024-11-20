#include <iostream>
#include "../units/plane.hpp"
#include "../units/crew_members.hpp"
#include "../units/passengers.hpp"

void runPlaneTests() {
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

    // �������� ����� �������� ������ ����� ���������� ����������
    int expectedWeight = economyPassenger1->getLuggageWeight() + economyPassenger2->getLuggageWeight() +
        businessPassenger->getLuggageWeight() + firstClassPassenger->getLuggageWeight();
    std::cout << ((plane.getTotalLuggageWeight() == expectedWeight)
        ? "Total luggage weight calculation test passed.\n"
        : "Total luggage weight calculation test failed.\n");

    // �������� ���������� ������ ������ ��� Economy
    std::shared_ptr<Unit> extraEconomyPassenger = std::make_shared<EconomyPassenger>(5, 5, 35);
    std::cout << ((!plane.addUnit(extraEconomyPassenger))
        ? "Exceeded economy luggage limit test passed.\n"
        : "Exceeded economy luggage limit test failed.\n");

    // ���������� ������� � �������� ��� �����
    std::shared_ptr<Unit> pilot = std::make_shared<Pilot>(6);
    plane.addUnit(pilot);

    // �������� ����� ���������� �������
    int totalWeightWithCrew = plane.getTotalLuggageWeight();
    std::cout << ((totalWeightWithCrew == expectedWeight)
        ? "Crew member baggage impact test passed.\n"
        : "Crew member baggage impact test failed.\n");

    // ���� � �������, ������ ������ ������ Business
    Plane newPlane(50, 30, 70);
    std::shared_ptr<Unit> exactBusinessPassenger = std::make_shared<BusinessPassenger>(7, 10, 10, 30, 0);
    std::cout << ((newPlane.addUnit(exactBusinessPassenger))
        ? "Exact business luggage limit test passed.\n"
        : "Exact business luggage limit test failed.\n");

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

    // ���������� ��������� � ������ ����� ������ ��� First Class
    Plane exactFirstClassPlane(50, 50, 40);
    std::shared_ptr<Unit> exactFirstClassPassenger = std::make_shared<FirstClassPassenger>(11, 10, 10, 20, 0);
    std::cout << ((exactFirstClassPlane.addUnit(exactFirstClassPassenger))
        ? "Exact first class luggage limit test passed.\n"
        : "Exact first class luggage limit test failed.\n");

    // �������� ���������� ������� ��� ����������� ������ Economy
    Plane fullEconomyPlane(50, 50, 50);
    std::shared_ptr<Unit> econPassenger1 = std::make_shared<EconomyPassenger>(12, 10, 40);
    std::shared_ptr<Unit> econPassenger2 = std::make_shared<EconomyPassenger>(13, 5, 10);
    fullEconomyPlane.addUnit(econPassenger1);
    fullEconomyPlane.addUnit(econPassenger2);
    std::shared_ptr<Unit> crewMember = std::make_shared<Pilot>(14);
    std::cout << ((fullEconomyPlane.addUnit(crewMember))
        ? "Crew member addition to full economy test passed.\n"
        : "Crew member addition to full economy test failed.\n");

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

    // �������� ������ �������, ������� �� ������ ������ �� ����� ���
    Plane pilotLuggageTestPlane(100, 100, 100);

    // �������� ���� ������� � ������� ����������������
    std::shared_ptr<Unit> pilot11 = std::make_shared<Pilot>(100);
    std::shared_ptr<Unit> pilot22 = std::make_shared<Pilot>(101);

    // ���������� ������� �� �������
    pilotLuggageTestPlane.addUnit(pilot11);
    pilotLuggageTestPlane.addUnit(pilot22);

    // ��������, ��� ����� ��� ������ �� ��������� (������ �������� ������ ����)
    int luggageWeightAfterPilots = pilotLuggageTestPlane.getTotalLuggageWeight();
    std::cout << ((luggageWeightAfterPilots == 0) ? "Pilot luggage non-impact test passed.\n" : "Pilot luggage non-impact test failed.\n");

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

    // �������� ����������� �������� ������ ��� ������-������
    Plane maxEconomyLuggagePlane(30, 50, 50);
    std::shared_ptr<Unit> maxEconomyPassenger = std::make_shared<EconomyPassenger>(27, 5, 30);

    // �������� ������-������ � ������� �� ������� ������ ���� ������� ��������
    bool maxEconomyAccepted = maxEconomyLuggagePlane.addUnit(maxEconomyPassenger);
    std::cout << (maxEconomyAccepted ? "Max economy luggage limit test passed.\n" : "Max economy luggage limit test failed.\n");

    // ����� �� ���������� ������ ����� ���������� ����������� �������� ������ ��� ������� � ������-�������
    Plane maxFirstBusinessTestPlane(30, 50, 50);
    std::shared_ptr<Unit> maxFirstClassPassenger = std::make_shared<FirstClassPassenger>(28, 10, 10, 20, 0);
    std::shared_ptr<Unit> maxBusinessPassenger = std::make_shared<BusinessPassenger>(29, 10, 10, 15, 0);

    bool firstClassAdded = maxFirstBusinessTestPlane.addUnit(maxFirstClassPassenger);
    bool businessClassAdded = maxFirstBusinessTestPlane.addUnit(maxBusinessPassenger);

    std::cout << (firstClassAdded ? "First class at max luggage test passed.\n" : "First class at max luggage test failed.\n");
    std::cout << (businessClassAdded ? "Business class at max luggage test passed.\n" : "Business class at max luggage test failed.\n");
}
