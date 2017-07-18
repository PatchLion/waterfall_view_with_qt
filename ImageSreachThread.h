#ifndef ImageSreachThread_h__
#define ImageSreachThread_h__

#include <QtCore>
#include <QtGui>

class CImageSreachThread : public QThread
{
	Q_OBJECT
public:
	CImageSreachThread(QObject* object = 0);

public:
	void setRootPaths(const QStringList& paths) { m_rootPaths = paths; }
	QStringList fileList() const { return m_fileList; }
	bool isSuccessed() const { return m_isSuccessed; }
	void setFileSuffixes(const QStringList& suffixes) { m_fileSuffixes = suffixes; }

protected:
	void run();
	void imageFilePaths(const QString& root, QStringList& paths);

Q_SIGNALS:
	//¶ÁÈ¡¹ý³Ì
	void readProgress(const QStringList& listFile);


private:
	bool m_isSuccessed;
	QStringList m_rootPaths;
	QStringList m_fileList;
	QStringList m_fileSuffixes;
};

#endif // ImageSreachThread_h__
