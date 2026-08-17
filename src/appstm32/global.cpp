#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"

//
#include "vhliboptimal.hpp"

//
#include "classes/cmdlinebuff.hpp"

//
#include "timer/vhtimerstamp.hpp"

//
#include "testcontainer/testcontainer.hpp"

//
VHCommandLineBuffer cmdLine;

//
TestLibraryContainer testContainer;

//
static constexpr char strlineInfo       []  = "Processing System Info ...";
static constexpr char strlineMem        []  = "MEM@XXXX";

static constexpr char strlineUnknown    []  = "? Unknown command";

void SendText(const char * txt);
void SendTextLine(const char * txt);


void VHAppInitGlobalVars() {
    VHTimerStamp::init();
}

/**
 * 
 */
void execcmd() {

    printf("\r\n");

    // 
    if(cmdLine.iscmd(VHCommandLineBuffer::cmdi)) {

        SendTextLine(strlineInfo);

    } else if(cmdLine.iscmd(VHCommandLineBuffer::cmde)) {

        verr result = testContainer.StartTests();
        printf("testContainer() ");
        if(!result) {
            printf("Done\n"); }
        else {
            printf("Error: %d\n", (int)result);
        }


    } else if(cmdLine.iscmd(VHCommandLineBuffer::cmdm)) {

        SendTextLine(strlineMem);

    } else if(!cmdLine.data()[0]) {

        // SendTextLine("");

    } else {

        SendTextLine(strlineUnknown);

    }

    cmdLine.reset();
}
