#include <QtWidgets>
#include "WaterFallScrollArea.h"

void imageFilePaths(const QString& root, QStringList& paths)
{
	qDebug() << "Search: " << root;

	QDir dir(root);
	QFileInfoList listFileInfo = dir.entryInfoList();

	Q_FOREACH(QFileInfo fileInfo, listFileInfo)
	{

		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
		{
			continue;
		}

		if (fileInfo.isDir())
		{
			imageFilePaths(fileInfo.absoluteFilePath(), paths);
		}
		else
		{
			if (fileInfo.suffix().trimmed().toLower() == "jpg"
				|| fileInfo.suffix().trimmed().toLower() == "jpeg"
				|| fileInfo.suffix().trimmed().toLower() == "jpe"
				|| fileInfo.suffix().trimmed().toLower() == "png"
				|| fileInfo.suffix().trimmed().toLower() == "bmp")
			{
				paths.append(fileInfo.absoluteFilePath());
			}
		}
	}

}

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	CWaterFallScrollArea widget;
	widget.resize(800, 600);
	widget.show();

	QString root = "E://meizitu_images";
	QStringList listImagePath;
	imageFilePaths(root, listImagePath);
	if (!listImagePath.isEmpty())
	{
		widget.setImageList(listImagePath);
	}

	return app.exec();
}
