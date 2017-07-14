#ifndef WaterFallScrollArea_h__
#define WaterFallScrollArea_h__

#include <QtCore>
#include <QtWidgets>

class CWaterFallWidget;
class CWaterFallScrollArea : public QScrollArea
{
	Q_OBJECT
public:
	CWaterFallScrollArea(QWidget* parant = 0);

public:
	void setImageList(const QStringList& listImagePath);

protected:
	void resizeEvent(QResizeEvent *event);

protected Q_SLOTS:
	void onVerticalBarRangeChanged(int min, int max);
	void onVerticalBarValueChanged(int value);
	void onImageThumbLoaded(const QPixmap& pixmap);


private:
	CWaterFallWidget* m_content;
};

#endif // WaterFallScrollArea_h__
