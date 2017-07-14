#include "ImageSaveThread.h"

CImageSaveThread::CImageSaveThread(QObject* object /*= 0*/)
	: QThread(object)
	, m_isSuccessed(false)
{

}

void CImageSaveThread::run()
{
	m_isSuccessed = false;
	if (!m_imagePath.isEmpty() && m_image)
	{
		QImageWriter writer(m_imagePath);

		m_isSuccessed = writer.write(*m_image);
	}
}

