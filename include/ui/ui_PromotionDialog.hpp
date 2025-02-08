#ifndef UI_PROMOTIONDIALOG
#define UI_PROMOTIONDIALOG

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PromotionDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *Queen;
    QPushButton *Rook;
    QPushButton *Knight;
    QPushButton *Bishop;

    void setupUi(QDialog *PromotionDialog)
    {
        if (PromotionDialog->objectName().isEmpty())
            PromotionDialog->setObjectName("PromotionDialog");
        PromotionDialog->resize(480, 160);
        PromotionDialog->setMinimumSize(QSize(480, 160));
        PromotionDialog->setMaximumSize(QSize(480, 160));
        PromotionDialog->setStyleSheet(QString::fromUtf8("QDialog {\n"
"	background-color: rgb(45, 45, 45);\n"
"}"));
        horizontalLayout = new QHBoxLayout(PromotionDialog);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(8, 8, 8, 8);
        Queen = new QPushButton(PromotionDialog);
        Queen->setObjectName("Queen");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Queen->sizePolicy().hasHeightForWidth());
        Queen->setSizePolicy(sizePolicy);
        Queen->setMinimumSize(QSize(115, 144));
        Queen->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(69, 69, 69);\n"
"	outline: none;\n"
"	border: none;\n"
"	background-position: center;\n"
"	background-repeat: no-repeat;\n"
"	border-top-left-radius: 8px;\n"
"	border-bottom-left-radius: 8px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgb(77, 77, 77);\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: rgb(88, 88, 88);\n"
"}"));

        horizontalLayout->addWidget(Queen);

        Rook = new QPushButton(PromotionDialog);
        Rook->setObjectName("Rook");
        sizePolicy.setHeightForWidth(Rook->sizePolicy().hasHeightForWidth());
        Rook->setSizePolicy(sizePolicy);
        Rook->setMinimumSize(QSize(115, 144));
        Rook->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(69, 69, 69);\n"
"	outline: none;\n"
"	border: none;\n"
"	background-position: center;\n"
"	background-repeat: no-repeat;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgb(77, 77, 77);\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: rgb(88, 88, 88);\n"
"}"));

        horizontalLayout->addWidget(Rook);

        Knight = new QPushButton(PromotionDialog);
        Knight->setObjectName("Knight");
        sizePolicy.setHeightForWidth(Knight->sizePolicy().hasHeightForWidth());
        Knight->setSizePolicy(sizePolicy);
        Knight->setMinimumSize(QSize(115, 144));
        Knight->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(69, 69, 69);\n"
"	outline: none;\n"
"	border: none;\n"
"	background-position: center;\n"
"	background-repeat: no-repeat;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgb(77, 77, 77);\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: rgb(88, 88, 88);\n"
"}"));

        horizontalLayout->addWidget(Knight);

        Bishop = new QPushButton(PromotionDialog);
        Bishop->setObjectName("Bishop");
        sizePolicy.setHeightForWidth(Bishop->sizePolicy().hasHeightForWidth());
        Bishop->setSizePolicy(sizePolicy);
        Bishop->setMinimumSize(QSize(115, 144));
        Bishop->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(69, 69, 69);\n"
"	outline: none;\n"
"	border: none;\n"
"	background-position: center;\n"
"	background-repeat: no-repeat;\n"
"	border-top-right-radius: 8px;\n"
"	border-bottom-right-radius: 8px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgb(77, 77, 77);\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: rgb(88, 88, 88);\n"
"}"));

        horizontalLayout->addWidget(Bishop);


        retranslateUi(PromotionDialog);

        QMetaObject::connectSlotsByName(PromotionDialog);
    } // setupUi

    void retranslateUi(QDialog *PromotionDialog)
    {
        PromotionDialog->setWindowTitle(QCoreApplication::translate("PromotionDialog", "Select pawn promotion", nullptr));
        Queen->setText(QString());
        Rook->setText(QString());
        Knight->setText(QString());
        Bishop->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PromotionDialog: public Ui_PromotionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif //UI_PROMOTIONDIALOG
