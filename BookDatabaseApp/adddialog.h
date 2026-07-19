#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent = nullptr);

    QString bookTitle() const;
    QString author() const;
    double price() const;
    QString publisher() const;

private slots:
    void onConfirm();

private:
    QLineEdit *editTitle;
    QLineEdit *editAuthor;
    QDoubleSpinBox *spinPrice;
    QLineEdit *editPublisher;
    QPushButton *btnOk;
    QPushButton *btnCancel;
};

#endif // ADDDIALOG_H
