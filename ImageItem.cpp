#include "ImageItem.h"
#include <QFontMetrics>

CImageItem::CImageItem(const QString& path, bool isLocalFile, QWidget* parent /*= 0*/)
	: QDialog(parent)
	, m_isLoading(true)
	, m_scale(1.0)
{
	ImageLib::stReadParam param(path, isLocalFile);
	m_imageLoadThread.setParam(param);
	connect(&m_imageLoadThread, &QThread::finished, this, &CImageItem::onImageLoaded);

	setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint | Qt::FramelessWindowHint);

	//resize(1024, 768);
}


void CImageItem::paintEvent(QPaintEvent *event)
{

	QPainter painter(this);
	if (m_isLoading)
	{
		painter.setPen(Qt::gray);
		painter.setBrush(Qt::gray);
		painter.drawRect(rect());
		painter.setPen(Qt::white);
		painter.setBrush(Qt::white);
		const QString loading = QString::fromLocal8Bit("¼ÓÔØÍ¼Æ¬ÖÐ......");

		QFont f = font();
		f.setPixelSize(50);
		f.setBold(true);
		f.setFamily(QString::fromLocal8Bit("Î¢ÈíÑÅºÚ"));
		painter.setFont(f);
		QFontMetrics fontM(f);
		QRect textR = fontM.boundingRect(loading);

		painter.drawText(rect().center().x() - textR.width() / 2.0, rect().center().y(), loading);
	}
	else
	{
		QImage temp = m_imageLoadThread.image().scaled(size() * m_scale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		painter.drawImage(QRect(rect().center().x() - temp.width() / 2, rect().center().y() - temp.height() / 2, 
			temp.width(), temp.height()), m_imageLoadThread.image());
	}
	
}


void CImageItem::showEvent(QShowEvent *event)
{
	m_isLoading = true;

	m_imageLoadThread.start();
}

void CImageItem::onImageLoaded()
{
	m_isLoading = !(m_imageLoadThread.result().isSuccess && !m_imageLoadThread.image().isNull());
	update();
}

void CImageItem::mousePressEvent(QMouseEvent *event)
{
	close();
}

const int kMinScale = 0.1;
const int kMaxScale = 3.0;
void CImageItem::wheelEvent(QWheelEvent *event)
{
	const int i = event->delta() / 120;

	m_scale = m_scale - i * 0.05;

	if (m_scale < kMinScale)
	{
		m_scale = kMinScale;
	}
	else if (m_scale > kMaxScale)
	{
		m_scale = kMaxScale;
	}

	qDebug() << "scale -->" << m_scale;
	
	update();
}

