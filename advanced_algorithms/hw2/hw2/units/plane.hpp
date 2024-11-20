#ifndef PLANE_HPP
#define PLANE_HPP

#include "unit.hpp"
#include <vector>
#include <memory>

class Plane {
public:
    Plane(int maxEconomyLuggage, int maxBusinessLuggage, int maxFirstClassLuggage);

    bool addUnit(std::shared_ptr<Unit> unit);
    int getTotalLuggageWeight() const;
    bool removeLuggageForWeight(int requiredWeight);

private:
    int maxEconomyLuggage_;
    int maxBusinessLuggage_;
    int maxFirstClassLuggage_;
    int currentEconomyLuggage_;
    int currentBusinessLuggage_;
    int currentFirstClassLuggage_;

    int economyPassengerCount_ = 0;
    int businessPassengerCount_ = 0;
    int firstClassPassengerCount_ = 0;
    int pilotCount_ = 0;
    int flightAttendantCount_ = 0;

    std::vector<std::shared_ptr<Unit>> units_;

    static constexpr int maxEconomyPassengers = 200;
    static constexpr int maxBusinessPassengers = 10;
    static constexpr int maxFirstClassPassengers = 4;
    static constexpr int maxPilots = 2;
    static constexpr int maxFlightAttendants = 6;

};

#endif 
