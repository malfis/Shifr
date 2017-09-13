#include "convertthread.h"
#include "funcdyblicat.cpp"
#include <QTextStream>

ConvertThread::ConvertThread(QWidget *parent) :
    QObject(parent)
{
    exit=false;
    ui=NULL;


    okno= new QMainWindow;
    okno->setFixedSize(300,50);
    okno->setParent(0);
    pb = new QProgressBar;
    pb->setParent(okno);
    pb->setFixedSize(300,50);
    okno->setCentralWidget(pb);
    okno->showMinimized();
    okno->hide();

}

ConvertThread::~ConvertThread()
{
    delete okno;
}


void ConvertThread::file_shifr(QString cur)
{
    int chast_file_byte=100080;
    QString err="";

    QString file_name=cur;
    file_name.remove(0,file_name.lastIndexOf("/")+1);
    if (file_name.lastIndexOf(".")!=-1)
        file_name.remove(file_name.lastIndexOf("."),
                         file_name.length()-file_name.lastIndexOf(".")+1);

    QString file_format=cur;
    file_format.remove(0,file_format.lastIndexOf("/")+1);
    if (file_format.lastIndexOf(".")!=-1) file_format.remove(0,file_format.lastIndexOf(".")+1);
    else file_format="";



    QFile file(cur);
    cur.remove(cur.lastIndexOf("/")+1,cur.length()-cur.lastIndexOf("/")-1);
    cur+=file_name+".zhdan";
    QFile file_save(cur);
    cur.remove(cur.lastIndexOf("/")+1,cur.length()-cur.lastIndexOf("/")-1);

    //открытие файлов
    if (file.open(QIODevice::ReadOnly))
    {
        file_save.remove();
        if (!file_save.open(QIODevice::ReadWrite))
        {
            file.close();
            err="Ошибка записи!";
            emit file_exit(err);
            return;
        }
    }
    else
    {
        err="Ошибка чтения!";
        emit file_exit(err);
        return;
    }





    //запись формата файла
    QString tex;
    if (file_format!="") tex=QString::number(file_format.length())+" "+file_format;
    else tex="0 "+file_format;

    //создание массива char из wchar_t тех информации
    int texWCharT_size=tex.length()*2;
    char *texWCharT = new char [texWCharT_size];
    for (int i=0; i<tex.length()*2; i+=2)
    {
        texWCharT[i]=tex.at(i/2).cell();
        texWCharT[i+1]=tex.at(i/2).row();
    }


    //Формируем файл кратный размеру блока 240 бит
    int size_byte=8;
    unsigned char normir_chast_data_bit=((file.size()+texWCharT_size)%30)*size_byte;
    unsigned char kolvo_normir_bit=240-8-normir_chast_data_bit;
    bool *MasNormirBit= new bool [240];
    bool *MasChastBit= new bool [normir_chast_data_bit];


    char *full_data= new char[normir_chast_data_bit/8];
    if (normir_chast_data_bit/8>texWCharT_size)
    {
        for (int i=0; i<texWCharT_size; i++) full_data[i]=texWCharT[i];


        //чтения части полезных данных для нормировки
        char *file_data= new char[normir_chast_data_bit/8-texWCharT_size];
        file.seek(0);
        QDataStream potok_is_file(&file);
        potok_is_file.readRawData(file_data, normir_chast_data_bit/8-texWCharT_size);

        for (int i=texWCharT_size; i<normir_chast_data_bit/8; i++) full_data[i]=file_data[i-texWCharT_size];
        delete [] file_data;
    }
    else
    {
        for (int i=0; i<normir_chast_data_bit/8; i++) full_data[i]=texWCharT[i];
    }

    //преобразуем всю входную информацию в массив бит
    ToBit2(full_data, normir_chast_data_bit/8, MasChastBit);
    delete [] full_data;



    SetNormirMas2(MasNormirBit, 240, MasChastBit, kolvo_normir_bit);

    int errn=ui->shivrovanie(MasNormirBit, 240);
    if (errn==-1)
    {
        err="Ошибка шифрования!";
        file.close();
        file_save.remove();
        file_save.close();
        emit file_exit(err);
        return;
    }

    delete [] MasChastBit;

    int size_MasNormirByte = 30;
    char* MasNormirByte= new  char [size_MasNormirByte];
    ToType2(MasNormirBit, MasNormirByte, size_MasNormirByte);
    delete [] MasNormirBit;

    //запись нормировочного блока перед частью данных до нормировки
    file_save.write(MasNormirByte,size_MasNormirByte);

    delete [] MasNormirByte;


    //дозапись остатка тех. данных, если они не записались полностью
    if (normir_chast_data_bit/8<texWCharT_size)
    {
        int dozap_size=(texWCharT_size-normir_chast_data_bit/8)+
                (30-(texWCharT_size-normir_chast_data_bit/8)%30);
        char *dozap= new char[dozap_size];

        for (int i=normir_chast_data_bit/8; i<texWCharT_size; i++)
            dozap[i-normir_chast_data_bit/8]=texWCharT[i];

        char *buf= new char[(30-(texWCharT_size-normir_chast_data_bit/8)%30)];
        QDataStream potok_is_file(&file);
        potok_is_file.readRawData(buf, (30-(texWCharT_size-normir_chast_data_bit/8)%30));

        for (int i=texWCharT_size-normir_chast_data_bit/8; i<dozap_size; i++)
            dozap[i]=buf[i-(texWCharT_size-normir_chast_data_bit/8)];

        delete [] buf;

        bool *dozap_bit= new bool[dozap_size*size_byte];
        ToBit2(dozap, dozap_size, dozap_bit);

        int errn=ui->shivrovanie(dozap_bit, dozap_size*size_byte);
        if (errn==-1)
        {
            err="Ошибка шифрования!";
            file.close();
            file_save.remove();
            file_save.close();
            emit file_exit(err);
            return;
        }

        ToType2(dozap_bit, dozap, dozap_size);
        delete [] dozap_bit;

        file_save.write(dozap,dozap_size);


        delete [] dozap;
    }


    delete [] texWCharT;

    //шифрование файла по частям
    char *file_data;
    int prsbr_old=-1;
    while (!file.atEnd())
    {
        int size_file_data;
        if (file.bytesAvailable()>chast_file_byte)
            size_file_data=chast_file_byte;
        else
            size_file_data=file.bytesAvailable();

        file_data = new char[size_file_data];

        QDataStream potok_is_file2(&file);
        potok_is_file2.readRawData(file_data, size_file_data);


        //преобразуем всю входную информацию в массив бит
        int size_MasDataBit = sizeof(char)*size_byte*size_file_data;
        bool* MasDataBit= new bool [size_MasDataBit];
        ToBit2(file_data, size_file_data, MasDataBit);



        int errn=ui->shivrovanie(MasDataBit, size_MasDataBit);
        if (errn==-1)
        {
            err="Ошибка шифрования!";
            file.close();
            file_save.remove();
            file_save.close();
            emit file_exit(err);
            return;
        }

        ToType2(MasDataBit, file_data, size_file_data);

        delete [] MasDataBit;

        file_save.write(file_data, size_file_data);

        delete [] file_data;


        int prsbr_new=100-(100*file.bytesAvailable())/file.size();
        if (prsbr_new>prsbr_old)
        {
            prsbr_old=prsbr_new;
            emit setProgressBar(prsbr_new, "Шифрование файла...");
        }
        if (exit)
        {
            err="Прервано!";
            file.close();
            file_save.remove();
            file_save.close();
            emit file_exit(err);
            return;
        }
    }


    file.close();
    file_save.close();

    err="Шифрование завершено!";
    emit file_exit(err);
}


