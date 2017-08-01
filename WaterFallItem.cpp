#include "WaterFallItem.h"
#include "ImageItem.h"
#include "ImageReadThread.h"
#include "ImageWriteThread.h"

CWaterFallItem::CWaterFallItem(const QPixmap& thumb, const QUrl& path, QWidget* parent /*= 0*/)
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
	QFileInfo fileInfo(path.toString());
	setToolTip(QString::fromLocal8Bit("Â·¾¶: %1\nÃû³Æ: %2").arg(fileInfo.absolutePath()).arg(fileInfo.fileName()));

	setMouseTracking(true);
}

void CWaterFallItem::setThumb(const QPixmap& thumb, const QUrl& url)
{
	m_imageUrl = url;
	m_thumb = thumb;
	m_size = m_thumb.size();
	update();
}

void CWaterFallItem::paintEvent(QPaintEvent *event)
{
	if (m_isDumped)
	{
		QEventLoop loop;
		/*CImageLoadThread loadThread;
		loadThread.setImagePath(m_dumpedPath);
		connect(&loadThread, &CImageLoadThread::finished, &loop, &QEventLoop::quit);
		loadThread.start();
		loop.exec();
		Q_ASSERT(loadThread.isSuccessed());
		m_thumb = QPixmap::fromImage(loadThread.image());*/
		m_thumb.load(m_dumpedPath);
		qDebug() << "Reload image --> " << m_dumpedPath << m_thumb.width() << " " << m_thumb.height();
		m_isDumped = false;
		removeDumpFile();
	}
	if (!m_thumb.isNull())
	{
		QPainter painter(this);
		QRect r = m_isHovering ? rect() : rect().adjusted(3, 3, -3, -3);
		painter.drawPixmap(r, m_thumb);

		QColor color(0, 0, 0, 130);
		painter.setPen(color);
		painter.setBrush(color);

		const int kHeight = 36;

		QRect bgRect(0, height() - kHeight, width(), kHeight);
		painter.drawRect(bgRect);

		painter.setPen(Qt::white);
		painter.setBrush(Qt::white);

		QFont f = font();
		f.setPixelSize(14);
		f.setFamily(QString::fromLocal8Bit("Î¢ÈíÑÅºÚ"));
		painter.setFont(f);
		QFontMetrics fontM(f);

		if (!m_imageUrl.isEmpty())
		{
			QStringList temp = m_imageUrl.toString().split('/');
			QString text = temp[temp.size() - 2];
			const int kLimitSize = 12;
			if (text.size() > kLimitSize)
			{
				text = text.mid(0, kLimitSize) + "...";
			}
			QRect textRect = fontM.boundingRect(text);

			painter.drawText(bgRect.center().x() - textRect.width() / 2.0, bgRect.center().y() + textRect.height() / 3.0, text);
		}
		
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
	CImageItem imageItem(m_imageUrl.toString(), m_imageUrl.isLocalFile(), this);
	imageItem.showMaximized();
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
		ImageLib::stWriteParam param(m_dumpedPath);
		ImageLib::CImageWriteThread saveThread(param);
		connect(&saveThread, &ImageLib::CImageWriteThread::finished, &loop, &QEventLoop::quit);
		QImage tempImage = m_thumb.toImage();
		saveThread.setImage(tempImage);
		saveThread.start();
		loop.exec();
		Q_ASSERT(saveThread.result().isSuccess);
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
