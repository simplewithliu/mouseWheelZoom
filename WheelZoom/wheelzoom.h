#ifndef WHEELZOOM_H
#define WHEELZOOM_H

#include <opencv2/opencv.hpp>
#include <QtWidgets/QMainWindow>
#include <QWheelEvent>
#include <QMouseEvent>
#include "ui_wheelzoom.h"


class WheelZoom : public QMainWindow
{
	Q_OBJECT

public:
	WheelZoom(QWidget *parent = 0);
	void wheelEvent(QWheelEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void DisplayMat();
	~WheelZoom();

private slots:
	void on_addPic();

private:
	Ui::WheelZoomClass ui;
	//Դͼ��
	cv::Mat inputImg;
	//������ʾ��ͼ��
	cv::Mat imgShow;
	//����ʾ���е������λ��
	int cursorWinX, cursorWinY;
	//��Դͼ���е������λ��
	int cursorImgX, cursorImgY;
	//��ʾ�����ϽǶ�ӦԴͼ��������
	int leftUpX, leftUpY;
	//��ʾ���ӦԴͼ��Ŀ�͸�
	int showWidth, showHeight;
	//��ʾ��Ŀ�͸�
	int labelWidth, labelHeight;
	//���ű�
	double scale_ratio;
	//��С���űȺ�������ű�
	double min_ratio, max_ratio;
	//��ʾ���ڿͻ��������Ͻ�����
	int labelUp, labelLeft;

	QString picPath;
	bool haveImg;

};

#endif // WHEELZOOM_H
