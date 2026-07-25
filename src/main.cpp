#include "vhplatform.hpp"
#include "vhliboptimal.hpp"

#include <QImage>


static QImage imgsrc;


const std::vector<uint8_t> & IFACE_OPTIMAL_GetLinePixels(
    uint16_t pxlx,
    uint16_t pxly,
    uint16_t cnt);

void IFACE_OPTIMAL_SetPos(
    uint8_t cmd,
    uint8_t dirh,
    uint8_t dirv,
    uint16_t cellx,
    uint16_t celly,
    uint16_t pxlx,
    uint16_t pxly);

/**
 * 
 */
const QImage & GetOptimalQImage() {
    return imgsrc;
};

/**
 * 
 */
std::string vharg(int argn, int argc, char *argv[]) {
    std::string r;

    if(argn + 2 <= argc) {
        r = std::string(argv[argn+1]);
    }

    return r;
}

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

/**
 * 
 */
verr runtest(const std::string & fname) {


    bool flagl = imgsrc.load(QString::fromStdString(fname));
    if(!flagl) {
        return verrmsg(1, "Invalid image file:" + fname);
    }

    //
    vhliboptimal::VHLibOptimal    detector;

    const vhliboptimal::stConfig cfg = {
        .imageWidth     = (uint16_t)imgsrc.width(),
        .imageHeight    = (uint16_t)imgsrc.height(),
        .cellsize       = 16,
        .spccnt         = 0,
        .minColorVal    = 128
    };

    detector.SetLogLevel(vhliboptimal::LOG_LEVEL_EXT);

    verr flag1 = detector.Setup(cfg, IFACE_OPTIMAL_GetLinePixels, IFACE_OPTIMAL_SetPos);
    if(flag1) return verrmsg(1, "Invalid settings");

    verr flag2 = detector.Run();
    if(flag2) return verrmsg(2, "Shape contour detection failed");

    for(int i = 0; i < detector.GetObjectsCount(); i++) {
        const vhliboptimal::VHOptimalFigure & obj = detector.GetObject(i);
        const vhliboptimal::CellsMatrix & cmtx = detector.GetCMatrix();
        obj.Border(cmtx, IFACE_OPTIMAL_SetPos);
    }

    return vok;
}

/**
 * 
 */
int main(int argc, char *argv[]) {

    std::string fname = vharg(0, argc, argv);

    if(!fname.empty()) {
        return runtest(fname);
    }

    return 1;
}
