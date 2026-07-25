#include "vhplatform.hpp"
#include "vhliboptimal.hpp"

#include <QImage>

using namespace vhliboptimal;

const QImage & GetOptimalQImage();


/** 
 * Load pixels line starting from (x,y)
 */
const std::vector<uint8_t> & IFACE_OPTIMAL_GetLinePixels(uint16_t pxlx, uint16_t pxly, uint16_t cnt) {

    static std::vector<uint8_t> r;

    if(r.empty()) {
        r = std::vector<uint8_t>(cnt);
    }

    const QImage & img = GetOptimalQImage();

    int pxlsInLineAvail = img.width() - pxlx;
    int bytesRead = (cnt > pxlsInLineAvail) ? pxlsInLineAvail : cnt;

    if(pxly < img.height()) {

        const uint8_t *line = img.scanLine(pxly);
        QImage::Format fmt = img.format();
        int depth = img.depth();
        int bytesPerPixel = depth / CHAR_BIT;

        for(int i=0; i<bytesRead;i++) {

            // RGBA
            const uint8_t *pixel = line + ((i+pxlx) * bytesPerPixel);

            // яркость по формуле NTSC
            uint8_t gray = static_cast<uint8_t>(0.299*pixel[2] + 0.587*pixel[1] + 0.114*pixel[0]);
            r[i] = gray;
        }
    }

    for (uint8_t val : r) {
        if (val != 0) {
            asm("nop"); // Нашли ненулевой элемент, сразу выходим
        }
    }

    return r;
}

/**
 * 
 */
void IFACE_OPTIMAL_SetPos(
    uint8_t cmd,
    uint8_t dirh,
    uint8_t dirv,
    uint16_t cellx,
    uint16_t celly,
    uint16_t pxlx,
    uint16_t pxly)
{
    if(cmd == VHOptimalFigure::cmdStart) std::cout << std::endl;

    std::string msg = std::format(
        "cmd={} dirh={} dirv={} cx:cy={}:{} x:y={}:{}",
        cmd, dirh, dirv, cellx, celly, pxlx,pxly);

    std::cout << msg << std::endl;
}
