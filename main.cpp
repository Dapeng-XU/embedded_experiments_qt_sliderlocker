#include "w.h"
#include <qapplication.h>
int main(int argc,char **argv)
{
	QApplication a(argc,argv);
	Form1 form;
	form.setCaption("Form");
	//a.setMainWidget(&win);
	form.show();
	return a.exec();
}