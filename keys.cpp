#include "mainwindow.h"
#include "combosegment.h"
#include "combosegmentk.h"
#include "spinsegment.h"
#include "spinsegmentk.h"
#include "spinsegmentn.h"


void MainWindow::on_pushButton_8_clicked()
{
    QString buf="";
    QTime midnight(0,0,0);
    qsrand(midnight.msecsTo(QTime::currentTime()));
    for (int i=0; i<5040; i++)
    {
        buf+=QString::number(qrand()%2);
    }
    int kol_vo_rayndov = ui->spinBox->value();
    ui->plainTextEdit_2->setPlainText(buf.left(240*kol_vo_rayndov));
}

void MainWindow::on_pushButton_3_clicked()
{
    this->setEnabled(false);
    emit generate();
}

void MainWindow::all_generate()
{
    if (up.tryLock())
    {



        int kolvo_rayndov = ui->spinBox->text().toInt();
        QTime midnight(0,0,0);
        qsrand(midnight.msecsTo(QTime::currentTime()));
        int vpd_chast=50/kolvo_rayndov;
        int sum=100%vpd_chast;
        for (int i=0; i<kolvo_rayndov; i++)
        {
            ui->tabWidget->setCurrentIndex(i);


            int ver=qrand()%100+1;
            int segmentov=1;
            if (ver>(100-p3)) segmentov=(qrand()%(md-rd))+rd;
            if ((ver>p1)&&(ver<=(100-p3))) segmentov=(qrand()%(rd-ld))+ld;
            if (ver<=p1) segmentov=(qrand()%(ld-nd))+nd;



            segment_zamen[i]->setValue(segmentov);
            smesch_zamen[i]->setValue((qrand()%240)+1);

            //случайные числа для сегментов замен
            sum+=vpd_chast;
            emit vpered(sum);
            ZamenaSegmentGen(segmentov);

            ver=qrand()%100+1;
            if (ver>(100-p3)) segmentov=(qrand()%(md-rd))+rd;
            if ((ver>p1)&&(ver<=(100-p3))) segmentov=(qrand()%(rd-ld))+ld;
            if (ver<=p1) segmentov=(qrand()%(ld-nd))+nd;

            segment_key[i]->setValue(segmentov);
            //случайные числа для сегментов ключа
            sum+=vpd_chast;
            emit vpered(sum);
            KeySegmentGen(segmentov);


        }


        ui->tabWidget->setCurrentIndex(0);
        ui->pushButton_8->clicked();


        this->setEnabled(true);
        emit hide_wind();
        up.unlock();
    }
}

void MainWindow::smw()
{
    on_tabWidget_currentChanged(0);
}


