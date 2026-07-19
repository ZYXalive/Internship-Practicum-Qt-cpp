#include "mainwindow.h"

#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("2025112454-朱雅新-文件列表查看器");
    resize(700, 500);

    currentFont = QFont("Microsoft YaHei", 10);
    textColor = Qt::black;
    backgroundColor = Qt::white;

    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    // 左侧按钮区域
    QGroupBox *btnGroup = new QGroupBox("操作面板", central);
    QVBoxLayout *btnLayout = new QVBoxLayout(btnGroup);

    btnOpenFile = new QPushButton("打开文件", btnGroup);
    btnSetFont = new QPushButton("设置字体", btnGroup);
    btnSetTextColor = new QPushButton("设置文字颜色", btnGroup);
    btnSetBackgroundColor = new QPushButton("设置背景颜色", btnGroup);
    btnExit = new QPushButton("退出", btnGroup);

    btnLayout->addWidget(btnOpenFile);
    btnLayout->addWidget(btnSetFont);
    btnLayout->addWidget(btnSetTextColor);
    btnLayout->addWidget(btnSetBackgroundColor);
    btnLayout->addStretch();
    btnLayout->addWidget(btnExit);

    btnGroup->setLayout(btnLayout);

    // 右侧 QListView
    QGroupBox *listGroup = new QGroupBox("文件列表", central);
    QVBoxLayout *listLayout = new QVBoxLayout(listGroup);

    listView = new QListView(listGroup);
    model = new QStringListModel(this);
    model->setStringList(fileList);
    listView->setModel(model);

    listLayout->addWidget(listView);
    listGroup->setLayout(listLayout);

    mainLayout->addWidget(btnGroup, 1);
    mainLayout->addWidget(listGroup, 3);

    // 信号和槽连接 - 使用 lambda 避免 Qt6 clicked(bool) 签名匹配问题
    connect(btnOpenFile, &QPushButton::clicked, this, [this]() { onOpenFile(); });
    connect(btnSetFont, &QPushButton::clicked, this, [this]() { onSetFont(); });
    connect(btnSetTextColor, &QPushButton::clicked, this, [this]() { onSetTextColor(); });
    connect(btnSetBackgroundColor, &QPushButton::clicked, this, [this]() { onSetBackgroundColor(); });
    connect(btnExit, &QPushButton::clicked, this, [this]() { onExit(); });

    updateStyleSheet();
}

MainWindow::~MainWindow() {}

void MainWindow::onOpenFile()
{
    QStringList files = QFileDialog::getOpenFileNames(
        this, "选择文件", "",
        "所有文件 (*.*);;文本文件 (*.txt);;C++源文件 (*.cpp *.h)");

    if (!files.isEmpty()) {
        fileList.append(files);
        model->setStringList(fileList);
    }
}

void MainWindow::onSetFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, currentFont, this, "选择字体");
    if (ok) {
        currentFont = font;
        updateStyleSheet();
    }
}

void MainWindow::onSetTextColor()
{
    QColor color = QColorDialog::getColor(textColor, this, "选择文字颜色");
    if (color.isValid()) {
        textColor = color;
        updateStyleSheet();
    }
}

void MainWindow::onSetBackgroundColor()
{
    QColor color = QColorDialog::getColor(backgroundColor, this, "选择背景颜色");
    if (color.isValid()) {
        backgroundColor = color;
        updateStyleSheet();
    }
}

void MainWindow::onExit()
{
    close();
}

void MainWindow::updateStyleSheet()
{
    QString stylePart;
    if (currentFont.italic())
        stylePart += "italic ";
    if (currentFont.bold())
        stylePart += "bold ";

    QString fontCSS = QString("%1%2pt \"%3\"")
        .arg(stylePart)
        .arg(currentFont.pointSize())
        .arg(currentFont.family());

    QString styleSheet = QString(
        "QListView {"
        "  font: %1;"
        "  color: %2;"
        "  background-color: %3;"
        "}"
        "QListView::item:selected {"
        "  color: %4;"
        "}"
    ).arg(fontCSS)
     .arg(textColor.name())
     .arg(backgroundColor.name())
     .arg(textColor.name());

    listView->setStyleSheet(styleSheet);
}
