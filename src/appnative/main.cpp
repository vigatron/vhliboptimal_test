#include "main.hpp"
#include "vhargs.hpp"

#include "testcontainer/testcontainer.hpp"

TestLibraryContainer testContainer;

/**
 * Parsing args and starting TestLibraryContainer 
 * 
 * "fname"      // 
 * "startx"     // 0 default
 * "starty"     // 0 default
 * "width"      // 0 auto
 * "height"     // 0 auto
 * 
 * Test single file (passed as parameter)
 * Test linked 512x512 B&W examples 1-7
 */
int main(int argc, char *argv[]) {

    //
    verr retInit = testContainer.Init();
    if(retInit)
        return verrmsg(100, "Initialization Error");
    //
    verr result = testContainer.StartTests();
    if(result)  std::cout << "Error: " << result;
    else        std::cout << "Done";

    std::cout << std::endl;

    return result;
}
