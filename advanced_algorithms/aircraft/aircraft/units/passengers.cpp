#include "passengers.hpp"

EconomyPassenger::EconomyPassenger(int id, int handLuggage, int luggage)
    : Unit(Type::ECONOMY, id), handLuggage_(handLuggage), luggage_(luggage) {}

int EconomyPassenger::getHandLuggageWeight() const { return handLuggage_; } 
int EconomyPassenger::getLuggageWeight() const { return luggage_; } 

BusinessPassenger::BusinessPassenger(int id, int handLuggage1, int handLuggage2, int luggage1, int luggage2)
    : Unit(Type::BUSINESS, id), handLuggage1_(handLuggage1), handLuggage2_(handLuggage2), luggage1_(luggage1), luggage2_(luggage2) {}

int BusinessPassenger::getHandLuggageWeight() const { return handLuggage1_ + handLuggage2_; } 
int BusinessPassenger::getLuggageWeight() const { return luggage1_ + luggage2_; } 

FirstClassPassenger::FirstClassPassenger(int id, int handLuggage1, int handLuggage2, int luggage1, int luggage2)
    : Unit(Type::FIRST_CLASS, id), handLuggage1_(handLuggage1), handLuggage2_(handLuggage2), luggage1_(luggage1), luggage2_(luggage2) {}

int FirstClassPassenger::getHandLuggageWeight() const { return handLuggage1_ + handLuggage2_; } 
int FirstClassPassenger::getLuggageWeight() const { return luggage1_ + luggage2_; } 
