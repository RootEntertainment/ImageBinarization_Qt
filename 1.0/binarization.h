#ifndef BINARIZATION_H
#define BINARIZATION_H

#include <QImage>
#include <QColor>

using namespace std;

class Binarization{

public:
    Binarization(QImage img);
    Binarization();
    QImage showGray();
    QImage showBin();

    int otsu();
private:
    QImage originImg;
    QImage grayImg;
    QImage binImg;

    void toBin();
    void toGray();
    int threshold;
};


#endif // BINARIZATION_H
