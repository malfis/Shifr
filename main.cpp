#include "combosegment.h"
#include "spinsegment.h"
#include "spinsegmentk.h"
#include "knopkasmena.h"
#include "func.cpp"

#include <QTime>

#include <QApplication>
#include <QFileDialog>
#include <QTextStream>
#include <QDataStream>
#include <QBuffer>
#include "convertthread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->radioButton_3->isChecked())
    {
        if (stop.tryLock())
        {
            ui->pushButton_8->setEnabled(false);
            ui->label_5->setEnabled(false);
            ui->checkBox_2->setEnabled(false);
            ui->plainTextEdit_2->setEnabled(false);
            ui->groupBox_3->setEnabled(false);
            ui->toolBox->setEnabled(false);
            ui->radioButton_3->setEnabled(false);
            ui->radioButton_4->setEnabled(false);

            bool balance_error=false;
            for (int i=0; i<ui->spinBox->value(); i++)
                if (balance_zamen[i]->text()!="Балансировка: 0"||
                        balance_key[i]->text()!="Балансировка: 0")
                {
                    balance_error=true;
                    i=ui->spinBox->value();
                }
            if (balance_error)
            {
                ui->lineEdit_4->setText("Ошибка разбалансировки!");
                stop.unlock();
                ui->pushButton_8->setEnabled(true);
                ui->label_5->setEnabled(true);
                ui->checkBox_2->setEnabled(true);
                ui->plainTextEdit_2->setEnabled(true);
                ui->groupBox_3->setEnabled(true);
                ui->toolBox->setEnabled(true);
                ui->radioButton_3->setEnabled(true);
                ui->radioButton_4->setEnabled(true);
                return;
            }

            ui->lineEdit_4->setText("Откройте файл!");

            cur.remove(cur.lastIndexOf("/")+1,cur.length()-cur.lastIndexOf("/")-1);
            cur=QFileDialog::getOpenFileName(this,"Выберите файл для шифрования",cur,
                                             "Все файлы (*)");



            if(cur!="")
            {
                ui->pushButton->setText("Прервать");
                time.restart();
                emit file_shifr(cur);
            }
            else
            {
                stop.unlock();
                ui->pushButton_8->setEnabled(true);
                ui->label_5->setEnabled(true);
                ui->checkBox_2->setEnabled(true);
                ui->plainTextEdit_2->setEnabled(true);
                ui->groupBox_3->setEnabled(true);
                ui->toolBox->setEnabled(true);
                ui->radioButton_3->setEnabled(true);
                ui->radioButton_4->setEnabled(true);
            }
        }
        else
        {
            convert->exit=true;
        }
    }

    if (ui->radioButton_4->isChecked())
    {
        if (stop.tryLock())
        {
            ui->pushButton_8->setEnabled(false);
            ui->label_5->setEnabled(false);
            ui->checkBox_2->setEnabled(false);
            ui->plainTextEdit_2->setEnabled(false);
            ui->groupBox_3->setEnabled(false);
            ui->toolBox->setEnabled(false);
            ui->radioButton_3->setEnabled(false);
            ui->radioButton_4->setEnabled(false);




            bool balance_error=false;
            for (int i=0; i<ui->spinBox->value(); i++)
                if (balance_zamen[i]->text()!="Балансировка: 0"||
                        balance_key[i]->text()!="Балансировка: 0")
                {
                    balance_error=true;
                    i=ui->spinBox->value();
                }
            if (balance_error)
            {
                ui->lineEdit_4->setText("Ошибка разбалансировки!");
                stop.unlock();
                ui->pushButton_8->setEnabled(true);
                ui->label_5->setEnabled(true);
                ui->checkBox_2->setEnabled(true);
                ui->plainTextEdit_2->setEnabled(true);
                ui->groupBox_3->setEnabled(true);
                ui->toolBox->setEnabled(true);
                ui->radioButton_3->setEnabled(true);
                ui->radioButton_4->setEnabled(true);
                return;
            }



            ui->lineEdit_4->setText("Откройте файл!");


            cur.remove(cur.lastIndexOf("/")+1,cur.length()-cur.lastIndexOf("/")-1);
            cur=QFileDialog::getOpenFileName(this,"Выберите файл для расшифрования",cur,
                                             "Жданы (*.zhdan);;"
                                             "Все файлы (*)");

            if(cur!="")
            {
                ui->pushButton->setText("Прервать");
                time.restart();
                emit file_rasshifr(cur);
            }
            else
            {
                stop.unlock();
                ui->pushButton_8->setEnabled(true);
                ui->label_5->setEnabled(true);
                ui->checkBox_2->setEnabled(true);
                ui->plainTextEdit_2->setEnabled(true);
                ui->groupBox_3->setEnabled(true);
                ui->toolBox->setEnabled(true);
                ui->radioButton_3->setEnabled(true);
                ui->radioButton_4->setEnabled(true);
            }
        }
        else
        {
            convert->exit=true;
        }
    }
}

