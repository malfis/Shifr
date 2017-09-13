#include "combosegment.h"
#include "combosegmentk.h"
#include "spinsegment.h"
#include "spinsegmentk.h"
#include "spinsegmentn.h"
#include "spinsegmentrk.h"
#include "knopkasmena.h"
#include "knopkagenaz.h"
#include "knopkagenak.h"
#include <QScrollArea>


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    //не вытаскивать общие переменные под if, т.к. события вызвается многократно
    //будет ошибка
    int kolvo_tab_do_izmeneniy = ui->tabWidget->count();
    if (arg1>kolvo_tab_do_izmeneniy)
    {
        //временный с новым размером для сохранения в них старой инф до удаления
        //общие параметры раунда
        QStackedWidget **buffer_perexod_config=new QStackedWidget*[arg1];
        //параметры конфигурации раунда
        int *buffer_kol_vo_segmentov_zamen=new int [arg1];
        int **buffer_id_polinoma_na_segment=new int *[arg1];
        ComboSegment **buffer_segment_zamen=new ComboSegment*[arg1];
        QSpinBox **buffer_smesch_zamen=new QSpinBox*[arg1];
        QLabel **buffer_balance_zamen=new QLabel*[arg1];
        SpinSegment ***buffer_spinbox_zamen= new SpinSegment**[arg1];
        SpinSegmentN ***buffer_combobox_zamen= new SpinSegmentN**[arg1];
        QLabel ***buffer_label_zamen= new QLabel**[arg1];
        QHBoxLayout ***buffer_horizontal_layout_zamen = new QHBoxLayout**[arg1];
        //параметры конфигурации ключа
        int *buffer_kol_vo_segmentov_key=new int [arg1];
        bool **buffer_raynd_key=new bool *[arg1];
        ComboSegmentK **buffer_segment_key=new ComboSegmentK*[arg1];
        SpinSegmentRK **buffer_smesch_key=new SpinSegmentRK*[arg1];
        QLabel **buffer_balance_key=new QLabel*[arg1];
        SpinSegmentK ***buffer_spinbox_key= new SpinSegmentK**[arg1];
        QLabel ***buffer_label_key= new QLabel**[arg1];
        QHBoxLayout ***buffer_horizontal_layout_key = new QHBoxLayout**[arg1];


        //сохранение старых (не удаляемых,а пересоздоваемых)
        //элементов настроек раундов
        for (int i=0; i<kolvo_tab_do_izmeneniy; i++)
        {
            buffer_perexod_config[i]=perexod_config[i];


            buffer_kol_vo_segmentov_zamen[i]=kol_vo_segmentov_zamen[i];
            buffer_id_polinoma_na_segment[i]=id_polinoma_na_segment[i];
            buffer_segment_zamen[i]=segment_zamen[i];
            buffer_smesch_zamen[i]=smesch_zamen[i];
            buffer_balance_zamen[i]=balance_zamen[i];
            buffer_spinbox_zamen[i]=mas_of_spinbox_zamen[i];
            buffer_combobox_zamen[i]=mas_of_combobox_zamen[i];
            buffer_label_zamen[i]=mas_of_label_zamen[i];
            buffer_horizontal_layout_zamen[i]=mas_horizontal_layout_zamen[i];


            buffer_kol_vo_segmentov_key[i]=kol_vo_segmentov_key[i];
            buffer_raynd_key[i]=raynd_key[i];
            buffer_segment_key[i]=segment_key[i];

            //изменяем максимальное значение общего ключа,
            //т.к. изменилось кол-во раундов
            smesch_key[i]->setMaximum(240*arg1);
            buffer_smesch_key[i]=smesch_key[i];

            buffer_balance_key[i]=balance_key[i];
            buffer_spinbox_key[i]=mas_of_spinbox_key[i];
            buffer_label_key[i]=mas_of_label_key[i];
            buffer_horizontal_layout_key[i]=mas_horizontal_layout_key[i];

        }
        delete [] perexod_config;
        perexod_config=buffer_perexod_config;
        buffer_perexod_config=NULL;

        delete [] kol_vo_segmentov_zamen;
        kol_vo_segmentov_zamen=buffer_kol_vo_segmentov_zamen;
        buffer_kol_vo_segmentov_zamen=NULL;
        delete [] id_polinoma_na_segment;
        id_polinoma_na_segment=buffer_id_polinoma_na_segment;
        buffer_id_polinoma_na_segment=NULL;
        delete [] segment_zamen;
        segment_zamen=buffer_segment_zamen;
        buffer_segment_zamen=NULL;
        delete [] smesch_zamen;
        smesch_zamen=buffer_smesch_zamen;
        buffer_smesch_zamen=NULL;
        delete [] balance_zamen;
        balance_zamen=buffer_balance_zamen;
        buffer_balance_zamen=NULL;
        delete [] mas_of_spinbox_zamen;
        mas_of_spinbox_zamen=buffer_spinbox_zamen;
        buffer_spinbox_zamen=NULL;
        delete [] mas_of_combobox_zamen;
        mas_of_combobox_zamen=buffer_combobox_zamen;
        buffer_combobox_zamen=NULL;
        delete [] mas_of_label_zamen;
        mas_of_label_zamen=buffer_label_zamen;
        buffer_label_zamen=NULL;
        delete [] mas_horizontal_layout_zamen;
        mas_horizontal_layout_zamen=buffer_horizontal_layout_zamen;
        buffer_horizontal_layout_zamen=NULL;

        delete [] kol_vo_segmentov_key;
        kol_vo_segmentov_key=buffer_kol_vo_segmentov_key;
        buffer_kol_vo_segmentov_key=NULL;
        delete [] raynd_key;
        raynd_key=buffer_raynd_key;
        buffer_raynd_key=NULL;
        delete [] segment_key;
        segment_key=buffer_segment_key;
        buffer_segment_key=NULL;
        delete [] smesch_key;
        smesch_key=buffer_smesch_key;
        buffer_smesch_key=NULL;
        delete [] balance_key;
        balance_key=buffer_balance_key;
        buffer_balance_key=NULL;
        delete [] mas_of_spinbox_key;
        mas_of_spinbox_key=buffer_spinbox_key;
        buffer_spinbox_key=NULL;
        delete [] mas_of_label_key;
        mas_of_label_key=buffer_label_key;
        buffer_label_key=NULL;
        delete [] mas_horizontal_layout_key;
        mas_horizontal_layout_key=buffer_horizontal_layout_key;
        buffer_horizontal_layout_key=NULL;


        //обработка новых элементов
        int kolvo_dop_stranic=arg1-kolvo_tab_do_izmeneniy;
        for (int i=0; i<kolvo_dop_stranic; i++)
        {
            perexod_config[kolvo_tab_do_izmeneniy+i]=new QStackedWidget;


            kol_vo_segmentov_zamen[kolvo_tab_do_izmeneniy+i]=1;


            segment_zamen[kolvo_tab_do_izmeneniy+i]=new ComboSegment;
            segment_zamen[kolvo_tab_do_izmeneniy+i]->setMinimumWidth(45);
            segment_zamen[kolvo_tab_do_izmeneniy+i]->setMaximumWidth(45);
            segment_zamen[kolvo_tab_do_izmeneniy+i]->setMinimum(1);
            segment_zamen[kolvo_tab_do_izmeneniy+i]->setMaximum(240);



            smesch_zamen[kolvo_tab_do_izmeneniy+i]=new QSpinBox;
            smesch_zamen[kolvo_tab_do_izmeneniy+i]->setMinimumWidth(45);
            smesch_zamen[kolvo_tab_do_izmeneniy+i]->setMaximumWidth(45);
            smesch_zamen[kolvo_tab_do_izmeneniy+i]->setMinimum(1);
            smesch_zamen[kolvo_tab_do_izmeneniy+i]->setMaximum(240);
            smesch_zamen[kolvo_tab_do_izmeneniy+i]->setValue(13);

            balance_zamen[kolvo_tab_do_izmeneniy+i]=new QLabel;
            balance_zamen[kolvo_tab_do_izmeneniy+i]->setText("Балансировка: 0");
            balance_zamen[kolvo_tab_do_izmeneniy+i]->setMinimumWidth(100);
            balance_zamen[kolvo_tab_do_izmeneniy+i]->setMaximumWidth(100);


            id_polinoma_na_segment[kolvo_tab_do_izmeneniy+i]=
                    new int [kol_vo_segmentov_zamen[kolvo_tab_do_izmeneniy+i]];
            mas_of_label_zamen[kolvo_tab_do_izmeneniy+i]=
                    new QLabel *[kol_vo_segmentov_zamen[kolvo_tab_do_izmeneniy+i]];
            mas_of_spinbox_zamen[kolvo_tab_do_izmeneniy+i]=
                    new SpinSegment *[kol_vo_segmentov_zamen[kolvo_tab_do_izmeneniy+i]];
            mas_of_combobox_zamen[kolvo_tab_do_izmeneniy+i]=
                    new SpinSegmentN *[kol_vo_segmentov_zamen[kolvo_tab_do_izmeneniy+i]];

            //количество строк сегментов в области настройки раунда
            mas_horizontal_layout_zamen[kolvo_tab_do_izmeneniy+i]=new QHBoxLayout *[max_strok_config];
            for (int r=0; r<max_strok_config; r++)
                mas_horizontal_layout_zamen[kolvo_tab_do_izmeneniy+i][r]= new QHBoxLayout;




            kol_vo_segmentov_key[kolvo_tab_do_izmeneniy+i]=1;


            segment_key[kolvo_tab_do_izmeneniy+i]=new ComboSegmentK;
            segment_key[kolvo_tab_do_izmeneniy+i]->setMinimumWidth(45);
            segment_key[kolvo_tab_do_izmeneniy+i]->setMaximumWidth(45);
            segment_key[kolvo_tab_do_izmeneniy+i]->setMinimum(1);
            segment_key[kolvo_tab_do_izmeneniy+i]->setMaximum(240);

            smesch_key[kolvo_tab_do_izmeneniy+i]=new SpinSegmentRK;
            smesch_key[kolvo_tab_do_izmeneniy+i]->setMinimumWidth(45);
            smesch_key[kolvo_tab_do_izmeneniy+i]->setMaximumWidth(45);
            smesch_key[kolvo_tab_do_izmeneniy+i]->setMinimum(0);
            smesch_key[kolvo_tab_do_izmeneniy+i]->setMaximum(5039);
            smesch_key[kolvo_tab_do_izmeneniy+i]->setValue(0);

            raynd_key[kolvo_tab_do_izmeneniy+i]=new bool[240];
            if(!general_key_off)
            {
                bool *buf_general_key = new bool [size_general_key];

                int local_smesch=smesch_key[kolvo_tab_do_izmeneniy+i]->value()+240*(kolvo_tab_do_izmeneniy+i);
                if (size_general_key<local_smesch)
                    while (local_smesch-size_general_key>=0) local_smesch-=size_general_key;

                for (int v=0; v<size_general_key-local_smesch; v++) buf_general_key[v]=general_key[v+local_smesch];
                for (int v=size_general_key-local_smesch; v<size_general_key; v++)
                    buf_general_key[v]=general_key[v-(size_general_key-local_smesch)];
                for (int v=0; v<240; v++) raynd_key[kolvo_tab_do_izmeneniy+i][v]=buf_general_key[v];


                delete [] buf_general_key;
            }



            balance_key[kolvo_tab_do_izmeneniy+i]=new QLabel;
            balance_key[kolvo_tab_do_izmeneniy+i]->setText("Балансировка: 0");
            balance_key[kolvo_tab_do_izmeneniy+i]->setMaximumWidth(100);


            mas_of_label_key[kolvo_tab_do_izmeneniy+i]=
                    new QLabel *[kol_vo_segmentov_key[kolvo_tab_do_izmeneniy+i]];
            mas_of_spinbox_key[kolvo_tab_do_izmeneniy+i]=
                    new SpinSegmentK *[kol_vo_segmentov_key[kolvo_tab_do_izmeneniy+i]];

            //количество строк сегментов в области настройки раунда
            mas_horizontal_layout_key[kolvo_tab_do_izmeneniy+i]=new QHBoxLayout *[max_strok_config];
            for (int r=0; r<max_strok_config; r++)
                mas_horizontal_layout_key[kolvo_tab_do_izmeneniy+i][r]= new QHBoxLayout;



            for (int j=0; j<kol_vo_segmentov_zamen[kolvo_tab_do_izmeneniy+i]; j++)
            {

                mas_of_label_zamen[kolvo_tab_do_izmeneniy+i][j]=new QLabel;
                mas_of_label_zamen[kolvo_tab_do_izmeneniy+i][j]->setMaximumWidth(20);
                mas_of_label_zamen[kolvo_tab_do_izmeneniy+i][j]->
                        setText(QString::number(j+1));

                mas_of_spinbox_zamen[kolvo_tab_do_izmeneniy+i][j]=new SpinSegment;
                mas_of_spinbox_zamen[kolvo_tab_do_izmeneniy+i][j]->setMinimumWidth(37);
                mas_of_spinbox_zamen[kolvo_tab_do_izmeneniy+i][j]->setMinimum(240);
                mas_of_spinbox_zamen[kolvo_tab_do_izmeneniy+i][j]->setMaximum(240);
                //чтобы вызвать функцию update
                //идет строго после всех mas_of_spinbox_raynd
                mas_of_spinbox_zamen[kolvo_tab_do_izmeneniy+i][j]->ui=this;

                mas_of_combobox_zamen[kolvo_tab_do_izmeneniy+i][j]=new SpinSegmentN;
                mas_of_combobox_zamen[kolvo_tab_do_izmeneniy+i][j]->setMinimumWidth(37);
                mas_of_combobox_zamen[kolvo_tab_do_izmeneniy+i][j]->setMinimum(1);
                mas_of_combobox_zamen[kolvo_tab_do_izmeneniy+i][j]->setMaximum(
                            ui->tableWidget_2->item(0,mas_of_spinbox_zamen[kolvo_tab_do_izmeneniy+i][j]->value()-1)->
                        text().toInt());
                mas_of_combobox_zamen[kolvo_tab_do_izmeneniy+i][j]->setValue(
                            mas_of_combobox_zamen[kolvo_tab_do_izmeneniy+i][j]->maximum());

                //чтобы вызвать функцию update
                //идет строго после всех mas_of_combobox_zamen
                mas_of_combobox_zamen[kolvo_tab_do_izmeneniy+i][j]->ui=this;
            }




            for (int j=0; j<kol_vo_segmentov_key[kolvo_tab_do_izmeneniy+i]; j++)
            {

                mas_of_label_key[kolvo_tab_do_izmeneniy+i][j]=new QLabel;
                mas_of_label_key[kolvo_tab_do_izmeneniy+i][j]->setMaximumWidth(20);
                mas_of_label_key[kolvo_tab_do_izmeneniy+i][j]->
                        setText(QString::number(j+1));

                mas_of_spinbox_key[kolvo_tab_do_izmeneniy+i][j]=new SpinSegmentK;
                mas_of_spinbox_key[kolvo_tab_do_izmeneniy+i][j]->setMinimumWidth(37);
                mas_of_spinbox_key[kolvo_tab_do_izmeneniy+i][j]->setMinimum(240);
                mas_of_spinbox_key[kolvo_tab_do_izmeneniy+i][j]->setMaximum(240);
                //чтобы вызвать функцию update
                //идет строго после всех mas_of_spinbox_raynd
                mas_of_spinbox_key[kolvo_tab_do_izmeneniy+i][j]->ui=this;
            }



            QTabWidget *stranica=CreatePage(kolvo_tab_do_izmeneniy+i);
            ui->tabWidget->addTab(stranica,"Раунд "+
                                  QString::number(kolvo_tab_do_izmeneniy+(i+1)));
        }
    }
    if (arg1<kolvo_tab_do_izmeneniy)
    {
        //временный с новым размером для сохранения в них старой инф до удаления
        //общие параметры раунда
        QStackedWidget **buffer_perexod_config=new QStackedWidget*[arg1];
        //параметры конфигурации раунда
        int *buffer_kol_vo_segmentov_zamen=new int [arg1];
        int **buffer_id_polinoma_na_segment=new int *[arg1];
        ComboSegment **buffer_segment_zamen=new ComboSegment*[arg1];
        QSpinBox **buffer_smesch_zamen=new QSpinBox*[arg1];
        QLabel **buffer_balance_zamen=new QLabel*[arg1];
        SpinSegment ***buffer_spinbox_zamen= new SpinSegment**[arg1];
        SpinSegmentN ***buffer_combobox_zamen= new SpinSegmentN**[arg1];
        QLabel ***buffer_label_zamen= new QLabel**[arg1];
        //параметры конфигурации ключа
        int *buffer_kol_vo_segmentov_key=new int [arg1];
        bool **buffer_raynd_key= new bool *[arg1];
        ComboSegmentK **buffer_segment_key=new ComboSegmentK*[arg1];
        SpinSegmentRK **buffer_smesch_key=new SpinSegmentRK*[arg1];
        QLabel **buffer_balance_key=new QLabel*[arg1];
        SpinSegmentK ***buffer_spinbox_key= new SpinSegmentK**[arg1];
        QLabel ***buffer_label_key= new QLabel**[arg1];
        QHBoxLayout ***buffer_horizontal_layout_key = new QHBoxLayout**[arg1];


        //сохранение старых (не удаляемых,а пересоздоваемых)
        //элементов настроек раундов
        int kolvo_lishnix_stranic=kolvo_tab_do_izmeneniy-arg1;
        for (int i=0; i<kolvo_tab_do_izmeneniy-kolvo_lishnix_stranic; i++)
        {
            buffer_perexod_config[i]=perexod_config[i];


            buffer_kol_vo_segmentov_zamen[i]=kol_vo_segmentov_zamen[i];
            buffer_id_polinoma_na_segment[i]=id_polinoma_na_segment[i];
            buffer_segment_zamen[i]=segment_zamen[i];
            buffer_smesch_zamen[i]=smesch_zamen[i];
            buffer_balance_zamen[i]=balance_zamen[i];
            buffer_label_zamen[i]=mas_of_label_zamen[i];
            buffer_spinbox_zamen[i]=mas_of_spinbox_zamen[i];
            buffer_combobox_zamen[i]=mas_of_combobox_zamen[i];


            buffer_kol_vo_segmentov_key[i]=kol_vo_segmentov_key[i];
            buffer_raynd_key[i]=raynd_key[i];
            buffer_segment_key[i]=segment_key[i];

            //изменяем максимальное значение общего ключа,
            //т.к. изменилось кол-во раундов
            smesch_key[i]->setMaximum(240*arg1);
            buffer_smesch_key[i]=smesch_key[i];

            buffer_balance_key[i]=balance_key[i];
            buffer_spinbox_key[i]=mas_of_spinbox_key[i];
            buffer_label_key[i]=mas_of_label_key[i];
            buffer_horizontal_layout_key[i]=mas_horizontal_layout_key[i];
        }

        //удаление лишних элементов

        for (int i=0; i<kolvo_lishnix_stranic; i++)
        {
            for (int j=0; j<kol_vo_segmentov_zamen[(kolvo_tab_do_izmeneniy-1)-i]; j++)
            {
                delete mas_of_label_zamen[(kolvo_tab_do_izmeneniy-1)-i][j];
                delete mas_of_spinbox_zamen[(kolvo_tab_do_izmeneniy-1)-i][j];
                delete mas_of_combobox_zamen[(kolvo_tab_do_izmeneniy-1)-i][j];
            }
            delete [] id_polinoma_na_segment[(kolvo_tab_do_izmeneniy-1)-i];
            delete [] mas_of_label_zamen[(kolvo_tab_do_izmeneniy-1)-i];
            delete [] mas_of_spinbox_zamen[(kolvo_tab_do_izmeneniy-1)-i];
            delete [] mas_of_combobox_zamen[(kolvo_tab_do_izmeneniy-1)-i];

            delete segment_zamen[(kolvo_tab_do_izmeneniy-1)-i];
            delete smesch_zamen[(kolvo_tab_do_izmeneniy-1)-i];
            delete balance_zamen[(kolvo_tab_do_izmeneniy-1)-i];



            for (int j=0; j<kol_vo_segmentov_key[(kolvo_tab_do_izmeneniy-1)-i]; j++)
            {
                delete mas_of_label_key[(kolvo_tab_do_izmeneniy-1)-i][j];
                delete mas_of_spinbox_key[(kolvo_tab_do_izmeneniy-1)-i][j];
            }
            delete [] mas_of_label_key[(kolvo_tab_do_izmeneniy-1)-i];
            delete [] mas_of_spinbox_key[(kolvo_tab_do_izmeneniy-1)-i];
            delete [] raynd_key[(kolvo_tab_do_izmeneniy-1)-i];

            delete segment_key[(kolvo_tab_do_izmeneniy-1)-i];
            delete smesch_key[(kolvo_tab_do_izmeneniy-1)-i];
            delete balance_key[(kolvo_tab_do_izmeneniy-1)-i];




            //удалять строго предпоследней,т.к. в табе, все остальное в нем
            delete perexod_config[(kolvo_tab_do_izmeneniy-1)-i];

            //таб удалять последним
            QWidget *pw=ui->tabWidget->widget((kolvo_tab_do_izmeneniy-1)-i);
            ui->tabWidget->removeTab((kolvo_tab_do_izmeneniy-1)-i);
            delete pw;
        }

        delete [] perexod_config;
        perexod_config=buffer_perexod_config;
        buffer_perexod_config=NULL;

        delete [] kol_vo_segmentov_zamen;
        kol_vo_segmentov_zamen=buffer_kol_vo_segmentov_zamen;
        buffer_kol_vo_segmentov_zamen=NULL;
        delete [] id_polinoma_na_segment;
        id_polinoma_na_segment=buffer_id_polinoma_na_segment;
        buffer_id_polinoma_na_segment=NULL;
        delete [] segment_zamen;
        segment_zamen=buffer_segment_zamen;
        buffer_segment_zamen=NULL;
        delete [] smesch_zamen;
        smesch_zamen=buffer_smesch_zamen;
        buffer_smesch_zamen=NULL;
        delete [] balance_zamen;
        balance_zamen=buffer_balance_zamen;
        buffer_balance_zamen=NULL;
        delete [] mas_of_spinbox_zamen;
        mas_of_spinbox_zamen=buffer_spinbox_zamen;
        buffer_spinbox_zamen=NULL;
        delete [] mas_of_combobox_zamen;
        mas_of_combobox_zamen=buffer_combobox_zamen;
        buffer_combobox_zamen=NULL;
        delete [] mas_of_label_zamen;
        mas_of_label_zamen=buffer_label_zamen;
        buffer_label_zamen=NULL;

        delete [] kol_vo_segmentov_key;
        kol_vo_segmentov_key=buffer_kol_vo_segmentov_key;
        buffer_kol_vo_segmentov_key=NULL;
        delete [] raynd_key;
        raynd_key=buffer_raynd_key;
        buffer_raynd_key=NULL;
        delete [] segment_key;
        segment_key=buffer_segment_key;
        buffer_segment_key=NULL;
        delete [] smesch_key;
        smesch_key=buffer_smesch_key;
        buffer_smesch_key=NULL;
        delete [] balance_key;
        balance_key=buffer_balance_key;
        buffer_balance_key=NULL;
        delete [] mas_of_spinbox_key;
        mas_of_spinbox_key=buffer_spinbox_key;
        buffer_spinbox_key=NULL;
        delete [] mas_of_label_key;
        mas_of_label_key=buffer_label_key;
        buffer_label_key=NULL;
    }
}

