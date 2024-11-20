#ifndef CREW_MEMBERS_HPP
#define CREW_MEMBERS_HPP

#include "unit.hpp"
#include <memory>

class Pilot : public Unit {
public:
    Pilot(int id);  
    int getHandLuggageWeight() const override;  
    int getLuggageWeight() const override;       
};

class FlightAttendant : public Unit {
public:
    FlightAttendant(int id);  
    int getHandLuggageWeight() const override;  
    int getLuggageWeight() const override;      
};

#endif 
