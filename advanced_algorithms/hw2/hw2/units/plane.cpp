#include "plane.hpp"
#include <iostream>
#include <algorithm>

Plane::Plane(int maxEconomyLuggage, int maxBusinessLuggage, int maxFirstClassLuggage)
    : maxEconomyLuggage_(maxEconomyLuggage), maxBusinessLuggage_(maxBusinessLuggage),
    maxFirstClassLuggage_(maxFirstClassLuggage), currentEconomyLuggage_(0),
    currentBusinessLuggage_(0), currentFirstClassLuggage_(0) {}

bool Plane::addUnit(std::shared_ptr<Unit> unit) {
    int luggageWeight = unit->getLuggageWeight();

    switch (unit->getType()) {
    case Unit::Type::ECONOMY:
        if (economyPassengerCount_ >= maxEconomyPassengers) {
            std::cout << "!!CANT REGISTER ECONOMY PASSENGER, ID = " << unit->getId() << " - PASSENGER LIMIT EXCEEDED!!\n";
            return false;
        }
        if (currentEconomyLuggage_ + luggageWeight > maxEconomyLuggage_) {
            std::cout << "!!CANT REGISTER ECONOMY PASSENGER, ID = " << unit->getId() << " - LUGGAGE LIMIT EXCEEDED!!\n";
            return false;
        }
        currentEconomyLuggage_ += luggageWeight;
        ++economyPassengerCount_;
        break;

    case Unit::Type::BUSINESS:
        if (businessPassengerCount_ >= maxBusinessPassengers) {
            std::cout << "!!CANT REGISTER BUSINESS PASSENGER, ID = " << unit->getId() << " - PASSENGER LIMIT EXCEEDED!!\n";
            return false;
        }
        if (currentBusinessLuggage_ + luggageWeight > maxBusinessLuggage_) {
            if (currentEconomyLuggage_ + luggageWeight > maxEconomyLuggage_) {
                if (!removeLuggageForWeight(luggageWeight)) {
                    std::cout << "!!CANT REGISTER BUSINESS PASSENGER, ID = " << unit->getId() << " - ECONOMY LUGGAGE LIMIT EXCEEDED!!\n";
                    return false;
                }
            }
            currentEconomyLuggage_ += luggageWeight;
        }
        else {
            currentBusinessLuggage_ += luggageWeight;
        }
        ++businessPassengerCount_;
        break;

    case Unit::Type::FIRST_CLASS:
        if (firstClassPassengerCount_ >= maxFirstClassPassengers) {
            std::cout << "!!CANT REGISTER FIRST CLASS PASSENGER, ID = " << unit->getId() << " - PASSENGER LIMIT EXCEEDED!!\n";
            return false;
        }
        if (currentFirstClassLuggage_ + luggageWeight > maxFirstClassLuggage_) {
            if (currentEconomyLuggage_ + luggageWeight > maxEconomyLuggage_) {
                if (!removeLuggageForWeight(luggageWeight)) {
                    std::cout << "!!CANT REGISTER FIRST CLASS PASSENGER, ID = " << unit->getId() << " - ECONOMY LUGGAGE LIMIT EXCEEDED!!\n";
                    return false;
                }
            }
            currentEconomyLuggage_ += luggageWeight;
        }
        else {
            currentFirstClassLuggage_ += luggageWeight;
        }
        ++firstClassPassengerCount_;
        break;

    case Unit::Type::PILOT:
        if (pilotCount_ >= maxPilots) {
            std::cout << "!!CANT REGISTER PILOT, ID = " << unit->getId() << "!!\n";
            return false;
        }
        ++pilotCount_;
        break;

    case Unit::Type::FLIGHT_ATTENDANT:
        if (flightAttendantCount_ >= maxFlightAttendants) {
            std::cout << "!!CANT REGISTER FLIGHT ATTENDANT, ID = " << unit->getId() << "!!\n";
            return false;
        }
        ++flightAttendantCount_;
        break;

    default:
        break;
    }

    units_.push_back(unit);
    return true;
}

bool Plane::removeLuggageForWeight(int requiredWeight) {
    auto compare = [](const std::shared_ptr<Unit>& a, const std::shared_ptr<Unit>& b) {
        return a->getLuggageWeight() < b->getLuggageWeight();
    };

    std::vector<std::shared_ptr<Unit>> economyLuggage;
    for (const auto& unit : units_) {
        if (unit->getType() == Unit::Type::ECONOMY && unit->getLuggageWeight() > 0) {
            economyLuggage.push_back(unit);
        }
    }

    std::sort(economyLuggage.begin(), economyLuggage.end(), compare);

    int removedWeight = 0;
    for (auto& unit : economyLuggage) {
        if (removedWeight >= requiredWeight) break;
        removedWeight += unit->getLuggageWeight();
        currentEconomyLuggage_ -= unit->getLuggageWeight();
        std::cout << "!!PASSENGER’S LUGGAGE REMOVED FROM FLIGHT, ID = " << unit->getId() << "!!\n";
    }

    return removedWeight >= requiredWeight;
}

int Plane::getTotalLuggageWeight() const {
    return currentEconomyLuggage_ + currentBusinessLuggage_ + currentFirstClassLuggage_;
}
