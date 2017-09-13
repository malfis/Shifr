#ifndef SPINSEGMENTN_H
#define SPINSEGMENTN_H


#include "mainwindow.h"

class SpinSegmentN : public QSpinBox
{
    Q_OBJECT
public:
    explicit SpinSegmentN(QWidget *parent = 0);
    ~SpinSegmentN();

    MainWindow *ui;


private slots:

    void redacktirovanieSegmentov (int );


private:


};

#endif // SPINSEGMENTN_H
