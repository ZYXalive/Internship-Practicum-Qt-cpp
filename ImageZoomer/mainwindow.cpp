#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QStyle>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPainter>
#include <QFont>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), imageVisible(false), currentZoom(1.0)
{
    // 创建测试图片（如果无外部图片，先生成一个）
    originalPixmap = QPixmap(400, 300);
    originalPixmap.fill(Qt::white);
    {
        QPainter painter(&originalPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        // 绘制一个测试图案
        painter.setBrush(Qt::blue);
        painter.drawRect(50, 50, 300, 200);

        painter.setPen(Qt::white);
        QFont font("Microsoft YaHei", 20);
        painter.setFont(font);
        painter.drawText(originalPixmap.rect(), Qt::AlignCenter, "测试图片\nTest Image");

        painter.setPen(Qt::red);
        painter.setBrush(Qt::green);
        painter.drawEllipse(100, 80, 60, 60);
        painter.drawEllipse(240, 80, 60, 60);

        painter.setBrush(Qt::yellow);
        painter.drawChord(130, 160, 140, 80, 30 * 16, 300 * 16);
    }
    // 保存图片以供后续使用
    originalPixmap.save("test_image.png");

    // 中心部件 - 放在滚动区域中
    imageLabel = new QLabel;
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(200, 200);
    imageLabel->setFrameShape(QFrame::StyledPanel);
    imageLabel->setText(tr("点击 \"显示\" 查看图片"));
    imageLabel->setStyleSheet("QLabel { background-color: #f0f0f0; font-size: 16px; }");

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(imageLabel);
    scrollArea->setWidgetResizable(true);
    setCentralWidget(scrollArea);

    createActions();
    createMenus();
    createToolBar();
    createDockWidget();
    createStatusBar();

    setWindowTitle(tr("2025112454-朱雅新-图片查看器"));
    resize(900, 700);

    updateStatusBar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    // 显示/隐藏 动作
    toggleAct = new QAction(style()->standardIcon(QStyle::SP_ComputerIcon), tr("显示"), this);
    toggleAct->setShortcut(QKeySequence(tr("Ctrl+D")));
    toggleAct->setStatusTip(tr("显示图片"));
    connect(toggleAct, &QAction::triggered, this, &MainWindow::toggleImage);

    // 放大
    zoomInAct = new QAction(style()->standardIcon(QStyle::SP_ArrowUp), tr("放大"), this);
    zoomInAct->setShortcut(QKeySequence(tr("Ctrl++")));
    zoomInAct->setStatusTip(tr("放大图片"));
    connect(zoomInAct, &QAction::triggered, this, &MainWindow::zoomIn);

    // 缩小
    zoomOutAct = new QAction(style()->standardIcon(QStyle::SP_ArrowDown), tr("缩小"), this);
    zoomOutAct->setShortcut(QKeySequence(tr("Ctrl+-")));
    zoomOutAct->setStatusTip(tr("缩小图片"));
    connect(zoomOutAct, &QAction::triggered, this, &MainWindow::zoomOut);

    // 复原
    zoomResetAct = new QAction(style()->standardIcon(QStyle::SP_BrowserReload), tr("复原"), this);
    zoomResetAct->setShortcut(QKeySequence(tr("Ctrl+R")));
    zoomResetAct->setStatusTip(tr("恢复原始尺寸"));
    connect(zoomResetAct, &QAction::triggered, this, &MainWindow::zoomReset);
}

void MainWindow::createMenus()
{
    // 位图菜单
    QMenu *bitmapMenu = menuBar()->addMenu(tr("位图(&B)"));
    bitmapMenu->addAction(toggleAct);

    // 缩放菜单
    QMenu *zoomMenu = menuBar()->addMenu(tr("缩放(&Z)"));
    zoomMenu->addAction(zoomInAct);
    zoomMenu->addAction(zoomOutAct);
    zoomMenu->addAction(zoomResetAct);
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar(tr("工具栏"));
    toolBar->addAction(toggleAct);
    toolBar->addAction(zoomInAct);
    toolBar->addAction(zoomOutAct);
    toolBar->addAction(zoomResetAct);
}

void MainWindow::createDockWidget()
{
    dockWidget = new QDockWidget(tr("缩放设置"), this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QWidget *dockContent = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel(tr("缩放比例："));
    label->setStyleSheet("font-size: 14px;");

    zoomSpinBox = new QDoubleSpinBox;
    zoomSpinBox->setRange(0.1, 1.0);
    zoomSpinBox->setSingleStep(0.1);
    zoomSpinBox->setValue(0.8);
    zoomSpinBox->setDecimals(1);
    zoomSpinBox->setPrefix(tr("比例: "));
    zoomSpinBox->setSuffix(tr(" 倍"));
    zoomSpinBox->setStyleSheet("font-size: 14px; padding: 4px;");

    QLabel *hintLabel = new QLabel(tr("（0.1 - 1.0 倍）"));
    hintLabel->setStyleSheet("color: gray; font-size: 12px;");

    // 连接值变化信号更新状态栏
    connect(zoomSpinBox, &QDoubleSpinBox::valueChanged,
            this, &MainWindow::updateStatusBar);

    layout->addWidget(label);
    layout->addWidget(zoomSpinBox);
    layout->addWidget(hintLabel);
    layout->addStretch();

    dockContent->setLayout(layout);
    dockWidget->setWidget(dockContent);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("就绪 — 缩放因子: %1").arg(currentZoom, 0, 'f', 1));
}

void MainWindow::toggleImage()
{
    imageVisible = !imageVisible;
    if (imageVisible) {
        toggleAct->setText(tr("隐藏"));
        toggleAct->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
        toggleAct->setStatusTip(tr("隐藏图片"));
        updateImage();
    } else {
        toggleAct->setText(tr("显示"));
        toggleAct->setIcon(style()->standardIcon(QStyle::SP_ComputerIcon));
        toggleAct->setStatusTip(tr("显示图片"));
        imageLabel->clear();
        imageLabel->setText(tr("图片已隐藏"));
    }
    updateStatusBar();
}

void MainWindow::zoomIn()
{
    if (!imageVisible || originalPixmap.isNull()) return;

    double step = zoomSpinBox->value();
    currentZoom += step;
    if (currentZoom > 5.0) currentZoom = 5.0; // 限制最大放大倍数
    updateImage();
    updateStatusBar();
}

void MainWindow::zoomOut()
{
    if (!imageVisible || originalPixmap.isNull()) return;

    double step = zoomSpinBox->value();
    currentZoom -= step;
    if (currentZoom < 0.1) currentZoom = 0.1; // 限制最小缩小倍数
    updateImage();
    updateStatusBar();
}

void MainWindow::zoomReset()
{
    currentZoom = 1.0;
    if (imageVisible && !originalPixmap.isNull()) {
        updateImage();
    }
    updateStatusBar();
}

void MainWindow::updateImage()
{
    if (originalPixmap.isNull()) return;

    QSize newSize = originalPixmap.size() * currentZoom;
    QPixmap scaled = originalPixmap.scaled(newSize, Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation);
    imageLabel->setPixmap(scaled);
}

void MainWindow::updateStatusBar()
{
    QString state;
    if (imageVisible) {
        state = tr("可见");
    } else {
        state = tr("隐藏");
    }

    double step = zoomSpinBox ? zoomSpinBox->value() : 0.8;
    statusBar()->showMessage(
        tr("图片: %1 | 当前缩放: %2倍 | 缩放步长: %3倍")
            .arg(state)
            .arg(currentZoom, 0, 'f', 2)
            .arg(step, 0, 'f', 1)
    );
}
