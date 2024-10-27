#include "lru.hpp"
#include <cassert>
#include <iostream>

void runTests() {
    // Создаем кэш на 3 элемента
    LRUCache<std::string, std::vector<float>> cache(3, 2048);

    // Добавляем 3 эмбеддинга
    std::vector<float> embed1(64, 1.0f);
    std::vector<float> embed2(64, 2.0f);
    std::vector<float> embed3(64, 3.0f);

    assert(cache.put("query1", std::move(embed1)));
    assert(cache.put("query2", std::move(embed2)));
    assert(cache.put("query3", std::move(embed3)));

    // Проверяем, что кэш содержит 3 элемента
    assert(cache.size() == 3);

    // Проверяем получение эмбеддингов
    std::string result1 = cache.get("query1");
    assert(!result1.empty());

    // Добавляем новый элемент, старый query1 должен быть вытеснен
    std::vector<float> embed4(64, 4.0f);
    assert(cache.put("query4", std::move(embed4)));

    // Проверка, что query1 был вытеснен
    std::string result1_evicted = cache.get("query1");
    assert(result1_evicted == "!NOEMBED!");

    // Проверяем корректность работы после удаления
    std::string result2 = cache.get("query2");
    assert(!result2.empty());

    // Все тесты пройдены
    std::cout << "All tests passed!" << std::endl;
}
