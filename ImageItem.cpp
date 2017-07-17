#include "ImageItem.h"
#include <QFontMetrics>

CImageItem::CImageItem(const QUrl& url, QWidget* parent /*= 0*/)
	: QDialog(parent)
	, m_isLoading(true)
{
	ImageLib::stReadParam param(url);
	m_imageLoadThread.setParam(param);
	connect(&m_imageLoadThread, &QThread::finished, this, &CImageItem::onImageLoaded);

	setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);

	resize(800, 600);
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
		const QString loading = QString::fromLocal8Bit("º”‘ÿÕº∆¨÷–......");

		QFont f = font();
		f.setPixelSize(50);
		f.setBold(true);
		f.setFamily(QString::fromLocal8Bit("Œ¢»Ì—≈∫⁄"));
		painter.setFont(f);
		QFontMetrics fontM(f);
		QRect textR = fontM.boundingRect(loading);

		painter.drawText(rect().center().x() - textR.width() / 2.0, rect().center().y(), loading);
	}
	else
	{
		QImage temp = m_imageLoadThread.image().scaled(size(), Qt::KeepAspectRatio);
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

