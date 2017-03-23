/********************************************************************************
** Form generated from reading UI file 'irmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IRMAINWINDOW_H
#define UI_IRMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <playwidget.h>

QT_BEGIN_NAMESPACE

class Ui_IrMainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    PlayWidget *playwidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *le_ip;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_connect;
    QPushButton *btn_disconnect;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btn_play;
    QPushButton *btn_stop;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QLabel *label_2;
    QComboBox *comboBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *IrMainWindow)
    {
        if (IrMainWindow->objectName().isEmpty())
            IrMainWindow->setObjectName(QStringLiteral("IrMainWindow"));
        IrMainWindow->resize(839, 597);
        centralwidget = new QWidget(IrMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        playwidget = new PlayWidget(centralwidget);
        playwidget->setObjectName(QStringLiteral("playwidget"));

        horizontalLayout_3->addWidget(playwidget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        le_ip = new QLineEdit(groupBox);
        le_ip->setObjectName(QStringLiteral("le_ip"));

        horizontalLayout->addWidget(le_ip);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btn_connect = new QPushButton(groupBox);
        btn_connect->setObjectName(QStringLiteral("btn_connect"));

        horizontalLayout_2->addWidget(btn_connect);

        btn_disconnect = new QPushButton(groupBox);
        btn_disconnect->setObjectName(QStringLiteral("btn_disconnect"));

        horizontalLayout_2->addWidget(btn_disconnect);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btn_play = new QPushButton(groupBox);
        btn_play->setObjectName(QStringLiteral("btn_play"));

        horizontalLayout_4->addWidget(btn_play);

        btn_stop = new QPushButton(groupBox);
        btn_stop->setObjectName(QStringLiteral("btn_stop"));

        horizontalLayout_4->addWidget(btn_stop);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(pushButton_3, 0, 0, 1, 1);

        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(pushButton_4, 0, 1, 1, 1);

        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(pushButton_5, 1, 0, 1, 1);

        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(pushButton_6, 1, 1, 1, 1);

        pushButton_7 = new QPushButton(groupBox_2);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(pushButton_7, 2, 0, 1, 1);

        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(pushButton_8, 2, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(80, 30));

        gridLayout->addWidget(comboBox, 3, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 4);

        horizontalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_3->setStretch(0, 10);
        horizontalLayout_3->setStretch(1, 2);
        IrMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(IrMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 839, 23));
        IrMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(IrMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        IrMainWindow->setStatusBar(statusbar);

        retranslateUi(IrMainWindow);

        QMetaObject::connectSlotsByName(IrMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *IrMainWindow)
    {
        IrMainWindow->setWindowTitle(QApplication::translate("IrMainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("IrMainWindow", "\350\256\276\345\244\207\350\277\236\346\216\245", 0));
        label->setText(QApplication::translate("IrMainWindow", "IP:", 0));
        le_ip->setText(QApplication::translate("IrMainWindow", "192.168.1.64", 0));
        btn_connect->setText(QApplication::translate("IrMainWindow", "\350\277\236\346\216\245", 0));
        btn_disconnect->setText(QApplication::translate("IrMainWindow", "\346\263\250\351\224\200", 0));
        btn_play->setText(QApplication::translate("IrMainWindow", "\346\222\255\346\224\276", 0));
        btn_stop->setText(QApplication::translate("IrMainWindow", "\345\201\234\346\255\242", 0));
        groupBox_2->setTitle(QApplication::translate("IrMainWindow", "\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        pushButton_3->setText(QApplication::translate("IrMainWindow", "\345\277\253\351\227\250\350\241\245\345\201\277", 0));
        pushButton_4->setText(QApplication::translate("IrMainWindow", "PushButton", 0));
        pushButton_5->setText(QApplication::translate("IrMainWindow", "\347\224\273\346\241\206", 0));
        pushButton_6->setText(QApplication::translate("IrMainWindow", "PushButton", 0));
        pushButton_7->setText(QApplication::translate("IrMainWindow", "PushButton", 0));
        pushButton_8->setText(QApplication::translate("IrMainWindow", "\350\256\276\345\244\207\351\205\215\347\275\256", 0));
        label_2->setText(QApplication::translate("IrMainWindow", "<html><head/><body><p align=\"center\">\350\260\203\350\211\262\346\235\277</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class IrMainWindow: public Ui_IrMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IRMAINWINDOW_H
