#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(1280,720);
    choosepic=new QPushButton("选择图片",this);
    choosepic->setGeometry(40,60,100,50);
    connect(choosepic,SIGNAL(clicked(bool)),this,SLOT(setpic()));
    showpic=new QLabel("Please Select a Picture");
    QFont ft;
    ft.setPointSize(15);
    showpic->setFont(ft);
    showpic->setGeometry(680,30,560,315);
    showpic->setAlignment(Qt::AlignCenter);
    showpic->setParent(this);

    tobinBtn=new QPushButton("二值化",this);
    tobinBtn->setGeometry(40,150,100,50);
    connect(tobinBtn,SIGNAL(clicked(bool)),this,SLOT(showBin()));

    graypic=new QLabel("Gray Picture Window",this);
    graypic->setFont(ft);
    graypic->setAlignment(Qt::AlignCenter);
    graypic->setGeometry(40,375,560,315);
    binarizationpic=new QLabel("Binarization Picture Window",this);
    binarizationpic->setFont(ft);
    binarizationpic->setAlignment(Qt::AlignCenter);
    binarizationpic->setGeometry(680,375,560,315);

    saveBtn=new QPushButton("保存灰度与\n二值化图片",this);
    saveBtn->setGeometry(160,60,100,50);
    connect(saveBtn,SIGNAL(clicked(bool)),this,SLOT(saveImg()));

    isbin=false;
    imagedir=QDir::homePath();
}
MainWindow::~MainWindow()
{
}

void MainWindow::setpic(){
    QFileDialog fd;
    QString imagename=fd.getOpenFileName(this,"Open Image",imagedir,"图片(*.jpg *.bmp *.png)");
    if(imagename.isNull()) return;
    pic=QImage(imagename);
    imagedir=QFileInfo(imagename).absolutePath();
    if(!pic.isNull()){
        //showpic->setScaledContents(true);
        showpic->setPixmap(QPixmap::fromImage(pic).scaled(showpic->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        isbin=false;
    }else{
        QMessageBox::information(this,"Caution","Invalid Image");
    }
}
void MainWindow::resizeEvent(QResizeEvent *event){


}
void MainWindow::showBin(){
    if(pic.isNull()){
        QMessageBox::information(this,"Caution","Please Select a Picture");
    }else{
        if(isbin) return;
        bi=Binarization(pic);
        graypic->setPixmap(QPixmap::fromImage(bi.showGray()).scaled(graypic->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        binarizationpic->setPixmap(QPixmap::fromImage(bi.showBin()).scaled(graypic->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        isbin=true;
    }

}
void MainWindow::saveImg(){
    if(pic.isNull()){
        QMessageBox::information(this,"Caution","Please Select a Picture");
    }else{
        if(!isbin){
            showBin();
        }
        QFileDialog *fd=new QFileDialog(this);
        QString s=fd->getExistingDirectory(this,"Save Image",imagedir);
        if(s.isNull()) return;
        bi.showGray().save(s+"/gray.jpg","JPG",100);
        bi.showBin().save(s+"/bin.jpg","JPG",100);
    }

}


