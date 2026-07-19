#include "adddialog.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

AddDialog::AddDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("添加新图书记录");
    setFixedSize(350, 250);

    QFormLayout *formLayout = new QFormLayout();

    editTitle = new QLineEdit(this);
    editAuthor = new QLineEdit(this);
    spinPrice = new QDoubleSpinBox(this);
    spinPrice->setRange(0.0, 999999.99);
    spinPrice->setDecimals(2);
    spinPrice->setPrefix("¥ ");
    editPublisher = new QLineEdit(this);

    formLayout->addRow("书名:", editTitle);
    formLayout->addRow("著者:", editAuthor);
    formLayout->addRow("价格:", spinPrice);
    formLayout->addRow("出版社:", editPublisher);

    btnOk = new QPushButton("确定", this);
    btnCancel = new QPushButton("取消", this);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnOk);
    btnLayout->addWidget(btnCancel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);

    connect(btnOk, &QPushButton::clicked, this, &AddDialog::onConfirm);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

QString AddDialog::bookTitle() const { return editTitle->text(); }
QString AddDialog::author() const { return editAuthor->text(); }
double AddDialog::price() const { return spinPrice->value(); }
QString AddDialog::publisher() const { return editPublisher->text(); }

void AddDialog::onConfirm()
{
    if (editTitle->text().isEmpty() || editAuthor->text().isEmpty()
        || editPublisher->text().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "所有字段不能为空！");
        return;
    }
    if (spinPrice->value() <= 0.0) {
        QMessageBox::warning(this, "输入错误", "价格必须大于0！");
        return;
    }
    accept();
}
