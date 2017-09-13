#include "combosegment.h"
#include "spinsegment.h"
#include "knopkasmena.h"
#include "convertthread.h"
#include <QScrollBar>
#include <QThread>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);



    grafic= new QGraphicsScene;


    one_more=new QThread;
    convert= new ConvertThread;
    convert->moveToThread(one_more);
    convert->ui=this;



    nd=ui->spinBox_8->value();
    ld=ui->spinBox_3->value();
    rd=ui->spinBox_4->value();
    md=ui->spinBox_9->value();

    p1=ui->spinBox_5->value();
    p3=ui->spinBox_7->value();

    b2=ui->spinBox_10->value();


    progressbar= new QProgressBar;
    progressbar->setOrientation(Qt::Vertical);
    progressbar->setValue(0);
    progressbar->setStyleSheet("QProgressBar {"
                               "border: 1px solid gray;"
                               "text-align: bottom;"
                               "padding: 1px;"
                               "border-bottom-right-radius: 7px;"
                               "border-bottom-left-radius: 7px;"
                               "background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,"
                               "stop: 0 #fff,"
                               "stop: 0.4999 #eee,"
                               "stop: 0.5 #ddd,"
                               "stop: 1 #eee );"
                               "width: 24px;"
                               "margin-bottom: 15px;"
                               "margin-left: 2px;"
                               "margin-right: 2px;"
                               "}"
                               "QProgressBar::chunk {"
                               "background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,"
                               "stop: 0 #009dde,"
                               "stop: 0.4999 #08aaee,"
                               "stop: 0.5 #11b1f3,"
                               "stop: 1 #2bc1ff );"
                               "border-bottom-right-radius: 7px;"
                               "border-bottom-left-radius: 7px;"
                               "border: 1px solid #0076a7;"
                               "}");



    ui->verticalLayout->addWidget(progressbar);
    progressbar->show();



    connect(this,SIGNAL(file_shifr(QString )),convert,SLOT(file_shifr(QString )));
    connect(this,SIGNAL(file_rasshifr(QString )),convert,SLOT(file_rasshifr(QString )));

    connect(convert,SIGNAL(setProgressBar(int ,QString )),this,SLOT(setProgressBar(int ,QString )));
    connect(convert,SIGNAL(file_exit(QString )),this,SLOT(file_exit(QString )));


    connect(this,SIGNAL(generate()),convert,SLOT(generate()));
    connect(this,SIGNAL(vpered(int )),convert,SLOT(vpered(int )));
    connect(convert,SIGNAL(start_gen()),this,SLOT(all_generate()));
    connect(this,SIGNAL(hide_wind()),convert,SLOT(hide_wind()));
    connect(convert,SIGNAL(smw()),this,SLOT(smw()));

    one_more->start(QThread::NormalPriority);


    cur="";

    mas_polinomov=NULL;


    //общие параметры раунда
    general_key_off=false;
    size_general_key=0;
    general_key=NULL;
    max_strok_config=30;
    nomer_raynda=0;
    perexod_config=NULL;
    //параметры конфигурации раунда
    kol_vo_segmentov_zamen=NULL;
    id_polinoma_na_segment=NULL;
    segment_zamen=NULL;
    smesch_zamen=NULL;
    balance_zamen=NULL;
    mas_of_spinbox_zamen=NULL;
    mas_of_combobox_zamen=NULL;
    mas_of_label_zamen=NULL;
    mas_horizontal_layout_zamen=NULL;
    //параметры конфигурации ключа
    kol_vo_segmentov_key=NULL;
    raynd_key=NULL;
    segment_key=NULL;
    smesch_key=NULL;
    balance_key=NULL;
    mas_of_spinbox_key=NULL;
    mas_of_label_key=NULL;
    mas_horizontal_layout_key=NULL;


    on_plainTextEdit_2_textChanged();
    opred_kolva_polinomov();
    on_spinBox_valueChanged(1);
    ui->tabWidget->setFixedHeight(cor_tab);
    ui->tabWidget->setTabPosition(QTabWidget::South);

    fon_w.setColor(QPalette::Base, Qt::white);
    fon_t.setColor(QPalette::Base, QColor(50,200,78,135));

    ui->radioButton->clicked();



    hideshow=242;
    ui->spinBox_2->setValue(11);


}