void MainWindow::ZamenaSegmentGen(int segmentov)
{

    bool *zapolnenie=new bool [segmentov];
    for (int k=0; k<segmentov; k++) zapolnenie[k]=false;
    int buf_segmentov=segmentov;
    int bvs=240-segmentov+1;
    int kolvo_segmentov_donorov=0;


    for (int j=0; j<segmentov; j++)
    {
        int shagov=qrand()%buf_segmentov;
        int tek_segment=-1;
        for (int m=-1; m<shagov; m++)
        {
            tek_segment++;
            if (zapolnenie[tek_segment]) m--;
        }

        zapolnenie[tek_segment]=true;
        kolvo_segmentov_donorov++;

        int tek_bvs=0;
        if (j==segmentov-1) tek_bvs=bvs;
        else tek_bvs=qrand()%bvs+1;


        mas_of_spinbox_zamen[nomer_raynda][tek_segment]->setValue(tek_bvs);

        bvs=bvs-tek_bvs+1;

        buf_segmentov--;
    }



    int kolvo_segmentov_edinic=0;
    for (int k=0; k<segmentov; k++)
        if (mas_of_spinbox_zamen[nomer_raynda][k]->value()==1)
            kolvo_segmentov_edinic++;


    //уменьшение количества единиц
    int edinic=0;
    if (segmentov<=b2) edinic=0;
    if (segmentov>b2) edinic=segmentov;
    while (kolvo_segmentov_edinic>edinic)
    {

        for (int rt=0; rt<kolvo_segmentov_edinic; rt++)
        {
            int nomer_segmenta_donora=qrand()%kolvo_segmentov_donorov+1;
            int ch=0;
            int segment_donora=0;
            for (int t=0; t<segmentov; t++)
            {
                if (mas_of_spinbox_zamen[nomer_raynda][t]->value()!=1) ch++;
                if (ch==nomer_segmenta_donora)
                {
                    segment_donora=t;
                    t=segmentov;
                }
            }


            int nomer_segmenta_edinic=qrand()%kolvo_segmentov_edinic+1;
            int ch2=0;
            int segment_edinic=0;
            for (int t=0; t<segmentov; t++)
            {
                if (mas_of_spinbox_zamen[nomer_raynda][t]->value()==1) ch2++;
                if (ch2==nomer_segmenta_edinic)
                {
                    segment_edinic=t;
                    t=segmentov;
                }
            }


            int bvs2=mas_of_spinbox_zamen[nomer_raynda][segment_donora]->value();
            int zaim=qrand()%bvs2;


            mas_of_spinbox_zamen[nomer_raynda][segment_donora]->setValue(bvs2-zaim);
            mas_of_spinbox_zamen[nomer_raynda][segment_edinic]->setValue(zaim+1);


            kolvo_segmentov_donorov++;
            kolvo_segmentov_edinic--;
        }


        kolvo_segmentov_edinic=0;
        for (int k=0; k<segmentov; k++)
            if (mas_of_spinbox_zamen[nomer_raynda][k]->value()==1)
                kolvo_segmentov_edinic++;
        kolvo_segmentov_donorov=segmentov-kolvo_segmentov_edinic;

    }

    delete [] zapolnenie;



    //выбор номера полинома
    for (int j=0; j<segmentov; j++)
    {
        int nomer=qrand()%mas_of_combobox_zamen[nomer_raynda][j]->maximum()+1;
        if (nomer==0) nomer++;
        mas_of_combobox_zamen[nomer_raynda][j]->setValue(nomer);
    }

}


void MainWindow::KeySegmentGen(int segmentov)
{

    bool *zapolnenie=new bool [segmentov];
    for (int k=0; k<segmentov; k++) zapolnenie[k]=false;
    int buf_segmentov=segmentov;
    int bvs=240-segmentov+1;
    int kolvo_segmentov_donorov=0;


    for (int j=0; j<segmentov; j++)
    {
        int shagov=qrand()%buf_segmentov;
        int tek_segment=-1;
        for (int m=-1; m<shagov; m++)
        {
            tek_segment++;
            if (zapolnenie[tek_segment]) m--;
        }

        zapolnenie[tek_segment]=true;
        kolvo_segmentov_donorov++;

        int tek_bvs=0;
        if (j==segmentov-1) tek_bvs=bvs;
        else tek_bvs=qrand()%bvs+1;

        mas_of_spinbox_key[nomer_raynda][tek_segment]->setValue(tek_bvs);

        bvs=bvs-tek_bvs+1;

        buf_segmentov--;
    }



    int kolvo_segmentov_edinic=0;
    for (int k=0; k<segmentov; k++)
        if (mas_of_spinbox_key[nomer_raynda][k]->value()==1)
            kolvo_segmentov_edinic++;


    //уменьшение количества единиц
    int edinic=0;
    if (segmentov<=b2) edinic=0;
    if (segmentov>b2) edinic=segmentov;
    while (kolvo_segmentov_edinic>edinic)
    {

        for (int rt=0; rt<kolvo_segmentov_edinic; rt++)
        {
            int nomer_segmenta_donora=qrand()%kolvo_segmentov_donorov+1;
            int ch=0;
            int segment_donora=0;
            for (int t=0; t<segmentov; t++)
            {
                if (mas_of_spinbox_key[nomer_raynda][t]->value()!=1) ch++;
                if (ch==nomer_segmenta_donora)
                {
                    segment_donora=t;
                    t=segmentov;
                }
            }


            int nomer_segmenta_edinic=qrand()%kolvo_segmentov_edinic+1;
            int ch2=0;
            int segment_edinic=0;
            for (int t=0; t<segmentov; t++)
            {
                if (mas_of_spinbox_key[nomer_raynda][t]->value()==1) ch2++;
                if (ch2==nomer_segmenta_edinic)
                {
                    segment_edinic=t;
                    t=segmentov;
                }
            }


            int bvs2=mas_of_spinbox_key[nomer_raynda][segment_donora]->value();
            int zaim=qrand()%bvs2;

            mas_of_spinbox_key[nomer_raynda][segment_donora]->setValue(bvs2-zaim);
            mas_of_spinbox_key[nomer_raynda][segment_edinic]->setValue(zaim+1);


            kolvo_segmentov_donorov++;
            kolvo_segmentov_edinic--;
        }


        kolvo_segmentov_edinic=0;
        for (int k=0; k<segmentov; k++)
            if (mas_of_spinbox_key[nomer_raynda][k]->value()==1)
                kolvo_segmentov_edinic++;
        kolvo_segmentov_donorov=segmentov-kolvo_segmentov_edinic;

    }

    delete [] zapolnenie;

}

