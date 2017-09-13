#include "spinsegmentrk.h"

SpinSegmentRK::SpinSegmentRK(QWidget *parent):
    QSpinBox (parent)
{
    ui=NULL;
    connect(this , SIGNAL(valueChanged(int)),this,SLOT(redacktirovanieSegmentov(int)));
}

SpinSegmentRK::~SpinSegmentRK()
{

}

void SpinSegmentRK::redacktirovanieSegmentov (int )
{
    if (ui!=NULL) ui->updateRayndKey();
}
