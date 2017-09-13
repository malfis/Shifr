#include "combosegmentk.h"

ComboSegmentK::ComboSegmentK(QWidget *parent):
    QSpinBox (parent)
{
    ui=NULL;
    connect(this , SIGNAL(valueChanged(int)),this,SLOT(redacktirovanieSegmentov(int)));
}

ComboSegmentK::~ComboSegmentK()
{

}

void ComboSegmentK::redacktirovanieSegmentov (int )
{
    if (ui!=NULL) ui->updatePageK(this->value());
}