void MainWindow::file_exit(QString err)
{
    ui->label_13->setText("<html><head/><body><p align='center'>"+
                          QString::number(time.elapsed())+" мс</p></body></html>");

    progressbar->setValue(0);
    convert->exit=false;
    ui->pushButton->setText("Открыть файл");
    ui->lineEdit_4->setText(err);

    stop.unlock();
    ui->pushButton_8->setEnabled(true);
    ui->label_5->setEnabled(true);
    ui->checkBox_2->setEnabled(true);
    ui->plainTextEdit_2->setEnabled(true);
    ui->groupBox_3->setEnabled(true);
    ui->toolBox->setEnabled(true);
    ui->radioButton_3->setEnabled(true);
    ui->radioButton_4->setEnabled(true);
}

void MainWindow::on_plainTextEdit_2_textChanged()
{
    if (stop.tryLock())
    {
        //преобразуем общий ключ в массив бит
        QString key = ui->plainTextEdit_2->toPlainText();
        if (key=="")
        {
            general_key_off=true;
            stop.unlock();
            return;
        }
        else
            general_key_off=false;

        if (key.size()<240)
        {
            size_general_key = 240;
            general_key = new bool [size_general_key];
            int dyplir_key=0;
            for (int i=0; i<size_general_key; i++)
            {
                if (dyplir_key>key.size()-1) dyplir_key=0;
                QString odin_simbol=key.at(dyplir_key);
                general_key[i]=odin_simbol.toInt();
                dyplir_key++;
            }
        }
        else
        {
            size_general_key = key.size();
            general_key = new bool [size_general_key];
            for (int i=0; i<size_general_key; i++)
            {
                QString odin_simbol=key.at(i);
                general_key[i]=odin_simbol.toInt();
            }
        }

        if (smesch_key!=NULL) updateRayndKey();

        testK1(ui->plainTextEdit_2->toPlainText());
        testK2(ui->plainTextEdit_2->toPlainText());
        stop.unlock();
    }
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if (stop.tryLock())
    {
        QString text = ui->plainTextEdit->toPlainText();
        QString output;
        if (checked)
        {
            wchar_t MasOf2Byte[text.size()];
            text.toWCharArray(MasOf2Byte);

            int size_MasOfBit = text.size()*symbol;
            bool MasOfBit[size_MasOfBit];
            ToBit(MasOf2Byte, text.size(), MasOfBit);

            for (unsigned int i=0; i<sizeof(MasOfBit); i++)
                output=output+QString::number(MasOfBit[i]);

            ui->plainTextEdit->binary=true;
        }else
        {
            bool MasOfBit[text.size()];
            QString odin_simbol;
            for (int i=0; i<text.size(); i++)
            {
                odin_simbol=text.at(i);
                MasOfBit[i]=odin_simbol.toInt();
            }

            int size_MasOf2Byte = text.size()/symbol;
            wchar_t MasOf2Byte[size_MasOf2Byte];
            ToType(MasOfBit, MasOf2Byte, size_MasOf2Byte);

            output=QString::fromWCharArray(MasOf2Byte,size_MasOf2Byte);

            ui->plainTextEdit->binary=false;
        }

        ui->plainTextEdit->setPlainText(output);
        stop.unlock();
    }
}

