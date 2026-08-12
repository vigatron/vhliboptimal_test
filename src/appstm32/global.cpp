#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"

//
#include "vhliboptimal.hpp"

//
#include "classes/cmdlinebuff.hpp"

//
#include "benchmark/benchmark.hpp"


VHCommandLineBuffer cmdLine;

//
static constexpr char strlineInfo       []  = "Processing System Info ...";
static constexpr char strlineMem        []  = "MEM@XXXX";

static constexpr char strlineUnknown    []  = "? Unknown command";

void SendText(const char * txt);
void SendTextLine(const char * txt);

verr VHLIBOptimalRun();



void VHAppInitGlobalVars() {
    VHTimeStamp::Init();
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

        VHLIBOptimalRun();

    } else if(cmdLine.iscmd(VHCommandLineBuffer::cmdm)) {

        SendTextLine(strlineMem);

    } else if(!cmdLine.data()[0]) {

        // SendTextLine("");

    } else {

        SendTextLine(strlineUnknown);

    }

    cmdLine.reset();
}
