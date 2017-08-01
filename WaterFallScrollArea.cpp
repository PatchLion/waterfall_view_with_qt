#include "WaterFallScrollArea.h"
#include "WaterFallWidget.h"
#include "ImageSreachThread.h"

CWaterFallScrollArea::CWaterFallScrollArea(QWidget* parant /*= 0*/)
	: QScrollArea(parant)
	, m_content(0)
	, m_sreachThread(0)
{
	m_content = new CWaterFallWidget;
	m_content->setFixedHeight(30);
	setWidget(m_content);

	connect(verticalScrollBar(), &QScrollBar::rangeChanged, this, &CWaterFallScrollArea::onVerticalBarRangeChanged);
	connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &CWaterFallScrollArea::onVerticalBarValueChanged);

	//setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setAcceptDrops(true);
}

void CWaterFallScrollArea::resizeEvent(QResizeEvent *event)
{
	Q_ASSERT(m_content);
	m_content->setFixedWidth(width()-20);
	m_content->setFixedHeight(height() + 100);
}

void CWaterFallScrollArea::onVerticalBarRangeChanged(int min, int max)
{
	qDebug() << QString("range changed: %1 - %2").arg(min).arg(max);
}

void CWaterFallScrollArea::onVerticalBarValueChanged(int value)
{
	qDebug() << QString("value moved: %1").arg(value);
	Q_ASSERT(m_content);
	if (value >= (verticalScrollBar()->maximum() - 5))
	{
		
		m_content->onScrollToBottom(height());
	}
	else if (value <= 5)
	{
		m_content->onScrollToTop(height());
	}
}

void CWaterFallScrollArea::setImageList(const QStringList& listImagePath)
{
	Q_ASSERT(m_content);
	m_content->setImageList(listImagePath);
}

void CWaterFallScrollArea::appendImageList(const QStringList& listImagePath)
{
	Q_ASSERT(m_content);
	m_content->appendImageList(listImagePath);
}

void CWaterFallScrollArea::dropEvent(QDropEvent *event)
{
	setEnabled(false);
	if (event->mimeData()->hasUrls())
	{
		QList<QUrl> urls = event->mimeData()->urls();
		if (!urls.isEmpty())
		{
			QStringList paths;
			for (int i = 0; i < urls.size(); i++	)
			{
				if (urls[i].isLocalFile())
				{
					paths << urls[i].toLocalFile();
				}
			}


			if (!paths.isEmpty())
			{
				if (!m_sreachThread)
				{
					m_sreachThread = new CImageSreachThread(this);
				}

				m_sreachThread->setRootPaths(paths);

				connect(m_sreachThread, &CImageSreachThread::finished, this, &CWaterFallScrollArea::onImageAllLoadFinished);
				connect(m_sreachThread, &CImageSreachThread::readProgress, this, &CWaterFallScrollArea::onImageLoadProgress);

				m_sreachThread->start();
			}
		}
	}
}

void CWaterFallScrollArea::dragEnterEvent(QDragEnterEvent *event)
{
	event->accept();
}

void CWaterFallScrollArea::onImageAllLoadFinished()
{
	setEnabled(true);
}

void CWaterFallScrollArea::onImageLoadProgress(const QStringList& listFile)
{
	setEnabled(true);
	appendImageList(listFile);
}

