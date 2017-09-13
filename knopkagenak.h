#ifndef KNOPKAGENAK_H
#define KNOPKAGENAK_H


#include "mainwindow.h"

class KnopkaGenaK : public QPushButton
{
    Q_OBJECT
public:
    explicit KnopkaGenaK(QWidget *parent = 0);
    ~KnopkaGenaK();

    MainWindow *ui;

private slots:

    void Generate (bool );


private:


};

#endif // KNOPKAGENAK_H
