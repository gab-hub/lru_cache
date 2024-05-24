#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include "lru_cache.hpp"
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <vector>

// call print in put and then make print private
// preprocess definition ndebug --> check debug
//reorganize this file
/* 
#ifdef NDEBUG
	#define log_info(...)
	#define display_lru()
#else
	#define log_info(...) printf(__VA_ARGS__);
	#define display_lru() display();
#endif

^ have different functions here if you are in debug or no
*/
// search for it in the cache rotate and push to the top of the stack
// if it found the item (and print it there)
// testing suite
// contracts: See if size input is int ,Check if input later is URL for specific kind of cache 
// Generic container lru cache and outer cache makes it more specific URL 
// Use assert (see alan 1:1 links) and catch3 libraries 
// See if you can use this 
// https://git.alteryx.com/devsec/cryptolib/-/blob/latest-nightly/Library/include/CryptoImpl/Contracts.h 
// https://git.alteryx.com/devsec/katas/-/tree/katas_cpp_alan?ref_type=heads 
/*volatile
§ Lambda function for rotate’  
§ destructor
§ Give back a const copy bc it’s a library  --> actually no 
□ Think how vectors work and write library similar 
□ New vector, rvo to copy, and return? 
◊ Return value optimization 
□ For comments, what would it look like to implement? Why would i do this? 
□ Do const iterator... can’t change underlying data structure bc it’s just a pointer under the hood 
□ Look at vector implementation 
□ Implent index ones and at 
Access to use range-based algorithm in case people decide to filter*/
// gcc file treat warnings as error -wall?

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

/* Gabriela Gonzalez
April 18, 2024
This program creates an LRU cache */



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