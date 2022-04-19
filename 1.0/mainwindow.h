#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QImage>
#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <binarization.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPushButton* choosepic;
    QLabel* showpic;
    QLabel* graypic;
    QLabel* binarizationpic;
    QPushButton* tobinBtn;
    QPushButton* saveBtn;

public slots:
    void setpic();
    void showBin();
    void saveImg();
private:
    QImage pic;
    Binarization bi;
    bool isbin;
    QString imagedir;
protected:
    virtual void resizeEvent(QResizeEvent *event);
};
#endif // MAINWINDOW_H