MainWindow::~MainWindow()
{

    delete grafic;


    one_more->exit(0);
    while(!one_more->isFinished());

    delete one_more;
    delete convert;

    delete ui;
    delete progressbar;

    delete [] general_key;
    delete [] mas_polinomov;

    delete [] perexod_config;
    //параметры конфигурации раунда
    delete [] kol_vo_segmentov_zamen;
    delete [] id_polinoma_na_segment;
    delete [] segment_zamen;
    delete [] smesch_zamen;
    delete [] balance_zamen;
    delete [] mas_of_spinbox_zamen;
    delete [] mas_of_combobox_zamen;
    delete [] mas_of_label_zamen;
    delete [] mas_horizontal_layout_zamen;
    //параметры конфигурации ключа
    delete [] kol_vo_segmentov_key;
    delete [] raynd_key;
    delete [] segment_key;
    delete [] smesch_key;
    delete [] balance_key;
    delete [] mas_of_spinbox_key;
    delete [] mas_of_label_key;
    delete [] mas_horizontal_layout_key;
}


void MainWindow::showEvent(QShowEvent *)
{
    if (ui->toolBox->height()-cor_height>10)
    {
        if (ui->toolBox->height()<=ui->toolBox->width()/1.15)
        {
            ui->label->setFixedHeight(ui->toolBox->height()-cor_height);
            ui->label_2->setFixedHeight(ui->toolBox->height()-cor_height);
            ui->label_8->setFixedHeight(ui->toolBox->height()-cor_height);
            ui->label->setFixedWidth(ui->label->height()*1.15);
            ui->label_2->setFixedWidth(ui->label_2->height()*1.15);
            ui->label_8->setFixedWidth(ui->label_8->height()*1.35);
        }
        else
        {
            ui->label->setFixedHeight(ui->label->width()/1.15);
            ui->label_2->setFixedHeight(ui->label_2->width()/1.15);
            ui->label_8->setFixedHeight(ui->label_8->width()/1.35);
            ui->label->setFixedWidth(ui->toolBox->width()-cor_width);
            ui->label_2->setFixedWidth(ui->toolBox->width()-cor_width);
            ui->label_8->setFixedWidth(ui->toolBox->width()-cor_width2);
        }
    }

    if (ui->toolBox_2->height()-464>10)
    {
        if (ui->toolBox_2->height()<627)
        {
            ui->graphicsView->setFixedHeight(ui->toolBox_2->height()-464);
            ui->listWidget_2->setFixedHeight(ui->toolBox_2->height()-464);
        }
        else
        {
            ui->graphicsView->setFixedHeight(163);
            ui->listWidget_2->setFixedHeight(163);
        }
        ui->graphicsView->fitInView(grafic->sceneRect(),Qt::KeepAspectRatio);
    }
}

