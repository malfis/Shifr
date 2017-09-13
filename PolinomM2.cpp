#include "PolinomM2.h"

PolinomM2::PolinomM2()
{
    binar_oper=false;
    //начальные значеия полиномов 0 и порядок 1
    polinom_size=1;
    polinom = new bool[polinom_size];
    polinom[0]=0;
}

PolinomM2::~PolinomM2()
{
    delete [] polinom;
}

//предоставляют доступ к чтению приватных значений массива многочлена
bool PolinomM2::getBinarOper()
{
    return binar_oper;
}
bool PolinomM2::getPolinom(int position)
{
    return polinom[position];
}
int PolinomM2::getPolinomSize()
{
    return polinom_size;
}

//заполняет из блока байт массив 0 и 1 полинома в поле или порождающего,
//если порядок pole_sizeX2=1 и pole[0]=0.
void PolinomM2::fromMasBitToPolinomM2(bool *MasOfBit, int size_MasOfBit)
{
    delete [] polinom;
    //определеяем корректный порядок, убирая нули спереди
    int otstyp_ot_nachala=0;
    while ((MasOfBit[otstyp_ot_nachala]==0)&&
           (otstyp_ot_nachala!=size_MasOfBit-1)) otstyp_ot_nachala++;
    polinom_size=size_MasOfBit-otstyp_ot_nachala;

    polinom= new bool [polinom_size];
    for (int m=0; m<polinom_size; m++)
        polinom[m]=MasOfBit[m+otstyp_ot_nachala];

    return;
}

//f - делимое (неприводимый многочлен)
//g - делитель (исходная информация)
//x - коэф. при g (замена к исходной)
//y - коэф. при f
int Evklid (PolinomM2& g, PolinomM2& f,
                              PolinomM2& x, PolinomM2& y)
{
    int err;
    if (g.polinom_size > f.polinom_size)
    {
        err=-1;
        return err;
    }
    if (g == x) //т.е. g == 0
    {
        //чтобы следующая обертка давала коэффициент 1
        //при остатке, gX+fy=1
        y.polinom[0] = 1;
        err=0;
        return err;
    }
    PolinomM2 x1, y1, buf;
    buf = f%g;
    err=Evklid(buf, g, x1, y1);
    x = f/g;
    x = x*x1;
    x = y1-x;
    y = x1;
    return err;
}

void PolinomM2::operator = (PolinomM2 &right)
{
    //проверка на самоприсваивание
    if (*this == right)
    {
        if (right.getBinarOper()==true) delete &right;
        return;
    }

    delete [] polinom;

    polinom_size=right.getPolinomSize();
    polinom=new bool[polinom_size];

    for (int i=0; i<polinom_size; i++)
    {
        polinom[i]=right.getPolinom(i);
    }



    if (right.getBinarOper()==true) delete &right;
    return;
}

//сдвигает биты в ПолиномеМ2 на sdvig позиций влево
//на место сдвига помещается 0
void PolinomM2::operator << (int sdvig)
{
    if (sdvig>polinom_size) sdvig=polinom_size;

    for (int m=0; m<polinom_size-sdvig; m++)
        polinom[m]=polinom[m+sdvig];
    for (int m=0; m<sdvig; m++)
        polinom[polinom_size-1-m]=0;

    return;
}

//сдвигает биты в ПолиномеМ2 на sdvig позиций вправо
//на место сдвига помещается 0
void PolinomM2::operator >> (int sdvig)
{
    if (sdvig>polinom_size) sdvig=polinom_size;

    for (int m=polinom_size-1; m>=sdvig; m--)
        polinom[m]=polinom[m-sdvig];
    for (int m=0; m<sdvig; m++)
        polinom[m]=0;

    return;
}

