#ifndef POLINOMM2_H
#define POLINOMM2_H
#include "math.h"

class PolinomM2
{
private:
    int polinom_size;
    bool *polinom;
    bool binar_oper;

public:
    //конструкторы
    PolinomM2();
    ~PolinomM2();

    //функции
    void fromMasBitToPolinomM2(bool *, int );

    //перегруженые операторы
    void operator << (int );
    void operator >> (int );
    void operator = (PolinomM2 & );
    friend PolinomM2& operator + (PolinomM2& ,PolinomM2& );
    friend PolinomM2& operator - (PolinomM2& , PolinomM2& );
    friend bool operator== (PolinomM2& ,PolinomM2& );
    friend PolinomM2& operator% (PolinomM2& ,PolinomM2& );
    friend PolinomM2& operator/ (PolinomM2& ,PolinomM2& );
    friend PolinomM2& operator* (PolinomM2& ,PolinomM2& );
    friend int Evklid (PolinomM2& g, PolinomM2& f,
                                PolinomM2& x, PolinomM2& y);


    //возрат приватных значений
    bool getBinarOper();
    bool getPolinom(int );
    int getPolinomSize();
};

#endif // POLINOMM2_H
