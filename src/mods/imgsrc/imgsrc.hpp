#pragma once

#include <QImage>
#include <QFileInfo>


class VHImageSource {

    public:

        verr load(const std::string & fname) {
            QString fileName = QString::fromStdString(fname);
            bool flagl = imgsrc.load(fileName);
            return flagl ? vok : verror(1);
        }

        verr convert(int cellsize) {

            imgbw8 = imgsrc.convertToFormat(QImage::Format_Grayscale8);

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

};
