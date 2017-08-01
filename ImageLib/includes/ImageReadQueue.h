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
			Ready,				//��׼����
			Loading,				//������
			Loaded,				//���سɹ�	
			LoadFailed,		//����ʧ��
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

		//�Ƿ������������
		bool isAllFinished() const;

	private:
		//��������һ����������
		ImageLib::CImageReadThread* createImageLoader(const ImageLib::stReadParam& param);

		//��ʼ��һ������
		void startNextTask();

		//�̳߳ظ���
		int poolSize() const { return m_poolSize; }

	private Q_SLOTS:
		void onImageLoadFinished();
		void onThreadFinished(CImageReadThread* loader);

	signals:
		//�������
		void loadFinished(const QString& taskID, bool success, const QImage& image);


	signals:
		//�߳̽����źţ��ڲ�ʹ�ã��ⲿ�������ӣ�
		void threadFinished(CImageReadThread* loader);

	public:
		QMutex														m_mutex;
		ListLoader													m_loaders;
		int																m_poolSize;
	};
}

#endif // ImageReadQueue_h__
