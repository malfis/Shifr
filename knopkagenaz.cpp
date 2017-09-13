#include "knopkagenaz.h"
#include "combosegment.h"

KnopkaGenaZ::KnopkaGenaZ(QWidget *parent):
    QPushButton (parent)
{
    ui=NULL;
    connect(this , SIGNAL(clicked(bool )),this,SLOT(Generate(bool )));
}

KnopkaGenaZ::~KnopkaGenaZ()
{

}

void KnopkaGenaZ::Generate (bool )
{
    if (ui!=NULL) ui->ZamenaSegmentGen(ui->sz(ui->nr())->value());
}
