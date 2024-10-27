#pragma once
#include <list>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

template<typename Key, typename Value>
class LRUCache {
public:
    LRUCache(size_t capacity, size_t max_size_bytes)
        : capacity_(capacity), max_size_bytes_(max_size_bytes), current_size_bytes_(0) {}

    bool put(const Key& key, Value value) {
        size_t entry_size = calculateEntrySize(key, value);
        if (entry_size > max_size_bytes_) {
            std::cout << "!STORERR!" << std::endl;
            return false;
        }

        // Если ключ уже существует, перемещаем его в начало списка
        if (cache_map_.find(key) != cache_map_.end()) {
            cache_items_list_.erase(cache_map_[key]);
            current_size_bytes_ -= calculateEntrySize(key, cache_map_[key]->second);
        }

        // Если кэш полон по байтам или числу записей, удаляем элементы
        while (cache_items_list_.size() >= capacity_ || current_size_bytes_ + entry_size > max_size_bytes_) {
            auto last = cache_items_list_.back();
            current_size_bytes_ -= calculateEntrySize(last.first, last.second);
            cache_map_.erase(last.first);
            cache_items_list_.pop_back();
        }

        // Вставляем новый элемент
        cache_items_list_.push_front({ key, std::move(value) });
        cache_map_[key] = cache_items_list_.begin();
        current_size_bytes_ += entry_size;

        std::cout << "!STORED!" << std::endl;
        return true;
    }

    std::string get(const Key& key) {
        if (cache_map_.find(key) == cache_map_.end()) {
            return "!NOEMBED!";
        }
        return key;
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
        return key.size() + value.size() * sizeof(float);
    }
};
