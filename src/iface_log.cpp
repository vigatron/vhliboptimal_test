#include "vhplatform.hpp"


/**
 * 
 */
verr verrmsg(int x, const char * txt) {
    std::cout << txt << std::endl;
    return x;
}

/**
 * 
 */
verr verrmsg(int x, std::string strerr) {
    std::cout << strerr << std::endl;
    return x;
}
