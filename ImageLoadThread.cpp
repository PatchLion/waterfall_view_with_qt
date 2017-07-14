#include "ImageLoadThread.h"

CImageLoadThread::CImageLoadThread(QObject* object /*= 0*/)
	: QThread(object)
	, m_isSuccessed(false)
{

}

void CImageLoadThread::run()
{
	m_isSuccessed = false;
	if (!m_imagePath.isEmpty())
	{
		QImageReader reader(m_imagePath);

		m_isSuccessed = reader.read(&m_image);
	}
}

