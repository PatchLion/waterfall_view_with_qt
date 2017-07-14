#ifndef ImageSreachThread_h__
#define ImageSreachThread_h__

#include <QtCore>
#include <QtGui>

class CImageSreachThread : public QThread
{
public:
	CImageSreachThread(QObject* object = 0);

public:
	void setRootPath(const QString& path) { m_rootPath = path; }
	QStringList fileList() const { return m_fileList; }
	bool isSuccessed() const { return m_isSuccessed; }
	void setFileSuffixes(const QStringList& suffixes) { m_fileSuffixes = suffixes; }
protected:
	void run();
	void imageFilePaths(const QString& root, QStringList& paths);
private:
	bool m_isSuccessed;
	QString m_rootPath;
	QStringList m_fileList;
	QStringList m_fileSuffixes;
};

#endif // ImageSreachThread_h__
