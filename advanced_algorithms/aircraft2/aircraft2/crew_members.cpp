// units/crew_members.cpp

#include "crew_members.hpp"

// Реализация конструктора для класса Pilot
Pilot::Pilot(int id) : Unit(Unit::Type::PILOT, id) {}  // Передаем тип и id базовому классу

// Пилоты не имеют ручной клади или багажа
int Pilot::getHandLuggageWeight() const { return 0; }
int Pilot::getLuggageWeight() const { return 0; }

// Реализация конструктора для класса FlightAttendant
FlightAttendant::FlightAttendant(int id) : Unit(Unit::Type::FLIGHT_ATTENDANT, id) {}  // Передаем тип и id базовому классу

// Бортпроводники не имеют ручной клади или багажа
int FlightAttendant::getHandLuggageWeight() const { return 0; }
int FlightAttendant::getLuggageWeight() const { return 0; }