PolinomM2& operator + (PolinomM2& left, PolinomM2& right)
{
    PolinomM2 *otvet=new PolinomM2;
    otvet->binar_oper=true;

    //когда оба равны - сложение xor зануляет
    if (right==left)
    {
        if (left.getBinarOper()==true) delete &left;
        if (right.getBinarOper()==true) delete &right;
        return *otvet;
    }

    if (left.getPolinomSize()==right.getPolinomSize())
    {
        *otvet=right;

        //убавлять размер только до 1 встречной 1,
        //т.к. только в случае равенства может
        //уменьшится порядок мн-на при сложении
        bool key=true;
        for (int i=0; i<left.getPolinomSize(); i++)
        {
            otvet->polinom[i]=otvet->getPolinom(i) ^ left.getPolinom(i);

            //нули вначале сокращают порядок мн-на от исходного
            if (key&&otvet->polinom[i]==1) key=false;
            if (key&&otvet->polinom[i]==0) otvet->polinom_size--;
        }

        //нужно отформатировать новое число
        bool *byfer=new bool[otvet->getPolinomSize()];
        for (int i=0; i<otvet->getPolinomSize(); i++)
        {
            byfer[i]=otvet->getPolinom(left.getPolinomSize()
                                       -otvet->getPolinomSize()
                                       +i);
        }

        delete [] otvet->polinom;
        otvet->polinom=byfer;


        if (left.getBinarOper()==true) delete &left;
        if (right.getBinarOper()==true) delete &right;
        return *otvet;
    }

    if (left.getPolinomSize()>right.getPolinomSize())
    {
        *otvet=left;

        for (int i=0; i<right.getPolinomSize(); i++)
        {
            otvet->polinom[i+left.getPolinomSize()-right.getPolinomSize()]
                    =otvet->getPolinom(i+left.getPolinomSize()
                                       -right.getPolinomSize())
                    ^ right.getPolinom(i);
        }
    }
    else
    {
        *otvet=right;

        for (int i=0; i<left.getPolinomSize(); i++)
        {
            otvet->polinom[i+right.getPolinomSize()-left.getPolinomSize()]
                    =otvet->getPolinom(i+right.getPolinomSize()
                                       -left.getPolinomSize())
                    ^ left.getPolinom(i);
        }
    }


    if (left.getBinarOper()==true) delete &left;
    if (right.getBinarOper()==true) delete &right;
    return *otvet;
}
PolinomM2& operator - (PolinomM2& left, PolinomM2& right)
{
    PolinomM2 *otvet=new PolinomM2;
    otvet->binar_oper=true;

    //когда оба равны - сложение xor зануляет
    if (right==left)
    {
        if (left.getBinarOper()==true) delete &left;
        if (right.getBinarOper()==true) delete &right;
        return *otvet;
    }

    if (left.getPolinomSize()==right.getPolinomSize())
    {
        *otvet=right;

        //убавлять размер только до 1 встречной 1,
        //т.к. только в случае равенства может
        //уменьшится порядок мн-на при сложении
        bool key=true;
        for (int i=0; i<left.getPolinomSize(); i++)
        {
            otvet->polinom[i]=otvet->getPolinom(i) ^ left.getPolinom(i);

            //нули вначале сокращают порядок мн-на от исходного
            if (key&&otvet->polinom[i]==1) key=false;
            if (key&&otvet->polinom[i]==0) otvet->polinom_size--;
        }

        //в любой случае порядок уменьшится и
        //нужно отформатировать новое число
        bool *byfer=new bool[otvet->getPolinomSize()];
        for (int i=0; i<otvet->getPolinomSize(); i++)
        {
            byfer[i]=otvet->getPolinom(left.getPolinomSize()
                                       -otvet->getPolinomSize()
                                       +i);
        }

        delete [] otvet->polinom;
        otvet->polinom=byfer;


        if (left.getBinarOper()==true) delete &left;
        if (right.getBinarOper()==true) delete &right;
        return *otvet;
    }

    if (left.getPolinomSize()>right.getPolinomSize())
    {
        *otvet=left;

        for (int i=0; i<right.getPolinomSize(); i++)
        {
            otvet->polinom[i+left.getPolinomSize()-right.getPolinomSize()]
                    =otvet->getPolinom(i+left.getPolinomSize()
                                       -right.getPolinomSize())
                    ^ right.getPolinom(i);
        }
    }
    else
    {
        *otvet=right;

        for (int i=0; i<left.getPolinomSize(); i++)
        {
            otvet->polinom[i+right.getPolinomSize()-left.getPolinomSize()]
                    =otvet->getPolinom(i+right.getPolinomSize()
                                       -left.getPolinomSize())
                    ^ left.getPolinom(i);
        }
    }

    if (left.getBinarOper()==true) delete &left;
    if (right.getBinarOper()==true) delete &right;
    return *otvet;
}


//сравнивает по порядку и элементам в массиве
bool operator== (PolinomM2& left, PolinomM2& right)
{
    bool ravenstvo=true;
    if (left.getPolinomSize()!=right.getPolinomSize())
        return !ravenstvo;
    else
        for (int i=0;i<left.getPolinomSize();i++)
            if (left.getPolinom(i)!=right.getPolinom(i))
                return !ravenstvo;

    return ravenstvo;
}

