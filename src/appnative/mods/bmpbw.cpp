#include <QImage>
#include <QString>
#include <QColor>

//
QString infile(QString fname) {
    return "../data/original/" + fname;
}

//
bool cell(const QImage & img, uint16_t x, uint16_t y, uint8_t cs, uint8_t level) {

    QImage::Format fmt = img.format();
    int depth = img.depth() / 8;

    for(uint16_t j=y; j < y+cs; j++) {
        for(uint16_t i=x; i < x + cs; i++) {

            if(i < img.width() && j < img.height()) {
                const uchar *line = img.scanLine(y);
                QColor c = img.pixel(i, j);
                uint8_t color = qGray(c.rgb());
                if(color >= level) return true;
            }

        }
    }

    return false;
}

//
int test_convert_bmp(const QString & fname) {

    //
    QString infnames [] = {
        infile("testimage1r4096.jpg"),      // 0
        infile("testimage2r4096.jpg"),      // 1
        infile("testimage3r1080p.jpg"),     // 2
        infile("testimage4r1080p.jpg"),     // 3
        infile("testimage5rvga.jpg"),       // 4
        infile("testimage6rsvga.jpg"),      // 5
        infile("testimage7r720p.jpg")       // 6
    };

    //
    int samplen = 6;
    QString inFileName = infnames[samplen];
    QString  outFileName = "out" + QString::number(samplen+1) + ".bmp";

    // Load original
    QImage originalImage;
    if(!originalImage.load(inFileName))
        return 1;

    //
    uint8_t cs = (1<<2);
    int w = originalImage.width()   / cs;
    int h = originalImage.height()  / cs;

    // создаём монохромный QImage
    QImage bw(w, h, QImage::Format_Mono);

    // палитра: 0 = чёрный, 1 = белый
    QVector<QRgb> bwPalette(2);
    bwPalette[0] = qRgb(0, 0, 0);
    bwPalette[1] = qRgb(255, 255, 255);
    bw.setColorTable(bwPalette);

    // заполняем картинку простым паттерном (шахматка)
    for (int y = 0; y < h; ++y) {
        uchar *line = bw.scanLine(y);
        for (int x = 0; x < w; ++x) {

            bool pixel = cell(originalImage, x * cs, y * cs, cs, 128);
            if (pixel)  line[x >> 3] |=  (1 << (7 - (x & 7))); // ставим бит
            else        line[x >> 3] &= ~(1 << (7 - (x & 7))); // очищаем бит
        }
    }    

    // сохраняем в BMP
    bw.save(outFileName, "BMP");

    return 0;
}
