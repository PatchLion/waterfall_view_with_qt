#ifndef ImageSaveThread_h__
#define ImageSaveThread_h__

#include <QtCore>
#include <QtGui>

class CImageSaveThread : public QThread
{
public:
	CImageSaveThread(QObject* object = 0);

public:
	void setImagePath(const QString& path, QImage* image) { m_imagePath = path; m_image = image; }
	bool isSuccessed() const { return m_isSuccessed; }

protected:
	void run();

private:
	bool m_isSuccessed;
	QString m_imagePath;
	QImage* m_image;
};

#endif // ImageSaveThread_h__
