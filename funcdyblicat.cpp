#include <QTime>

template <typename Type>
void ToBit2(Type* MasType, int size_MasType, bool *MasBit)
{
    int size_byte=8;
    int type_size=sizeof(Type)*size_byte;
    int sm=0;
    for (int i=0; i<size_MasType; i++)
    {
        for (int k=0; k<type_size; k++)
            MasBit[sm+k]=(MasType[i]&(int)pow(2,(type_size-1)-k))>>((type_size-1)-k);
        sm+=type_size;
    }
}

template <typename Type>
void ToType2(bool* MasBit, Type* MasType, int size_MasType)
{
    int size_byte=8;
    int type_size=sizeof(Type)*size_byte;
    int sm=0;
    for (int i=0; i<size_MasType; i++)
    {
        Type sborka=0;
        for (int k=0; k<type_size; k++)
            sborka=sborka|(MasBit[sm+k]<<((type_size-1)-k));
        MasType[i]=sborka;
        sm+=type_size;
    }
}


void SetNormirMas2(bool *MasNormirBit, int size_MasNormirBit,
                  bool* MasTextBit, unsigned char kolvo_normir_bit)
{
    const int size_byte=8;

    for (int i=0; i<size_MasNormirBit; i++)
    {
        MasNormirBit[i]=0;
    }

    //Заполнение нормированного массива
    //добавление числа лишних случайных битов
    int size_buf=1;
    unsigned char *buf = new unsigned char [size_buf];

    if (kolvo_normir_bit==0)
    {
        QTime midnight(0,0,0);
        qsrand(midnight.msecsTo(QTime::currentTime()));
        buf[0]=qrand()%24;
        if (buf[0] !=23) buf[0]=255-buf[0];
        else buf[0]=0;
    }
    else buf[0]=kolvo_normir_bit;
    int size_MasChislaNormirBit = size_buf*size_byte;
    bool *MasChislaNormirBit= new bool [size_MasChislaNormirBit];
    ToBit2(buf, size_buf, MasChislaNormirBit);
    for (int i=0; i<size_buf*size_byte; i++)
    {
        MasNormirBit[i]=MasChislaNormirBit[i];
    }
    delete [] buf;
    delete [] MasChislaNormirBit;

    //заполнение случайными числами нормировочных бит
    QTime midnight(0,0,0);
    qsrand(midnight.msecsTo(QTime::currentTime()));
    for (int i=size_buf*size_byte; i<size_buf*size_byte+kolvo_normir_bit; i++)
    {
        MasNormirBit[i]=qrand()%2;
    }

    //добавление полезных данных
    for (int i=kolvo_normir_bit+size_buf*size_byte;
         i<size_MasNormirBit; i++)
    {
        MasNormirBit[i]=MasTextBit[i-(kolvo_normir_bit+8)];
    }
}

