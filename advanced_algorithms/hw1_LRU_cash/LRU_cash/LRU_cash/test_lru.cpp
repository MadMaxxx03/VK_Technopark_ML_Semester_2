#include "lru.hpp"
#include <cassert>
#include <iostream>

void runTests() {
    // ���� 1: ���������� � ���������� ��������
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);

        assert(cache.put("query1", embed1)); // �������� ����������
        auto result1 = cache.get("query1");
        assert(result1 == embed1); // �������� ����������
        std::cout << "Test 1 passed!" << std::endl;
    }

    // ���� 2: ���������� ������������� ��������
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query1", embed2)); // ��������� ��������
        auto result = cache.get("query1");
        assert(result == embed2); // �������� �� ����������
        std::cout << "Test 2 passed!" << std::endl;
    }

    // ���� 3: ���������� ��������� ��� ���������� capacity
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);
        std::vector<float> embed3(64, 3.0f);
        std::vector<float> embed4(64, 4.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        assert(cache.put("query3", embed3));
        assert(cache.put("query4", embed4)); // query1 �����������

        assert(cache.get("query1").empty()); // query1 ��������
        assert(!cache.get("query2").empty()); // query2 �� �����
        std::cout << "Test 3 passed!" << std::endl;
    }

    // ���� 4: ������� ����
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        cache.clear(); // �������

        assert(cache.size() == 0); // ��� ������ ���� ����
        assert(cache.get("query1").empty());
        std::cout << "Test 4 passed!" << std::endl;
    }

    // ���� 5: �������� ���������� ���������� ��� ����������
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);
        std::vector<float> embed3(64, 3.0f);
        std::vector<float> embed4(64, 4.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        assert(cache.put("query3", embed3));
        assert(cache.put("query1", embed1)); // query1 ���������� ����� ���������

        assert(cache.put("query4", embed4)); // query2 �����������
        assert(cache.get("query2").empty()); // query2 ������ �������������
        std::cout << "Test 5 passed!" << std::endl;
    }

    // ���� 6: �������� ������������� ������ � ����� ���������
    {
        LRUCache<std::string, std::vector<float>> cache(2, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));

        assert(cache.get("query1") == embed1); // query1 �������� � ������ ���� ����������

        std::vector<float> embed3(64, 3.0f);
        assert(cache.put("query3", embed3)); // query2 �����������
        assert(cache.get("query2").empty()); // query2 ������ �������������
        std::cout << "Test 6 passed!" << std::endl;
    }

    // ���� 7: ��������� ��������� max_size_bytes
    {
        LRUCache<std::string, std::vector<float>> cache(3, 128); // ����� �� ������
        std::vector<float> embed1(64, 1.0f);

        assert(!cache.put("query1", embed1)); // ������ ��������� false ��-�� ������ �� �������
        assert(cache.get("query1").empty()); // query1 �� ������ ����������
        std::cout << "Test 7 passed!" << std::endl;
    }

    // ���� 8: ������� ������� ����� �������
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);

        assert(cache.put("query1", embed1)); // ��������� �������
        cache.clear(); // ������� ����
        assert(cache.put("query2", embed1)); // ������ �������� ����� �������
        std::cout << "Test 8 passed!" << std::endl;
    }

    // ���� 9: �������� ���������� � ���������� � ����������� cache_size
    {
        LRUCache<std::string, std::vector<float>> cache(1, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);

        assert(cache.put("query1", embed1)); // ��������� ������ �������
        assert(cache.get("query1") == embed1); // ���������, ��� �� ��������
        assert(cache.put("query2", embed2)); // ��������� ������ �������, �������� ������
        assert(cache.get("query1").empty()); // query1 ������ �������������
        assert(cache.get("query2") == embed2); // query2 ��������
        std::cout << "Test 9 passed!" << std::endl;
    }

    // ���� 10: �������� ������� ��������� ����������� ������� � ����������
    {
        LRUCache<std::string, std::vector<float>> cache(2, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));

        std::vector<float> embed3(64, 3.0f);
        assert(cache.put("query3", embed3)); // query1 �����������, �.�. query2 ������������� ���������

        assert(cache.get("query1").empty()); // query1 ������ �������������
        assert(!cache.get("query2").empty()); // query2 ������ ���� ��������
        assert(cache.get("query3") == embed3); // query3 ������ ���� ��������
        std::cout << "Test 10 passed!" << std::endl;
    }

    // ���� 11: �������� �� ��������� ���������� ���� ��� ����������� max_size_bytes
    {
        LRUCache<std::string, std::vector<float>> cache(3, 256); // ������, ��� ��������� ��� ���� ���������
        std::vector<float> embed1(32, 1.0f); // �������� ������� ���������� ��������

        assert(cache.put("query1", embed1)); // ������ ����������
        assert(cache.get("query1") == embed1); // �������� �� ������� query1

        std::vector<float> embed2(64, 2.0f);
        assert(!cache.put("query2", embed2)); // ������ �� ���������� ��-�� ����������� �� ������
        assert(cache.get("query2").empty()); // query2 �����������
        std::cout << "Test 11 passed!" << std::endl;
    }

    // ���� 12: �������� ���������� ��������� ����� ���������� �������
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);

        assert(cache.put("query1", embed1)); // ��������� �������
        cache.clear(); // ������ �������
        cache.clear(); // ������ �������
        assert(cache.size() == 0); // ������ ������ ���� 0 ����� �������
        assert(cache.get("query1").empty()); // query1 ������ �������������
        std::cout << "Test 12 passed!" << std::endl;
    }

    // ���� 13: �������� ���������� ������ ������� �������� ��� ���������� ������
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);
        std::vector<float> embed3(64, 3.0f);
        std::vector<float> embed4(64, 4.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        assert(cache.put("query3", embed3));
        assert(cache.put("query4", embed4)); // query1 �����������, ��� ��� �� ��� ����� ������

        assert(cache.get("query1").empty()); // query1 ������ �������������
        assert(cache.get("query2") == embed2); // query2 ������ ��������������
        assert(cache.get("query3") == embed3); // query3 ������ ��������������
        assert(cache.get("query4") == embed4); // query4 ������ ��������������
        std::cout << "Test 13 passed!" << std::endl;
    }

    // ���� 14: �������� ������������ ���������� ��������� ����� ����������
    {
        LRUCache<std::string, std::vector<float>> cache(2, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);
        std::vector<float> embed3(64, 3.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        assert(cache.size() == 2); // ��� ������ ��������� 2 ��������
        assert(cache.put("query3", embed3)); // query1 �����������

        assert(cache.size() == 2); // ������ ������ ���������� 2
        assert(cache.get("query1").empty()); // query1 ������ �������������
        assert(cache.get("query2") == embed2); // query2 ������ ��������������
        assert(cache.get("query3") == embed3); // query3 ������ ��������������
        std::cout << "Test 14 passed!" << std::endl;
    }

    // ���� 15: �������� ��������� ��� ��������� ������� � ��������
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);
        std::vector<float> embed3(64, 3.0f);
        std::vector<float> embed4(64, 4.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        assert(cache.put("query3", embed3));
        assert(cache.get("query1") == embed1); // ������ � query1, ����� �������� ��� ���������
        assert(cache.put("query4", embed4)); // query2 ����������� ������ query1

        assert(cache.get("query2").empty()); // query2 ������ �������������
        assert(cache.get("query1") == embed1); // query1 ������ ��������������
        assert(cache.get("query3") == embed3); // query3 ������ ��������������
        assert(cache.get("query4") == embed4); // query4 ������ ��������������
        std::cout << "Test 15 passed!" << std::endl;
    }

    // ���� 16: �������� ������ ���� ��� ������ ����������, �� ��� ����������
    {
        LRUCache<std::string, std::vector<float>> cache(3, 4096);
        std::vector<float> embed1(64, 1.0f);
        std::vector<float> embed2(64, 2.0f);
        std::vector<float> embed3(64, 3.0f);

        assert(cache.put("query1", embed1));
        assert(cache.put("query2", embed2));
        assert(cache.put("query3", embed3)); // ��� ��������� ��������

        assert(cache.get("query1") == embed1); // ��� �������� ������������
        assert(cache.get("query2") == embed2);
        assert(cache.get("query3") == embed3);
        std::cout << "Test 16 passed!" << std::endl;
    }

    // ���� 17: �������� ���������� ��������� �������� �������, ��� max_size_bytes
    {
        LRUCache<std::string, std::vector<float>> cache(3, 128); // ��������� ����� �� �������
        std::vector<float> embed1(64, 1.0f); // ������ �������� 256 ���� (64 * 4 �����)

        assert(!cache.put("query1", embed1)); // ������ ��������� false ��-�� ����������� �� �������
        assert(cache.get("query1").empty()); // query1 �� ������ ���������� � ���
        std::cout << "Test 17 passed!" << std::endl;
    }

    std::cout << "All tests passed!" << std::endl;
}
