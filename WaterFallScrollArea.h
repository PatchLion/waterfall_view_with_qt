#ifndef WaterFallScrollArea_h__
#define WaterFallScrollArea_h__

#include <QtCore>
#include <QtWidgets>

class CWaterFallWidget;
class CWaterFallScrollArea : public QScrollArea
{
public:
	CWaterFallScrollArea(QWidget* parant = 0);

private:
	CWaterFallWidget* m_content;
};

#endif // WaterFallScrollArea_h__
