#include "wheelzoom.h"
#include <Qtcore/QFile>
#include <Qtwidgets/QFileDialog>
#include <Qtcore/QTextStream>
#include <QtGui/QPixmap>
#include <Qtcore/QRect>
#include <Qtwidgets/QFontDialog>
#include <Qtcore/QCoreApplication>
#include <Qtwidgets/QScrollbar>
#include <Qtwidgets/Qlabel>
#include <QtGui/QTextCharFormat>
#include <QtWidgets/QScrollArea>
#include <Qtwidgets/QMessagebox>
#include <string>
#include <algorithm>

WheelZoom::WheelZoom(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.addPic, SIGNAL(clicked()), this, SLOT(on_addPic()));
	//初始化显示框左上角对应源图像坐标为（0，0）
	leftUpX = 0, leftUpY = 0;
	min_ratio = 0.01, max_ratio = 5;
	//初始化显示框的长和宽
	labelWidth = ui.showPic->width();
	labelHeight = ui.showPic->height();
	haveImg = false;
}

WheelZoom::~WheelZoom()
{

}

void WheelZoom::DisplayMat()
{
	QImage temp_qimage((uchar*)imgShow.data, imgShow.cols, imgShow.rows, imgShow.step, QImage::Format_RGB888);
	ui.showPic->setPixmap(QPixmap::fromImage(temp_qimage));
}

void WheelZoom::on_addPic()
{
	//加载源图像
	picPath = QFileDialog::getOpenFileName(this, QStringLiteral("选择图片："), ".", tr("Image Files(*.jpg *.png)"));
	if (picPath.length() <= 0)
		return;
	std::string tempPath = picPath.toStdString();
	inputImg = cv::imread(tempPath);
	cv::cvtColor(inputImg, inputImg, CV_BGR2RGB);
	//*******************
	//注意：控件大小会实时变化，最好每次使用前都获取一次，不能只在构造函数中初始化。
	//有一个窗口扩大缩小的事件，也可以在哪个函数里面实时更新。
	//*******************
	labelWidth = ui.showPic->width();
	labelHeight = ui.showPic->height();
	//如果显示框比源图像大，那么缩放比为1，如果显示框小于源图像，那么缩放比取长宽缩放比大者，
	//保证初始显示时整个图像都在框内，同时左上角点坐标对应源图像的（0，0）
	if (inputImg.cols <= labelWidth&&inputImg.rows <= labelHeight)
		scale_ratio = 1.0;
	else
		scale_ratio = std::max(inputImg.cols / (double)(labelWidth), inputImg.rows / (double)(labelHeight));
	cv::resize(inputImg, imgShow, cv::Size(), 1 / scale_ratio, 1 / scale_ratio, cv::INTER_NEAREST);
	DisplayMat();
	QString tempInfo(QStringLiteral("图像信息："));
	tempInfo += QString::number(inputImg.cols) + " * " + QString::number(inputImg.rows);
	ui.picInfo->setText(tempInfo);
	//pos()获得相对于父窗口的坐标值
	labelLeft = ui.showPic->pos().x();
	labelUp = ui.showPic->pos().y() + ui.mainToolBar->height();//为何没有菜单栏的高度
	haveImg = true;
}

void WheelZoom::wheelEvent(QWheelEvent *event)
{
	//当鼠标点不在图片上时不执行缩放
	if (!(cursorImgY < inputImg.rows&&cursorImgY >= 0 && cursorImgX < inputImg.cols&&cursorImgX >= 0))
		return;
	if (event->delta() < 0)
	{
		scale_ratio = std::min(max_ratio, (double)(scale_ratio * 1.2));
	}
	else
	{
		scale_ratio = std::max(min_ratio, (double)(scale_ratio / 1.2));
	}
	//显示框中的长宽对应源图像中的长宽，放大图像，实际宽度应该缩小
	//如果显示框显示了全部图像，实际长宽就是源图像长宽
	labelWidth = ui.showPic->width();
	labelHeight = ui.showPic->height();
	showWidth = std::min((double)(inputImg.cols), labelWidth*scale_ratio);
	showHeight = std::min((double)(inputImg.rows), labelHeight*scale_ratio);
	//得出显示框左上角坐标在源图像中对应的坐标
	//鼠标点在源图像中的坐标点减去鼠标点在显示框中的坐标点*缩放比例
	leftUpX = cursorImgX - floor(cursorWinX*scale_ratio + 0.5);
	leftUpY = cursorImgY - floor(cursorWinY*scale_ratio + 0.5);
	//这里需要考虑存在图像缩小到比显示框还小的情况
	leftUpX = std::max(0.0, std::min((double)(leftUpX), (double)(inputImg.cols - showWidth)));
	leftUpY = std::max(0.0, std::min((double)(leftUpY), (double)(inputImg.rows - showHeight)));
	//需要在源图像中截取的部分。
	CvRect roi = cvRect(leftUpX, leftUpY, showWidth, showHeight);
	cv::Mat imageRoi = inputImg(roi);
	//将截取的图像放大或缩小
	int widthInLabel, heightInLabel;
	double tempRatio;
	widthInLabel = showWidth / scale_ratio;
	heightInLabel = showHeight / scale_ratio;
	//进行缩放操作。
	cv::resize(imageRoi, imgShow, cv::Size(widthInLabel, heightInLabel), 0, 0, cv::INTER_NEAREST);
	DisplayMat();
}

void WheelZoom::mouseMoveEvent(QMouseEvent *event)
{
	//找到鼠标在显示框中的坐标点
	cursorWinX = event->pos().x() - labelLeft;
	cursorWinY = event->pos().y() - labelUp;
	if (!haveImg)
		return;
	//得出框中鼠标坐标点在源图像中的坐标点，左上角的坐标点+框中坐标点*缩放比例，向下取整
	//如果框中图片大小大于实际的大小，框中的坐标相对于实际要大，则要乘以缩放比例，放大时缩放比例小于1
	cursorImgX = floor(cursorWinX*scale_ratio + 0.5 + leftUpX);
	cursorImgY = floor(cursorWinY*scale_ratio + 0.5 + leftUpY);
	//显示源图像坐标信息
	QRect labelRect = QRect(labelLeft, labelUp, ui.showPic->width(), ui.showPic->height());
	QString posInfo(QStringLiteral("坐标信息："));
	if (labelRect.contains(event->pos()) && cursorImgX <= inputImg.cols&&cursorImgY <= inputImg.rows)
	{
		posInfo += QString::number(cursorImgX);
		posInfo += " * ";
		posInfo += QString::number(cursorImgY);
	}
	ui.pos->setText(posInfo);
	//显示源图像的RBG信息
	QImage show((uchar*)inputImg.data, inputImg.cols, inputImg.rows, inputImg.step, QImage::Format_RGB888);
	QString rgbInfo(QStringLiteral("RBG信息："));
	QRgb qRgb = show.pixel(cursorImgX, cursorImgY);
	rgbInfo += QString::number(qRed(qRgb));
	rgbInfo += ",";
	rgbInfo += QString::number(qGreen(qRgb));
	rgbInfo += ",";
	rgbInfo += QString::number(qBlue(qRgb));
	ui.rgbinfo->setText(rgbInfo);

}
