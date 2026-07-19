#include "mainwindow.h"
#include "combodelegate.h"

#include <QAction>
#include <QApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QStatusBar>
#include <QStyle>
#include <QTextStream>
#include <QToolBar>
#include <QVBoxLayout>
#include <QSqlRecord>
#include <QDebug>
#include <QIntValidator>
#include <QPushButton>
#include <QStringConverter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 初始化数据库
    initDatabase();

    // 创建模型
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({tr("账号"), tr("用户"), tr("年龄")});

    // 创建视图
    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setAlternatingRowColors(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 设置自定义委托
    ComboDelegate *delegate = new ComboDelegate(this);
    tableView->setItemDelegate(delegate);

    setCentralWidget(tableView);

    // 加载数据
    loadData();

    createActions();
    createMenus();
    createToolBar();
    createStatusBar();

    setWindowTitle(tr("2025112454-朱雅新-StandardItemModel数据模型"));
    resize(800, 500);

    connect(model, &QStandardItemModel::itemChanged,
            this, &MainWindow::updateStatusBar);
}

MainWindow::~MainWindow()
{
    if (db.isOpen())
        db.close();
}

void MainWindow::initDatabase()
{
    // 使用SQLite数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("student.db");

    if (!db.open()) {
        QMessageBox::critical(this, tr("数据库错误"),
                              tr("无法打开数据库: %1").arg(db.lastError().text()));
        return;
    }

    // 创建表
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS student ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "age INTEGER NOT NULL DEFAULT 20)");

    // 插入初始数据（如果表为空）
    query.exec("SELECT COUNT(*) FROM student");
    if (query.next() && query.value(0).toInt() == 0) {
        query.exec("INSERT INTO student (name, age) VALUES ('张三', 20)");
        query.exec("INSERT INTO student (name, age) VALUES ('李四', 21)");
        query.exec("INSERT INTO student (name, age) VALUES ('王五', 22)");
        query.exec("INSERT INTO student (name, age) VALUES ('赵六', 19)");
        query.exec("INSERT INTO student (name, age) VALUES ('孙七', 23)");
    }
}

void MainWindow::loadData()
{
    model->removeRows(0, model->rowCount());

    QSqlQuery query(db);
    query.exec("SELECT id, name, age FROM student");

    int row = 0;
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        int age = query.value(2).toInt();

        QStandardItem *idItem = new QStandardItem(QString::number(id));
        idItem->setEditable(false); // ID不可编辑
        model->setItem(row, 0, idItem);

        QStandardItem *nameItem = new QStandardItem(name);
        model->setItem(row, 1, nameItem);

        QStandardItem *ageItem = new QStandardItem(QString::number(age));
        model->setItem(row, 2, ageItem);

        row++;
    }
}

void MainWindow::createActions()
{
    addAct = new QAction(style()->standardIcon(QStyle::SP_FileDialogNewFolder), tr("添加记录(&A)"), this);
    addAct->setShortcut(QKeySequence(tr("Ctrl+A")));
    addAct->setStatusTip(tr("打开对话框添加一条新记录（输入账号、姓名、年龄）"));
    connect(addAct, &QAction::triggered, this, &MainWindow::showAddDialog);

    deleteAct = new QAction(style()->standardIcon(QStyle::SP_TrashIcon), tr("删除记录(&D)"), this);
    deleteAct->setShortcut(QKeySequence(tr("Ctrl+D")));
    deleteAct->setStatusTip(tr("删除选中的记录"));
    connect(deleteAct, &QAction::triggered, this, &MainWindow::deleteRow);

    refreshAct = new QAction(style()->standardIcon(QStyle::SP_BrowserReload), tr("刷新(&R)"), this);
    refreshAct->setShortcut(QKeySequence::Refresh);
    refreshAct->setStatusTip(tr("从数据库重新加载数据"));
    connect(refreshAct, &QAction::triggered, this, &MainWindow::refreshData);

    importAct = new QAction(style()->standardIcon(QStyle::SP_DialogOpenButton), tr("导入(&I)..."), this);
    importAct->setShortcut(QKeySequence(tr("Ctrl+I")));
    importAct->setStatusTip(tr("从CSV文件导入数据到数据库"));
    connect(importAct, &QAction::triggered, this, &MainWindow::importFromFile);

    exportAct = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), tr("导出(&E)..."), this);
    exportAct->setShortcut(QKeySequence(tr("Ctrl+E")));
    exportAct->setStatusTip(tr("将数据库数据导出为CSV文件"));
    connect(exportAct, &QAction::triggered, this, &MainWindow::exportToFile);
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("文件(&F)"));
    fileMenu->addAction(importAct);
    fileMenu->addAction(exportAct);
    fileMenu->addSeparator();

    QMenu *dataMenu = menuBar()->addMenu(tr("数据(&D)"));
    dataMenu->addAction(addAct);
    dataMenu->addAction(deleteAct);
    dataMenu->addAction(refreshAct);
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar(tr("数据操作"));
    toolBar->addAction(addAct);
    toolBar->addAction(deleteAct);
    toolBar->addAction(refreshAct);
    toolBar->addSeparator();
    toolBar->addAction(importAct);
    toolBar->addAction(exportAct);
}

