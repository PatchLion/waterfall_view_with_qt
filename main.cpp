#include <QtWidgets>
#include "WaterFallScrollArea.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	CWaterFallScrollArea widget;
	widget.resize(800, 600);
	widget.show();

	return app.exec();
}
