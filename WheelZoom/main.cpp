#include "wheelzoom.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	WheelZoom w;
	w.show();
	return a.exec();
}
