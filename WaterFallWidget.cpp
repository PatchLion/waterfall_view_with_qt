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
	connect(&m_loadThread, &CImageLoadThreadManager::imageLoadFinished, this, &CWaterFallWidget::onImageLoaded, Qt::QueuedConnection);
	m_loadThread.start();

	resetHeights();
}

void CWaterFallWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setPen(Qt::red);
	painter.setBrush(Qt::lightGray);

	painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

void CWaterFallWidget::onScrollToBottom(int scrollareaHeight)
{
	qDebug() << "scroll to bottom......";

	pushImagePathToLoad();

	tryToDumpItem(scrollareaHeight * 2.5);
}

QSize CWaterFallWidget::fixedSizeWithWidth(const QSize& imageSize, int width)
{
	if (imageSize.width() <= 0 || imageSize.height() <= 0 || width <= 0)
	{
		return QSize(0, 0);
	}

	return QSize(width, (double)width * (double)imageSize.height() / (double)imageSize.width());
}

void CWaterFallWidget::setImageList(const QStringList& listImagePath)
{
	m_listImagePath = listImagePath;
	pushImagePathToLoad(15);
}
void CWaterFallWidget::onImageLoaded(const QPixmap& image, const QString& originpath)
{
	if (!image.isNull())
	{
		CWaterFallItem* item = new CWaterFallItem(image, originpath, this);

		appendItem(item);
	}

}

void CWaterFallWidget::pushImagePathToLoad(int count)
{
	for (int i = 0; i < count && !m_listImagePath.isEmpty(); i++)
	{
		const QString path = m_listImagePath.takeFirst();

		m_loadThread.appendImagePath(path);
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
	m_loadThread.quit();
	m_loadThread.wait();
}

void CWaterFallWidget::tryToDumpItem(int size)
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