void MainWindow::createStatusBar()
{
    updateStatusBar();
}

// ============================================================
//  核心功能：显示添加对话框，供用户输入完整记录
// ============================================================
void MainWindow::showAddDialog()
{
    // 创建对话框
    QDialog dialog(this);
    dialog.setWindowTitle(tr("添加新记录"));
    dialog.setMinimumWidth(350);

    QFormLayout *formLayout = new QFormLayout(&dialog);

    QLineEdit *idEdit = new QLineEdit(&dialog);
    idEdit->setPlaceholderText(tr("输入账号（数字，可选，留空自动生成）"));
    idEdit->setValidator(new QIntValidator(1, 99999, idEdit));

    QLineEdit *nameEdit = new QLineEdit(&dialog);
    nameEdit->setPlaceholderText(tr("输入用户名"));

    QLineEdit *ageEdit = new QLineEdit(&dialog);
    ageEdit->setPlaceholderText(tr("输入年龄"));
    ageEdit->setValidator(new QIntValidator(1, 150, ageEdit));

    formLayout->addRow(tr("账号："), idEdit);
    formLayout->addRow(tr("姓名："), nameEdit);
    formLayout->addRow(tr("年龄："), ageEdit);

    // 按钮
    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    buttonBox->button(QDialogButtonBox::Ok)->setText(tr("确定"));
    buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));
    formLayout->addRow(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted)
        return;

    // 获取输入
    QString idStr = idEdit->text().trimmed();
    QString name = nameEdit->text().trimmed();
    QString ageStr = ageEdit->text().trimmed();

    // 验证
    if (name.isEmpty()) {
        QMessageBox::warning(this, tr("输入错误"), tr("姓名不能为空！"));
        return;
    }
    if (ageStr.isEmpty()) {
        QMessageBox::warning(this, tr("输入错误"), tr("年龄不能为空！"));
        return;
    }
    bool ageOk = false;
    int age = ageStr.toInt(&ageOk);
    if (!ageOk || age < 1 || age > 150) {
        QMessageBox::warning(this, tr("输入错误"), tr("请输入有效年龄（1-150）！"));
        return;
    }

    QSqlQuery query(db);

    if (!idStr.isEmpty()) {
        // 用户指定了账号，使用自定义ID插入
        bool idOk = false;
        int customId = idStr.toInt(&idOk);
        if (idOk) {
            query.prepare("INSERT INTO student (id, name, age) VALUES (?, ?, ?)");
            query.addBindValue(customId);
            query.addBindValue(name);
            query.addBindValue(age);
        }
    } else {
        query.prepare("INSERT INTO student (name, age) VALUES (?, ?)");
        query.addBindValue(name);
        query.addBindValue(age);
    }

    if (!query.exec()) {
        QMessageBox::critical(this, tr("数据库错误"),
                              tr("插入数据失败: %1").arg(query.lastError().text()));
        return;
    }

    // 重新加载数据
    loadData();
    tableView->scrollToBottom();
    updateStatusBar();

    statusBar()->showMessage(tr("已添加记录: %1, 年龄 %2").arg(name).arg(age), 3000);
}

// ============================================================
//  删除行
// ============================================================
void MainWindow::deleteRow()
{
    QModelIndex currentIndex = tableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::information(this, tr("提示"), tr("请先选择要删除的行"));
        return;
    }

    int row = currentIndex.row();
    int id = model->item(row, 0)->text().toInt();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, tr("确认删除"),
        tr("确定要删除账号为 %1 的记录吗？").arg(id),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query(db);
        query.exec(QString("DELETE FROM student WHERE id = %1").arg(id));

        // 从模型中移除行
        model->removeRow(row);
        updateStatusBar();
        statusBar()->showMessage(tr("已删除账号 %1").arg(id), 3000);
    }
}