void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    if (arg1>=ui->spinBox_4->value()) ui->spinBox_4->setValue(arg1+1);
    if (arg1<=ui->spinBox_8->value()) ui->spinBox_8->setValue(arg1-1);



    nd=ui->spinBox_8->value();
    ld=ui->spinBox_3->value();
    rd=ui->spinBox_4->value();
    md=ui->spinBox_9->value();
}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    if (arg1<=ui->spinBox_3->value()) ui->spinBox_3->setValue(arg1-1);
    if (arg1>=ui->spinBox_9->value()) ui->spinBox_9->setValue(arg1+1);




    nd=ui->spinBox_8->value();
    ld=ui->spinBox_3->value();
    rd=ui->spinBox_4->value();
    md=ui->spinBox_9->value();
}

void MainWindow::on_spinBox_8_valueChanged(int arg1)
{
    if (arg1>=ui->spinBox_3->value()) ui->spinBox_3->setValue(arg1+1);



    nd=ui->spinBox_8->value();
    ld=ui->spinBox_3->value();
    rd=ui->spinBox_4->value();
    md=ui->spinBox_9->value();
}

void MainWindow::on_spinBox_9_valueChanged(int arg1)
{
    if (arg1<=ui->spinBox_4->value()) ui->spinBox_4->setValue(arg1-1);



    nd=ui->spinBox_8->value();
    ld=ui->spinBox_3->value();
    rd=ui->spinBox_4->value();
    md=ui->spinBox_9->value();
}

void MainWindow::on_spinBox_5_valueChanged(int arg1)
{
    if (arg1+ui->spinBox_7->value()>100)
        ui->spinBox_5->setValue(100-ui->spinBox_7->value());
    else ui->spinBox_6->setValue(100-arg1-ui->spinBox_7->value());

    p1=ui->spinBox_5->value();
    p3=ui->spinBox_7->value();
}

void MainWindow::on_spinBox_7_valueChanged(int arg1)
{
    if (arg1+ui->spinBox_5->value()>100)
        ui->spinBox_7->setValue(100-ui->spinBox_5->value());
    else ui->spinBox_6->setValue(100-arg1-ui->spinBox_5->value());

    p1=ui->spinBox_5->value();
    p3=ui->spinBox_7->value();
}

void MainWindow::on_spinBox_10_valueChanged(int arg1)
{
    b2=arg1;
}

