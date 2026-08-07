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



    struct stConfig {
        std::string fname;
        uint16_t offssx;
        uint16_t offssy;
        uint16_t width;
        uint16_t height;

    };

    // Parse Command line file


    // B) Embedded .bmp example   : Autosize to grid

    // First parameter: FileName
    std::string paramFileName = vhargstr(0, argc, argv);
    if(paramFileName.empty())
        return 1;

    #ifdef VHAPP_OPTIMAL_TEST_CONVERT_BMP
    int test_convert_bmp(const QString & fname);
    return test_convert_bmp(QString::fromStdString(paramFileName));
    #endif

    // Second param GridSize
    int paramCellSize = vhargint(1, argc, argv);
    if(paramCellSize == -1) { paramCellSize = 2; }


    verr result = testContainer.runtest(paramFileName, __builtin_ctz(paramCellSize));

    return result;
}
