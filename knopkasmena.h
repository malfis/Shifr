#ifndef KNOPKASMENA_H
#define KNOPKASMENA_H

#include "mainwindow.h"

class KnopkaSmena : public QPushButton
{
    Q_OBJECT
public:
    explicit KnopkaSmena(QWidget *parent = 0);
    ~KnopkaSmena();

    MainWindow *ui;

private slots:

    void Smena (bool );


private:


};

#endif // KNOPKASMENA_H
