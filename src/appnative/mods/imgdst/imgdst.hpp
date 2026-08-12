#pragma once

#include <QImage>
#include <QFileInfo>
#include <QPainter>

#include "vhliboptimal.hpp"


class VHImageDestination {

    public:

        /**
         * 
         */
        void generateOutPic(
            const QImage & imgsrc,
            const vhliboptimal::VHLibOptimal & detector,
            const QString & fileout )
        {

            imgdst = QImage(imgsrc.width(), imgsrc.height(), QImage::Format_RGB32);
            imgdst.fill(Qt::black);

            int pwdth = (imgsrc.width() / 1000) + 1;

            QColor colorpen = QColor(0, 0, 192);
            QColor colorbrs = QColor(0, 0, 100);

            {

                for(int fign = 0; fign < detector.ObjectsCount(); fign++) {

                    const vhliboptimal::VHOptimalFigure & obj = detector.Object(fign);
                    const vhliboptimal::CellsMatrix & cmtx = detector.GetCMatrix();

                    // Fill cells
                    {
                        QPainter painter(&imgdst);

                        painter.setPen  (colorpen);
                        painter.setBrush(colorbrs);

                        for(uint32_t spann=0; spann < obj.SpansCount(); spann++) {
                            uint32_t globalidx = obj.StartSpanIDX() + spann;
                            const vhliboptimal::spanword word = detector.GetGlobalSpan(globalidx);
                            int cellid = vhliboptimal::get_span_id    (word);
                            int spanwd = vhliboptimal::get_span_len   (word);

                            for(int celln=cellid; celln < (cellid + spanwd); celln++) {
                                auto [cx, cy] = cmtx.CellXY(celln);
                                int cs = 1; // detector.CellSZ();
                                painter.drawRect(cx * cs, cy * cs, cs, cs);
                            }
                        }

                        painter.end();
                    }

                    // max size
                    const vhliboptimal::VHArea & area = obj.Area();
                    {
                        auto [cx, cy] = cmtx.CellXY(area.cellid);
                        int cs = 1; // detector.CellSZ();
                        int x = cx * cs;
                        int y = cy * cs;
                        int w = area.cntx * cs;
                        int h = area.cnty * cs;

                        QPainter painter(&imgdst);

                        painter.setPen( QPen(QColor(0, 255, 0), pwdth));
                        painter.setBrush(Qt::NoBrush);
                        painter.drawRect(x, y, w, h);

                        painter.end();
                    }

                }

            }

            // Original image over rects
            {
                for(int y = 0; y < imgsrc.height(); y++) {
                    for(int x = 0; x < imgsrc.width(); x++) {
                        QRgb pxl = imgsrc.pixel(x, y);
                        if(qBlue(pxl)>200)
                            imgdst.setPixel(x, y, pxl);
                    }
                }
            }

            imgdst.save(fileout, "jpg", 50);

        }


    private:

        QImage imgdst;
};

