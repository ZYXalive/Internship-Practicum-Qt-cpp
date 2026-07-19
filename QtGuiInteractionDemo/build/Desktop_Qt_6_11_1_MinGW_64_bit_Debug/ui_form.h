/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QComboBox *comboBox;
    QFontComboBox *fontComboBox;
    QLineEdit *lineEdit;
    QTimeEdit *timeEdit;
    QDateEdit *dateEdit;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(360, 243);
        comboBox = new QComboBox(Form);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(30, 20, 81, 21));
        fontComboBox = new QFontComboBox(Form);
        fontComboBox->setObjectName("fontComboBox");
        fontComboBox->setGeometry(QRect(30, 60, 191, 22));
        lineEdit = new QLineEdit(Form);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(30, 100, 113, 20));
        timeEdit = new QTimeEdit(Form);
        timeEdit->setObjectName("timeEdit");
        timeEdit->setGeometry(QRect(30, 190, 118, 22));
        dateEdit = new QDateEdit(Form);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(30, 150, 110, 22));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
