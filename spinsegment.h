#ifndef SPINSEGMENT_H
#define SPINSEGMENT_H

#include "mainwindow.h"

class SpinSegment : public QSpinBox
{
    Q_OBJECT
public:
    explicit SpinSegment(QWidget *parent = 0);
    ~SpinSegment();

    MainWindow *ui;


private slots:

    void redacktirovanieSegmentov (int );


private:


};

#endif // SPINSEGMENT_H