// ============================================================
//  刷新数据
// ============================================================
void MainWindow::refreshData()
{
    loadData();
    updateStatusBar();
    statusBar()->showMessage(tr("数据已刷新"), 2000);
}

// ============================================================
//  从CSV文件导入数据
//  格式：每行一个记录，以逗号分隔：id,name,age 或 name,age
//  支持 UTF-8 和 GBK 编码
// ============================================================
void MainWindow::importFromFile()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, tr("导入数据"), QString(),
        tr("CSV文件 (*.csv);;文本文件 (*.txt);;所有文件 (*)"));

    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("文件错误"),
                              tr("无法打开文件: %1").arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    // 尝试UTF-8读取
    in.setEncoding(QStringConverter::Utf8);

    int successCount = 0;
    int failCount = 0;
    QSqlQuery query(db);
    db.transaction(); // 事务：要么全成功要么全回滚

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith('#'))  // 跳过空行和注释行
            continue;

        QStringList parts;
        // 兼容逗号和制表符分隔
        if (line.contains(','))
            parts = line.split(',');
        else if (line.contains('\t'))
            parts = line.split('\t');
        else
            continue;

        if (parts.size() < 2)
            continue;

        QString name = parts[parts.size() - 2].trimmed();
        QString ageStr = parts[parts.size() - 1].trimmed();

        if (name.isEmpty())
            continue;

        bool ageOk = false;
        int age = ageStr.toInt(&ageOk);
        if (!ageOk) age = 20;

        // 如果前面还有字段，视为自定义ID
        if (parts.size() >= 3) {
            bool idOk = false;
            int customId = parts[0].trimmed().toInt(&idOk);
            if (idOk) {
                // 检查ID是否已存在
                query.prepare("SELECT COUNT(*) FROM student WHERE id = ?");
                query.addBindValue(customId);
                query.exec();
                if (query.next() && query.value(0).toInt() == 0) {
                    query.prepare("INSERT INTO student (id, name, age) VALUES (?, ?, ?)");
                    query.addBindValue(customId);
                    query.addBindValue(name);
                    query.addBindValue(age);
                    if (query.exec())
                        successCount++;
                    else
                        failCount++;
                    continue;
                }
            }
        }

        // 无ID或ID冲突，自动生成
        query.prepare("INSERT INTO student (name, age) VALUES (?, ?)");
        query.addBindValue(name);
        query.addBindValue(age);
        if (query.exec())
            successCount++;
        else
            failCount++;
    }

    file.close();

    if (failCount > 0) {
        db.rollback(); // 导入失败时回滚
        QMessageBox::warning(this, tr("导入结果"),
                             tr("成功导入: %1 条\n导入失败: %2 条\n已回滚所有更改。")
                                 .arg(successCount).arg(failCount));
    } else {
        db.commit();
        loadData();
        updateStatusBar();
        statusBar()->showMessage(tr("成功导入 %1 条记录").arg(successCount), 5000);
        QMessageBox::information(this, tr("导入完成"),
                                 tr("成功导入 %1 条记录到数据库。").arg(successCount));
    }
}

// ============================================================
//  导出数据到CSV文件
// ============================================================
void MainWindow::exportToFile()
{
    QString filePath = QFileDialog::getSaveFileName(
        this, tr("导出数据"), "student_data.csv",
        tr("CSV文件 (*.csv);;文本文件 (*.txt);;所有文件 (*)"));

    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("文件错误"),
                              tr("无法写入文件: %1").arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    // 写入表头
    out << "账号,姓名,年龄\n";

    // 写入数据
    for (int row = 0; row < model->rowCount(); ++row) {
        QString id = model->item(row, 0) ? model->item(row, 0)->text() : "";
        QString name = model->item(row, 1) ? model->item(row, 1)->text() : "";
        QString age = model->item(row, 2) ? model->item(row, 2)->text() : "";
        out << id << "," << name << "," << age << "\n";
    }

    file.close();
    updateStatusBar();
    statusBar()->showMessage(tr("已导出 %1 条记录到 %2").arg(model->rowCount()).arg(filePath), 5000);

    QMessageBox::information(this, tr("导出完成"),
                             tr("成功导出 %1 条记录到文件:\n%2")
                                 .arg(model->rowCount()).arg(filePath));
}

void MainWindow::updateStatusBar()
{
    statusBar()->showMessage(
        tr("数据库: student.db | 记录数: %1 条")
            .arg(model->rowCount()));
}
