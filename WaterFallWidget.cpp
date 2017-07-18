#include "WaterFallWidget.h"
#include "WaterFallItem.h"

#define kLeftSpacing 5
#define kRightSpacing 5
#define kBottomSpacing 5
#define kTopSpacing 5
#define kVSpacing 4
#define kHSpacing 7

CWaterFallWidget::CWaterFallWidget(QWidget* parent /*= 0*/)
	: QWidget(parent)
{
	connect(&m_loadThread, &ImageLib::CImageReadQueue::loadFinished, this, &CWaterFallWidget::onImageLoaded, Qt::QueuedConnection);

	resetHeights();
}

void CWaterFallWidget::paintEvent(QPaintEvent *event)
{
	/*QPainter painter(this);
	painter.setPen(Qt::red);
	painter.setBrush(Qt::lightGray);

	painter.drawRect(rect().adjusted(0, 0, -1, -1));*/
}

void CWaterFallWidget::onScrollToBottom(int scrollareaHeight)
{
	qDebug() << "scroll to bottom......";

	if (m_loadThread.isAllTaskFinished())
	{
		pushImagePathToLoad();


		tryToDumpTopItem(scrollareaHeight * 2.5);

	}
	
	update();
}

QSize CWaterFallWidget::fixedSizeWithWidth(const QSize& imageSize, int width)
{
	if (imageSize.width() <= 0 || imageSize.height() <= 0 || width <= 0)
	{
		return QSize(0, 0);
	}

	return QSize(width, (double)width * (double)imageSize.height() / (double)imageSize.width());
}

void CWaterFallWidget::appendImageList(const QStringList& listImagePath)
{
	m_listImagePath << listImagePath;

	if (m_loadThread.isAllTaskFinished())
	{
		pushImagePathToLoad(15);
	}
}

void CWaterFallWidget::setImageList(const QStringList& listImagePath)
{
	releaseItems();
	//m_loadThread.stopAndClear();
	//m_loadThread.start();
	QThread::msleep(200);
	refreshItems();
	update();
	m_listImagePath = listImagePath;
	pushImagePathToLoad(15);
}


void CWaterFallWidget::releaseItems()
{
	for (int i = 0; i < kColumnSize; i++)
	{
		Q_FOREACH(CWaterFallItem* item, m_listItemsWithColumn[i])
		{
			delete item;
			item = 0;
		}

		m_listItemsWithColumn[i].clear();
	}
}

void CWaterFallWidget::onImageLoaded(const QString& taskID, bool success, const QImage& image, const ImageLib::stReadParam& param)
{
	if (!image.isNull())
	{
		CWaterFallItem* item = new CWaterFallItem(QPixmap::fromImage(image), param.fileUrl, this);

		appendItem(item);
	}

}

void CWaterFallWidget::pushImagePathToLoad(int count)
{
	for (int i = 0; i < count && !m_listImagePath.isEmpty(); i++)
	{
		const QString path = m_listImagePath.takeFirst();

		ImageLib::stReadParam param(path, true, 500);
		m_loadThread.addLoadTask(param);
	}
}

void CWaterFallWidget::refreshItems()
{
	resetHeights();
	const int kUnitWidth = unitWidth();
	int posy[kColumnSize] = { kVSpacing, kVSpacing, kVSpacing, kVSpacing };

	for (int i = 0; i < kColumnSize; i++)
	{
		QList<CWaterFallItem*> listItems = m_listItemsWithColumn[i];

		const int posx = kLeftSpacing + i*(kUnitWidth + kHSpacing);

		for (int x = 0; x < listItems.size(); x++)
		{
			CWaterFallItem* item = listItems[x];
			const QSize size = fixedSizeWithWidth(item->imageSize(), kUnitWidth);

			item->setGeometry(posx, m_heights[i], size.width(), size.height());
			item->setVisible(true);

			m_heights[i] += size.height();
			if (x < (listItems.size()-1))
			{
				m_heights[i] += kVSpacing;
			}
			
		}
	}

	resetWidgetFixedHeight();
}

void CWaterFallWidget::resizeEvent(QResizeEvent *event)
{
	refreshItems();
}

void CWaterFallWidget::appendItem(CWaterFallItem* item)
{
	if (!item || item->thumb().isNull())
	{
		return;
	}

	int index = 0;
	int minHeight = 99999999;
	for (int i = 0; i < kColumnSize; i++)
	{
		if (m_heights[i] < minHeight)
		{
			index = i;
			minHeight = m_heights[i];
		}
	}
	const int kUnitWidth = unitWidth();
	const int posx = kLeftSpacing + index * (kUnitWidth + kHSpacing);
	const QSize size = fixedSizeWithWidth(item->imageSize(), kUnitWidth);
	item->setGeometry(posx, minHeight + kVSpacing, size.width(), size.height());
	item->setVisible(true);

	m_listItemsWithColumn[index].append(item);

	m_heights[index] += kVSpacing;
	m_heights[index] += size.height();

	resetWidgetFixedHeight();
}

void CWaterFallWidget::resetHeights()
{
	for (int i = 0; i < kColumnSize; i++)
	{
		m_heights[i] = kTopSpacing;
	}
}

int CWaterFallWidget::unitWidth() const
{
	return (width() - kLeftSpacing - kRightSpacing - kHSpacing * (kColumnSize - 1)) / kColumnSize;
}

void CWaterFallWidget::resetWidgetFixedHeight()
{
	int maxHeight = 0;
	for (int i = 0; i < kColumnSize; i++)
	{
		if (m_heights[i] > maxHeight)
		{
			maxHeight = m_heights[i];
		}
	}

	setFixedHeight(maxHeight + kBottomSpacing);
}

CWaterFallWidget::~CWaterFallWidget()
{
	
}

void CWaterFallWidget::tryToDumpBottomItem(int size)
{
	if (size > 0)
	{
		for (int i = 0; i < kColumnSize; i++)
		{
			QList<CWaterFallItem*> listItem = m_listItemsWithColumn[i];
			Q_FOREACH(CWaterFallItem* item, listItem)
			{
				QRect itemRect = item->geometry();
				QRect scrollAreaRect(0, 0, width(), size);

				if (!itemRect.intersects(scrollAreaRect))
				{
					item->dump();
				}
			}
		}
	}
}

void CWaterFallWidget::tryToDumpTopItem(int size)
{
	if (size > 0)
	{
		for (int i = 0; i < kColumnSize; i++)
		{
			QList<CWaterFallItem*> listItem = m_listItemsWithColumn[i];
			Q_FOREACH(CWaterFallItem* item, listItem)
			{
				QRect itemRect = item->geometry();
				QRect scrollAreaRect(0, height() - size, width(), size);

				if (!itemRect.intersects(scrollAreaRect))
				{
					item->dump();
				}
			}
		}
	}

}

void CWaterFallWidget::onScrollToTop(int scrollareaHeight)
{
	tryToDumpBottomItem(scrollareaHeight * 2.5);

	update();
}
