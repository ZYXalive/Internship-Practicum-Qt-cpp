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
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLineEdit *m_inputEdit;
    QLineEdit *m_resultEdit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(350, 500);
        m_inputEdit = new QLineEdit(Dialog);
        m_inputEdit->setObjectName("m_inputEdit");
        m_inputEdit->setGeometry(QRect(20, 50, 310, 35));
        m_inputEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_resultEdit = new QLineEdit(Dialog);
        m_resultEdit->setObjectName("m_resultEdit");
        m_resultEdit->setGeometry(QRect(20, 110, 310, 35));
        m_resultEdit->setReadOnly(true);
        m_resultEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "2025112454-\346\234\261\351\233\205\346\226\260-\350\277\233\345\210\266\350\275\254\346\215\242\345\231\250", nullptr));
        m_inputEdit->setText(QCoreApplication::translate("Dialog", "0", nullptr));
        m_resultEdit->setText(QCoreApplication::translate("Dialog", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
