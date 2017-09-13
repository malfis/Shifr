#include "spinsegment.h"

SpinSegment::SpinSegment(QWidget *parent):
    QSpinBox (parent)
{
    ui=NULL;
    connect(this , SIGNAL(valueChanged(int)),this,SLOT(redacktirovanieSegmentov(int)));
}

SpinSegment::~SpinSegment()
{

}

void SpinSegment::redacktirovanieSegmentov (int )
{
    if (ui!=NULL) ui->updateZameny();
}