void MainWindow::on_radioButton_clicked()
{
    if (stop.tryLock())
    {
        ui->checkBox->setEnabled(false);
        ui->radioButton_2->setEnabled(false);
        ui->tabWidget_2->setCurrentIndex(1);
        ui->plainTextEdit->setReadOnly(false);
        ui->plainTextEdit->setPalette(fon_w);
        ui->plainTextEdit_6->setReadOnly(true);
        ui->plainTextEdit_6->setPalette(fon_t);


        bool balance_error=false;
        for (int i=0; i<ui->spinBox->value(); i++)
            if (balance_zamen[i]->text()!="Балансировка: 0"||
                    balance_key[i]->text()!="Балансировка: 0")
            {
                balance_error=true;
                i=ui->spinBox->value();
            }
        if (balance_error)
        {
            ui->plainTextEdit_6->setPlainText("Ошибка разбалансировки!");
            stop.unlock();
            ui->checkBox->setEnabled(true);
            ui->radioButton_2->setEnabled(true);
            return;
        }

        //преобразуем всю входную информацию в массив бит
        QString text = ui->plainTextEdit->toPlainText();
        if (text=="")
        {
            ui->plainTextEdit_6->setPlainText("");
            stop.unlock();
            ui->checkBox->setEnabled(true);
            ui->radioButton_2->setEnabled(true);
            return;
        }

        const int size_byte=8;
        int size_MasTextBit;
        bool* MasTextBit;
        if (!ui->checkBox->isChecked())
        {
            //если UNICODE
            wchar_t MasText2Byte[text.size()];
            text.toWCharArray(MasText2Byte);

            size_MasTextBit = text.size()*sizeof(wchar_t)*size_byte;
            MasTextBit= new bool [size_MasTextBit];
            ToBit(MasText2Byte, text.size(), MasTextBit);
        }else
        {
            //если двоичный вид
            if (text.size()%symbol!=0)
            {
                ui->plainTextEdit_6->setPlainText(
                            "Внимание! Текст должен быть кратен "+
                            QString::number(symbol)+". "
                            "Добавляйте или убирайте знаки до тех пор, "
                            "пока текст не станет кратным "+
                            QString::number(symbol)+".");
                stop.unlock();
                return;
            }
            size_MasTextBit = text.size();
            MasTextBit= new bool [size_MasTextBit];
            QString odin_simbol;
            for (int i=0; i<size_MasTextBit; i++)
            {
                odin_simbol=text.at(i);
                MasTextBit[i]=odin_simbol.toInt();
            }
        }


        //Формируем массив кратный размеру блока 240 бит
        unsigned char kolvo_normir_bit=240-8-size_MasTextBit%240;
        int size_MasNormirBit=kolvo_normir_bit+8+size_MasTextBit;
        bool *MasNormirBit= new bool [size_MasNormirBit];

        SetNormirMas(MasNormirBit, size_MasNormirBit,
                     MasTextBit, kolvo_normir_bit);

        delete [] MasTextBit;


        //вывод нормированного текста
        QString normir="";
        for (int i=0; i<size_MasNormirBit; i++)
            normir+=QString::number(MasNormirBit[i]);
        ui->plainTextEdit_7->setPlainText(normir);


        int err=shivrovanie(MasNormirBit, size_MasNormirBit);
        if (err==-1)
        {
            ui->plainTextEdit_6->setPlainText("Ошибка! Введите корректный многочлен.");
            delete [] MasNormirBit;
            stop.unlock();
            ui->checkBox->setEnabled(true);
            ui->radioButton_2->setEnabled(true);
            return;
        }


        //вывод шифрованного текста
        QString output="";
        for (int i=0; i<size_MasNormirBit; i++)
            output+=QString::number(MasNormirBit[i]);
        ui->plainTextEdit_6->setPlainText(output);

        ui->label_14->setText("("+QString::number(output.length())+" бит)");

        delete [] MasNormirBit;


        testK1(output);
        testK2(output);


        stop.unlock();
        ui->checkBox->setEnabled(true);
        ui->radioButton_2->setEnabled(true);
    }
}

