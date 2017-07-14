#ifndef ImageLoadThreadManager_h__
#define ImageLoadThreadManager_h__

#include <QtCore>
#include <QtGui>

//Note: ¼ÓÔØµÄÊÇËõÂÔÍ¼
class CImageLoadThreadManager : public QThread
{
	Q_OBJECT
public:
	CImageLoadThreadManager(QObject* object = 0);
	~CImageLoadThreadManager();

public:
	void appendImagePath(const QString& path) { m_listImagePath.append(path); }

	void quit();

	void stopAndClear();

protected:
	void run();

Q_SIGNALS:
	void imageLoadFinished(const QPixmap& image, const QString& originpath);

private:
	QStringList m_listImagePath;
	QList<CImageLoadThreadManager> m_listLoadThread;
	bool m_quit;
};

#endif // ImageLoadThreadManager_h__
