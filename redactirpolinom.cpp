#include "mainwindow.h"
#include <QTextStream>
#include <QScrollBar>

void MainWindow::opred_kolva_polinomov()
{
    QFile base_polinom(":/p.txt");
    if (base_polinom.open(QIODevice::ReadOnly))
    {
        //подсчет количества многочленов
        for (int i=0; i<240; i++) kolvo_polinom[i]=0;

        QTextStream stream(&base_polinom);
        QString str;
        int vsego=0;
        while (!stream.atEnd())
        {
            stream>>str;
            kolvo_polinom[str.toInt()-1]++;
            stream.readLine();
            vsego++;
        }

        kolvo_polinom[0]=vsego;

        //заполнение таблицы
        ui->tableWidget_2->setRowCount(1);
        ui->tableWidget_2->setColumnCount(240);
        ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget_2->setStyleSheet("QTableWidget{"
                                         "selection-background-color: grey;"
                                         "}"
                                         "QHeaderView::section{"
                                         "border: 1px solid grey;"
                                         "}"
                                         "QTableWidget QTableCornerButton::section{"
                                         "border: 1px solid grey;"
                                         "}");
        ui->tableWidget_2->setRowHeight(0,15);

        QTableWidgetItem *headerItem = new QTableWidgetItem;
        headerItem->setText("Всего");
        ui->tableWidget_2->setHorizontalHeaderItem(0,headerItem);

        for (int i=0; i<240; i++)
        {
            ui->tableWidget_2->setColumnWidth(i,50);
            QTableWidgetItem *tableItem = new QTableWidgetItem;
            tableItem->setTextAlignment(Qt::AlignHCenter);
            tableItem->setText(QString::number(kolvo_polinom[i]));
            ui->tableWidget_2->setItem(0,i,tableItem);
        }


        ui->tableWidget_3->setRowCount(kolvo_polinom[0]);
        ui->tableWidget_3->setColumnCount(243);
        ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget_3->setStyleSheet("QTableWidget{"
                                         "selection-background-color: grey;"
                                         "}"
                                         "QHeaderView::section{"
                                         "border: 1px solid grey;"
                                         "}"
                                         "QTableWidget QTableCornerButton::section{"
                                         "border: 1px solid grey;"
                                         "}");

        for (int i=0; i<241; i++)
        {
            headerItem= new QTableWidgetItem;
            headerItem->setText(QString::number(240-i));
            ui->tableWidget_3->setHorizontalHeaderItem(i,headerItem);
            ui->tableWidget_3->setColumnWidth(i,20);
        }

        headerItem= new QTableWidgetItem;
        headerItem->setText("ЛН");
        ui->tableWidget_3->setHorizontalHeaderItem(241,headerItem);
        ui->tableWidget_3->setColumnWidth(241,50);

        headerItem= new QTableWidgetItem;
        headerItem->setText("СМ");
        ui->tableWidget_3->setHorizontalHeaderItem(242,headerItem);
        ui->tableWidget_3->setColumnWidth(242,50);

        for (int i=0; i<kolvo_polinom[0]; i++)
        {
            headerItem = new QTableWidgetItem;
            headerItem->setTextAlignment(Qt::AlignHCenter);
            headerItem->setText(QString::number(i+1));
            ui->tableWidget_3->setVerticalHeaderItem(i,headerItem);
            ui->tableWidget_3->setRowHeight(i,18);
        }

        mas_polinomov=new PolinomM2 [kolvo_polinom[0]];

        stream.seek(0);
        int cx=0;
        while (!stream.atEnd())
        {
            QString itog="";
            str=stream.readLine();

            //определяем число степени многочлена, пока не найдем табуляцию
            //while, т.к. степень многочлена может состоять из нескольких знаков в одном числе
            //а не из одного как в многочлене по модулю 2
            int ch=0;
            while (str.at(ch)!='	')
            {
                itog+=str.at(ch);
                ch++;
            }
            QTableWidgetItem *tableItem = new QTableWidgetItem;
            tableItem->setTextAlignment(Qt::AlignHCenter);
            tableItem->setText(itog);
            ui->tableWidget_3->setItem(cx,242,tableItem);


            itog="";
            //пропускаем табуляцию
            ch++;
            while (str.at(ch)!='	'&&ch<str.length())
            {
                itog+=str.at(ch);
                ch+=2;
            }

            //неприводимый многочлен в массив байт
            int size_NepMasBit=itog.size();
            bool* NepMasBit;
            NepMasBit= new bool [size_NepMasBit];

            QString odin_simbol;
            for (int i=0; i<size_NepMasBit; i++)
            {
                odin_simbol=itog.at(i);
                NepMasBit[size_NepMasBit-1-i]=odin_simbol.toInt();
            }

            //создание и заполнение полинома из массива байт
            mas_polinomov[cx].fromMasBitToPolinomM2(NepMasBit,size_NepMasBit);
            delete [] NepMasBit;
            cx++;
        }

        int st=2;
        int loc_num=0;
        for (int m=0; m<kolvo_polinom[0]; m++)
        {
            //присвоение локальных номеров от степени многочлена
            int new_st=ui->tableWidget_3->item(m,242)->text().toInt();
            if (new_st!=st)
            {
                loc_num=0;
                st=new_st;
            }
            loc_num++;
            QTableWidgetItem *tableItem = new QTableWidgetItem;
            tableItem->setTextAlignment(Qt::AlignHCenter);
            tableItem->setText(QString::number(loc_num));
            ui->tableWidget_3->setItem(m,241,tableItem);


            for (int k=0; k<mas_polinomov[m].getPolinomSize(); k++)
            {
                //заполнение таблицы многочленами
                QTableWidgetItem *tableItem = new QTableWidgetItem;
                tableItem->setTextAlignment(Qt::AlignHCenter);
                tableItem->setText(QString::number(mas_polinomov[m].getPolinom(mas_polinomov[m].getPolinomSize()-1-k)));
                ui->tableWidget_3->setItem(m,240-k,tableItem);
            }
        }
    }
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    int sverxy=kolvo_polinom[0];
    int snizy=0;
    for (int i=2; i<arg1; i++) snizy+=kolvo_polinom[i-1];
    for (int i=239; i>=arg1; i--) sverxy-=kolvo_polinom[i];

    for (int i=0; i<snizy; i++) ui->tableWidget_3->hideRow(i);
    for (int i=kolvo_polinom[0]; i>=sverxy; i--) ui->tableWidget_3->hideRow(i);
    for (int i=snizy; i<sverxy; i++) ui->tableWidget_3->showRow(i);

    if (hideshow>=arg1)
    {
        for (int i=0; i<240-arg1; i++) ui->tableWidget_3->hideColumn(i);
        hideshow=arg1;
    }
    else
    {
        for (int i=240-arg1; i<241; i++) ui->tableWidget_3->showColumn(i);
        hideshow=arg1;
    }
    ui->tableWidget_3->horizontalScrollBar()->setValue(
                ui->tableWidget_3->horizontalScrollBar()->maximum());
}

void MainWindow::on_checkBox_4_clicked()
{
    if (ui->checkBox_4->isChecked())
    {
        ui->spinBox_2->setEnabled(false);

        for (int i=0; i<240; i++) ui->tableWidget_3->showColumn(i);
        for (int i=0; i<kolvo_polinom[0]; i++) ui->tableWidget_3->showRow(i);

        ui->tableWidget_3->setEnabled(false);
        ui->tableWidget_3->setEnabled(true);

        ui->tableWidget_3->horizontalScrollBar()->setMaximum(230);
        ui->tableWidget_3->horizontalScrollBar()->setValue(
                    ui->tableWidget_3->horizontalScrollBar()->maximum());
    }
    else
    {
        ui->spinBox_2->valueChanged(ui->spinBox_2->value());
        ui->spinBox_2->setEnabled(true);
    }
}
