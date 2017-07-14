#include <QtWidgets>
#include "WaterFallScrollArea.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	CWaterFallScrollArea widget;
	widget.show();

	return app.exec();
}
