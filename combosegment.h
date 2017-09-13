#ifndef COMBOSEGMENT_H
#define COMBOSEGMENT_H

#include "mainwindow.h"

class ComboSegment : public QSpinBox
{
    Q_OBJECT
public:
    explicit ComboSegment(QWidget *parent = 0);
    ~ComboSegment();

    MainWindow *ui;


private slots:

    void redacktirovanieSegmentov (int );


private:


};



#endif // COMBOSEGMENT_H
