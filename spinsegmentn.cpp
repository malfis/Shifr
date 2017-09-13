#include "spinsegmentn.h"

SpinSegmentN::SpinSegmentN(QWidget *parent):
    QSpinBox (parent)
{
    ui=NULL;
    connect(this , SIGNAL(valueChanged(int)),this,SLOT(redacktirovanieSegmentov(int)));
}

SpinSegmentN::~SpinSegmentN()
{

}

void SpinSegmentN::redacktirovanieSegmentov (int )
{
    if (ui!=NULL) ui->updateNomer();
}
