#include "main.hpp"
#include "vhargs.hpp"

#include "testcontainer/testcontainer.hpp"


TestLibraryContainer testContainer;


verr ProcessInputFile(int argc, char *argv[]) {

    // QImage testImage;

    // // Parameter #1 - FileName
    // std::string paramFileName = vhargstr(0, argc, argv);
    // if(paramFileName.size()) {

    //     // filename to console
    //     vhliboptimal::log::partout("File Name: ");
    //     vhliboptimal::log::lineout(paramFileName.c_str());

    //     // Read source image
    //     QString fname = QString::fromStdString(paramFileName);
    //     bool flagtry = testImage.load(fname);
    //     if(!flagtry)
    //         return verrmsg(1, "Invalid filename: " + paramFileName);
        
    //     // Convert to Grayscale ?
    // }


    // // Parameter #2 - GridSize
    // uint8_t paramCellSize = vhargint(1, argc, argv);
    // if(paramCellSize == -1) { paramCellSize = 2; }



    return verror(1);
}

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
    verr result = testContainer.StartTests();
    if(result)  std::cout << "Error: " << result;
    else        std::cout << "Done";

    std::cout << std::endl;

    return result;
}