QTabWidget *MainWindow::CreatePage(int nomer_stranici)
{
    QWidget *raynd_wid = new QWidget;
    QWidget *key_wid = new QWidget;

    perexod_config[nomer_stranici]->addWidget(raynd_wid);
    perexod_config[nomer_stranici]->addWidget(key_wid);

    QTabWidget *page = new QTabWidget;
    QGridLayout *pagelayout = new QGridLayout;
    page->setLayout(pagelayout);
    pagelayout->addWidget(perexod_config[nomer_stranici]);

    QGridLayout *rayndlayout = new QGridLayout;
    raynd_wid->setLayout(rayndlayout);
    QGridLayout *keylayout = new QGridLayout;
    key_wid->setLayout(keylayout);





    //настройка замен
    QScrollArea *scroll_raynd = new QScrollArea;
    rayndlayout->addWidget(scroll_raynd,0,0,1,-1);
    scroll_raynd->setWidgetResizable(true);
    scroll_raynd->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_raynd->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll_raynd->setStyleSheet("QWidget {background: white}");
    scroll_raynd->setMaximumHeight(200);
    QVBoxLayout *scroll_raynd_layout = new QVBoxLayout;
    QWidget *scroll_raynd_wid = new QWidget;
    scroll_raynd_wid->setLayout(scroll_raynd_layout);
    scroll_raynd->setWidget(scroll_raynd_wid);


    QLabel *l=new QLabel;
    rayndlayout->addWidget(l,1,0);
    l->setText("Сегментация блоков замен:");
    l->setMaximumWidth(140);


    rayndlayout->addWidget(segment_zamen[nomer_stranici],1,1);
    //чтобы вызвать функцию
    //идет строго после всех segment_zamen
    segment_zamen[nomer_stranici]->ui=this;



    KnopkaGenaZ *knopka_gen_z=new KnopkaGenaZ;
    knopka_gen_z->setText("Сгенерировать");
    knopka_gen_z->setMinimumWidth(120);
    knopka_gen_z->setMaximumWidth(120);
    rayndlayout->addWidget(knopka_gen_z,1,2);
    //чтобы вызвать функцию внутри переопределенного класса кнопки
    knopka_gen_z->ui=this;



    QLabel *l2=new QLabel;
    rayndlayout->addWidget(l2,1,3);
    l2->setText("Циклический сдвиг после замены:");
    l2->setMaximumWidth(173);

    rayndlayout->addWidget(smesch_zamen[nomer_stranici],1,4,1,-1);
    rayndlayout->addWidget(balance_zamen[nomer_stranici],1,5);

    KnopkaSmena *knopka_na_key=new KnopkaSmena;
    knopka_na_key->setText("Настройка ключа");
    knopka_na_key->setMinimumWidth(120);
    knopka_na_key->setMaximumWidth(120);
    rayndlayout->addWidget(knopka_na_key,1,6,1,-1);
    //чтобы вызвать функцию внутри переопределенного класса кнопки
    knopka_na_key->ui=this;

    //-1 -всегда растягивать на максимум,
    //5- растянуть только на 5 блоков
    //вывод строк сегментов в области настройки раунда
    for (int r=0; r<max_strok_config; r++)
        scroll_raynd_layout->addLayout(mas_horizontal_layout_zamen[nomer_stranici][r]);

    int id=0;
    for (int i=0; i<ui->tableWidget_3->rowCount(); i++)
    {
        if (mas_of_spinbox_zamen[nomer_stranici][0]->value()==1)
            id=mas_of_combobox_zamen[nomer_stranici][0]->value();
        else
            if (mas_of_spinbox_zamen[nomer_stranici][0]->value()==
                    ui->tableWidget_3->item(i,242)->text().toInt())
                if (mas_of_combobox_zamen[nomer_stranici][0]->value()==
                        ui->tableWidget_3->item(i,241)->text().toInt())
                    id=ui->tableWidget_3->verticalHeaderItem(i)->text().toInt();
    }
    id_polinoma_na_segment[nomer_stranici][0]=id;
    mas_horizontal_layout_zamen[nomer_stranici][0]->addWidget(mas_of_label_zamen[nomer_stranici][0]);
    mas_horizontal_layout_zamen[nomer_stranici][0]->addWidget(mas_of_spinbox_zamen[nomer_stranici][0]);
    mas_horizontal_layout_zamen[nomer_stranici][0]->addWidget(mas_of_combobox_zamen[nomer_stranici][0]);



    //настройка ключа
    QScrollArea *scroll_key = new QScrollArea;
    keylayout->addWidget(scroll_key,0,0,1,-1);
    scroll_key->setWidgetResizable(true);
    scroll_key->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_key->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll_key->setStyleSheet("QWidget {background: white}");
    scroll_key->setMaximumHeight(200);
    QVBoxLayout *scroll_key_layout = new QVBoxLayout;
    QWidget *scroll_key_wid = new QWidget;
    scroll_key_wid->setLayout(scroll_key_layout);
    scroll_key->setWidget(scroll_key_wid);

    QLabel *lk=new QLabel;
    keylayout->addWidget(lk,1,0);
    lk->setText("Сегментация блоков ключа:");
    lk->setMaximumWidth(144);


    keylayout->addWidget(segment_key[nomer_stranici],1,1);
    //чтобы вызвать функцию
    //идет строго после всех segment_zamen
    segment_key[nomer_stranici]->ui=this;

    KnopkaGenaK *knopka_gen_k=new KnopkaGenaK;
    knopka_gen_k->setText("Сгенерировать");
    knopka_gen_k->setMinimumWidth(120);
    knopka_gen_k->setMaximumWidth(120);
    keylayout->addWidget(knopka_gen_k,1,2);
    //чтобы вызвать функцию внутри переопределенного класса кнопки
    knopka_gen_k->ui=this;


    QLabel *l2k=new QLabel;
    keylayout->addWidget(l2k,1,3);
    l2k->setText("Циклический сдвиг общего ключа:");
    l2k->setMaximumWidth(178);

    keylayout->addWidget(smesch_key[nomer_stranici],1,4,1,-1);
    //чтобы вызвать функцию
    //идет строго после всех smesch_key
    smesch_key[nomer_stranici]->ui=this;

    keylayout->addWidget(balance_key[nomer_stranici],1,5);

    KnopkaSmena *knopka_na_raynd=new KnopkaSmena;
    knopka_na_raynd->setText("Настройка замены");
    knopka_na_raynd->setMinimumWidth(120);
    knopka_na_raynd->setMaximumWidth(120);
    keylayout->addWidget(knopka_na_raynd,1,6,1,-1);
    //чтобы вызвать функцию внутри переопределенного класса кнопки
    knopka_na_raynd->ui=this;

    //-1 -всегда растягивать на максимум,
    //5- растянуть только на 5 блоков
    //вывод строк сегментов в области настройки раунда
    for (int r=0; r<max_strok_config; r++)
        scroll_key_layout->addLayout(mas_horizontal_layout_key[nomer_stranici][r]);

    mas_horizontal_layout_key[nomer_stranici][0]->addWidget(mas_of_label_key[nomer_stranici][0]);
    mas_horizontal_layout_key[nomer_stranici][0]->addWidget(mas_of_spinbox_key[nomer_stranici][0]);






    return page;
}

