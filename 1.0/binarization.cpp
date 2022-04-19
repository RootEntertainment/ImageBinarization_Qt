#include <binarization.h>
#include <QDebug>

Binarization::Binarization(QImage img){
    if(!img.isNull()) originImg=img;

    threshold=0;
}
void Binarization::toGray(){
    int w=originImg.width();
    int h=originImg.height();

    QImage gray(w, h, QImage::Format_Grayscale8);
    QRgb rgbVal;
    int grayVal;
    QRgb graypix;

    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            rgbVal=originImg.pixel(i,j);
            grayVal=qGray(rgbVal);//(r*11+g*16+b*5)/32
            graypix=QColor(grayVal,grayVal,grayVal).rgb();
            gray.setPixel(i,j,graypix);
        }
    }

    grayImg=gray;

    return ;
}
int Binarization::otsu(){
    int w=originImg.width();
    int h=originImg.height();
    unsigned int sum=w*h;
    unsigned int hist[256];

    double w0;
    double w1;
    double u0;
    double u1;
    double g;
    double gmax=0.0;
    int k=0;
    int t[270];

    for(int i=0; i<=255; i++) hist[i]=0;

    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            hist[qRed(originImg.pixel(i,j))]++;
        }
    }

    for(int i=0; i<=255; i++){
        w0=0;
        u0=0;
        for(int j=0; j<i; j++){
            w0+=hist[j];
            u0+=hist[j]*j;
        }
        if(w0!=0) u0=u0*1.0/w0;
        w0=w0*1.0/sum;

        w1=0;
        u1=0;
        for(int j=i; j<=255; j++){
            w1+=hist[j];
            u1+=hist[j]*j;
        }
        if(w1!=1) u1=u1*1.0/w1;
        w1=w1*1.0/sum;

        g=w0*w1*(u0-u1)*(u0-u1);

        if(g==gmax){
            k++;
            t[k]=i;
        }
        if(g>gmax){
            gmax=g;
            k=1;
            t[k]=i;
        }

        /*
        if(g>gmax){
            gmax=g;
            threshold=i;
        }
        */
    }

    for(int i=1; i<=k; i++){
        threshold+=t[i];
    }

    threshold/=k;
    return threshold;
}
void Binarization::toBin(){
    int w=originImg.width();
    int h=originImg.height();
    QImage bin(w, h, QImage::Format_Grayscale8);
    if(grayImg.isNull()) toGray();
    qDebug()<<otsu();
    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            if(qRed(grayImg.pixel(i,j))>=threshold) bin.setPixel(i,j,QColor(255,255,255).rgb());
            else bin.setPixel(i,j,QColor(0,0,0).rgb());
        }
    }

    binImg=bin;
    return;
}

QImage Binarization::showGray(){
    if(grayImg.isNull()){
        toBin();
    }
    return grayImg;
}
QImage Binarization::showBin(){
    if(binImg.isNull()){
        toBin();
    }
    return binImg;
}
Binarization::Binarization(){

}
