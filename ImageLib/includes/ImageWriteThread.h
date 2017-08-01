#ifndef ImageWriteThread_h__
#define ImageWriteThread_h__

#include <QtCore>
#include <QtGui>
#include "ImageStructs.h"


namespace ImageLib
{
	class CImageWriter;
	class CImageWriteThread : public QThread
	{
		Q_OBJECT
	public:
		CImageWriteThread(QObject *parent = 0);
		CImageWriteThread(const ImageLib::stWriteParam& param, QObject *parent = 0);
		~CImageWriteThread();

	public:
		//����ͼƬ
		void setImage(const QImage& image) { m_image = image; }

		//����ͼƬ
		void setParam(const ImageLib::stWriteParam& param) { m_param = param; }

		//���ؽ��
		const ImageLib::stWriteResult& result() const { return m_result; }

		//id
		QString id() const { return m_id; }

	protected:
		void run();

	private:
		const QString m_id;
		QImage m_image;
		CImageWriter* m_writer;
		ImageLib::stWriteParam m_param;
		ImageLib::stWriteResult m_result;
	};
}

#endif // ImageWriteThread_h__
