/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLineEdit *m_nameEdit;
    QGroupBox *m_genderGroup;
    QRadioButton *m_radioMale;
    QRadioButton *m_radioFemale;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(500, 650);
        m_nameEdit = new QLineEdit(Dialog);
        m_nameEdit->setObjectName("m_nameEdit");
        m_nameEdit->setGeometry(QRect(100, 70, 191, 31));
        m_genderGroup = new QGroupBox(Dialog);
        m_genderGroup->setObjectName("m_genderGroup");
        m_genderGroup->setGeometry(QRect(100, 110, 191, 51));
        m_radioMale = new QRadioButton(m_genderGroup);
        m_radioMale->setObjectName("m_radioMale");
        m_radioMale->setGeometry(QRect(10, 10, 61, 20));
        m_radioMale->setChecked(true);
        m_radioFemale = new QRadioButton(m_genderGroup);
        m_radioFemale->setObjectName("m_radioFemale");
        m_radioFemale->setGeometry(QRect(90, 10, 61, 20));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "2025112454-\346\234\261\351\233\205\346\226\260-\345\255\246\347\224\237\344\277\241\346\201\257\345\275\225\345\205\245\344\270\216\346\230\276\347\244\272", nullptr));
        m_nameEdit->setPlaceholderText(QCoreApplication::translate("Dialog", "\350\257\267\350\276\223\345\205\245\345\247\223\345\220\215", nullptr));
        m_genderGroup->setTitle(QString());
        m_radioMale->setText(QCoreApplication::translate("Dialog", "\347\224\267", nullptr));
        m_radioFemale->setText(QCoreApplication::translate("Dialog", "\345\245\263", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
