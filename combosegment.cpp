#include "combosegment.h"


ComboSegment::ComboSegment(QWidget *parent):
    QSpinBox (parent)
{
    ui=NULL;
    connect(this , SIGNAL(valueChanged(int)),this,SLOT(redacktirovanieSegmentov(int)));
}

ComboSegment::~ComboSegment()
{

}

void ComboSegment::redacktirovanieSegmentov (int )
{
    if (ui!=NULL) ui->updatePage(this->value());
}


