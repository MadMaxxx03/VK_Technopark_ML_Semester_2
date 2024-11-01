/*

#include "hashtable.hpp" // Подключаем файл с реализацией Hashtable
#include <iostream>
#include <string>

void runHashtableTests() {
    std::cout << "=== Hashtable Tests ===" << std::endl;

    // Создание хэш-таблицы с ключами типа std::string и значениями типа int
    Hashtable<std::string, int> ht(4);

    // Тест вставки
    std::cout << "Inserting values..." << std::endl;
    ht.insert({ "apple", 5 });
    ht.insert({ "banana", 7 });
    ht.insert({ "cherry", 9 });

    // Тест operator[] для добавления нового ключа
    std::cout << "Testing operator[] for new key insertion:" << std::endl;
    std::cout << "Value for 'orange' (should be 0): " << ht["orange"] << std::endl;
    ht["orange"] = 10;
    std::cout << "Value for 'orange' after assignment: " << ht["orange"] << std::endl;

    // Тест find
    auto it = ht.find("banana");
    if (it != ht.end()) {
        std::cout << "Found 'banana': " << it->second << std::endl;
    }
    else {
        std::cout << "'banana' not found" << std::endl;
    }

    // Тест erase
    std::cout << "Erasing 'banana'" << std::endl;
    ht.erase("banana");
    if (ht.find("banana") == ht.end()) {
        std::cout << "'banana' successfully erased" << std::endl;
    }
    else {
        std::cout << "'banana' still exists after erase" << std::endl;
    }

    // Тест count
    std::cout << "Count of 'cherry': " << ht.count("cherry") << std::endl;
    std::cout << "Count of 'banana' (should be 0): " << ht.count("banana") << std::endl;

    // Тест load_factor и max_load_factor
    std::cout << "Load factor: " << ht.load_factor() << std::endl;
    std::cout << "Max load factor: " << ht.max_load_factor() << std::endl;
    ht.max_load_factor(0.5f); // изменяем max_load_factor
    std::cout << "New max load factor: " << ht.max_load_factor() << std::endl;

    // Тест reserve
    std::cout << "Reserving larger capacity" << std::endl;
    ht.reserve(10);
    std::cout << "New capacity after reserve: " << ht.size() << std::endl;

    std::cout << "=== Hashtable Tests Completed ===" << std::endl;
}
*/