void MainWindow::resizeEvent(QResizeEvent* )
{
    if (ui->toolBox->height()-cor_height>10)
    {
        if (ui->toolBox->height()<=ui->toolBox->width()/1.15)
        {
            ui->label->setFixedHeight(ui->toolBox->height()-cor_height);
            ui->label_2->setFixedHeight(ui->toolBox->height()-cor_height);
            ui->label_8->setFixedHeight(ui->toolBox->height()-cor_height);
            ui->label->setFixedWidth(ui->label->height()*1.15);
            ui->label_2->setFixedWidth(ui->label_2->height()*1.15);
            ui->label_8->setFixedWidth(ui->label_8->height()*1.35);
        }
        else
        {
            ui->label->setFixedHeight(ui->label->width()/1.15);
            ui->label_2->setFixedHeight(ui->label_2->width()/1.15);
            ui->label_8->setFixedHeight(ui->label_8->width()/1.35);
            ui->label->setFixedWidth(ui->toolBox->width()-cor_width);
            ui->label_2->setFixedWidth(ui->toolBox->width()-cor_width);
            ui->label_8->setFixedWidth(ui->toolBox->width()-cor_width2);
        }
    }

    if (ui->toolBox_2->height()-464>10)
    {
        if (ui->toolBox_2->height()<627)
        {
            ui->graphicsView->setFixedHeight(ui->toolBox_2->height()-464);
            ui->listWidget_2->setFixedHeight(ui->toolBox_2->height()-464);
        }
        else
        {
            ui->graphicsView->setFixedHeight(163);
            ui->listWidget_2->setFixedHeight(163);
        }
        ui->graphicsView->fitInView(grafic->sceneRect(),Qt::KeepAspectRatio);
    }
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
    if (checked) ui->stackedWidget_2->setCurrentIndex(1);
    else ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_plainTextEdit_textChanged()
{
    if (ui->radioButton->isChecked()) ui->radioButton->clicked();
}

void MainWindow::on_plainTextEdit_6_textChanged()
{
    if (ui->radioButton_2->isChecked()) ui->radioButton_2->clicked();
}

void MainWindow::on_pushButton_4_clicked()
{
    if (ui->lineEdit->text().length()!=ui->lineEdit_2->text().length())
    {
        ui->lineEdit_3->setText("Количество бит должно быть равным!");
        return;
    }


    QString str = ui->lineEdit->text();
    QString str2 = ui->lineEdit_2->text();

    bool *mas = new bool [str.length()];
    bool *mas2 = new bool [str2.length()];

    for (int i=0; i<str.length(); i++)
    {
        QString buf=str.at(i);
        mas[i]=buf.toInt();
    }

    for (int i=0; i<str2.length(); i++)
    {
        QString buf=str2.at(i);
        mas2[i]=buf.toInt();
    }





    bool buf=0;
    int kolvo_edinic=0;
    for (int i=str.length()-1; i>=0; i--)
    {
        if (mas[i]==1) kolvo_edinic++;
        if (mas2[i]==1) kolvo_edinic++;
        if (buf==1) kolvo_edinic++;

        if (kolvo_edinic==1)
        {
            mas[i]=1;
            buf=0;
        }
        else if (kolvo_edinic==2)
        {
            mas[i]=0;
            buf=1;
        }
        else if (kolvo_edinic==0)
        {
            mas[i]=0;
            buf=0;
        }
        else
        {
            mas[i]=1;
            buf=1;
        }
        kolvo_edinic=0;
    }





    QString str3="";
    for (int i=0; i<str.length(); i++)
    {
        str3+=QString::number(mas[i]);
    }
    ui->lineEdit_3->setText(str3);

    delete [] mas;
    delete [] mas2;
}

void MainWindow::on_pushButton_5_clicked()
{
    if (ui->lineEdit->text().length()!=ui->lineEdit_2->text().length())
    {
        ui->lineEdit_3->setText("Количество бит должно быть равным!");
        return;
    }

    QString str = ui->lineEdit->text();
    QString str2 = ui->lineEdit_2->text();

    bool *mas = new bool [str.length()];
    bool *mas2 = new bool [str2.length()];

    for (int i=0; i<str.length(); i++)
    {
        QString buf=str.at(i);
        mas[i]=buf.toInt();
    }

    for (int i=0; i<str2.length(); i++)
    {
        QString buf=str2.at(i);
        //инверсия для вычитания
        if (buf.toInt()==1) mas2[i]=0;
        else mas2[i]=1;
    }


    //прибавление единицы
    bool buf=0;
    int kolvo_edinic=1;
    for (int i=str.length()-1; i>=0; i--)
    {
        if (mas2[i]==1) kolvo_edinic++;
        if (buf==1) kolvo_edinic++;

        if (kolvo_edinic==0)
        {
            mas2[i]=0;
            buf=0;
        }
        else if (kolvo_edinic==1)
        {
            mas2[i]=1;
            buf=0;
        }
        else if (kolvo_edinic==2)
        {
            mas2[i]=0;
            buf=1;
        }
        else
        {
            mas2[i]=1;
            buf=1;
        }
        kolvo_edinic=0;
    }

    //сложение для получения окончательного ответа
    buf=0;
    kolvo_edinic=0;
    for (int i=str.length()-1; i>=0; i--)
    {
        if (mas[i]==1) kolvo_edinic++;
        if (mas2[i]==1) kolvo_edinic++;
        if (buf==1) kolvo_edinic++;

        if (kolvo_edinic==1)
        {
            mas[i]=1;
            buf=0;
        }
        else if (kolvo_edinic==2)
        {
            mas[i]=0;
            buf=1;
        }
        else if (kolvo_edinic==0)
        {
            mas[i]=0;
            buf=0;
        }
        else
        {
            mas[i]=1;
            buf=1;
        }
        kolvo_edinic=0;
    }



    QString str3="";
    for (int i=0; i<str.length(); i++)
    {
        str3+=QString::number(mas[i]);
    }
    ui->lineEdit_3->setText(str3);

    delete [] mas;
    delete [] mas2;
}


