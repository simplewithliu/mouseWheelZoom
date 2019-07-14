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
	//��ʼ����ʾ�����ϽǶ�ӦԴͼ������Ϊ��0��0��
	leftUpX = 0, leftUpY = 0;
	min_ratio = 0.01, max_ratio = 5;
	//��ʼ����ʾ��ĳ��Ϳ�
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
	//����Դͼ��
	picPath = QFileDialog::getOpenFileName(this, QStringLiteral("ѡ��ͼƬ��"), ".", tr("Image Files(*.jpg *.png)"));
	if (picPath.length() <= 0)
		return;
	std::string tempPath = picPath.toStdString();
	inputImg = cv::imread(tempPath);
	cv::cvtColor(inputImg, inputImg, CV_BGR2RGB);
	//*******************
	//ע�⣺�ؼ���С��ʵʱ�仯�����ÿ��ʹ��ǰ����ȡһ�Σ�����ֻ�ڹ��캯���г�ʼ����
	//��һ������������С���¼���Ҳ�������ĸ���������ʵʱ���¡�
	//*******************
	labelWidth = ui.showPic->width();
	labelHeight = ui.showPic->height();
	//�����ʾ���Դͼ�����ô���ű�Ϊ1�������ʾ��С��Դͼ����ô���ű�ȡ�������űȴ��ߣ�
	//��֤��ʼ��ʾʱ����ͼ���ڿ��ڣ�ͬʱ���Ͻǵ������ӦԴͼ��ģ�0��0��
	if (inputImg.cols <= labelWidth&&inputImg.rows <= labelHeight)
		scale_ratio = 1.0;
	else
		scale_ratio = std::max(inputImg.cols / (double)(labelWidth), inputImg.rows / (double)(labelHeight));
	cv::resize(inputImg, imgShow, cv::Size(), 1 / scale_ratio, 1 / scale_ratio, cv::INTER_NEAREST);
	DisplayMat();
	QString tempInfo(QStringLiteral("ͼ����Ϣ��"));
	tempInfo += QString::number(inputImg.cols) + " * " + QString::number(inputImg.rows);
	ui.picInfo->setText(tempInfo);
	//pos()�������ڸ����ڵ�����ֵ
	labelLeft = ui.showPic->pos().x();
	labelUp = ui.showPic->pos().y() + ui.mainToolBar->height();//Ϊ��û�в˵����ĸ߶�
	haveImg = true;
}

void WheelZoom::wheelEvent(QWheelEvent *event)
{
	//�����㲻��ͼƬ��ʱ��ִ������
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
	//��ʾ���еĳ����ӦԴͼ���еĳ����Ŵ�ͼ��ʵ�ʿ��Ӧ����С
	//�����ʾ����ʾ��ȫ��ͼ��ʵ�ʳ������Դͼ�񳤿�
	labelWidth = ui.showPic->width();
	labelHeight = ui.showPic->height();
	showWidth = std::min((double)(inputImg.cols), labelWidth*scale_ratio);
	showHeight = std::min((double)(inputImg.rows), labelHeight*scale_ratio);
	//�ó���ʾ�����Ͻ�������Դͼ���ж�Ӧ������
	//������Դͼ���е�������ȥ��������ʾ���е������*���ű���
	leftUpX = cursorImgX - floor(cursorWinX*scale_ratio + 0.5);
	leftUpY = cursorImgY - floor(cursorWinY*scale_ratio + 0.5);
	//������Ҫ���Ǵ���ͼ����С������ʾ��С�����
	leftUpX = std::max(0.0, std::min((double)(leftUpX), (double)(inputImg.cols - showWidth)));
	leftUpY = std::max(0.0, std::min((double)(leftUpY), (double)(inputImg.rows - showHeight)));
	//��Ҫ��Դͼ���н�ȡ�Ĳ��֡�
	CvRect roi = cvRect(leftUpX, leftUpY, showWidth, showHeight);
	cv::Mat imageRoi = inputImg(roi);
	//����ȡ��ͼ��Ŵ����С
	int widthInLabel, heightInLabel;
	double tempRatio;
	widthInLabel = showWidth / scale_ratio;
	heightInLabel = showHeight / scale_ratio;
	//�������Ų�����
	cv::resize(imageRoi, imgShow, cv::Size(widthInLabel, heightInLabel), 0, 0, cv::INTER_NEAREST);
	DisplayMat();
}

void WheelZoom::mouseMoveEvent(QMouseEvent *event)
{
	//�ҵ��������ʾ���е������
	cursorWinX = event->pos().x() - labelLeft;
	cursorWinY = event->pos().y() - labelUp;
	if (!haveImg)
		return;
	//�ó���������������Դͼ���е�����㣬���Ͻǵ������+���������*���ű���������ȡ��
	//�������ͼƬ��С����ʵ�ʵĴ�С�����е����������ʵ��Ҫ����Ҫ�������ű������Ŵ�ʱ���ű���С��1
	cursorImgX = floor(cursorWinX*scale_ratio + 0.5 + leftUpX);
	cursorImgY = floor(cursorWinY*scale_ratio + 0.5 + leftUpY);
	//��ʾԴͼ��������Ϣ
	QRect labelRect = QRect(labelLeft, labelUp, ui.showPic->width(), ui.showPic->height());
	QString posInfo(QStringLiteral("������Ϣ��"));
	if (labelRect.contains(event->pos()) && cursorImgX <= inputImg.cols&&cursorImgY <= inputImg.rows)
	{
		posInfo += QString::number(cursorImgX);
		posInfo += " * ";
		posInfo += QString::number(cursorImgY);
	}
	ui.pos->setText(posInfo);
	//��ʾԴͼ���RBG��Ϣ
	QImage show((uchar*)inputImg.data, inputImg.cols, inputImg.rows, inputImg.step, QImage::Format_RGB888);
	QString rgbInfo(QStringLiteral("RBG��Ϣ��"));
	QRgb qRgb = show.pixel(cursorImgX, cursorImgY);
	rgbInfo += QString::number(qRed(qRgb));
	rgbInfo += ",";
	rgbInfo += QString::number(qGreen(qRgb));
	rgbInfo += ",";
	rgbInfo += QString::number(qBlue(qRgb));
	ui.rgbinfo->setText(rgbInfo);

}
