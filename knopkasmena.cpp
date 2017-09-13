#include "knopkasmena.h"

KnopkaSmena::KnopkaSmena(QWidget *parent):
    QPushButton (parent)
{
    ui=NULL;
    connect(this , SIGNAL(clicked(bool )),this,SLOT(Smena(bool )));
}

KnopkaSmena::~KnopkaSmena()
{

}

void KnopkaSmena::Smena (bool )
{
    if (ui!=NULL) ui->perekluchenie();
}
