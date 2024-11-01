#ifndef PASSENGERS_HPP
#define PASSENGERS_HPP

#include "unit.hpp"

class EconomyPassenger : public Unit {
public:
    EconomyPassenger(int id, int handLuggage, int luggage);
    int getLuggageWeight() const override;
    int getHandLuggageWeight() const override;

private:
    int handLuggage_;
    int luggage_;
};

class BusinessPassenger : public Unit {
public:
    BusinessPassenger(int id, int handLuggage1, int handLuggage2, int luggage1, int luggage2);
    int getLuggageWeight() const override;
    int getHandLuggageWeight() const override;

private:
    int handLuggage1_;
    int handLuggage2_;
    int luggage1_;
    int luggage2_;
};

class FirstClassPassenger : public Unit {
public:
    FirstClassPassenger(int id, int handLuggage1, int handLuggage2, int luggage1, int luggage2);
    int getLuggageWeight() const override;
    int getHandLuggageWeight() const override;

private:
    int handLuggage1_;
    int handLuggage2_;
    int luggage1_;
    int luggage2_;
};

#endif // PASSENGERS_HPP
