#include "vhargs.hpp"

/**
 * 
 */
std::string vhargstr(int argn, int argc, char *argv[]) {
    std::string r;

    if(argn + 2 <= argc) {
        r = std::string(argv[argn+1]);
    }

    return r;
}

/**
 * 
 */
int vhargint(int argn, int argc, char *argv[]) {

    std::string param = vhargstr(argn, argc, argv);

    if(param.empty())
        return -1;

    int r = std::stoi(param);

    return r;
}
