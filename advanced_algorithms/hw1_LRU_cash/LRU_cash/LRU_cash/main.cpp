#include "lru.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Декларация функции для запуска тестов, которая будет определена в test_lru.cpp
void runTests();

void process_input(LRUCache<std::string, std::vector<float>>& cache) {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string query;
        iss >> query;

        // Проверяем, является ли строка запросом с эмбедингами
        if (iss.peek() != EOF) {
            // Строка вида (а)
            std::vector<float> embedding(64);
            bool valid = true;
            for (int i = 0; i < 64; ++i) {
                iss >> embedding[i];
                if (iss.fail()) {
                    valid = false;
                    break;
                }
            }

            if (valid && cache.put(query, std::move(embedding))) {
                std::cout << "!STORED!" << std::endl;
            }
            else {
                std::cout << "!STORERR!" << std::endl;
            }
        }
        else {
            // Строка вида (б)
            auto embedding = cache.get(query);
            if (!embedding.empty()) {
                for (const auto& val : embedding) {
                    std::cout << val << " ";
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "!NOEMBED!" << std::endl;
            }
        }
    }
}

int main() {
    std::cout << "Запустить тесты или программу? (t/p): ";
    char choice;
    std::cin >> choice;

    if (choice == 't') {
        // Запускаем тесты
        runTests();
    }
    else if (choice == 'p') {
        // Пример использования LRUCache в основной программе
        LRUCache<std::string, std::vector<float>> cache(3, 2048);

        std::cout << "Введите запросы в формате <q> или <q> <f1> <f2> ... <f64>:" << std::endl;
        std::cin.ignore(); // Очищаем буфер после ввода выбора t/p
        process_input(cache);
    }
    else {
        std::cout << "Некорректный ввод. Завершение программы." << std::endl;
    }

    return 0;
}
