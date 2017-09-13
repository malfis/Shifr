#ifndef COMBOSEGMENTK_H
#define COMBOSEGMENTK_H


#include "mainwindow.h"

class ComboSegmentK : public QSpinBox
{
    Q_OBJECT
public:
    explicit ComboSegmentK(QWidget *parent = 0);
    ~ComboSegmentK();

    MainWindow *ui;



private slots:

    void redacktirovanieSegmentov (int );


private:


};


#endif // COMBOSEGMENTK_H
