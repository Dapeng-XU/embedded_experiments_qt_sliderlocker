/****************************************************************************
** Form interface generated from reading ui file 'w.ui'
**
** Created: Sun May 21 05:38:43 2017
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FORM1_H
#define FORM1_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QFrame;
class QLCDNumber;
class QLabel;
class QPushButton;
class QSlider;

class Form1 : public QWidget
{ 
    Q_OBJECT

public:
    Form1( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Form1();

    QFrame* Frame3;
    QSlider* Slider1;
    QLCDNumber* LCDNumber1;
    QPushButton* PushButton1;
    QLabel* TextLabel1;
    QLabel* TextLabel2;

    void textUnlock(int value);
    void textLock();
	
private slots:
    void on_Slider1_sliderMoved(int position);
    void on_PushButton1_clicked();
    void on_Slider1_sliderReleased();
	
private:
    bool isLocked;
};

#endif // FORM1_H
