#include "specedit.h"
#include <QClipboard>
#include <QApplication>

EditShifr::EditShifr(QWidget *parent):
    QPlainTextEdit (parent)
{

}

EditShifr::~EditShifr()
{

}
void EditShifr::keyPressEvent(QKeyEvent *e)
{
    QString str=toPlainText();
    if (str.length()>=5040)
    {
        if (e->key()==Qt::Key_Backspace||e->key()==Qt::Key_Delete||
                (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_C)||
                (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_A))
        {
            QPlainTextEdit::keyPressEvent(e);
        }
    }
    else
    {
        if (e->key()==Qt::Key_0||e->key()==Qt::Key_1||e->key()==Qt::Key_Backspace||
                (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_C)||
                e->key()==Qt::Key_Delete||(e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_A))
        {
            QPlainTextEdit::keyPressEvent(e);
        }
        if (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_V)
        {
            QClipboard *clipboard = QApplication::clipboard();
            QString text = clipboard->text();

            for (int i=0; i<text.size();i++)
                if (text.at(i)!='0'&&text.at(i)!='1') return;

            if (text.length()+str.length()>=5040)
            {
                text.chop(text.length()+str.length()-5040);
                clipboard->setText(text);
            }

            QPlainTextEdit::keyPressEvent(e);
        }
    }
}


EditShifr2::EditShifr2(QWidget *parent):
    QPlainTextEdit (parent)
{

}

EditShifr2::~EditShifr2()
{

}
void EditShifr2::keyPressEvent(QKeyEvent *e)
{
    QString str=toPlainText();
    if (str.length()>=24480)
    {
        if (e->key()==Qt::Key_Backspace||e->key()==Qt::Key_Delete||
                (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_C)||
                (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_A))
        {
            QPlainTextEdit::keyPressEvent(e);
        }
    }
    else
    {
        if (e->key()==Qt::Key_0||e->key()==Qt::Key_1||e->key()==Qt::Key_Backspace||
                (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_C)||
                e->key()==Qt::Key_Delete||(e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_A))
        {
            QPlainTextEdit::keyPressEvent(e);
        }
        if (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_V)
        {
            QClipboard *clipboard = QApplication::clipboard();
            QString text = clipboard->text();

            for (int i=0; i<text.size();i++)
                if (text.at(i)!='0'&&text.at(i)!='1') return;

            if (text.length()+str.length()>=24480)
            {
                text.chop(text.length()+str.length()-24480);
                clipboard->setText(text);
            }

            QPlainTextEdit::keyPressEvent(e);
        }
    }
}



EditIsxod::EditIsxod(QWidget *parent):
    QPlainTextEdit (parent)
{
    binary=false;
}

EditIsxod::~EditIsxod()
{

}

void EditIsxod::keyPressEvent(QKeyEvent *e)
{
    QString str=toPlainText();
    if (binary)
    {
        if (str.length()>=24464)
        {
            if (e->key()==Qt::Key_Backspace||e->key()==Qt::Key_Delete||
                    (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_C)||
                    (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_A))
            {
                QPlainTextEdit::keyPressEvent(e);
            }
        }
        else
        {
            if (e->key()==Qt::Key_0||e->key()==Qt::Key_1||e->key()==Qt::Key_Backspace||
                    (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_C)||
                    e->key()==Qt::Key_Delete||(e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_A))
            {
                QPlainTextEdit::keyPressEvent(e);
            }
            if (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_V)
            {
                QClipboard *clipboard = QApplication::clipboard();
                QString text = clipboard->text();

                for (int i=0; i<text.size();i++)
                    if (text.at(i)!='0'&&text.at(i)!='1') return;

                if (text.length()+str.length()>=24464)
                {
                    text.chop(text.length()+str.length()-24464);
                    clipboard->setText(text);
                }

                QPlainTextEdit::keyPressEvent(e);
            }
        }
    }else
    {
        if (str.length()>=1529)
        {
            if (e->key()==Qt::Key_Backspace||e->key()==Qt::Key_Delete||
                    (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_C)||
                    (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_A))
            {
                QPlainTextEdit::keyPressEvent(e);
            }
        }
        else
        {
            if (e->modifiers()==Qt::ControlModifier && e->key()==Qt::Key_V)
            {
                QClipboard *clipboard = QApplication::clipboard();
                QString text = clipboard->text();

                if (text.length()+str.length()>=1529)
                {
                    text.chop(text.length()+str.length()-1529);
                    clipboard->setText(text);
                }
            }

            QPlainTextEdit::keyPressEvent(e);
        }
    }
}
