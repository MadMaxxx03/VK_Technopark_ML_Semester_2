#include "lru.hpp"
#include <cassert>
#include <iostream>

void runTests() {
    // Тест 1: Добавление и извлечение элемента
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);

        assert(cache.put("query1", embed1)); // Успешное добавление
        auto result1 = cache.get("query1");
        assert(result1 == embed1); // Проверка извлечения
        std::cout << "Test 1 passed!" << std::endl;
    }

    // Тест 2: Обновление существующего элемента
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query1", embed2)); // Обновляем значение
        auto result = cache.get("query1");
        assert(result == embed2); // Проверка на обновление
        std::cout << "Test 2 passed!" << std::endl;
    }

    // Тест 3: Вытеснение элементов при превышении capacity
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);
        std::vector<float> embed3(64, 3.0f);
        std::vector<float> embed4(64, 4.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        assert(cache.put("query3", embed3));
        assert(cache.put("query4", embed4)); // query1 вытесняется

        assert(cache.get("query1").empty()); // query1 вытеснен
        assert(!cache.get("query2").empty()); // query2 на месте
        std::cout << "Test 3 passed!" << std::endl;
    }

    // Тест 4: Очистка кэша
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        cache.clear(); // Очистка

        assert(cache.size() == 0); // Кэш должен быть пуст
        assert(cache.get("query1").empty());
        std::cout << "Test 4 passed!" << std::endl;
    }

    // Тест 5: Проверка повторного добавления при вытеснении
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);
        std::vector<float> embed3(64, 3.0f);
        std::vector<float> embed4(64, 4.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        assert(cache.put("query3", embed3));
        assert(cache.put("query1", embed1)); // query1 становится самым последним

        assert(cache.put("query4", embed4)); // query2 вытесняется
        assert(cache.get("query2").empty()); // query2 должен отсутствовать
        std::cout << "Test 5 passed!" << std::endl;
    }

    // Тест 6: Проверка использования старых и новых элементов
    {
        LRUCache<std::string, std::vector<float>> cache(2, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));

        assert(cache.get("query1") == embed1); // query1 доступен и должен быть актуальным

        std::vector<float> embed3(64, 3.0f);
        assert(cache.put("query3", embed3)); // query2 вытесняется
        assert(cache.get("query2").empty()); // query2 должен отсутствовать
        std::cout << "Test 6 passed!" << std::endl;
    }

    // Тест 7: Обработка короткого max_size_bytes
    {
        LRUCache<std::string, std::vector<float>> cache(3, 128); // Лимит по байтам
        std::vector<float> embed1(64, 1.0f);

        assert(!cache.put("query1", embed1)); // Должен вернуться false из-за лимита по размеру
        assert(cache.get("query1").empty()); // query1 не должен добавиться
        std::cout << "Test 7 passed!" << std::endl;
    }

    // Тест 8: Попытка вставки после очистки
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);

        assert(cache.put("query1", embed1)); // Добавляем элемент
        cache.clear(); // Очистка кэша
        assert(cache.put("query2", embed1)); // Должно работать после очистки
        std::cout << "Test 8 passed!" << std::endl;
    }

    // Тест 9: Проверка добавления и вытеснения с минимальным cache_size
    {
        LRUCache<std::string, std::vector<float>> cache(1, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);

        assert(cache.put("query1", embed1)); // Добавляем первый элемент
        assert(cache.get("query1") == embed1); // Проверяем, что он доступен
        assert(cache.put("query2", embed2)); // Добавляем второй элемент, вытесняя первый
        assert(cache.get("query1").empty()); // query1 должен отсутствовать
        assert(cache.get("query2") == embed2); // query2 доступен
        std::cout << "Test 9 passed!" << std::endl;
    }

    // Тест 10: Проверка вставки элементов одинакового размера и вытеснения
    {
        LRUCache<std::string, std::vector<float>> cache(2, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));

        std::vector<float> embed3(64, 3.0f);
        assert(cache.put("query3", embed3)); // query1 вытесняется, т.к. query2 использовался последним

        assert(cache.get("query1").empty()); // query1 должен отсутствовать
        assert(!cache.get("query2").empty()); // query2 должен быть доступен
        assert(cache.get("query3") == embed3); // query3 должен быть доступен
        std::cout << "Test 10 passed!" << std::endl;
    }

    // Тест 11: Проверка на частичное заполнение кэша при ограничении max_size_bytes
    {
        LRUCache<std::string, std::vector<float>> cache(3, 256); // Меньше, чем требуется для всех элементов
        std::vector<float> embed1(32, 1.0f); // Половина размера предыдущих векторов

        assert(cache.put("query1", embed1)); // Должен добавиться
        assert(cache.get("query1") == embed1); // Проверка на наличие query1

        std::vector<float> embed2(64, 2.0f);
        assert(!cache.put("query2", embed2)); // Должен не добавиться из-за ограничения по байтам
        assert(cache.get("query2").empty()); // query2 отсутствует
        std::cout << "Test 11 passed!" << std::endl;
    }

    // Тест 12: Проверка отсутствия элементов после нескольких очисток
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);

        assert(cache.put("query1", embed1)); // Добавляем элемент
        cache.clear(); // Первая очистка
        cache.clear(); // Вторая очистка
        assert(cache.size() == 0); // Размер должен быть 0 после очисток
        assert(cache.get("query1").empty()); // query1 должен отсутствовать
        std::cout << "Test 12 passed!" << std::endl;
    }

    // Тест 13: Проверка вытеснения самого старого элемента при добавлении нового
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);
        std::vector<float> embed3(64, 3.0f);
        std::vector<float> embed4(64, 4.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        assert(cache.put("query3", embed3));
        assert(cache.put("query4", embed4)); // query1 вытесняется, так как он был самым старым

        assert(cache.get("query1").empty()); // query1 должен отсутствовать
        assert(cache.get("query2") == embed2); // query2 должен присутствовать
        assert(cache.get("query3") == embed3); // query3 должен присутствовать
        assert(cache.get("query4") == embed4); // query4 должен присутствовать
        std::cout << "Test 13 passed!" << std::endl;
    }

    // Тест 14: Проверка корректности количества элементов после вытеснения
    {
        LRUCache<std::string, std::vector<float>> cache(2, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);
        std::vector<float> embed3(64, 3.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        assert(cache.size() == 2); // Кэш должен содержать 2 элемента
        assert(cache.put("query3", embed3)); // query1 вытесняется

        assert(cache.size() == 2); // Размер должен оставаться 2
        assert(cache.get("query1").empty()); // query1 должен отсутствовать
        assert(cache.get("query2") == embed2); // query2 должен присутствовать
        assert(cache.get("query3") == embed3); // query3 должен присутствовать
        std::cout << "Test 14 passed!" << std::endl;
    }

    // Тест 15: Проверка поведения при повторном доступе к элементу
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);
        std::vector<float> embed3(64, 3.0f);
        std::vector<float> embed4(64, 4.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        assert(cache.put("query3", embed3));
        assert(cache.get("query1") == embed1); // Доступ к query1, чтобы обновить его положение
        assert(cache.put("query4", embed4)); // query2 вытесняется вместо query1

        assert(cache.get("query2").empty()); // query2 должен отсутствовать
        assert(cache.get("query1") == embed1); // query1 должен присутствовать
        assert(cache.get("query3") == embed3); // query3 должен присутствовать
        assert(cache.get("query4") == embed4); // query4 должен присутствовать
        std::cout << "Test 15 passed!" << std::endl;
    }

    // Тест 16: Проверка работы кэша при полном заполнении, но без вытеснения
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);
        std::vector<float> embed3(64, 3.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        assert(cache.put("query3", embed3)); // Кэш полностью заполнен

        assert(cache.get("query1") == embed1); // Все элементы присутствуют
        assert(cache.get("query2") == embed2);
        assert(cache.get("query3") == embed3);
        std::cout << "Test 16 passed!" << std::endl;
    }

    // Тест 17: Проверка добавления элементов большего размера, чем max_size_bytes
    {
        LRUCache<std::string, std::vector<float>> cache(3, 128); // Маленький лимит по размеру
        std::vector<float> embed1(64, 1.0f); // Вектор размером 256 байт (64 * 4 байта)

        assert(!cache.put("query1", embed1)); // Должен вернуться false из-за ограничения по размеру
        assert(cache.get("query1").empty()); // query1 не должен добавиться в кэш
        std::cout << "Test 17 passed!" << std::endl;
    }

    std::cout << "All tests passed!" << std::endl;
}
