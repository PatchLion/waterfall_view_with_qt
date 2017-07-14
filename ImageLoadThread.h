#ifndef ImageLoadThread_h__
#define ImageLoadThread_h__

#include <QtCore>
#include <QtGui>

class CImageLoadThread : public QThread
{
public:
	CImageLoadThread(QObject* object = 0);

public:
	void setImagePath(const QString& path) { m_imagePath = path; }
	QImage image() const { return m_image; }
	bool isSuccessed() const { return m_isSuccessed; }

protected:
	void run();

private:
	bool m_isSuccessed;
	QString m_imagePath;
	QImage m_image;
};

#endif // ImageLoadThread_h__
