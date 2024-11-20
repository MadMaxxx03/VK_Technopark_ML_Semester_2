#include <iostream>
#include "../units/passengers.hpp"

void runPassengersTests() {
    EconomyPassenger econ1(3, 5, 15);
    BusinessPassenger bus1(4, 7, 8, 20, 0);
    FirstClassPassenger first1(5, 10, 12, 25, 30);

    // ���� ��� ������ EconomyPassenger
    std::cout << ((econ1.getHandLuggageWeight() == 5 && econ1.getLuggageWeight() == 15)
        ? "EconomyPassenger luggage weight test passed.\n" : "EconomyPassenger luggage weight test failed.\n");

    // ���� ��� ������ BusinessPassenger
    std::cout << ((bus1.getHandLuggageWeight() == 15 && bus1.getLuggageWeight() == 20)
        ? "BusinessPassenger luggage weight test passed.\n" : "BusinessPassenger luggage weight test failed.\n");

    // ���� ��� ������ FirstClassPassenger
    std::cout << ((first1.getHandLuggageWeight() == 22 && first1.getLuggageWeight() == 55)
        ? "FirstClassPassenger luggage weight test passed.\n" : "FirstClassPassenger luggage weight test failed.\n");

    // ���� � ����������� ����������� ������ ����
    EconomyPassenger econ2(6, 0, 10);
    std::cout << ((econ2.getHandLuggageWeight() == 0 && econ2.getLuggageWeight() == 10)
        ? "Multiple EconomyPassenger instance test passed.\n" : "Multiple EconomyPassenger instance test failed.\n");

    // ���� �� ���������� ID ����������
    std::cout << ((econ1.getId() != econ2.getId())
        ? "Unique passenger ID test passed.\n" : "Unique passenger ID test failed.\n");

    // ���� ��� ���������� �������� ������ ��� EconomyPassenger
    EconomyPassenger econ3(7, 10, 20);
    std::cout << ((econ3.getHandLuggageWeight() == 10 && econ3.getLuggageWeight() == 20)
        ? "EconomyPassenger boundary luggage test passed.\n" : "EconomyPassenger boundary luggage test failed.\n");

    // ���� �� ���������� ���� ������ BusinessPassenger
    BusinessPassenger bus2(8, 15, 10, 40, 10);
    std::cout << ((bus2.getHandLuggageWeight() == 25 && bus2.getLuggageWeight() == 50)
        ? "BusinessPassenger max luggage test passed.\n" : "BusinessPassenger max luggage test failed.\n");

    // ���� ��� FirstClassPassenger � ������� �������
    FirstClassPassenger first2(9, 0, 0, 0, 0);
    std::cout << ((first2.getHandLuggageWeight() == 0 && first2.getLuggageWeight() == 0)
        ? "FirstClassPassenger zero luggage test passed.\n" : "FirstClassPassenger zero luggage test failed.\n");

    // ���� ��� ���������� ������ ���� ������ FirstClassPassenger
    std::cout << ((first1.getHandLuggageWeight() + first1.getLuggageWeight() == 77)
        ? "FirstClassPassenger total luggage weight test passed.\n" : "FirstClassPassenger total luggage weight test failed.\n");

    // ���� �� ���������� ���������� ������ ���������� ���������� ������ ����
    EconomyPassenger econ4(10, 8, 12);
    std::cout << ((econ1.getLuggageWeight() + econ2.getLuggageWeight() + econ4.getLuggageWeight() == 37)
        ? "Total EconomyPassenger luggage weight test passed.\n" : "Total EconomyPassenger luggage weight test failed.\n");
}
