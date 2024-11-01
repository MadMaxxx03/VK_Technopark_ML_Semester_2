#include "plane.hpp"
#include <iostream>

Plane::Plane(int maxEconomyLuggage, int maxBusinessLuggage, int maxFirstClassLuggage)
    : maxEconomyLuggage_(maxEconomyLuggage), maxBusinessLuggage_(maxBusinessLuggage),
    maxFirstClassLuggage_(maxFirstClassLuggage), currentEconomyLuggage_(0),
    currentBusinessLuggage_(0), currentFirstClassLuggage_(0) {}

bool Plane::addUnit(std::shared_ptr<Unit> unit) {
    int luggageWeight = unit->getLuggageWeight();

    switch (unit->getType()) {
    case Unit::Type::ECONOMY:
        if (currentEconomyLuggage_ + luggageWeight > maxEconomyLuggage_) {
            std::cout << "!!CANT REGISTER ECONOMY PASSENGER, ID = " << unit->getId() << "!!\n";
            return false;
        }
        currentEconomyLuggage_ += luggageWeight;
        break;
    case Unit::Type::BUSINESS:
        if (currentBusinessLuggage_ + luggageWeight > maxBusinessLuggage_) {
            std::cout << "!!CANT REGISTER BUSINESS PASSENGER, ID = " << unit->getId() << "!!\n";
            return false;
        }
        currentBusinessLuggage_ += luggageWeight;
        break;
    case Unit::Type::FIRST_CLASS:
        if (currentFirstClassLuggage_ + luggageWeight > maxFirstClassLuggage_) {
            std::cout << "!!CANT REGISTER FIRST CLASS PASSENGER, ID = " << unit->getId() << "!!\n";
            return false;
        }
        currentFirstClassLuggage_ += luggageWeight;
        break;
    default:
        break;
    }

    units_.push_back(unit);
    return true;
}

int Plane::getTotalLuggageWeight() const {
    return currentEconomyLuggage_ + currentBusinessLuggage_ + currentFirstClassLuggage_;
}
