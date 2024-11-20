#ifndef UNIT_HPP
#define UNIT_HPP

#include <memory>

class Unit {
public:
    enum class Type {
        PILOT,
        FLIGHT_ATTENDANT,
        ECONOMY,
        BUSINESS,
        FIRST_CLASS
    };

    Unit(Type type, int id) : type_(type), id_(id) {} 

    virtual ~Unit() = default;

    virtual int getLuggageWeight() const = 0; 
    virtual int getHandLuggageWeight() const = 0; 

    int getId() const { return id_; } 
    Type getType() const { return type_; } 

private:
    Type type_; 
    int id_; 
};

#endif 
