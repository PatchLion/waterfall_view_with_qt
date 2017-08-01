#ifndef ImageReadThread_h__
#define ImageReadThread_h__

#include <QtCore>
#include <QtGui>
#include "ImageStructs.h"


namespace ImageLib
{
	class CImageReader;
	class CImageReadThread : public QThread
	{
		Q_OBJECT
	public:
		CImageReadThread(QObject *parent = 0);
		CImageReadThread(const ImageLib::stReadParam& param, QObject *parent = 0);
		~CImageReadThread();

	public:
		//图片
		QImage image() const { return m_image; }

		//加载图片
		void setParam(const ImageLib::stReadParam& param) { m_param = param; }

		//加载结果
		const ImageLib::stReadResult& result() const { return m_result; }

		//id
		QString id() const { return m_id; }

	protected:
		void run(); 

	private:
		const QString m_id;
		QImage m_image;
		CImageReader* m_reader;
		ImageLib::stReadParam m_param;
		ImageLib::stReadResult m_result;
	};
}
#endif // ImageReadThread_h__
