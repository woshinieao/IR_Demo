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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <playwidget.h>

QT_BEGIN_NAMESPACE

class Ui_IrMainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_5;
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
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QToolBox *toolBox;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btn_play;
    QPushButton *btn_stop;
    QPushButton *btn_pic;
    QPushButton *btn_calibrate;
    QPushButton *btn_set;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_5;
    QPushButton *brn_draw;
    QPushButton *btn_point;
    QPushButton *btn_save;
    QPushButton *btn_rectClear;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *cbox_palette;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *IrMainWindow)
    {
        if (IrMainWindow->objectName().isEmpty())
            IrMainWindow->setObjectName(QStringLiteral("IrMainWindow"));
        IrMainWindow->resize(1053, 614);
        centralwidget = new QWidget(IrMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_5 = new QHBoxLayout(centralwidget);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        playwidget = new PlayWidget(centralwidget);
        playwidget->setObjectName(QStringLiteral("playwidget"));

        horizontalLayout_5->addWidget(playwidget);

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

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        toolBox = new QToolBox(groupBox_2);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        page_3->setGeometry(QRect(0, 0, 130, 292));
        verticalLayout_4 = new QVBoxLayout(page_3);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        btn_play = new QPushButton(page_3);
        btn_play->setObjectName(QStringLiteral("btn_play"));
        btn_play->setMinimumSize(QSize(50, 50));

        verticalLayout_4->addWidget(btn_play);

        btn_stop = new QPushButton(page_3);
        btn_stop->setObjectName(QStringLiteral("btn_stop"));
        btn_stop->setMinimumSize(QSize(50, 50));

        verticalLayout_4->addWidget(btn_stop);

        btn_pic = new QPushButton(page_3);
        btn_pic->setObjectName(QStringLiteral("btn_pic"));
        btn_pic->setMinimumSize(QSize(50, 50));

        verticalLayout_4->addWidget(btn_pic);

        btn_calibrate = new QPushButton(page_3);
        btn_calibrate->setObjectName(QStringLiteral("btn_calibrate"));
        btn_calibrate->setMinimumSize(QSize(50, 50));

        verticalLayout_4->addWidget(btn_calibrate);

        btn_set = new QPushButton(page_3);
        btn_set->setObjectName(QStringLiteral("btn_set"));
        btn_set->setMinimumSize(QSize(50, 50));

        verticalLayout_4->addWidget(btn_set);

        toolBox->addItem(page_3, QString::fromUtf8("\350\256\276\345\244\207\346\216\247\345\210\266"));
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        page_4->setGeometry(QRect(0, 0, 144, 259));
        verticalLayout_5 = new QVBoxLayout(page_4);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        brn_draw = new QPushButton(page_4);
        brn_draw->setObjectName(QStringLiteral("brn_draw"));
        brn_draw->setMinimumSize(QSize(50, 50));

        verticalLayout_5->addWidget(brn_draw);

        btn_point = new QPushButton(page_4);
        btn_point->setObjectName(QStringLiteral("btn_point"));
        btn_point->setMinimumSize(QSize(50, 50));

        verticalLayout_5->addWidget(btn_point);

        btn_save = new QPushButton(page_4);
        btn_save->setObjectName(QStringLiteral("btn_save"));
        btn_save->setMinimumSize(QSize(50, 50));

        verticalLayout_5->addWidget(btn_save);

        btn_rectClear = new QPushButton(page_4);
        btn_rectClear->setObjectName(QStringLiteral("btn_rectClear"));
        btn_rectClear->setMinimumSize(QSize(50, 50));

        verticalLayout_5->addWidget(btn_rectClear);

        toolBox->addItem(page_4, QString::fromUtf8("\346\270\251\345\272\246\346\265\213\351\207\217"));

        verticalLayout_3->addWidget(toolBox);


        verticalLayout->addWidget(groupBox_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        cbox_palette = new QComboBox(groupBox);
        QIcon icon;
        icon.addFile(QStringLiteral("logo/Palette0.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbox_palette->addItem(icon, QString());
        QIcon icon1;
        icon1.addFile(QStringLiteral("logo/Palette1.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbox_palette->addItem(icon1, QString());
        QIcon icon2;
        icon2.addFile(QStringLiteral("logo/Palette2.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbox_palette->addItem(icon2, QString());
        QIcon icon3;
        icon3.addFile(QStringLiteral("logo/Palette3.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbox_palette->addItem(icon3, QString());
        QIcon icon4;
        icon4.addFile(QStringLiteral("logo/Palette4.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbox_palette->addItem(icon4, QString());
        QIcon icon5;
        icon5.addFile(QStringLiteral("logo/Palette5.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbox_palette->addItem(icon5, QString());
        QIcon icon6;
        icon6.addFile(QStringLiteral("logo/Palette6.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbox_palette->addItem(icon6, QString());
        QIcon icon7;
        icon7.addFile(QStringLiteral("logo/Palette7.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbox_palette->addItem(icon7, QString());
        QIcon icon8;
        icon8.addFile(QStringLiteral("logo/Palette8.png"), QSize(), QIcon::Normal, QIcon::Off);
        cbox_palette->addItem(icon8, QString());
        cbox_palette->setObjectName(QStringLiteral("cbox_palette"));
        cbox_palette->setMinimumSize(QSize(80, 30));

        horizontalLayout_3->addWidget(cbox_palette);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 8);

        verticalLayout_2->addWidget(groupBox);

        verticalLayout_2->setStretch(0, 1);

        horizontalLayout_5->addLayout(verticalLayout_2);

        horizontalLayout_5->setStretch(0, 10);
        horizontalLayout_5->setStretch(1, 1);
        IrMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(IrMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1053, 22));
        IrMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(IrMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        IrMainWindow->setStatusBar(statusbar);

        retranslateUi(IrMainWindow);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(IrMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *IrMainWindow)
    {
        IrMainWindow->setWindowTitle(QApplication::translate("IrMainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("IrMainWindow", "\350\256\276\345\244\207\350\277\236\346\216\245", 0));
        label->setText(QApplication::translate("IrMainWindow", "IP:", 0));
        le_ip->setText(QApplication::translate("IrMainWindow", "192.168.1.24", 0));
        btn_connect->setText(QApplication::translate("IrMainWindow", "\350\277\236\346\216\245", 0));
        btn_disconnect->setText(QApplication::translate("IrMainWindow", "\346\263\250\351\224\200", 0));
        groupBox_2->setTitle(QString());
        btn_play->setText(QApplication::translate("IrMainWindow", "\346\222\255\346\224\276", 0));
        btn_stop->setText(QApplication::translate("IrMainWindow", "\345\201\234\346\255\242", 0));
        btn_pic->setText(QApplication::translate("IrMainWindow", "\346\212\223\345\233\276", 0));
        btn_calibrate->setText(QApplication::translate("IrMainWindow", "\345\277\253\351\227\250\350\241\245\345\201\277", 0));
        btn_set->setText(QApplication::translate("IrMainWindow", "\350\256\276\345\244\207\351\205\215\347\275\256", 0));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("IrMainWindow", "\350\256\276\345\244\207\346\216\247\345\210\266", 0));
        brn_draw->setText(QApplication::translate("IrMainWindow", "\347\224\273\346\241\206", 0));
        btn_point->setText(QApplication::translate("IrMainWindow", "\347\202\271\346\265\213\346\270\251", 0));
        btn_save->setText(QApplication::translate("IrMainWindow", "\344\277\235\345\255\230", 0));
        btn_rectClear->setText(QApplication::translate("IrMainWindow", "\346\270\205\351\231\244", 0));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("IrMainWindow", "\346\270\251\345\272\246\346\265\213\351\207\217", 0));
        label_2->setText(QApplication::translate("IrMainWindow", "<html><head/><body><p align=\"center\">\350\260\203\350\211\262\346\235\277</p></body></html>", 0));
        cbox_palette->setItemText(0, QApplication::translate("IrMainWindow", "1", 0));
        cbox_palette->setItemText(1, QApplication::translate("IrMainWindow", "2", 0));
        cbox_palette->setItemText(2, QApplication::translate("IrMainWindow", "3", 0));
        cbox_palette->setItemText(3, QApplication::translate("IrMainWindow", "4", 0));
        cbox_palette->setItemText(4, QApplication::translate("IrMainWindow", "5", 0));
        cbox_palette->setItemText(5, QApplication::translate("IrMainWindow", "6", 0));
        cbox_palette->setItemText(6, QApplication::translate("IrMainWindow", "7", 0));
        cbox_palette->setItemText(7, QApplication::translate("IrMainWindow", "8", 0));
        cbox_palette->setItemText(8, QApplication::translate("IrMainWindow", "9", 0));

    } // retranslateUi

};

namespace Ui {
    class IrMainWindow: public Ui_IrMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IRMAINWINDOW_H
