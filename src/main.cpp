#include "lru_cache.hpp"
#include <string>

int main(int argc, char* argv[]) {
    int size;

    // Checking if size has been provided by user
    if(argc > 1) {
        size = std::stoi(argv[1]);
    } else {
        size = 5; // Default
    }

    lru_cache<std::string> cache(size);

    // Test the put method
    cache.put("www.google.com");
    cache.put("www.google.com");
    cache.put("www.microsoft.com");
    cache.put("www.apple.com");
    cache.put("www.zillow.com");
    cache.put("www.alteryx.com");
    cache.put("www.columbia.edu");
    cache.put("www.harvard.edu");
    cache.put("www.apple.com");
    cache.put("www.zillow.com");
    
    cache.clear();
    cache.print();
    return 0;
}
