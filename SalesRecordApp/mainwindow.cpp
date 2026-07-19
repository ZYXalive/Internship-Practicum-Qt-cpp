#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("销售记录管理系统");
    resize(550, 450);

    // 重置静态总营业额
    SalesRecord::resetTotalTurnover();

    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // 输入区域
    QGroupBox *inputGroup = new QGroupBox("销售记录添加", central);
    QFormLayout *formLayout = new QFormLayout(inputGroup);

    comboSalesperson = new QComboBox(inputGroup);
    comboSalesperson->addItem("售货员001");
    comboSalesperson->addItem("售货员002");
    comboSalesperson->addItem("售货员003");
    comboSalesperson->addItem("售货员004");
    comboSalesperson->addItem("售货员005");

    spinAmount = new QDoubleSpinBox(inputGroup);
    spinAmount->setRange(0.0, 9999999.99);
    spinAmount->setDecimals(2);
    spinAmount->setPrefix("¥ ");
    spinAmount->setValue(0.0);

    btnAdd = new QPushButton("添加记录", inputGroup);

    formLayout->addRow("售货员:", comboSalesperson);
    formLayout->addRow("销售金额:", spinAmount);
    formLayout->addRow("", btnAdd);

    inputGroup->setLayout(formLayout);

    // 记录显示区域
    QGroupBox *recordGroup = new QGroupBox("记录明细", central);
    QVBoxLayout *recordLayout = new QVBoxLayout(recordGroup);

    textRecords = new QTextEdit(recordGroup);
    textRecords->setReadOnly(true);

    labelTotal = new QLabel("销售总金额: ¥ 0.00", recordGroup);
    labelTotal->setStyleSheet("font-size: 14pt; font-weight: bold; color: red; padding: 8px;");

    recordLayout->addWidget(textRecords);
    recordLayout->addWidget(labelTotal);

    recordGroup->setLayout(recordLayout);

    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(recordGroup, 1);

    // 信号和槽连接
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAddRecord);
}

MainWindow::~MainWindow() {}

void MainWindow::onAddRecord()
{
    double amount = spinAmount->value();
    if (amount <= 0.0) {
        QMessageBox::warning(this, "输入错误", "销售金额必须大于0！");
        return;
    }

    QString salespersonId = comboSalesperson->currentText();
    SalesRecord record(salespersonId, amount);
    records.append(record);

    // 更新记录显示
    textRecords->append(record.toString());

    // 更新总金额显示
    labelTotal->setText(QString("销售总金额: ¥ %1")
        .arg(SalesRecord::totalTurnover(), 0, 'f', 2));

    // 重置输入
    spinAmount->setValue(0.0);
}
