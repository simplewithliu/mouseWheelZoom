/********************************************************************************
** Form generated from reading UI file 'wheelzoom.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHEELZOOM_H
#define UI_WHEELZOOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WheelZoomClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *showPic;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addPic;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *picInfo;
    QLabel *rgbinfo;
    QLabel *pos;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WheelZoomClass)
    {
        if (WheelZoomClass->objectName().isEmpty())
            WheelZoomClass->setObjectName(QStringLiteral("WheelZoomClass"));
        WheelZoomClass->resize(800, 650);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WheelZoomClass->sizePolicy().hasHeightForWidth());
        WheelZoomClass->setSizePolicy(sizePolicy);
        WheelZoomClass->setMinimumSize(QSize(800, 650));
        WheelZoomClass->setMaximumSize(QSize(800, 650));
        WheelZoomClass->setMouseTracking(true);
        centralWidget = new QWidget(WheelZoomClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMouseTracking(true);
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        showPic = new QLabel(centralWidget);
        showPic->setObjectName(QStringLiteral("showPic"));
        showPic->setMouseTracking(true);
        showPic->setFrameShape(QFrame::Box);
        showPic->setScaledContents(false);
        showPic->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_3->addWidget(showPic);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        addPic = new QPushButton(centralWidget);
        addPic->setObjectName(QStringLiteral("addPic"));

        horizontalLayout_2->addWidget(addPic);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        picInfo = new QLabel(centralWidget);
        picInfo->setObjectName(QStringLiteral("picInfo"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(picInfo->sizePolicy().hasHeightForWidth());
        picInfo->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(picInfo);

        rgbinfo = new QLabel(centralWidget);
        rgbinfo->setObjectName(QStringLiteral("rgbinfo"));

        verticalLayout->addWidget(rgbinfo);

        pos = new QLabel(centralWidget);
        pos->setObjectName(QStringLiteral("pos"));

        verticalLayout->addWidget(pos);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);

        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalLayout_3->setStretch(0, 5);
        verticalLayout_3->setStretch(1, 1);
        WheelZoomClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WheelZoomClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menuBar->setMouseTracking(false);
        WheelZoomClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WheelZoomClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WheelZoomClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(WheelZoomClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WheelZoomClass->setStatusBar(statusBar);

        retranslateUi(WheelZoomClass);

        QMetaObject::connectSlotsByName(WheelZoomClass);
    } // setupUi

    void retranslateUi(QMainWindow *WheelZoomClass)
    {
        WheelZoomClass->setWindowTitle(QApplication::translate("WheelZoomClass", "WheelZoom", 0));
        showPic->setText(QString());
        addPic->setText(QApplication::translate("WheelZoomClass", "AddPic", 0));
        picInfo->setText(QApplication::translate("WheelZoomClass", "\345\233\276\345\203\217\344\277\241\346\201\257\357\274\232", 0));
        rgbinfo->setText(QApplication::translate("WheelZoomClass", "RGB\344\277\241\346\201\257\357\274\232", 0));
        pos->setText(QApplication::translate("WheelZoomClass", "\345\235\220\346\240\207\344\277\241\346\201\257\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class WheelZoomClass: public Ui_WheelZoomClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHEELZOOM_H
