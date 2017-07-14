#include "WaterFallScrollArea.h"
#include "WaterFallWidget.h"

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

	if (value >= (verticalScrollBar()->maximum() - 5))
	{
		Q_ASSERT(m_content);
		m_content->onScrollToBottom(height());
	}
}

void CWaterFallScrollArea::setImageList(const QStringList& listImagePath)
{
	Q_ASSERT(m_content);
	m_content->setImageList(listImagePath);
}

