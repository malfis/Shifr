#include "knopkagenak.h"
#include "combosegmentk.h"

KnopkaGenaK::KnopkaGenaK(QWidget *parent):
    QPushButton (parent)
{
    ui=NULL;
    connect(this , SIGNAL(clicked(bool )),this,SLOT(Generate(bool )));
}

KnopkaGenaK::~KnopkaGenaK()
{

}

void KnopkaGenaK::Generate (bool )
{
    if (ui!=NULL) ui->KeySegmentGen(ui->sk(ui->nr())->value());
}
