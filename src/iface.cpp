#include "vhplatform.hpp"
#include "vhliboptimal.hpp"

#include <QImage>

using namespace vhliboptimal;

const QImage & GetOptimalQImage();


/** 
 * 
 */
void IFACE_OPTIMAL_GetLinePixels(
    void *userData,
    uint8_t *dstptr,
    uint16_t bytescnt,
    uint16_t srcid,
    uint16_t srcx,
    uint16_t srcy
) {

    // static std::vector<uint8_t> r;
    // // settings changed ( cellsize ) - reallocate buffer
    // if(r.empty() || r.size() != bytescnt) { r = std::vector<uint8_t>(bytescnt); }

    const QImage & img = GetOptimalQImage();
    //     QImage::Format fmt = img.format();

    // Out of Y ?
    if( srcy >= img.height() ) {
        std::memset(dstptr, 0, bytescnt);
        return;
    }

    const uint8_t *line = img.scanLine(srcy);
    int depth = img.depth();
    int bytesPerPixel = depth / CHAR_BIT;
    int bytesAvail = img.width() - srcx;
    uint8_t c;

    for(int i=0; i < bytescnt; i++) {

        // RGBA > 256 B&W, яркость по формуле NTSC
        if(i < bytesAvail) {
            const uint8_t *pixel = line + ((i + srcx) * bytesPerPixel);
            c = static_cast<uint8_t>(0.299*pixel[2] + 0.587*pixel[1] + 0.114*pixel[0]);
        } else {
            c = 0;
        }
        dstptr[i] = c;
    }

}

/**
 * 
 */
void IFACE_OPTIMAL_Border(
    void *userData,
    uint8_t cmd,
    uint8_t dirh, 
    uint8_t dirv,
    uint16_t cellx,
    uint16_t celly, 
    uint16_t imgx,
    uint16_t imgy
) {

    // if(cmd == VHOptimalFigure::cmdStart) std::cout << std::endl;
    // std::string msg = std::format(
    //     "cmd={} dirh={} dirv={} cx:cy={}:{} x:y={}:{}",
    //     cmd, dirh, dirv, cellx, celly, pxlx,pxly);
    // std::cout << msg << std::endl;
}

/**
 * 
 */
void IFACE_OPTIMAL_Content(
    void *userData,
    uint32_t cell1,
    uint32_t cell2,
    uint8_t dir
) {

}