int MainWindow::shivrovanie(bool *MasBit, int size_MasBit)
{
    //цикл раундов
    for (int r=0; r<ui->spinBox->value(); r++)
    {
        //цикл блоков
        int kolvo_blokov240bit=size_MasBit/240;
        bool Mas240bit[240];
        for (int b=0; b<kolvo_blokov240bit; b++)
        {
            //заполняем массив для текущего блока
            for (int i=0; i<240; i++) Mas240bit[i]=MasBit[240*b+i];

            //осуществление замены
            int sdvig=0;
            for (int sz=0; sz<segment_zamen[r]->value(); sz++)
            {
                if (mas_of_spinbox_zamen[r][sz]->value()==1)
                {
                    //определение инверсии бита если сегмент из одного бита
                    if (id_polinoma_na_segment[r][sz]==2) Mas240bit[sdvig]=!Mas240bit[sdvig];
                    sdvig++;
                }
                else
                {
                    bool *MasSegmentBit = new bool [mas_of_spinbox_zamen[r][sz]->value()];
                    for (int i=0; i<mas_of_spinbox_zamen[r][sz]->value(); i++)
                        MasSegmentBit[i]=Mas240bit[i+sdvig];


                    PolinomM2 polinomSegmentBit;
                    polinomSegmentBit.fromMasBitToPolinomM2(MasSegmentBit, mas_of_spinbox_zamen[r][sz]->value());
                    delete [] MasSegmentBit;
                    PolinomM2 zamenaSegmentBit;
                    PolinomM2 mysor;



                    int err=Evklid(polinomSegmentBit,
                                   mas_polinomov[id_polinoma_na_segment[r][sz]-1],
                            zamenaSegmentBit, mysor);
                    if (err==-1) return -1;



                    for (int i=sdvig; i<sdvig+mas_of_spinbox_zamen[r][sz]->value()-zamenaSegmentBit.getPolinomSize(); i++)
                        Mas240bit[i]=0;

                    for (int i=0; i<zamenaSegmentBit.getPolinomSize(); i++)
                        Mas240bit[mas_of_spinbox_zamen[r][sz]->value()-1-i+sdvig]=
                                zamenaSegmentBit.getPolinom(zamenaSegmentBit.getPolinomSize()-1-i);




                    sdvig+=mas_of_spinbox_zamen[r][sz]->value();
                }
            }


            //циклический сдвиг после замены
            if (smesch_zamen[r]->value()!=240)
            {
                bool *buf_Mas240bit = new bool [smesch_zamen[r]->value()];

                for (int i=240-smesch_zamen[r]->value(); i<240; i++)
                    buf_Mas240bit[i-(240-smesch_zamen[r]->value())]=Mas240bit[i];

                for (int i=239-smesch_zamen[r]->value(); i>=0; i--)
                    Mas240bit[i+smesch_zamen[r]->value()]=Mas240bit[i];

                for (int i=0; i<smesch_zamen[r]->value(); i++)
                    Mas240bit[i]=buf_Mas240bit[i];

                delete [] buf_Mas240bit;
            }

            //объединение с ключом
            sdvig=0;
            for (int sk=0; sk<kol_vo_segmentov_key[r]; sk++)
            {
                bool buf=0;
                int kolvo_edinic=0;
                for (int i=mas_of_spinbox_key[r][sk]->value()-1; i>=0; i--)
                {
                    if (Mas240bit[i+sdvig]==1) kolvo_edinic++;
                    if (raynd_key[r][i+sdvig]==1) kolvo_edinic++;
                    if (buf==1) kolvo_edinic++;

                    if (kolvo_edinic==1)
                    {
                        Mas240bit[i+sdvig]=1;
                        buf=0;
                    }
                    else if (kolvo_edinic==2)
                    {
                        Mas240bit[i+sdvig]=0;
                        buf=1;
                    }
                    else if (kolvo_edinic==0)
                    {
                        Mas240bit[i+sdvig]=0;
                        buf=0;
                    }
                    else
                    {
                        Mas240bit[i+sdvig]=1;
                        buf=1;
                    }
                    kolvo_edinic=0;

                }

                sdvig+=mas_of_spinbox_key[r][sk]->value();
            }


            //заменяем шифртекстом блока часть исходного текста
            for (int i=0; i<240; i++) MasBit[240*b+i]=Mas240bit[i];
        }
    }

    return 0;
}

