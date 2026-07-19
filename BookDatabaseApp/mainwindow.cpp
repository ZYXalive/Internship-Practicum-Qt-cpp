#include "mainwindow.h"
#include "adddialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QLabel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("图书数据库管理系统");
    resize(750, 650);

    initDatabase();
    setupModel();

    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // 操作按钮区域
    QGroupBox *ctrlGroup = new QGroupBox("数据库操作", central);
    QHBoxLayout *ctrlLayout = new QHBoxLayout(ctrlGroup);

    btnAdd = new QPushButton("增加记录", ctrlGroup);
    btnDelete = new QPushButton("删除记录", ctrlGroup);

    comboSort = new QComboBox(ctrlGroup);
    comboSort->addItem("-- 排序字段 --");
    comboSort->addItem("书名");
    comboSort->addItem("著者");
    comboSort->addItem("价格");
    comboSort->addItem("出版社");

    ctrlLayout->addWidget(btnAdd);
    ctrlLayout->addWidget(btnDelete);
    ctrlLayout->addStretch();
    ctrlLayout->addWidget(comboSort);

    ctrlGroup->setLayout(ctrlLayout);

    // 表格视图
    tableView = new QTableView(central);
    tableView->setModel(model);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setAlternatingRowColors(true);
    tableView->setColumnHidden(0, true);

    // 数据映射区域 —— 通过 QDataWidgetMapper 将数据表字段映射到表单控件
    QGroupBox *mapGroup = new QGroupBox("数据映射（QDataWidgetMapper）", central);
    QFormLayout *mapForm = new QFormLayout(mapGroup);

    editMapTitle = new QLineEdit(mapGroup);
    editMapAuthor = new QLineEdit(mapGroup);
    spinMapPrice = new QDoubleSpinBox(mapGroup);
    spinMapPrice->setRange(0.0, 999999.99);
    spinMapPrice->setDecimals(2);
    spinMapPrice->setPrefix("¥ ");
    editMapPublisher = new QLineEdit(mapGroup);

    mapForm->addRow("书名:", editMapTitle);
    mapForm->addRow("著者:", editMapAuthor);
    mapForm->addRow("价格:", spinMapPrice);
    mapForm->addRow("出版社:", editMapPublisher);

    // 导航与提交按钮
    QHBoxLayout *navLayout = new QHBoxLayout();
    btnPrev = new QPushButton("上一条", mapGroup);
    btnNext = new QPushButton("下一条", mapGroup);
    btnSubmitMap = new QPushButton("提交修改", mapGroup);
    labelNav = new QLabel(mapGroup);

    navLayout->addWidget(btnPrev);
    navLayout->addWidget(btnNext);
    navLayout->addWidget(labelNav);
    navLayout->addStretch();
    navLayout->addWidget(btnSubmitMap);

    mapForm->addRow(navLayout);

    mapGroup->setLayout(mapForm);

    mainLayout->addWidget(ctrlGroup);
    mainLayout->addWidget(tableView, 2);
    mainLayout->addWidget(mapGroup);

    // 设置 QDataWidgetMapper
    setupMapper();

    // 连接信号与槽
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAdd);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDelete);
    connect(comboSort, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onSort);
    connect(btnPrev, &QPushButton::clicked, this, &MainWindow::onPrevRecord);
    connect(btnNext, &QPushButton::clicked, this, &MainWindow::onNextRecord);
    connect(btnSubmitMap, &QPushButton::clicked, this, &MainWindow::onSubmitMapping);
    connect(tableView->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &MainWindow::onTableSelectionChanged);
}

MainWindow::~MainWindow()
{
    db.close();
}

