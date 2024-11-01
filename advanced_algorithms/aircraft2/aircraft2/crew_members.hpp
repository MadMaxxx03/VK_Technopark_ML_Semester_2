// units/crew_members.hpp

#ifndef CREW_MEMBERS_HPP
#define CREW_MEMBERS_HPP

#include "unit.hpp"
#include <memory>

// Класс для пилота
class Pilot : public Unit {
public:
    Pilot(int id);  // Конструктор
    int getHandLuggageWeight() const override;  // Переопределение метода
    int getLuggageWeight() const override;       // Переопределение метода
};

// Класс для бортпроводника
class FlightAttendant : public Unit {
public:
    FlightAttendant(int id);  // Конструктор
    int getHandLuggageWeight() const override;  // Переопределение метода
    int getLuggageWeight() const override;       // Переопределение метода
};

#endif // CREW_MEMBERS_HPP
