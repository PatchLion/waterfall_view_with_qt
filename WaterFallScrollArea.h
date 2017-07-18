#ifndef WaterFallScrollArea_h__
#define WaterFallScrollArea_h__

#include <QtCore>
#include <QtWidgets>

class CWaterFallWidget;
class CImageSreachThread;
class CWaterFallScrollArea : public QScrollArea
{
	Q_OBJECT
public:
	CWaterFallScrollArea(QWidget* parant = 0);

public:
	void appendImageList(const QStringList& listImagePath);

protected:
	void resizeEvent(QResizeEvent *event);
	void dropEvent(QDropEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);

	void setImageList(const QStringList& listImagePath);

protected Q_SLOTS:
	void onVerticalBarRangeChanged(int min, int max);
	void onVerticalBarValueChanged(int value);
	void onImageAllLoadFinished();
	void onImageLoadProgress(const QStringList& listFile);

private:
	CWaterFallWidget* m_content;
	CImageSreachThread* m_sreachThread;
};

#endif // WaterFallScrollArea_h__
