#include "spinsegmentk.h"

SpinSegmentK::SpinSegmentK(QWidget *parent):
    QSpinBox (parent)
{
    ui=NULL;
    connect(this , SIGNAL(valueChanged(int)),this,SLOT(redacktirovanieSegmentov(int)));
}

SpinSegmentK::~SpinSegmentK()
{

}

void SpinSegmentK::redacktirovanieSegmentov (int )
{
    if (ui!=NULL) ui->updateKey();
}

