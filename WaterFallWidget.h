#ifndef WaterFallWidget_h__
#define WaterFallWidget_h__

#include <QtCore>
#include <QtWidgets>
#include "ImageReadQueue.h"

#define kColumnSize 4 


class CWaterFallItem;
class CWaterFallScrollArea;
class CWaterFallWidget : public QWidget
{
	Q_OBJECT

	friend class CWaterFallScrollArea;

public:
	CWaterFallWidget(QWidget* parent = 0);
	~CWaterFallWidget();

public:
	void setImageList(const QStringList& listImagePath);
	static QSize fixedSizeWithWidth(const QSize& imageSize, int width);

private:
	void onScrollToTop(int scrollareaHeight);
	void onScrollToBottom(int scrollareaHeight);
	void resetHeights();
	void releaseItems();

protected:
	void paintEvent(QPaintEvent *event);

	void pushImagePathToLoad(int count = 8);

	void refreshItems();
	void appendItem(CWaterFallItem* item);

	int unitWidth() const;

	void resizeEvent(QResizeEvent *event);

	void resetWidgetFixedHeight();

	void tryToDumpTopItem(int size);
	void tryToDumpBottomItem(int size);
protected Q_SLOTS:
void onImageLoaded(const QString& taskID, bool success, const QImage& image, const ImageLib::stReadParam& param);

private:
	QStringList m_listImagePath;
	ImageLib::CImageReadQueue m_loadThread;
	int m_heights[kColumnSize]; //
	QList<CWaterFallItem*> m_listItemsWithColumn[kColumnSize];
	//QList<CWaterFallItem*> m_listItem;
};


#endif // WaterFallWidget_h__