void MainWindow::on_radioButton_2_clicked()
{
    if (stop.tryLock())
    {
        ui->checkBox->setEnabled(false);
        ui->radioButton->setEnabled(false);
        ui->tabWidget_2->setCurrentIndex(2);
        ui->plainTextEdit->setReadOnly(true);
        ui->plainTextEdit->setPalette(fon_t);
        ui->plainTextEdit_6->setReadOnly(false);
        ui->plainTextEdit_6->setPalette(fon_w);
        ui->label_14->setText("("+QString::number(ui->plainTextEdit_6->toPlainText().length())+" бит)");

        bool balance_error=false;
        for (int i=0; i<ui->spinBox->value(); i++)
            if (balance_zamen[i]->text()!="Балансировка: 0"||
                    balance_key[i]->text()!="Балансировка: 0")
            {
                balance_error=true;
                i=ui->spinBox->value();
            }
        if (balance_error)
        {
            ui->plainTextEdit_6->setPlainText("Ошибка разбалансировки!");
            stop.unlock();
            ui->checkBox->setEnabled(true);
            ui->radioButton->setEnabled(true);
            return;
        }


        //преобразуем всю входную информацию в массив бит
        QString text = ui->plainTextEdit_6->toPlainText();
        if (text=="")
        {
            ui->plainTextEdit->setPlainText("");
            stop.unlock();
            ui->checkBox->setEnabled(true);
            ui->radioButton->setEnabled(true);
            return;
        }
        if (text.size()%240!=0)
        {
            ui->plainTextEdit->setPlainText(
                        "Внимание! Текст должен быть кратен 240. "
                        "Добавляйте или убирайте знаки до тех пор, "
                        "пока текст не станет кратным 240.");
            stop.unlock();
            return;
        }

        int size_MasBit;
        bool* MasBit;

        size_MasBit = text.size();
        MasBit= new bool [size_MasBit];
        QString odin_simbol;
        for (int i=0; i<size_MasBit; i++)
        {
            odin_simbol=text.at(i);
            MasBit[i]=odin_simbol.toInt();
        }



        int err=rasshivrovanie(MasBit, size_MasBit);
        if (err==-1)
        {
            ui->plainTextEdit_6->setPlainText("Ошибка! Введите корректный многочлен.");
            delete [] MasBit;
            stop.unlock();
            ui->checkBox->setEnabled(true);
            ui->radioButton_2->setEnabled(true);
            return;
        }



        int size_buf=1;
        unsigned char *buf = new unsigned char [size_buf];
        ToType(MasBit, buf, size_buf);
        unsigned char kolvo_normir_bit=buf[0];
        delete [] buf;

        if (kolvo_normir_bit>232) kolvo_normir_bit=0;


        //Получаем массив с полезными данными бит
        int size_MasTextBit=size_MasBit-8-kolvo_normir_bit;
        bool *MasTextBit= new bool [size_MasTextBit];
        for (int i=8+kolvo_normir_bit; i<size_MasBit; i++)
            MasTextBit[i-8-kolvo_normir_bit]=MasBit[i];


        //вывод расшифровки с выбором представления информации
        QString output;

        if (ui->checkBox->isChecked())
        {
            for (int i=0; i<size_MasTextBit; i++)
                output=output+QString::number(MasTextBit[i]);
        }else
        {
            const int size_byte=8;
            int size_MasText2Byte=size_MasTextBit/(sizeof(wchar_t)*size_byte);
            wchar_t MasText2Byte[size_MasText2Byte];
            ToType(MasTextBit, MasText2Byte, size_MasText2Byte);

            output=QString::fromWCharArray(MasText2Byte,size_MasText2Byte);
        }

        delete [] MasTextBit;

        ui->plainTextEdit->setPlainText(output);

        testK1(text);
        testK2(text);

        stop.unlock();
        ui->checkBox->setEnabled(true);
        ui->radioButton->setEnabled(true);
    }
}