PolinomM2& operator/ (PolinomM2& delimoe,PolinomM2& delitel)
{
    PolinomM2 *otvet=new PolinomM2;
    otvet->binar_oper=true;

    if (delimoe.getPolinomSize()<delitel.getPolinomSize())
    {
        if (delitel.getBinarOper()==true) delete &delitel;
        if (delimoe.getBinarOper()==true) delete &delimoe;
        return *otvet;
    }
    if (delitel==*otvet)
    {
        if (delitel.getBinarOper()==true) delete &delitel;
        if (delimoe.getBinarOper()==true) delete &delimoe;
        return *otvet;
    }


    *otvet=delimoe;
    int razmer_tselogo=delimoe.getPolinomSize()-delitel.getPolinomSize()+1;
    bool *tseloe=new bool[razmer_tselogo];

    for (int i=0; i<razmer_tselogo;i++)
    {
        if (otvet->getPolinom(i)==1)
        {
            //условие только для нахождения целой части
            //т.к. в этом случае последнее сложение можно не выполнять
            if (i!=razmer_tselogo-1)
            {
                for (int j=i;j<delitel.getPolinomSize()+i;j++)
                    otvet->polinom[j]=otvet->getPolinom(j)
                            ^delitel.getPolinom(j-i);
            }
            //постепенно формируем массив с целым числом
            tseloe[i]=1;
        }
        else
        {
            //постепенно формируем массив с целым числом
            tseloe[i]=0;
        }
    }

    otvet->polinom_size=razmer_tselogo;
    delete [] otvet->polinom;
    otvet->polinom=tseloe;

    if (delitel.getBinarOper()==true) delete &delitel;
    if (delimoe.getBinarOper()==true) delete &delimoe;
    return *otvet;
}

PolinomM2& operator% (PolinomM2& delimoe,PolinomM2& delitel)
{
    if (delimoe.getPolinomSize()<delitel.getPolinomSize())
    {
        if (delitel.getBinarOper()==true) delete &delitel;
        return delimoe;
    }

    PolinomM2 *otvet=new PolinomM2;
    otvet->binar_oper=true;

    if (delitel==*otvet||
            (delitel.getPolinomSize()==1&&
            delitel.getPolinom(0)==1)||delimoe==delitel)
    {
        if (delitel.getBinarOper()==true) delete &delitel;
        if (delimoe.getBinarOper()==true) delete &delimoe;
        return *otvet;
    }


    *otvet=delimoe;

    int razmer_tselogo=delimoe.getPolinomSize()-delitel.getPolinomSize()+1;
    for (int i=0; i<razmer_tselogo;i++)
    {
        if (otvet->getPolinom(i)==1)
            for (int j=i;j<delitel.getPolinomSize()+i;j++)
                otvet->polinom[j]=otvet->getPolinom(j)
                        ^delitel.getPolinom(j-i);
    }


    //определяем порядок остатка
    int lishnee=0;
    for (int i=0; i<delimoe.getPolinomSize(); i++)
    {
        if (otvet->getPolinom(i)==1)
        {
            otvet->polinom_size=
                    otvet->getPolinomSize()-lishnee;
            i=delimoe.getPolinomSize();
        }
        lishnee++;
    }

    //нужно отформатировать новое число
    bool *byfer=new bool[otvet->getPolinomSize()];
    for (int i=0; i<otvet->getPolinomSize(); i++)
    {
        byfer[i]=otvet->getPolinom(delimoe.getPolinomSize()
                                   -otvet->getPolinomSize()
                                   +i);
    }

    delete [] otvet->polinom;
    otvet->polinom=byfer;

    if (delitel.getBinarOper()==true) delete &delitel;
    if (delimoe.getBinarOper()==true) delete &delimoe;
    return *otvet;
}

PolinomM2& operator* (PolinomM2& left,PolinomM2& right)
{
    PolinomM2 *otvet=new PolinomM2;
    otvet->binar_oper=true;


    if(*otvet==left||*otvet==right)
    {
        if (left.getBinarOper()==true) delete &left;
        if (right.getBinarOper()==true) delete &right;
        return *otvet;
    }


    bool *proizvedenie= new bool[left.getPolinomSize()
                                    +right.getPolinomSize()-1];

    //т.к. при домножении на 0 просто сдвигаем,
    //необходимо заполнить массив 0 (защита от мусора)
    for (int i=0;i<left.getPolinomSize()
         +right.getPolinomSize()-1;i++)
    {
        proizvedenie[i]=0;
    }
    if (left.getPolinomSize()>=right.getPolinomSize())
    {
        for (int i=0;i<right.getPolinomSize();i++)
            if (right.getPolinom(i)==1)
                for (int j=0;j<left.getPolinomSize();j++)
                    proizvedenie[j+i]=proizvedenie[j+i]^left.getPolinom(j);
    }
    else
    {
        for (int i=0;i<left.getPolinomSize();i++)
            if (left.getPolinom(i)==1)
                for (int j=0;j<right.getPolinomSize();j++)
                    proizvedenie[j+i]=proizvedenie[j+i]^right.getPolinom(j);
    }

    delete [] otvet->polinom;
    otvet->polinom_size=left.getPolinomSize()
            +right.getPolinomSize()-1;
    otvet->polinom=proizvedenie;


    if (left.getBinarOper()==true) delete &left;
    if (right.getBinarOper()==true) delete &right;
    return *otvet;
}
