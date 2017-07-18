#include "ImageSreachThread.h"

CImageSreachThread::CImageSreachThread(QObject* object /*= 0*/)
	: QThread(object)
	, m_isSuccessed(false)
{
	m_fileSuffixes << "jpg" << "jpeg" << "jpe" << "png" << "bmp" << "tiff" << "tif";
}

void CImageSreachThread::run()
{
	m_isSuccessed = false;

	Q_FOREACH(QString root, m_rootPaths)
	{
		imageFilePaths(root, m_fileList);
	}

	 m_isSuccessed = true;
	
}



void CImageSreachThread::imageFilePaths(const QString& root, QStringList& paths)
{
	qDebug() << "Search: " << root;

	QDir dir(root);
	QFileInfoList listFileInfo = dir.entryInfoList();

	QStringList listTemp;

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
			if (m_fileSuffixes.contains(fileInfo.suffix().trimmed().toLower()))
			{
				paths.append(fileInfo.absoluteFilePath());
				listTemp << fileInfo.absoluteFilePath();
			}
		}
	}

	if (!listTemp.isEmpty())
	{
		readProgress(listTemp);
	}
}

