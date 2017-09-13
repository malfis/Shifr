#ifndef KNOPKAGENAZ_H
#define KNOPKAGENAZ_H

#include "mainwindow.h"

class KnopkaGenaZ : public QPushButton
{
    Q_OBJECT
public:
    explicit KnopkaGenaZ(QWidget *parent = 0);
    ~KnopkaGenaZ();

    MainWindow *ui;

private slots:

    void Generate (bool );


private:


};

#endif // KNOPKAGENAZ_H