int MainWindow::rasshivrovanie(bool *MasBit, int size_MasBit)
{
    //цикл раундов
    for (int r=ui->spinBox->value()-1; r>=0; r--)
    {
        //цикл блоков
        int kolvo_blokov240bit=size_MasBit/240;
        bool Mas240bit[240];
        for (int b=0; b<kolvo_blokov240bit; b++)
        {
            //заполняем массив для текущего блока
            for (int i=0; i<240; i++) Mas240bit[i]=MasBit[240*b+i];

            //объединение с ключом
            int sdvig=0;
            for (int sk=0; sk<kol_vo_segmentov_key[r]; sk++)
            {

                bool *mas2 = new bool [mas_of_spinbox_key[r][sk]->value()];
                for (int i=0; i<mas_of_spinbox_key[r][sk]->value(); i++)
                {
                    //инверсия для вычитания
                    if (raynd_key[r][i+sdvig]==1) mas2[i]=0;
                    else mas2[i]=1;
                }


                //прибавление единицы
                bool buf=0;
                int kolvo_edinic=1;
                for (int i=mas_of_spinbox_key[r][sk]->value()-1; i>=0; i--)
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
                for (int i=mas_of_spinbox_key[r][sk]->value()-1; i>=0; i--)
                {
                    if (Mas240bit[i+sdvig]==1) kolvo_edinic++;
                    if (mas2[i]==1) kolvo_edinic++;
                    if (buf==1) kolvo_edinic++;

                    if (kolvo_edinic==1)
                    {
                        Mas240bit[i+sdvig]=1;
                        buf=0;
                    }
                    else if (kolvo_edinic==2)
                    {
                        Mas240bit[i+sdvig]=0;
                        buf=1;
                    }
                    else if (kolvo_edinic==0)
                    {
                        Mas240bit[i+sdvig]=0;
                        buf=0;
                    }
                    else
                    {
                        Mas240bit[i+sdvig]=1;
                        buf=1;
                    }
                    kolvo_edinic=0;
                }

                delete [] mas2;



                sdvig+=mas_of_spinbox_key[r][sk]->value();
            }

            //циклический сдвиг после замены
            if (smesch_zamen[r]->value()!=240)
            {
                bool *buf_Mas240bit = new bool [smesch_zamen[r]->value()];

                for (int i=0; i<smesch_zamen[r]->value(); i++)
                    buf_Mas240bit[i]=Mas240bit[i];

                for (int i=0; i<240-smesch_zamen[r]->value(); i++)
                    Mas240bit[i]=Mas240bit[i+smesch_zamen[r]->value()];

                for (int i=240-smesch_zamen[r]->value(); i<240; i++)
                    Mas240bit[i]=buf_Mas240bit[i-(240-smesch_zamen[r]->value())];

                delete [] buf_Mas240bit;
            }

            //осуществление замены
            sdvig=0;
            for (int sz=0; sz<segment_zamen[r]->value(); sz++)
            {
                if (mas_of_spinbox_zamen[r][sz]->value()==1)
                {
                    //определение инверсии бита если сегмент из одного бита
                    if (id_polinoma_na_segment[r][sz]==2) Mas240bit[sdvig]=!Mas240bit[sdvig];
                    sdvig++;
                }
                else
                {
                    bool *MasSegmentBit = new bool [mas_of_spinbox_zamen[r][sz]->value()];
                    for (int i=0; i<mas_of_spinbox_zamen[r][sz]->value(); i++)
                        MasSegmentBit[i]=Mas240bit[i+sdvig];


                    PolinomM2 polinomSegmentBit;
                    polinomSegmentBit.fromMasBitToPolinomM2(MasSegmentBit, mas_of_spinbox_zamen[r][sz]->value());
                    delete [] MasSegmentBit;
                    PolinomM2 zamenaSegmentBit;
                    PolinomM2 mysor;



                    int err=Evklid(polinomSegmentBit,
                                   mas_polinomov[id_polinoma_na_segment[r][sz]-1],
                            zamenaSegmentBit, mysor);
                    if (err==-1) return -1;


                    for (int i=sdvig; i<sdvig+mas_of_spinbox_zamen[r][sz]->value()-zamenaSegmentBit.getPolinomSize(); i++)
                        Mas240bit[i]=0;

                    for (int i=0; i<zamenaSegmentBit.getPolinomSize(); i++)
                        Mas240bit[mas_of_spinbox_zamen[r][sz]->value()-1-i+sdvig]=
                                zamenaSegmentBit.getPolinom(zamenaSegmentBit.getPolinomSize()-1-i);


                    sdvig+=mas_of_spinbox_zamen[r][sz]->value();
                }
            }

            //заменяем шифртекстом блока часть исходного текста
            for (int i=0; i<240; i++) MasBit[240*b+i]=Mas240bit[i];
        }
    }

    return 0;
}


