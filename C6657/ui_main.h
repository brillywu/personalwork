/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *serial_go;
    QPlainTextEdit *serial_txt;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *filter_txt;
    QPushButton *filter_go;
    QLineEdit *choice_txt;
    QPushButton *choice_go;
    QPlainTextEdit *udp_txt;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1195, 849);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 1171, 831));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEditable(true);

        horizontalLayout->addWidget(comboBox);

        serial_go = new QPushButton(layoutWidget);
        serial_go->setObjectName(QStringLiteral("serial_go"));

        horizontalLayout->addWidget(serial_go);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 8);
        horizontalLayout->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout);

        serial_txt = new QPlainTextEdit(layoutWidget);
        serial_txt->setObjectName(QStringLiteral("serial_txt"));

        verticalLayout->addWidget(serial_txt);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        filter_txt = new QLineEdit(layoutWidget);
        filter_txt->setObjectName(QStringLiteral("filter_txt"));

        horizontalLayout_2->addWidget(filter_txt);

        filter_go = new QPushButton(layoutWidget);
        filter_go->setObjectName(QStringLiteral("filter_go"));

        horizontalLayout_2->addWidget(filter_go);

        choice_txt = new QLineEdit(layoutWidget);
        choice_txt->setObjectName(QStringLiteral("choice_txt"));

        horizontalLayout_2->addWidget(choice_txt);

        choice_go = new QPushButton(layoutWidget);
        choice_go->setObjectName(QStringLiteral("choice_go"));

        horizontalLayout_2->addWidget(choice_go);


        verticalLayout->addLayout(horizontalLayout_2);

        udp_txt = new QPlainTextEdit(layoutWidget);
        udp_txt->setObjectName(QStringLiteral("udp_txt"));

        verticalLayout->addWidget(udp_txt);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "\347\203\255\345\203\217\344\273\252\345\221\275\344\273\244", Q_NULLPTR));
        serial_go->setText(QApplication::translate("Widget", "\345\217\221\351\200\201", Q_NULLPTR));
        filter_go->setText(QApplication::translate("Widget", "\350\277\207\346\273\244", Q_NULLPTR));
        choice_txt->setText(QApplication::translate("Widget", "3,4,5,6,17,18,19,20,21", Q_NULLPTR));
        choice_go->setText(QApplication::translate("Widget", "\346\214\221\351\200\211", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
