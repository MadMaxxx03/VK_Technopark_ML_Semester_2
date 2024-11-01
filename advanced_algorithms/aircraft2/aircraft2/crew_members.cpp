// units/crew_members.cpp

#include "crew_members.hpp"

// ���������� ������������ ��� ������ Pilot
Pilot::Pilot(int id) : Unit(Unit::Type::PILOT, id) {}  // �������� ��� � id �������� ������

// ������ �� ����� ������ ����� ��� ������
int Pilot::getHandLuggageWeight() const { return 0; }
int Pilot::getLuggageWeight() const { return 0; }

// ���������� ������������ ��� ������ FlightAttendant
FlightAttendant::FlightAttendant(int id) : Unit(Unit::Type::FLIGHT_ATTENDANT, id) {}  // �������� ��� � id �������� ������

// �������������� �� ����� ������ ����� ��� ������
int FlightAttendant::getHandLuggageWeight() const { return 0; }
int FlightAttendant::getLuggageWeight() const { return 0; }
