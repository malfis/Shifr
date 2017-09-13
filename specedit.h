#ifndef SPECEDIT_H
#define SPECEDIT_H

#include <QPlainTextEdit>

class EditShifr : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit EditShifr(QWidget *parent = 0);
    ~EditShifr();


private:
    void keyPressEvent(QKeyEvent* );


};


class EditShifr2 : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit EditShifr2(QWidget *parent = 0);
    ~EditShifr2();


private:
    void keyPressEvent(QKeyEvent* );


};



class EditIsxod : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit EditIsxod(QWidget *parent = 0);
    ~EditIsxod();

    bool binary;

private:

        void keyPressEvent(QKeyEvent* );


};

#endif // SPECEDIT_H
