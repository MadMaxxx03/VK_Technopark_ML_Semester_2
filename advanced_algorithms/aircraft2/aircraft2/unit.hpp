// units/unit.hpp

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

    Unit(Type type, int id) : type_(type), id_(id) {} // Добавленный конструктор

    virtual ~Unit() = default;

    virtual int getLuggageWeight() const = 0; // Метод для получения веса багажа
    virtual int getHandLuggageWeight() const = 0; // Метод для получения веса ручной клади
    int getId() const { return id_; } // Возврат ID юнита
    Type getType() const { return type_; } // Возврат типа юнита

private:
    Type type_; // Хранение типа юнита
    int id_; // Хранение уникального идентификатора юнита
};

#endif // UNIT_HPP
