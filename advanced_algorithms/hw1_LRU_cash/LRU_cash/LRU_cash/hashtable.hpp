/*

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <vector>
#include <functional>
#include <optional>
#include <utility>
#include <stdexcept>
#include <iterator>

template<typename Key, typename Value, typename HashT = std::hash<Key>, typename ComparatorT = std::equal_to<Key>>
class Hashtable {
public:
    using KeyValuePair = std::pair<Key, Value>;

    class iterator;
    class const_iterator;

    // Конструкторы
    explicit Hashtable(size_t bucket_count = 16, float max_load_factor = 0.75f);
    ~Hashtable() = default;

    // Итераторы
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    // Управление таблицей
    bool empty() const;
    size_t size() const;
    void clear();
    void reserve(size_t new_capacity);
    float load_factor() const;
    float max_load_factor() const;
    void max_load_factor(float new_max_load_factor);

    // Поиск и модификация
    iterator find(const Key& key);
    const_iterator find(const Key& key) const;
    size_t count(const Key& key) const;
    std::pair<iterator, bool> insert(const KeyValuePair& kv);
    size_t erase(const Key& key);
    Value& operator[](const Key& key);

private:
    std::vector<std::optional<KeyValuePair>> buckets_;
    size_t size_;
    float max_load_factor_;
    HashT hash_;
    ComparatorT comparator_;

    void rehash(size_t new_bucket_count);
    size_t bucket_index(const Key& key) const;

    void check_load_factor();
};

// Итератор
template<typename Key, typename Value, typename HashT, typename ComparatorT>
class Hashtable<Key, Value, HashT, ComparatorT>::iterator {
public:
    using KeyValuePair = std::pair<Key, Value>;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = KeyValuePair;
    using pointer = KeyValuePair*;
    using reference = KeyValuePair&;

    iterator(Hashtable* table, size_t index = 0)
        : table_(table), index_(index) {
        if (table && index_ < table_->buckets_.size() && !table_->buckets_[index_].has_value()) {
            ++(*this);
        }
    }

    reference operator*() const {
        return table_->buckets_[index_].value();
    }

    pointer operator->() const {
        return &table_->buckets_[index_].value();
    }

    iterator& operator++() {
        do {
            ++index_;
        } while (index_ < table_->buckets_.size() && !table_->buckets_[index_].has_value());
        return *this;
    }

    iterator operator++(int) {
        iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const iterator& other) const {
        return table_ == other.table_ && index_ == other.index_;
    }

    bool operator!=(const iterator& other) const {
        return !(*this == other);
    }

private:
    Hashtable* table_;
    size_t index_;
};

// Реализация методов Hashtable
template<typename Key, typename Value, typename HashT, typename ComparatorT>
Hashtable<Key, Value, HashT, ComparatorT>::Hashtable(size_t bucket_count, float max_load_factor)
    : buckets_(bucket_count), size_(0), max_load_factor_(max_load_factor) {}

template<typename Key, typename Value, typename HashT, typename ComparatorT>
size_t Hashtable<Key, Value, HashT, ComparatorT>::size() const {
    return size_;
}

template<typename Key, typename Value, typename HashT, typename ComparatorT>
bool Hashtable<Key, Value, HashT, ComparatorT>::empty() const {
    return size_ == 0;
}

template<typename Key, typename Value, typename HashT, typename ComparatorT>
void Hashtable<Key, Value, HashT, ComparatorT>::clear() {
    buckets_.clear();
    buckets_.resize(16);
    size_ = 0;
}

template<typename Key, typename Value, typename HashT, typename ComparatorT>
float Hashtable<Key, Value, HashT, ComparatorT>::load_factor() const {
    return static_cast<float>(size_) / buckets_.size();
}

template<typename Key, typename Value, typename HashT, typename ComparatorT>
float Hashtable<Key, Value, HashT, ComparatorT>::max_load_factor() const {
    return max_load_factor_;
}

template<typename Key, typename Value, typename HashT, typename ComparatorT>
void Hashtable<Key, Value, HashT, ComparatorT>::max_load_factor(float new_max_load_factor) {
    max_load_factor_ = new_max_load_factor;
    check_load_factor();
}

template<typename Key, typename Value, typename HashT, typename ComparatorT>
void Hashtable<Key, Value, HashT, ComparatorT>::check_load_factor() {
    if (load_factor() > max_load_factor_) {
        rehash(buckets_.size() * 2);
    }
}

template<typename Key, typename Value, typename HashT, typename ComparatorT>
typename Hashtable<Key, Value, HashT, ComparatorT>::iterator Hashtable<Key, Value, HashT, ComparatorT>::begin() {
    return iterator(this, 0);
}

template<typename Key, typename Value, typename HashT, typename ComparatorT>
typename Hashtable<Key, Value, HashT, ComparatorT>::iterator Hashtable<Key, Value, HashT, ComparatorT>::end() {
    return iterator(this, buckets_.size());
}

template<typename Key, typename Value, typename HashT, typename ComparatorT>
typename Hashtable<Key, Value, HashT, ComparatorT>::const_iterator Hashtable<Key, Value, HashT, ComparatorT>::begin() const {
    return const_iterator(this, 0);
}

template<typename Key, typename Value, typename HashT, typename ComparatorT>
typename Hashtable<Key, Value, HashT, ComparatorT>::const_iterator Hashtable<Key, Value, HashT, ComparatorT>::end() const {
    return const_iterator(this, buckets_.size());
}

// Реализация `rehash`
template<typename Key, typename Value, typename HashT, typename ComparatorT>
void Hashtable<Key, Value, HashT, ComparatorT>::rehash(size_t new_bucket_count) {
    std::vector<std::optional<KeyValuePair>> new_buckets(new_bucket_count);
    for (const auto& bucket : buckets_) {
        if (bucket.has_value()) {
            size_t new_index = hash_(bucket->first) % new_bucket_count;
            while (new_buckets[new_index].has_value()) {
                new_index = (new_index + 1) % new_bucket_count;
            }
            new_buckets[new_index] = bucket;
        }
    }
    buckets_.swap(new_buckets);
}

#endif // HASHTABLE_HPP
*/