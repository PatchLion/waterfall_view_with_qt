#include "WaterFallItem.h"
#include "ImageItem.h"
#include "ImageSaveThread.h"
#include "ImageLoadThread.h"

CWaterFallItem::CWaterFallItem(const QPixmap& thumb, const QString& path, QWidget* parent /*= 0*/)
	: QWidget(parent)
	, m_isHovering(false)
	, m_isDumped(false)
{
	setThumb(thumb, path);

	setCursor(Qt::PointingHandCursor);
/*
	const QStringList listName = path.split("/");
	if (listName.size() >= 2)
	{
		setToolTip(listName[listName.size() - 2]);
	}*/
	QFileInfo fileInfo(path);
	setToolTip(QString::fromLocal8Bit("Â·¾¶: %1\nÃû³Æ: %2").arg(fileInfo.absolutePath()).arg(fileInfo.fileName()));

	setMouseTracking(true);
}

void CWaterFallItem::setThumb(const QPixmap& thumb, const QString& path)
{
	m_originImagePath = path;
	m_thumb = thumb;
	m_size = m_thumb.size();
	update();
}

void CWaterFallItem::paintEvent(QPaintEvent *event)
{
	if (m_isDumped)
	{
		QEventLoop loop;
		CImageLoadThread loadThread;
		loadThread.setImagePath(m_dumpedPath);
		connect(&loadThread, &CImageLoadThread::finished, &loop, &QEventLoop::quit);
		loop.exec();
		Q_ASSERT(loadThread.isSuccessed());
		m_thumb = QPixmap::fromImage(loadThread.image());
		qDebug() << "Reload image --> " << m_dumpedPath << m_thumb.width() << " " << m_thumb.height();
		m_isDumped = false;
		removeDumpFile();
	}
	if (!m_thumb.isNull())
	{
		QPainter painter(this);
		QRect r = m_isHovering ? rect() : rect().adjusted(3, 3, -3, -3);
		painter.drawPixmap(r, m_thumb);
	}
}

void CWaterFallItem::enterEvent(QEvent *event)
{
	m_isHovering = true;
	update();
}

void CWaterFallItem::leaveEvent(QEvent *event)
{
	m_isHovering = false;
	update();
}

void CWaterFallItem::mousePressEvent(QMouseEvent *event)
{
	CImageItem imageItem(m_originImagePath);
	imageItem.exec();
}

void CWaterFallItem::dump()
{
	if (!m_isDumped)
	{
		const QString dir = QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0];
		if (!QDir().exists(dir))
		{
			QDir().mkpath(dir);
		}
		m_dumpedPath = dir + "/" + QUuid::createUuid().toString() + ".jpg";

		QEventLoop loop;
		CImageSaveThread saveThread;
		connect(&saveThread, &CImageSaveThread::finished, &loop, &QEventLoop::quit);
		saveThread.setImagePath(m_dumpedPath, &m_thumb.toImage());
		loop.exec();
		Q_ASSERT(saveThread.isSuccessed());
		m_thumb = QPixmap();
		m_isDumped = true;
		qDebug() << "Dump item ---> " << m_dumpedPath;
	}
	
}

CWaterFallItem::~CWaterFallItem()
{
	removeDumpFile();
}

void CWaterFallItem::removeDumpFile()
{
	if (!m_dumpedPath.isEmpty())
	{
		if (!QFile::remove(m_dumpedPath))
		{
			qDebug() << "Failed to remove dump file! " << m_dumpedPath;
		}
		m_dumpedPath.clear();
	}
}
