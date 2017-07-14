#include "ImageLoadThreadManager.h"

CImageLoadThreadManager::CImageLoadThreadManager(QObject* object /*= 0*/)
	: QThread(object)
	, m_quit(false)
{

}

void CImageLoadThreadManager::run()
{
	while (!m_quit)
	{
		if (!m_listImagePath.isEmpty())
		{
			const QString path = m_listImagePath.takeFirst();

			if (!path.isEmpty())
			{
				qDebug() << "Start to load: " << path;
				QImageReader reader(path);
				QImage image;
				if (reader.read(&image))
				{
					const int kLimitSize = 500;
					if (image.width() > kLimitSize || image.height() > kLimitSize)
					{
						image = image.scaled(kLimitSize, kLimitSize, Qt::KeepAspectRatio);
					}
					Q_EMIT imageLoadFinished(QPixmap::fromImage(image), path);
				}
			}
		}

		msleep(10);
	}
}

void CImageLoadThreadManager::quit()
{
	m_quit = true;
	QThread::quit();
}

