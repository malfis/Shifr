#ifndef CONVERTTHREAD_H
#define CONVERTTHREAD_H
#include "mainwindow.h"
#include "QThread"


class ConvertThread: public QObject
{
    Q_OBJECT


public:
    explicit ConvertThread(QWidget *parent = 0);
    ~ConvertThread();


    bool exit;
    MainWindow *ui;

private:
    QMainWindow *okno;
    QProgressBar *pb;



signals:
    void setProgressBar(int , QString );
    void file_exit(QString );
    void start_gen();
    void smw();


private slots:
    void file_shifr(QString );
    void file_rasshifr(QString );
    void generate();
    void vpered(int p) {pb->setValue(p);}
    void hide_wind();


};

#endif // CONVERTTHREAD_H
