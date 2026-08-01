#pragma once

#include <QImage>
#include <QFileInfo>


class VHImageSource {

    public:

        /**
         * 
         */
        verr load(const std::string & fname) {

            QString fileName = QString::fromStdString(fname);

            if(!imgsrc.load(fileName))
                return verror(1);

            imgbw8 = imgsrc.convertToFormat(QImage::Format_Grayscale8);

            return vok;
        }

        /**
         * 
         */
        verr convert(

            // Source window props
            int gfxstartx, int gfxstarty,

            // Cells count & scale
            size_t cntx, size_t cnty, uint8_t levelcs,

            // Grid props
            const vhliboptimal::CellsMatrix & cmtx,

            // Bitfield
            vhliboptimal::BitField & bfld,

            uint8_t filterLevel
        ) {

            // Check image format
            QImage::Format fmt = imgbw8.format();
            if(fmt != QImage::Format_Grayscale8) return verrmsg(1, "B&W SRC Image format only");

            // Clearing previous
            bfld.Clear(cmtx);

            // Border always '0'
            size_t maxx = cmtx.CellsX() - 1;
            size_t maxy = cmtx.CellsY() - 1;

            // Actual sampling cells
            size_t samplingx = cntx > maxx ? maxx : cntx;
            size_t samplingy = cnty > maxy ? maxy : cnty;

            int cellsz = 1 << levelcs;
            int area_pxls_w = cntx << levelcs;
            int area_pxls_h = cnty << levelcs;

            // j:i
            for(int j=1; j < samplingy; j++) {
                for(int i=1; i < samplingx; i++) {
                    bool avail = CheckCell(gfxstartx, gfxstarty, cellsz, filterLevel, i, j);
                    uint32_t celln = cmtx.CellN(i, j);
                    if(avail) {
                        bfld.SetCell(celln);
                    } else {
                        bfld.ClrCell(celln);
                    }
                }
            }

            return vok;
        }

        /**
         * 
         */
        const QImage & GetImage() {
            return imgsrc;
        };

        /**
         * 
         */
        const QImage & GetBWImage() {
            return imgbw8;
        };

        /**
         * 
         */
        void saveResults(const std::string & srcfname) {

            QFileInfo info(QString::fromStdString(srcfname));

            QString file1 = info.baseName() + "_src.jpg";
            QString file2 = info.baseName() + "_bw8.jpg";

            imgsrc.save(file1, "jpg", 50);
            imgbw8.save(file2, "jpg", 50);

        }

    private:

        QImage imgsrc;
        QImage imgbw8;


        bool CheckWhiteLevel(const uint8_t *parr, size_t blocklen, uint8_t whitelevel) const noexcept {
            for(size_t i=0; i < blocklen;i++) {
                if(parr[i] >= whitelevel) return true; }
            return false; }

        //
        bool CheckCell(int posx, int posy, int cellsize, uint8_t whitelevel, size_t cellx, size_t celly) {

            int gfxpossx = cellx * cellsize;
            int gfxpossy = celly * cellsize;
            int gfxposex = gfxpossx + cellsize;
            int gfxposey = gfxpossy + cellsize;

            if(gfxpossx < 0) return false;
            if(gfxposex >= imgbw8.width()) return false;
            if(gfxpossy < 0) return false;
            if(gfxposey >= imgbw8.height()) return false;

            for(int j=0;j<cellsize;j++) {
                const uint8_t * line = imgbw8.scanLine(gfxpossy+j);
                const uint8_t * cellpxlx = line + gfxpossx;
                bool found = CheckWhiteLevel(cellpxlx, cellsize, whitelevel);
                if(found) return true;
            }

            return false;
        }

};


// Out of X-Y ?
// if(startx + area_pxls_w >= imgsrc.width())  return verror(2);
// if(starty + area_pxls_h >= imgsrc.height()) return verror(3);

//         
//         
//         bool  avail = CheckWhiteLevel(cellpxlx, cellsz, filterLevel);
