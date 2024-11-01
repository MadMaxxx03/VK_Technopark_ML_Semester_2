// units/passengers.cpp

#include "passengers.hpp"

// Реализация конструктора и методов для класса EconomyPassenger
EconomyPassenger::EconomyPassenger(int id, int handLuggage, int luggage)
    : Unit(Type::ECONOMY, id), handLuggage_(handLuggage), luggage_(luggage) {}

int EconomyPassenger::getHandLuggageWeight() const { return handLuggage_; } // Переопределяет метод из Unit
int EconomyPassenger::getLuggageWeight() const { return luggage_; } // Переопределяет метод из Unit

// Реализация конструктора и методов для класса BusinessPassenger
BusinessPassenger::BusinessPassenger(int id, int handLuggage1, int handLuggage2, int luggage1, int luggage2)
    : Unit(Type::BUSINESS, id), handLuggage1_(handLuggage1), handLuggage2_(handLuggage2), luggage1_(luggage1), luggage2_(luggage2) {}

int BusinessPassenger::getHandLuggageWeight() const { return handLuggage1_ + handLuggage2_; } // Переопределяет метод из Unit
int BusinessPassenger::getLuggageWeight() const { return luggage1_ + luggage2_; } // Переопределяет метод из Unit

// Реализация конструктора и методов для класса FirstClassPassenger
FirstClassPassenger::FirstClassPassenger(int id, int handLuggage1, int handLuggage2, int luggage1, int luggage2)
    : Unit(Type::FIRST_CLASS, id), handLuggage1_(handLuggage1), handLuggage2_(handLuggage2), luggage1_(luggage1), luggage2_(luggage2) {}

int FirstClassPassenger::getHandLuggageWeight() const { return handLuggage1_ + handLuggage2_; } // Переопределяет метод из Unit
int FirstClassPassenger::getLuggageWeight() const { return luggage1_ + luggage2_; } // Переопределяет метод из Unit