void ConvertThread::file_rasshifr(QString cur)
{
    int chast_file_byte=100080;
    QString err="";

    QString file_name=cur;
    file_name.remove(0,file_name.lastIndexOf("/")+1);
    if (file_name.lastIndexOf(".")!=-1)
        file_name.remove(file_name.lastIndexOf("."),
                         file_name.length()-file_name.lastIndexOf(".")+1);



    QFile file(cur);
    cur.remove(cur.lastIndexOf("/")+1,cur.length()-cur.lastIndexOf("/")-1);
    cur+=file_name;
    QFile file_save(cur);
    cur.remove(cur.lastIndexOf("/")+1,cur.length()-cur.lastIndexOf("/")-1);


    if (file.open(QIODevice::ReadOnly))
    {
        if (file.size()%30!=0)
        {
            file.close();
            err="Размер должен быть кратен 30!";
            emit file_exit(err);
            return;
        }
        //первичное копирование итогового файла
        file_save.remove();
        if (!file_save.open(QIODevice::ReadWrite))
        {
            file.close();
            err="Ошибка записи!";
            emit file_exit(err);
            return;
        }
    }
    else
    {
        err="Ошибка чтения!";
        emit file_exit(err);
        return;
    }



    int size_byte=8;
    int predvor_size=30*7;
    if (file.size()<=predvor_size) predvor_size=file.size();

    char *predvor= new char[predvor_size];

    QDataStream potok_is_file(&file);
    potok_is_file.readRawData(predvor, predvor_size);

    int predvor_bit_size=predvor_size*size_byte;
    bool *predvor_bit= new bool[predvor_bit_size];
    ToBit2(predvor, predvor_size, predvor_bit);

    int errn=ui->rasshivrovanie(predvor_bit, predvor_bit_size);
    if (errn==-1)
    {
        err="Ошибка шифрования!";
        file.close();
        file_save.remove();
        file_save.close();
        emit file_exit(err);
        return;
    }

    ToType2(predvor_bit, predvor, predvor_size);
    delete [] predvor_bit;

    file_save.write(predvor,predvor_size);


    delete [] predvor;



    //чтение тех информации и отбрасывание лишнего
    int size_buf=1;
    char *buf = new char [size_buf];

    file_save.seek(0);
    file_save.read(buf, size_buf);


    unsigned char kolvo_normir_bit=(unsigned char)buf[0];
    delete [] buf;


    if (kolvo_normir_bit>232) kolvo_normir_bit=0;

    int kolvo_normir_byte=kolvo_normir_bit/8+1;


    file_save.seek(kolvo_normir_byte);

    //определяем длину формата
    QTextStream potok (&file_save);
    QString file_format_l = potok.read(64*2);
    file_format_l.remove(file_format_l.indexOf(" "),file_format_l.length()-file_format_l.indexOf(" "));

    QString file_format="";
    for (int i=0; i<file_format_l.length(); i++)
        if (file_format_l.at(i).toLatin1()!='\0') file_format+=file_format_l.at(i);

    int size_format=file_format.toInt()*2;

    kolvo_normir_byte+=file_format_l.length()+2;


    if (size_format>predvor_size-kolvo_normir_byte)
    {
        int dop_size=size_format-(predvor_size-kolvo_normir_byte)+
                (30-(size_format-(predvor_size-kolvo_normir_byte))%30);
        char *dop= new char[dop_size];

        QDataStream potok_is_file(&file);
        potok_is_file.readRawData(dop, dop_size);

        int dop_bit_size=dop_size*size_byte;
        bool *dop_bit= new bool[dop_bit_size];
        ToBit2(dop, dop_size, dop_bit);

        int errn=ui->rasshivrovanie(dop_bit, dop_bit_size);
        if (errn==-1)
        {
            err="Ошибка шифрования!";
            file.close();
            file_save.remove();
            file_save.close();
            emit file_exit(err);
            return;
        }

        ToType2(dop_bit, dop, dop_size);
        delete [] dop_bit;

        file_save.write(dop,dop_size);


        delete [] dop;
    }



    //определяем название формата
    file_save.seek(kolvo_normir_byte);
    char *char_buf=new char[size_format];
    file_save.read(char_buf, size_format);

    file_format="";
    QChar wc;
    for (int i=0; i<size_format; i+=2)
    {
        wc.setCell(char_buf[i]);
        wc.setRow(char_buf[i+1]);
        file_format+=wc;
    }
    delete [] char_buf;

    kolvo_normir_byte+=size_format;


    //перезаписываем ненужные данные смещая полезные
    qint64 cx=kolvo_normir_byte;
    QByteArray temp;

    int size_file_data=file_save.bytesAvailable();


    file_save.seek(cx);
    temp=file_save.read(size_file_data);
    file_save.seek(cx-kolvo_normir_byte);
    file_save.write(temp);
    file_save.resize(file_save.size()-kolvo_normir_byte);



    //расшифровка файла по частям
    int prsbr_old=-1;
    while (!file.atEnd())
    {
        int size_file_data;
        if (file.bytesAvailable()>chast_file_byte)
            size_file_data=chast_file_byte;
        else
            size_file_data=file.bytesAvailable();

        char *file_data = new char[size_file_data];

        QDataStream potok_is_file2(&file);
        potok_is_file2.readRawData(file_data, size_file_data);


        //преобразуем всю входную информацию в массив бит
        int size_MasDataBit = sizeof(char)*size_byte*size_file_data;
        bool* MasDataBit= new bool [size_MasDataBit];
        ToBit2(file_data, size_file_data, MasDataBit);



        int errn=ui->rasshivrovanie(MasDataBit, size_MasDataBit);
        if (errn==-1)
        {
            err="Ошибка расшифрования!";
            file.close();
            file_save.remove();
            file_save.close();
            emit file_exit(err);
            return;
        }

        ToType2(MasDataBit, file_data, size_file_data);

        delete [] MasDataBit;

        file_save.write(file_data, size_file_data);

        delete [] file_data;


        int prsbr_new=100-(100*file.bytesAvailable())/file.size();
        if (prsbr_new>prsbr_old)
        {
            prsbr_old=prsbr_new;
            emit setProgressBar(prsbr_new, "Расшифрование файла...");
        }
        if (exit)
        {
            err="Прервано!";
            file.close();
            file_save.remove();
            file_save.close();
            emit file_exit(err);
            return;
        }
    }


    if (file_format!="")
    {
        QFile trash(file_save.fileName()+"."+file_format);
        if (trash.open(QIODevice::WriteOnly)) trash.remove();
        trash.close();

        file_save.rename(file_save.fileName()+"."+file_format);
    }


    file.close();
    file_save.close();


    err="Расшифрование завершено!";
    emit file_exit(err);
}

void ConvertThread::generate()
{
    okno->showNormal();
    emit start_gen();
}

void ConvertThread::hide_wind()
{


    QMutex wait;
    wait.lock();
    wait.tryLock(100);
    wait.unlock();

    okno->hide();
    emit smw();
}
