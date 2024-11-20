#ifndef CREW_MEMBERS_HPP
#define CREW_MEMBERS_HPP

#include "unit.hpp"
#include <memory>

// Класс для пилота
class Pilot : public Unit {
public:
    Pilot(int id);  
    int getHandLuggageWeight() const override;  
    int getLuggageWeight() const override;       
};

// Класс для бортпроводника
class FlightAttendant : public Unit {
public:
    FlightAttendant(int id);  
    int getHandLuggageWeight() const override;  
    int getLuggageWeight() const override;      
};

#endif 
