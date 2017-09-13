#ifndef SPINSEGMENTK_H
#define SPINSEGMENTK_H


#include "mainwindow.h"

class SpinSegmentK : public QSpinBox
{
    Q_OBJECT
public:
    explicit SpinSegmentK(QWidget *parent = 0);
    ~SpinSegmentK();

    MainWindow *ui;


private slots:

    void redacktirovanieSegmentov (int );


private:


};

#endif // SPINSEGMENTK_H