void MainWindow::on_pushButton_2_clicked()
{
    //получаем неприводимый многочлен
    QString text2 = ui->plainTextEdit_5->toPlainText();
    int size_NepMas120Bit=text2.size();
    bool* NepMas120Bit;
    NepMas120Bit= new bool [size_NepMas120Bit];
    QString odin_simbol2;
    for (int i=0; i<size_NepMas120Bit; i++)
    {
        odin_simbol2=text2.at(i);
        NepMas120Bit[i]=odin_simbol2.toInt();
    }
    //создание и заполнение полинома из массива байт
    PolinomM2 neprivodim120bit;
    neprivodim120bit.fromMasBitToPolinomM2(NepMas120Bit,size_NepMas120Bit);
    delete [] NepMas120Bit;

    //получаем исходный многочлен
    QString text = ui->plainTextEdit_4->toPlainText();
    int size_Mas120Bit=text.size();
    bool* Mas120Bit;
    Mas120Bit= new bool [size_Mas120Bit];
    QString odin_simbol;
    for (int i=0; i<size_Mas120Bit; i++)
    {
        odin_simbol=text.at(i);
        Mas120Bit[i]=odin_simbol.toInt();
    }
    //создание и заполнение полинома из массива байт
    PolinomM2 polinom120bit;
    polinom120bit.fromMasBitToPolinomM2(Mas120Bit,size_Mas120Bit);
    delete [] Mas120Bit;



    PolinomM2 zamena120bit;
    PolinomM2 mysor;
    int err=Evklid(polinom120bit,neprivodim120bit,zamena120bit,mysor);
    if (err==-1)
    {
        ui->plainTextEdit_3->setPlainText("Ошибка! Введите корректный многочлен.");
        return;
    }

    //вывод заполненного полинома
    QString output;
    for (int i=0; i<zamena120bit.getPolinomSize(); i++)
        output=output+QString::number(zamena120bit.getPolinom(i));

    ui->plainTextEdit_3->setPlainText(output);
}

void MainWindow::on_checkBox_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->checkBox_5->setChecked(false);
}

void MainWindow::on_checkBox_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->checkBox_3->setChecked(false);
}



