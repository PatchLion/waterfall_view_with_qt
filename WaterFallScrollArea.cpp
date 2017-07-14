#include "WaterFallScrollArea.h"
#include "WaterFallWidget.h"
#include "ImageSreachThread.h"

CWaterFallScrollArea::CWaterFallScrollArea(QWidget* parant /*= 0*/)
	: QScrollArea(parant)
	, m_content(0)
{
	m_content = new CWaterFallWidget;
	m_content->setFixedHeight(30);
	setWidget(m_content);

	connect(verticalScrollBar(), &QScrollBar::rangeChanged, this, &CWaterFallScrollArea::onVerticalBarRangeChanged);
	connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &CWaterFallScrollArea::onVerticalBarValueChanged);

	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setAcceptDrops(true);
}

void CWaterFallScrollArea::resizeEvent(QResizeEvent *event)
{
	Q_ASSERT(m_content);
	m_content->setFixedWidth(width()-2);
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
					QEventLoop loop;
					CImageSreachThread sreachThread;
					connect(&sreachThread, &CImageSreachThread::finished, &loop, &QEventLoop::quit);
					sreachThread.setRootPath(urls[i].toLocalFile());
					sreachThread.start();
					loop.exec();

					paths.append(sreachThread.fileList());
				}
			}

			setImageList(paths);
		}
	}
	setEnabled(true);
}

void CWaterFallScrollArea::dragEnterEvent(QDragEnterEvent *event)
{
	event->accept();
}

