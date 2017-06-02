/****************************************************************************
** Form implementation generated from reading ui file 'w.ui'
**
** Created: Sun May 21 05:38:43 2017
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "w.h"

#include <qframe.h>
#include <qlabel.h>
#include <qlcdnumber.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include <sys/ioctl.h>
#include <fcntl.h>

int fd = 0;
unsigned char LEDCODE[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int LEDWORD;

/* 
 *  Constructs a Form1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
Form1::Form1( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "Form1" );
    resize( 262, 479 ); 
    setCaption( tr( "Slide to Unlock" ) );

    Frame3 = new QFrame( this, "Frame3" );
    Frame3->setGeometry( QRect( 10, 0, 231, 120 ) ); 
    Frame3->setFrameShape( QFrame::StyledPanel );
    Frame3->setFrameShadow( QFrame::Raised );

    Slider1 = new QSlider( Frame3, "Slider1" );
    Slider1->setGeometry( QRect( 10, 50, 211, 24 ) ); 
    Slider1->setOrientation( QSlider::Horizontal );

    LCDNumber1 = new QLCDNumber( Frame3, "LCDNumber1" );
    LCDNumber1->setGeometry( QRect( 140, 10, 81, 31 ) ); 

    PushButton1 = new QPushButton( Frame3, "PushButton1" );
    PushButton1->setGeometry( QRect( 130, 80, 91, 31 ) ); 
    PushButton1->setText( tr( "Lock" ) );

    TextLabel1 = new QLabel( Frame3, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 10, 130, 30 ) ); 
    TextLabel1->setText( tr( "Slide to Unlock [pos = 0]" ) );

    TextLabel2 = new QLabel( Frame3, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 10, 80, 121, 30 ) ); 
    TextLabel2->setText( tr( "State: LOCKED" ) );
	
	isLocked = true;
	
	connect(PushButton1, SIGNAL( clicked() ), this, SLOT( on_PushButton1_clicked() ));
	connect(Slider1, SIGNAL( valueChanged(int) ), this, SLOT( on_Slider1_sliderMoved(int) ));
	connect(Slider1, SIGNAL( sliderReleased() ), this, SLOT( on_Slider1_sliderReleased() ));

	fd = open("/dev/led/0raw",O_RDWR);
}

/*  
 *  Destroys the object and frees any allocated resources
 */
Form1::~Form1()
{
    // no need to delete child widgets, Qt does it all for us
}

void Form1::textLock() {
    TextLabel2->setText("State: LOCKED");
    Slider1->setEnabled(true);
    Slider1->setValue(0);
    PushButton1->setEnabled(false);
    isLocked = true;
}

void Form1::textUnlock(int value) {
    if (value > 90) {
        TextLabel2->setText("State: UNLOCKED");
        PushButton1->setEnabled(true);
        isLocked = false;
    }
}

void Form1::on_PushButton1_clicked()
{
    textLock();
}

void Form1::on_Slider1_sliderMoved(int position)
{
	LCDNumber1->display(position);
	int a = position / 10;
	int b = position % 10;

	LEDWORD=(LEDCODE[a]<<8)|LEDCODE[b];
	ioctl(fd,0x12,LEDWORD);

    TextLabel1->setText(tr("Slide to Unlock [pos = %1]").arg(position));
    textUnlock(position);
}

void Form1::on_Slider1_sliderReleased()
{
    if (!isLocked) {
        Slider1->setValue(99);
        Slider1->setEnabled(false);
    } else {
        Slider1->setValue(0);
    }
}