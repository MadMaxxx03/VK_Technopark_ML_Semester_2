#pragma once
#include <list>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

template<typename Key, typename Value>
class LRUCache {
public:
    LRUCache(size_t capacity, size_t max_size_bytes)
        : capacity_(capacity), max_size_bytes_(max_size_bytes), current_size_bytes_(0) {}

    bool put(const Key& key, const Value& value) {
        size_t entry_size = calculateEntrySize(key, value);

        // Проверка, что размер элемента не превышает максимальный допустимый размер кэша
        if (entry_size > max_size_bytes_) {
            std::cout << "!STORERR!" << std::endl;
            return false;
        }

        // Если ключ уже существует, обновляем элемент и перемещаем в начало
        if (cache_map_.find(key) != cache_map_.end()) {
            auto it = cache_map_[key];
            current_size_bytes_ -= calculateEntrySize(it->first, it->second);
            cache_items_list_.erase(it);
        }

        // Если кэш полон по размеру или числу элементов, удаляем последние
        while (cache_items_list_.size() >= capacity_ || current_size_bytes_ + entry_size > max_size_bytes_) {
            auto last = cache_items_list_.back();
            current_size_bytes_ -= calculateEntrySize(last.first, last.second);
            cache_map_.erase(last.first);
            cache_items_list_.pop_back();
        }

        // Вставляем новый элемент
        cache_items_list_.push_front({ key, value });
        cache_map_[key] = cache_items_list_.begin();
        current_size_bytes_ += entry_size;

        std::cout << "!STORED!" << std::endl;
        return true;
    }

    Value get(const Key& key) {
        if (cache_map_.find(key) == cache_map_.end()) {
            std::cout << "!NOEMBED!" << std::endl;
            return Value();
        }

        // Перемещаем найденный элемент в начало списка
        auto it = cache_map_[key];
        cache_items_list_.splice(cache_items_list_.begin(), cache_items_list_, it);

        return it->second;
    }

    size_t size() const {
        return cache_items_list_.size();
    }

    size_t size_bytes() const {
        return current_size_bytes_;
    }

    void clear() {
        cache_items_list_.clear();
        cache_map_.clear();
        current_size_bytes_ = 0;
    }

private:
    size_t capacity_;
    size_t max_size_bytes_;
    size_t current_size_bytes_;
    std::list<std::pair<Key, Value>> cache_items_list_;
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> cache_map_;

    size_t calculateEntrySize(const Key& key, const Value& value) const {
        return key.size() + value.size() * sizeof(typename Value::value_type);
    }
};
