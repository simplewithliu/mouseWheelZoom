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
	//源图像
	cv::Mat inputImg;
	//用于显示的图像
	cv::Mat imgShow;
	//在显示框中的坐标点位置
	int cursorWinX, cursorWinY;
	//在源图像中的坐标点位置
	int cursorImgX, cursorImgY;
	//显示框左上角对应源图像的坐标点
	int leftUpX, leftUpY;
	//显示框对应源图像的宽和高
	int showWidth, showHeight;
	//显示框的宽和高
	int labelWidth, labelHeight;
	//缩放比
	double scale_ratio;
	//最小缩放比和最大缩放比
	double min_ratio, max_ratio;
	//显示框在客户区的左上角坐标
	int labelUp, labelLeft;

	QString picPath;
	bool haveImg;

};

#endif // WHEELZOOM_H