void MainWindow::updatePage(int tek_segmentaciya)
{
    if (gen3.tryLock())
    {
        //удаление  элементов
        for (int j=0; j<kol_vo_segmentov_zamen[nomer_raynda]; j++)
        {
            delete mas_of_label_zamen[nomer_raynda][j];
            delete mas_of_spinbox_zamen[nomer_raynda][j];
            delete mas_of_combobox_zamen[nomer_raynda][j];
        }
        delete [] id_polinoma_na_segment[nomer_raynda];
        delete [] mas_of_label_zamen[nomer_raynda];
        delete [] mas_of_spinbox_zamen[nomer_raynda];
        delete [] mas_of_combobox_zamen[nomer_raynda];

        //строка с новым количеством сегментов раунда
        //обязательно идет первой
        kol_vo_segmentov_zamen[nomer_raynda]=tek_segmentaciya;
        id_polinoma_na_segment[nomer_raynda]=
                new int [kol_vo_segmentov_zamen[nomer_raynda]];
        mas_of_label_zamen[nomer_raynda]=
                new QLabel *[kol_vo_segmentov_zamen[nomer_raynda]];
        mas_of_spinbox_zamen[nomer_raynda]=
                new SpinSegment *[kol_vo_segmentov_zamen[nomer_raynda]];
        mas_of_combobox_zamen[nomer_raynda]=
                new SpinSegmentN *[kol_vo_segmentov_zamen[nomer_raynda]];


        //динамическая разбивка по строкам элементов раунда
        int coef_yvel=0;
        int elem_v_stroke=8;
        while (elem_v_stroke<36)
        {
            if ((kol_vo_segmentov_zamen[nomer_raynda]-1)/elem_v_stroke<max_strok_config)
            {
                coef_yvel=(kol_vo_segmentov_zamen[nomer_raynda]-1)/elem_v_stroke;
                elem_v_stroke=36;
            }
            else elem_v_stroke++;
        }


        int buf_coef;
        if (coef_yvel<7) buf_coef=coef_yvel;
        else buf_coef=6;


        if (ui->toolBox->height()-cor_height>10)
        {
            if (ui->toolBox->height()<=ui->toolBox->width()/1.15)
            {
                ui->label->setFixedHeight(ui->toolBox->height()-cor_height+(ui->tabWidget->height()-cor_tab-buf_coef*27));
                ui->label_2->setFixedHeight(ui->toolBox->height()-cor_height+(ui->tabWidget->height()-cor_tab-buf_coef*27));
                ui->label_8->setFixedHeight(ui->toolBox->height()-cor_height+(ui->tabWidget->height()-cor_tab-buf_coef*27));
                ui->label->setFixedWidth(ui->label->height()*1.15);
                ui->label_2->setFixedWidth(ui->label->height()*1.15);
                ui->label_8->setFixedWidth(ui->label->height()*1.35);
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

        ui->tabWidget->setFixedHeight(cor_tab+buf_coef*27);




        if (ui->toolBox_2->height()-464>100)
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

        int bal=-240;
        for (int j=0; j<kol_vo_segmentov_zamen[nomer_raynda]; j++)
        {
            mas_of_spinbox_zamen[nomer_raynda][j]=new SpinSegment;
            mas_of_spinbox_zamen[nomer_raynda][j]->setMinimumWidth(37);
            if (kol_vo_segmentov_zamen[nomer_raynda]==1)
            {
                mas_of_spinbox_zamen[nomer_raynda][j]->setMinimum(240);
                mas_of_spinbox_zamen[nomer_raynda][j]->setMaximum(240);
            }
            else
            {
                mas_of_spinbox_zamen[nomer_raynda][j]->setMinimum(1);
                mas_of_spinbox_zamen[nomer_raynda][j]->setMaximum(241-kol_vo_segmentov_zamen[nomer_raynda]);

                if (j==0) mas_of_spinbox_zamen[nomer_raynda][j]->
                        setValue(240/kol_vo_segmentov_zamen[nomer_raynda]+240%kol_vo_segmentov_zamen[nomer_raynda]);
                else mas_of_spinbox_zamen[nomer_raynda][j]->setValue(240/kol_vo_segmentov_zamen[nomer_raynda]);
            }
            //чтобы вызвать функцию update
            //идет строго после всех mas_of_spinbox_raynd
            mas_of_spinbox_zamen[nomer_raynda][j]->ui=this;

            mas_of_combobox_zamen[nomer_raynda][j]=new SpinSegmentN;
            mas_of_combobox_zamen[nomer_raynda][j]->setMinimumWidth(37);
            mas_of_combobox_zamen[nomer_raynda][j]->setMinimum(1);
            if (mas_of_spinbox_zamen[nomer_raynda][j]->value()==1)
            {
                mas_of_combobox_zamen[nomer_raynda][j]->setMaximum(2);
                mas_of_combobox_zamen[nomer_raynda][j]->setValue(2);
            }
            else
            {
                mas_of_combobox_zamen[nomer_raynda][j]->setMaximum(
                            ui->tableWidget_2->item(0,mas_of_spinbox_zamen[nomer_raynda][j]->value()-1)->
                            text().toInt());
                mas_of_combobox_zamen[nomer_raynda][j]->setValue(
                            mas_of_combobox_zamen[nomer_raynda][j]->maximum());
            }

            //чтобы вызвать функцию update
            //идет строго после всех mas_of_combobox_zamen
            mas_of_combobox_zamen[nomer_raynda][j]->ui=this;


            mas_of_label_zamen[nomer_raynda][j]=new QLabel;
            mas_of_label_zamen[nomer_raynda][j]->setMaximumWidth(20);
            mas_of_label_zamen[nomer_raynda][j]->setText(QString::number(j+1));


            int id=0;
            for (int i=0; i<ui->tableWidget_3->rowCount(); i++)
            {
                if (mas_of_spinbox_zamen[nomer_raynda][j]->value()==1)
                    id=mas_of_combobox_zamen[nomer_raynda][j]->value();
                else
                    if (mas_of_spinbox_zamen[nomer_raynda][j]->value()==
                            ui->tableWidget_3->item(i,242)->text().toInt())
                        if (mas_of_combobox_zamen[nomer_raynda][j]->value()==
                                ui->tableWidget_3->item(i,241)->text().toInt())
                            id=ui->tableWidget_3->verticalHeaderItem(i)->text().toInt();

            }
            id_polinoma_na_segment[nomer_raynda][j]=id;




            mas_horizontal_layout_zamen[nomer_raynda][j%(coef_yvel+1)]->
                    addWidget(mas_of_label_zamen[nomer_raynda][j]);
            mas_horizontal_layout_zamen[nomer_raynda][j%(coef_yvel+1)]->
                    addWidget(mas_of_spinbox_zamen[nomer_raynda][j]);
            mas_horizontal_layout_zamen[nomer_raynda][j%(coef_yvel+1)]->
                    addWidget(mas_of_combobox_zamen[nomer_raynda][j]);


            bal+=mas_of_spinbox_zamen[nomer_raynda][j]->value();
        }
        balance_zamen[nomer_raynda]->setText("Балансировка: "+QString::number(bal));
        gen3.unlock();
    }
}

void MainWindow::updatePageK(int tek_segmentaciya)
{
    //удаление  элементов
    for (int j=0; j<kol_vo_segmentov_key[nomer_raynda]; j++)
    {
        delete mas_of_label_key[nomer_raynda][j];
        delete mas_of_spinbox_key[nomer_raynda][j];
    }
    delete [] mas_of_label_key[nomer_raynda];
    delete [] mas_of_spinbox_key[nomer_raynda];

    //строка с новым количеством сегментов раунда
    //обязательно идет первой
    kol_vo_segmentov_key[nomer_raynda]=tek_segmentaciya;
    mas_of_label_key[nomer_raynda]=
            new QLabel *[kol_vo_segmentov_key[nomer_raynda]];
    mas_of_spinbox_key[nomer_raynda]=
            new SpinSegmentK *[kol_vo_segmentov_key[nomer_raynda]];


    //динамическая разбивка по строкам элементов раунда
    int coef_yvel=0;
    int elem_v_stroke=8;
    while (elem_v_stroke<36)
    {
        if ((kol_vo_segmentov_key[nomer_raynda]-1)/elem_v_stroke<max_strok_config)
        {
            coef_yvel=(kol_vo_segmentov_key[nomer_raynda]-1)/elem_v_stroke;
            elem_v_stroke=36;
        }
        else elem_v_stroke++;
    }


    int buf_coef;
    if (coef_yvel<7) buf_coef=coef_yvel;
    else buf_coef=6;


    if (ui->toolBox->height()-cor_height>10)
    {
        if (ui->toolBox->height()<=ui->toolBox->width()/1.15)
        {
            ui->label->setFixedHeight(ui->toolBox->height()-cor_height+(ui->tabWidget->height()-cor_tab-buf_coef*27));
            ui->label_2->setFixedHeight(ui->toolBox->height()-cor_height+(ui->tabWidget->height()-cor_tab-buf_coef*27));
            ui->label_8->setFixedHeight(ui->toolBox->height()-cor_height+(ui->tabWidget->height()-cor_tab-buf_coef*27));
            ui->label->setFixedWidth(ui->label->height()*1.15);
            ui->label_2->setFixedWidth(ui->label->height()*1.15);
            ui->label_8->setFixedWidth(ui->label->height()*1.35);
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

    ui->tabWidget->setFixedHeight(cor_tab+buf_coef*27);




    if (ui->toolBox_2->height()-464>100)
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

    int bal=-240;
    for (int j=0; j<kol_vo_segmentov_key[nomer_raynda]; j++)
    {
        mas_of_spinbox_key[nomer_raynda][j]=new SpinSegmentK;
        mas_of_spinbox_key[nomer_raynda][j]->setMinimumWidth(37);

        if (kol_vo_segmentov_key[nomer_raynda]==1)
        {
            mas_of_spinbox_key[nomer_raynda][j]->setMinimum(240);
            mas_of_spinbox_key[nomer_raynda][j]->setMaximum(240);
        }
        else
        {
            mas_of_spinbox_key[nomer_raynda][j]->setMinimum(1);
            mas_of_spinbox_key[nomer_raynda][j]->setMaximum(241-kol_vo_segmentov_key[nomer_raynda]);

            if (j==0) mas_of_spinbox_key[nomer_raynda][j]->
                    setValue(240/kol_vo_segmentov_key[nomer_raynda]+240%kol_vo_segmentov_key[nomer_raynda]);
            else mas_of_spinbox_key[nomer_raynda][j]->setValue(240/kol_vo_segmentov_key[nomer_raynda]);
        }

        //чтобы вызвать функцию update
        //идет строго после всех mas_of_spinbox_raynd
        mas_of_spinbox_key[nomer_raynda][j]->ui=this;


        mas_of_label_key[nomer_raynda][j]=new QLabel;
        mas_of_label_key[nomer_raynda][j]->setMaximumWidth(20);
        mas_of_label_key[nomer_raynda][j]->setText(QString::number(j+1));



        mas_horizontal_layout_key[nomer_raynda][j%(coef_yvel+1)]->
                addWidget(mas_of_label_key[nomer_raynda][j]);
        mas_horizontal_layout_key[nomer_raynda][j%(coef_yvel+1)]->
                addWidget(mas_of_spinbox_key[nomer_raynda][j]);


        bal+=mas_of_spinbox_key[nomer_raynda][j]->value();
    }
    balance_key[nomer_raynda]->setText("Балансировка: "+QString::number(bal));
}


void MainWindow::updateZameny()
{
    if (gen.tryLock())
    {
        int bal=-240;
        for (int j=0; j<kol_vo_segmentov_zamen[nomer_raynda]; j++)
        {
            if (mas_of_spinbox_zamen[nomer_raynda][j]->value()==1)
            {
                mas_of_combobox_zamen[nomer_raynda][j]->setMaximum(2);
                if (mas_of_combobox_zamen[nomer_raynda][j]->value()>2)
                    mas_of_combobox_zamen[nomer_raynda][j]->setValue(2);
            }
            else
            {
                int new_max=ui->tableWidget_2->item(0,mas_of_spinbox_zamen[nomer_raynda][j]->value()-1)->text().toInt();
                mas_of_combobox_zamen[nomer_raynda][j]->setMaximum(new_max);
                if (mas_of_combobox_zamen[nomer_raynda][j]->value()>new_max)
                    mas_of_combobox_zamen[nomer_raynda][j]->setValue(
                                mas_of_combobox_zamen[nomer_raynda][j]->maximum());
            }


            bal+=mas_of_spinbox_zamen[nomer_raynda][j]->value();
        }
        balance_zamen[nomer_raynda]->setText("Балансировка: "+QString::number(bal));

        updateNomer();
        gen.unlock();
    }
}

void MainWindow::updateKey()
{
    if (gen4.tryLock())
    {
        int bal=-240;
        for (int j=0; j<kol_vo_segmentov_key[nomer_raynda]; j++)
            bal+=mas_of_spinbox_key[nomer_raynda][j]->value();
        balance_key[nomer_raynda]->setText("Балансировка: "+QString::number(bal));
        gen4.unlock();
    }
}

void MainWindow::updateNomer()
{
    if (gen2.tryLock())
    {
        int id=0;
        for (int j=0; j<kol_vo_segmentov_zamen[nomer_raynda]; j++)
        {
            for (int i=0; i<ui->tableWidget_3->rowCount(); i++)
            {
                if (mas_of_spinbox_zamen[nomer_raynda][j]->value()==1)
                    id=mas_of_combobox_zamen[nomer_raynda][j]->value();
                else
                    if (mas_of_spinbox_zamen[nomer_raynda][j]->value()==
                            ui->tableWidget_3->item(i,242)->text().toInt())
                        if (mas_of_combobox_zamen[nomer_raynda][j]->value()==
                                ui->tableWidget_3->item(i,241)->text().toInt())
                            id=ui->tableWidget_3->verticalHeaderItem(i)->text().toInt();

            }
            id_polinoma_na_segment[nomer_raynda][j]=id;
        }
        gen2.unlock();
    }
}

void MainWindow::updateRayndKey()
{
    if (gen5.tryLock())
    {
        if(!general_key_off)
        {
            int config_n=0;
            for (int i=0; i<ui->spinBox->value(); i++)
            {
                bool *buf_general_key = new bool [size_general_key];


                int local_smesch=240*i+config_n;
                config_n+=smesch_key[i]->value();

                if (size_general_key<local_smesch)
                    while (local_smesch-size_general_key>=0) local_smesch-=size_general_key;

                for (int v=0; v<size_general_key-local_smesch; v++) buf_general_key[v]=general_key[v+local_smesch];
                for (int v=size_general_key-local_smesch; v<size_general_key; v++)
                    buf_general_key[v]=general_key[v-(size_general_key-local_smesch)];
                for (int v=0; v<240; v++) raynd_key[i][v]=buf_general_key[v];


                delete [] buf_general_key;
            }
        }
        gen5.unlock();
    }
}


void MainWindow::perekluchenie()
{
    if (perexod_config[nomer_raynda]->currentIndex()==0)
        perexod_config[nomer_raynda]->setCurrentIndex(1);
    else perexod_config[nomer_raynda]->setCurrentIndex(0);

    this->on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    nomer_raynda=index;
    int coef_yvel=0;
    int elem_v_stroke=8;
    //изменение размера по настройкам замен
    if (perexod_config[nomer_raynda]->currentIndex()==0)
        while (elem_v_stroke<36)
        {
            if ((kol_vo_segmentov_zamen[index]-1)/elem_v_stroke<max_strok_config)
            {
                coef_yvel=(kol_vo_segmentov_zamen[index]-1)/elem_v_stroke;
                elem_v_stroke=36;
            }
            else elem_v_stroke++;
        }
    //изменение размера по настройкам ключа
    if (perexod_config[nomer_raynda]->currentIndex()==1)
        while (elem_v_stroke<36)
        {
            if ((kol_vo_segmentov_key[index]-1)/elem_v_stroke<max_strok_config)
            {
                coef_yvel=(kol_vo_segmentov_key[index]-1)/elem_v_stroke;
                elem_v_stroke=36;
            }
            else elem_v_stroke++;
        }



    int buf_coef;
    if (coef_yvel<7) buf_coef=coef_yvel;
    else buf_coef=6;


    if (ui->toolBox->height()-cor_height>10)
    {
        if (ui->toolBox->height()<=ui->toolBox->width()/1.15)
        {
            ui->label->setFixedHeight(ui->toolBox->height()-cor_height+(ui->tabWidget->height()-cor_tab-buf_coef*27));
            ui->label_2->setFixedHeight(ui->toolBox->height()-cor_height+(ui->tabWidget->height()-cor_tab-buf_coef*27));
            ui->label_8->setFixedHeight(ui->toolBox->height()-cor_height+(ui->tabWidget->height()-cor_tab-buf_coef*27));
            ui->label->setFixedWidth(ui->label->height()*1.15);
            ui->label_2->setFixedWidth(ui->label->height()*1.15);
            ui->label_8->setFixedWidth(ui->label->height()*1.35);
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

    ui->tabWidget->setFixedHeight(cor_tab+buf_coef*27);



    if (ui->toolBox_2->height()-464>100)
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
