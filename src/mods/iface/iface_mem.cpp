#include "iface.hpp"
#include "vhliboptimalstructs.hpp"
#include "vhliboptimal.hpp"



namespace vhliboptimal {

// Массив фигур
static std::vector<VHOptimalFigure>         arrObjects;

// Содержит в себе массив участков:
// spanlen [31 .. 21] + spanid  [20 ..  0]
static std::vector<uint32_t>                arrSpans;

//
static std::vector<uint8_t>                 buffArrSrc;

//
static std::vector<uint8_t>                 buffArrDst;


/**
 *
 */
void VHLIB_OPTIMAL_IFACE_FrameReset() {

    vhliboptimal::arrObjects        .reserve    ( VHOPTIMAL_OBJECTS_MAX  );
    vhliboptimal::arrSpans          .reserve    ( VHOPTIMAL_SPANS_MAX    );

    vhliboptimal::arrObjects    .clear();

    vhliboptimal::arrSpans      .clear();

    //
    uint32_t w = 1 << VHOPTIMAL_GRID_X_LEVEL;
    uint32_t h = 1 << VHOPTIMAL_GRID_Y_LEVEL;
    uint32_t s = (w>>3) * h;

    //
    buffArrSrc.assign(s, 0);

    //
    buffArrDst.assign(s, 0);

}

/**
 *
 */
VHOptimalFigure & VHLIB_OPTIMAL_IFACE_Object(int objn) {
    return arrObjects[objn];
}

/**
 *
 */
bool VHLIB_OPTIMAL_IFACE_AddObject() {
    bool memavail = (arrObjects.size() < VHOPTIMAL_OBJECTS_MAX) ? true : false;

    if(memavail) {
        VHOptimalFigure obj;
        arrObjects.push_back(obj);
    }

    return memavail;
}

/**
 *
 */
bool VHLIB_OPTIMAL_IFACE_RemoveObject() {

    if(arrObjects.size()) {
        arrObjects.pop_back();
        return true;
    }

    return false;
}

/**
 *
 */
int VHLIB_OPTIMAL_IFACE_ObjectsCount() {
    return arrObjects.size();
}

/**
 *
 */
verr VHLIB_OPTIMAL_IFACE_AddSpan(vhliboptimal::spanword dword) {
    if(arrSpans.size() >= VHOPTIMAL_SPANS_MAX) return verror(1);
    arrSpans.push_back(dword);
    return vok;
}

/**
 *
 */
const vhliboptimal::spanword VHLIB_OPTIMAL_IFACE_GetSpan(int spanid) {
    if(spanid >= VHOPTIMAL_SPANS_MAX) return 0;
    return arrSpans[spanid];
}

/**
 *
 */
const int VHLIB_OPTIMAL_IFACE_GetSpansCount() {
    return arrSpans.size();
}

/**
 * 
 */
uint8_t * VHLIB_OPTIMAL_IFACE_BitFieldSrcPtr() {
    return buffArrSrc.data();
}

/**
 * 
 */
uint8_t * VHLIB_OPTIMAL_IFACE_BitFieldDstPtr() {
    return buffArrDst.data();
}

};

