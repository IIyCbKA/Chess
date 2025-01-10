/********************************************************************************
** Form generated from reading UI file 'App.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_H
#define UI_APP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "ChessBoard.hpp"
#include "HistoryTable.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *centralWidgetGridLayout;
    QFrame *rootFrame;
    QGridLayout *rootFrameGridLayout;
    QFrame *boardFrame;
    QGridLayout *boardFrameGridLayout;
    ChessBoard *chessBoardView;
    QFrame *gameStateFrame;
    QGridLayout *gameStateFrameGridLayout;
    QFrame *btnsFrame;
    QGridLayout *btnsFrameGridLayout;
    QPushButton *easyBotBtn;
    QPushButton *mediumBotBtn;
    QPushButton *hardBotBtn;
    QFrame *tableFrame;
    QGridLayout *tableFrameGridLayout;
    HistoryTable *tableView;
    QFrame *upperIndicator;
    QFrame *lowerIndicator;
    QPushButton *restartGameBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 675);
        MainWindow->setMinimumSize(QSize(1200, 675));
        QIcon icon(":/icons/icon.png");
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        centralWidget->setMinimumSize(QSize(1200, 675));
        QFont font;
        font.setFamilies({QString::fromUtf8("Ubuntu Sans Mono")});
        centralWidget->setFont(font);
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        centralWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(82, 115, 63);"));
        centralWidgetGridLayout = new QGridLayout(centralWidget);
        centralWidgetGridLayout->setObjectName("centralWidgetGridLayout");
        centralWidgetGridLayout->setContentsMargins(0, 0, 0, 0);
        rootFrame = new QFrame(centralWidget);
        rootFrame->setObjectName("rootFrame");
        rootFrame->setMinimumSize(QSize(1200, 675));
        QFont font1;
        font1.setBold(true);
        rootFrame->setFont(font1);
        rootFrame->setStyleSheet(QString::fromUtf8("border: none;\n"
"outline: none;"));
        rootFrame->setFrameShape(QFrame::StyledPanel);
        rootFrame->setFrameShadow(QFrame::Raised);
        rootFrameGridLayout = new QGridLayout(rootFrame);
        rootFrameGridLayout->setObjectName("rootFrameGridLayout");
        rootFrameGridLayout->setHorizontalSpacing(20);
        rootFrameGridLayout->setVerticalSpacing(10);
        rootFrameGridLayout->setContentsMargins(35, 15, 35, 20);
        boardFrame = new QFrame(rootFrame);
        boardFrame->setObjectName("boardFrame");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(boardFrame->sizePolicy().hasHeightForWidth());
        boardFrame->setSizePolicy(sizePolicy);
        boardFrame->setMinimumSize(QSize(640, 640));
        boardFrame->setStyleSheet(QString::fromUtf8("border: none;\n"
"outline: none;"));
        boardFrame->setFrameShape(QFrame::StyledPanel);
        boardFrame->setFrameShadow(QFrame::Raised);
        boardFrameGridLayout = new QGridLayout(boardFrame);
        boardFrameGridLayout->setObjectName("boardFrameGridLayout");
        boardFrameGridLayout->setContentsMargins(0, 0, 0, 0);
        chessBoardView = new ChessBoard(boardFrame);
        chessBoardView->setObjectName("chessBoardView");
        chessBoardView->setMinimumSize(QSize(640, 640));
        chessBoardView->setStyleSheet(QString::fromUtf8("border: none;"));
        chessBoardView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        chessBoardView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        boardFrameGridLayout->addWidget(chessBoardView, 0, 0, 1, 1);


        rootFrameGridLayout->addWidget(boardFrame, 0, 0, 1, 1);

        gameStateFrame = new QFrame(rootFrame);
        gameStateFrame->setObjectName("gameStateFrame");
        gameStateFrame->setMinimumSize(QSize(470, 640));
        gameStateFrame->setFrameShape(QFrame::StyledPanel);
        gameStateFrame->setFrameShadow(QFrame::Raised);
        gameStateFrameGridLayout = new QGridLayout(gameStateFrame);
        gameStateFrameGridLayout->setObjectName("gameStateFrameGridLayout");
        gameStateFrameGridLayout->setHorizontalSpacing(10);
        gameStateFrameGridLayout->setVerticalSpacing(20);
        gameStateFrameGridLayout->setContentsMargins(0, 0, 0, 0);
        btnsFrame = new QFrame(gameStateFrame);
        btnsFrame->setObjectName("btnsFrame");
        btnsFrame->setMinimumSize(QSize(0, 50));
        btnsFrame->setFrameShape(QFrame::StyledPanel);
        btnsFrame->setFrameShadow(QFrame::Raised);
        btnsFrameGridLayout = new QGridLayout(btnsFrame);
        btnsFrameGridLayout->setObjectName("btnsFrameGridLayout");
        btnsFrameGridLayout->setContentsMargins(5, 5, 5, 5);
        easyBotBtn = new QPushButton(btnsFrame);
        easyBotBtn->setObjectName("easyBotBtn");
        easyBotBtn->setMinimumSize(QSize(0, 40));
        QFont font2;
        font2.setPointSize(12);
        easyBotBtn->setFont(font2);
        easyBotBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(66, 93, 52);\n"
"    outline: none;\n"
"    border: none;\n"
"	border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgb(59, 89, 43);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	padding: 0;\n"
"	background-color: rgb(56, 80, 45);\n"
"}\n"
""));

        btnsFrameGridLayout->addWidget(easyBotBtn, 0, 0, 1, 1);

        mediumBotBtn = new QPushButton(btnsFrame);
        mediumBotBtn->setObjectName("mediumBotBtn");
        mediumBotBtn->setMinimumSize(QSize(0, 40));
        mediumBotBtn->setFont(font2);
        mediumBotBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(66, 93, 52);\n"
"    outline: none;\n"
"    border: none;\n"
"	border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgb(59, 89, 43);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	padding: 0;\n"
"	background-color: rgb(56, 80, 45);\n"
"}\n"
""));

        btnsFrameGridLayout->addWidget(mediumBotBtn, 0, 1, 1, 1);

        hardBotBtn = new QPushButton(btnsFrame);
        hardBotBtn->setObjectName("hardBotBtn");
        hardBotBtn->setMinimumSize(QSize(0, 40));
        hardBotBtn->setFont(font2);
        hardBotBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(66, 93, 52);\n"
"    outline: none;\n"
"    border: none;\n"
"	border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgb(59, 89, 43);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	padding: 0;\n"
"	background-color: rgb(56, 80, 45);\n"
"}\n"
""));

        btnsFrameGridLayout->addWidget(hardBotBtn, 0, 2, 1, 1);


        gameStateFrameGridLayout->addWidget(btnsFrame, 2, 0, 1, 1);

        tableFrame = new QFrame(gameStateFrame);
        tableFrame->setObjectName("tableFrame");
        tableFrame->setMinimumSize(QSize(0, 0));
        tableFrame->setStyleSheet(QString::fromUtf8(""));
        tableFrame->setFrameShape(QFrame::StyledPanel);
        tableFrame->setFrameShadow(QFrame::Raised);
        tableFrameGridLayout = new QGridLayout(tableFrame);
        tableFrameGridLayout->setSpacing(0);
        tableFrameGridLayout->setObjectName("tableFrameGridLayout");
        tableFrameGridLayout->setContentsMargins(0, 0, 0, 0);
        tableView = new HistoryTable(tableFrame);
        tableView->setObjectName("tableView");
        tableView->setStyleSheet(QString::fromUtf8("background-color: rgb(66, 93, 52);"));

        tableFrameGridLayout->addWidget(tableView, 1, 0, 1, 1);

        upperIndicator = new QFrame(tableFrame);
        upperIndicator->setObjectName("upperIndicator");
        upperIndicator->setMinimumSize(QSize(0, 32));
        upperIndicator->setMaximumSize(QSize(160, 16777215));
        upperIndicator->setStyleSheet(QString::fromUtf8("border-top-left-radius: 10px;\n"
"border-top-right-radius: 10px;\n"
"border: 3px solid #55841f;"));
        upperIndicator->setFrameShape(QFrame::HLine);
        upperIndicator->setFrameShadow(QFrame::Sunken);

        tableFrameGridLayout->addWidget(upperIndicator, 0, 0, 1, 2);

        lowerIndicator = new QFrame(tableFrame);
        lowerIndicator->setObjectName("lowerIndicator");
        lowerIndicator->setMinimumSize(QSize(0, 32));
        lowerIndicator->setMaximumSize(QSize(160, 16777215));
        lowerIndicator->setStyleSheet(QString::fromUtf8("border-bottom-left-radius: 10px;\n"
"border-bottom-right-radius: 10px;\n"
"border: 3px solid #55841f;"));
        lowerIndicator->setFrameShape(QFrame::HLine);
        lowerIndicator->setFrameShadow(QFrame::Sunken);

        tableFrameGridLayout->addWidget(lowerIndicator, 2, 0, 1, 2);


        gameStateFrameGridLayout->addWidget(tableFrame, 0, 0, 1, 1);

        restartGameBtn = new QPushButton(gameStateFrame);
        restartGameBtn->setObjectName("restartGameBtn");
        restartGameBtn->setMinimumSize(QSize(0, 50));
        QPalette palette;
        QBrush brush(QColor(66, 93, 52, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        restartGameBtn->setPalette(palette);
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Ubuntu Sans")});
        font3.setPointSize(12);
        font3.setBold(false);
        restartGameBtn->setFont(font3);
        restartGameBtn->setCursor(QCursor(Qt::ArrowCursor));
        restartGameBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(66, 93, 52);\n"
"    outline: none;\n"
"    border: none;\n"
"	border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgb(59, 89, 43);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	padding: 0;\n"
"	background-color: rgb(56, 80, 45);\n"
"}\n"
""));

        gameStateFrameGridLayout->addWidget(restartGameBtn, 3, 0, 1, 1);


        rootFrameGridLayout->addWidget(gameStateFrame, 0, 1, 1, 1);


        centralWidgetGridLayout->addWidget(rootFrame, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Chess", nullptr));
        easyBotBtn->setText(QCoreApplication::translate("MainWindow", "Easy", nullptr));
        mediumBotBtn->setText(QCoreApplication::translate("MainWindow", "Medium", nullptr));
        hardBotBtn->setText(QCoreApplication::translate("MainWindow", "Hard", nullptr));
        restartGameBtn->setText(QCoreApplication::translate("MainWindow", "RESTART", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_H
