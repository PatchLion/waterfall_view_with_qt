#ifndef ImageReadQueue_h__
#define ImageReadQueue_h__

#include <QtCore>
#include <QtGui>
#include "ImageStructs.h"

namespace ImageLib
{
	class CImageReadThread;
	class CImageReadQueue : public QObject
	{
		Q_OBJECT
	private:
		enum ELoadState
		{
			Ready,				//已准备好
			Loading,				//加载中
			Loaded,				//加载成功	
			LoadFailed,		//加载失败
		};

		struct stLoader
		{
			stLoader()
			{
				state = Ready;
				reader = 0;
			}
			stLoader(const ImageLib::stReadParam& t)
			{
				state = Ready;
				param = t;
				reader = 0;
			}

			ImageLib::CImageReadThread *reader;
			ImageLib::stReadParam param;
			ELoadState state;
			QString id;
		};
		typedef QList<stLoader>  ListLoader;

	public:
		CImageReadQueue(int poolSize = 10, QObject *parent = 0);
		~CImageReadQueue();

	public:
		//
		QString addLoadTask(const ImageLib::stReadParam& param);
		
		//
		void releaseTask(const QString& taskID);

		//是否所有任务完成
		bool isAllFinished() const;

	private:
		//尝试生成一个加载任务
		ImageLib::CImageReadThread* createImageLoader(const ImageLib::stReadParam& param);

		//开始下一个任务
		void startNextTask();

		//线程池个数
		int poolSize() const { return m_poolSize; }

	private Q_SLOTS:
		void onImageLoadFinished();
		void onThreadFinished(CImageReadThread* loader);

	signals:
		//加载完成
		void loadFinished(const QString& taskID, bool success, const QImage& image);


	signals:
		//线程结束信号（内部使用，外部请勿链接）
		void threadFinished(CImageReadThread* loader);

	public:
		QMutex														m_mutex;
		ListLoader													m_loaders;
		int																m_poolSize;
	};
}

#endif // ImageReadQueue_h__