void MainWindow::initDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("books.db");

    if (!db.open()) {
        qDebug() << "数据库打开失败:" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
    bool ok = query.exec(
        "CREATE TABLE IF NOT EXISTS Book ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title VARCHAR(100) NOT NULL, "
        "author VARCHAR(50) NOT NULL, "
        "price REAL NOT NULL, "
        "publisher VARCHAR(100) NOT NULL)"
    );

    if (!ok) {
        qDebug() << "建表失败:" << query.lastError().text();
        return;
    }

    query.exec("SELECT COUNT(*) FROM Book");
    query.next();
    if (query.value(0).toInt() == 0) {
        query.exec("INSERT INTO Book(title, author, price, publisher) "
                    "VALUES ('Qt C++编程指南', '张三', 59.80, '清华大学出版社')");
        query.exec("INSERT INTO Book(title, author, price, publisher) "
                    "VALUES ('数据结构与算法', '李四', 45.00, '人民邮电出版社')");
        query.exec("INSERT INTO Book(title, author, price, publisher) "
                    "VALUES ('计算机组成原理', '王五', 38.50, '机械工业出版社')");
        query.exec("INSERT INTO Book(title, author, price, publisher) "
                    "VALUES ('操作系统概论', '赵六', 52.00, '电子工业出版社')");
        query.exec("INSERT INTO Book(title, author, price, publisher) "
                    "VALUES ('计算机网络', '孙七', 65.00, '高等教育出版社')");
    }
}

void MainWindow::setupModel()
{
    model = new QSqlTableModel(this, db);
    model->setTable("Book");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(1, Qt::Horizontal, "书名");
    model->setHeaderData(2, Qt::Horizontal, "著者");
    model->setHeaderData(3, Qt::Horizontal, "价格");
    model->setHeaderData(4, Qt::Horizontal, "出版社");
    model->select();
}

void MainWindow::setupMapper()
{
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    // 将数据库字段映射到表单控件
    mapper->addMapping(editMapTitle, model->fieldIndex("title"));
    mapper->addMapping(editMapAuthor, model->fieldIndex("author"));
    mapper->addMapping(spinMapPrice, model->fieldIndex("price"));
    mapper->addMapping(editMapPublisher, model->fieldIndex("publisher"));

    mapper->toFirst();
}

void MainWindow::onTableSelectionChanged()
{
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        mapper->setCurrentIndex(index.row());
        labelNav->setText(QString("第 %1 / %2 条")
            .arg(index.row() + 1).arg(model->rowCount()));
    }
}

void MainWindow::onPrevRecord()
{
    int row = mapper->currentIndex();
    if (row > 0) {
        mapper->setCurrentIndex(row - 1);
        tableView->selectRow(row - 1);
        labelNav->setText(QString("第 %1 / %2 条")
            .arg(row).arg(model->rowCount()));
    }
}

void MainWindow::onNextRecord()
{
    int row = mapper->currentIndex();
    if (row < model->rowCount() - 1) {
        mapper->setCurrentIndex(row + 1);
        tableView->selectRow(row + 1);
        labelNav->setText(QString("第 %1 / %2 条")
            .arg(row + 2).arg(model->rowCount()));
    }
}

void MainWindow::onSubmitMapping()
{
    if (mapper->submit()) {
        model->submitAll();
        model->select();
        mapper->toFirst();
        QMessageBox::information(this, "提示", "映射数据修改已提交！");
    } else {
        QMessageBox::warning(this, "错误", "提交失败: " + model->lastError().text());
    }
}

void MainWindow::onAdd()
{
    AddDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        QSqlRecord record = model->record();
        record.setValue("title", dlg.bookTitle());
        record.setValue("author", dlg.author());
        record.setValue("price", dlg.price());
        record.setValue("publisher", dlg.publisher());

        if (model->insertRecord(-1, record)) {
            model->submitAll();
            model->select();
        } else {
            QMessageBox::warning(this, "错误",
                "添加记录失败: " + model->lastError().text());
        }
    }
}

void MainWindow::onDelete()
{
    QModelIndex index = tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::information(this, "提示", "请先选择一条记录！");
        return;
    }

    int ret = QMessageBox::question(this, "确认删除",
        "确定要删除选中的记录吗？",
        QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes) {
        model->removeRow(index.row());
        model->submitAll();
        model->select();
    }
}

void MainWindow::onSort(int index)
{
    if (index == 0) return;

    QString field;
    switch (index) {
    case 1: field = "title"; break;
    case 2: field = "author"; break;
    case 3: field = "price"; break;
    case 4: field = "publisher"; break;
    }

    model->setSort(model->fieldIndex(field), Qt::AscendingOrder);
    model->select();
}
