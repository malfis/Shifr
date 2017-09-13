#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "PolinomM2.h"
#include <QMutex>
#include <QProgressBar>
#include <QTime>


namespace Ui {
class MainWindow;
}



class ComboSegment;
class ComboSegmentK;
class SpinSegment;
class SpinSegmentK;
class SpinSegmentN;
class SpinSegmentRK;
class ConvertThread;
class ConvertThread2;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    PolinomM2 *mas_polinomov;

    int kolvo_polinom[240];
    int hideshow;

    void resizeEvent(QResizeEvent* );
    void showEvent(QShowEvent *);
    QMutex stop;
    QMutex up;
    QMutex gen;
    QMutex gen2;
    QMutex gen3;
    QMutex gen4;
    QMutex gen5;
    QTime time;
    QThread *one_more;
    ConvertThread *convert;


    int cor_tab=125;
    int cor_height=152;
    int cor_width=175;
    int cor_width2=75;

    int symbol=16;


    QPalette fon_w, fon_t;
    QProgressBar *progressbar;
    QString cur;


    QGraphicsScene *grafic;


    QMainWindow *okno;
    QProgressBar *pb;



    //общие параметры раунда
    int ld,rd,nd,md, p1,p3, b2;

    bool general_key_off;
    int size_general_key;
    bool *general_key;
    int max_strok_config;
    int nomer_raynda;
    QStackedWidget **perexod_config;
    //параметры конфигурации замены
    int *kol_vo_segmentov_zamen;
    int **id_polinoma_na_segment;
    ComboSegment **segment_zamen;
    QSpinBox **smesch_zamen;
    QLabel **balance_zamen;
    SpinSegment ***mas_of_spinbox_zamen;
    SpinSegmentN ***mas_of_combobox_zamen;
    QLabel ***mas_of_label_zamen;
    QHBoxLayout ***mas_horizontal_layout_zamen;
    //параметры конфигурации ключа
    int *kol_vo_segmentov_key;
    bool **raynd_key;
    ComboSegmentK **segment_key;
    SpinSegmentRK **smesch_key;
    QLabel **balance_key;
    SpinSegmentK ***mas_of_spinbox_key;
    QLabel ***mas_of_label_key;
    QHBoxLayout ***mas_horizontal_layout_key;






    QTabWidget* CreatePage(int );


signals:
    void file_shifr(QString );
    void file_rasshifr(QString );
    void generate();
    void vpered(int);
    void hide_wind();


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();




    void updatePage(int );
    void updatePageK(int );
    void updateZameny();
    void updateKey();
    void updateNomer();
    void updateRayndKey();
    void perekluchenie();
    void ZamenaSegmentGen(int );
    void KeySegmentGen(int );


    int shivrovanie(bool* , int );

    int rasshivrovanie(bool* , int );





    int nr() {return nomer_raynda;}
    ComboSegment * sz(int nr) {return segment_zamen[nr];}
    ComboSegmentK * sk(int nr) {return segment_key[nr];}
private slots:

    void setProgressBar(int value, QString text)
    {progressbar->setValue(value);
        ui->lineEdit_4->setText(text);}

    void file_exit(QString );

    void all_generate();
    void smw();


    void opred_kolva_polinomov();



    void testK1(QString );
    void testK2(QString );




    void on_plainTextEdit_textChanged();

    void on_plainTextEdit_6_textChanged();

    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_spinBox_valueChanged(int arg1);



    void on_pushButton_2_clicked();



    void on_spinBox_2_valueChanged(int arg1);
    void on_checkBox_4_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_plainTextEdit_2_textChanged();
    void on_pushButton_clicked();
    void on_checkBox_3_clicked();
    void on_checkBox_5_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_spinBox_3_valueChanged(int arg1);
    void on_spinBox_4_valueChanged(int arg1);
    void on_spinBox_5_valueChanged(int arg1);
    void on_spinBox_7_valueChanged(int arg1);

    void on_pushButton_3_clicked();

    void on_spinBox_8_valueChanged(int arg1);
    void on_spinBox_9_valueChanged(int arg1);

    void on_spinBox_10_valueChanged(int arg1);

public slots:

    void on_tabWidget_currentChanged(int index);

};

#endif // MAINWINDOW_H
