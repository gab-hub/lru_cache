/* Gabriela Gonzalez
April 18, 2024
This program creates an LRU cache */


#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include "lru_cache.hpp"
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <vector>


template <typename T>
class lru_cache
{
public:
    lru_cache(int capacity) : m_capacity(capacity) {}
    void put(const T& url);
    void print() const;
    void clear();
private:
    int m_capacity; // module level
    std::unordered_set<T> cache_items;
    std::vector<T> cache_order;
    void print_cache_items() const;
    bool correct_cache() const;
    void rearrange_cache(const T& url);
};


/* Places item in cache and checks for other important conditions */
template <class T>
void lru_cache<T>::put(const T& item) {
    /* Check if item is cached */
    if (cache_items.find(item) != cache_items.end()) {
        rearrange_cache(item);
    } else {
        /* Cache item */
        if (cache_items.size() >= m_capacity) {
            const T last_item = cache_order.back();
            cache_order.pop_back();
            cache_items.erase(last_item);
        }
        cache_items.insert(item);
        cache_order.insert(cache_order.begin(), item);
    }
}


/* Prints items in cache in LRU order */
template <class T>
void lru_cache<T>::print() const{
    for (const T& item : cache_order) {
        std::cout << item << std::endl;
    }
    std::cout << " " << std::endl;
}


/* Clears the cache */
template <class T>
void lru_cache<T>::clear() {
    cache_order.clear();
    cache_items.clear();
    std::cout << "Cache has been cleared" << std::endl;
}

/* Used for testing purposes to print items in set */
template <class T>
void lru_cache<T>::print_cache_items() const {
    for (const T& item : cache_items) {
        std::cout << item << std::endl;
    }
}


/* Used for testing purposes to see if vector and set
    contain  the same items */
template <class T>
bool lru_cache<T>::correct_cache() const{
    if (cache_order.size() != cache_items.size()) {
        return false; 
    }
    for(const T& item : cache_order) {
        if (cache_items.find(item) == cache_items.end()) {
            return false;
        }
    }
    return true;
}

/* Rearranges already cached items for correct order */
template <class T>
void lru_cache<T>::rearrange_cache(const T& item) {
    auto it = std::find(cache_order.begin(), cache_order.end(), item);
    std::rotate(cache_order.begin(), it, it+1);
}


#endif // LRU_CACHE_HPP