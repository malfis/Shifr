#ifndef SPINSEGMENTRK_H
#define SPINSEGMENTRK_H


#include "mainwindow.h"

class SpinSegmentRK : public QSpinBox
{
    Q_OBJECT
public:
    explicit SpinSegmentRK(QWidget *parent = 0);
    ~SpinSegmentRK();

    MainWindow *ui;


private slots:

    void redacktirovanieSegmentov (int );


private:


};

#endif // SPINSEGMENTRK_H
