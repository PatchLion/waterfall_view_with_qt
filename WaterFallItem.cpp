#include "WaterFallItem.h"
#include "ImageItem.h"

CWaterFallItem::CWaterFallItem(const QPixmap& thumb, const QString& path, QWidget* parent /*= 0*/)
	: QWidget(parent)
	, m_isHovering(false)
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
	update();
}

void CWaterFallItem::paintEvent(QPaintEvent *event)
{
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

