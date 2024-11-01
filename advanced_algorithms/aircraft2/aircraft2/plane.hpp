// units/plane.hpp

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

private:
    int maxEconomyLuggage_;
    int maxBusinessLuggage_;
    int maxFirstClassLuggage_;
    int currentEconomyLuggage_;
    int currentBusinessLuggage_;
    int currentFirstClassLuggage_;
    std::vector<std::shared_ptr<Unit>> units_; // Вектор для хранения юнитов
};

#endif // PLANE_HPP
