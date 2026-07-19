#include "mainwindow.h"
#include "mdichild.h"

#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QMdiSubWindow>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea;
    mdiArea->setViewMode(QMdiArea::TabbedView);  // 使用标签页模式
    setCentralWidget(mdiArea);

    // 当没有子窗口时显示背景文字
    mdiArea->setBackground(Qt::lightGray);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    // 设置窗口属性
    setWindowTitle(tr("MDI记事本"));
    setMinimumSize(800, 600);
    resize(1000, 700);

    connect(mdiArea, &QMdiArea::subWindowActivated,
            this, &MainWindow::updateMenus);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    // 新建文件
    newAct = new QAction(style()->standardIcon(QStyle::SP_FileIcon), tr("新建(&N)"), this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setStatusTip(tr("创建一个新文件"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    // 打开文件
    openAct = new QAction(style()->standardIcon(QStyle::SP_DialogOpenButton), tr("打开(&O)..."), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("打开一个已有文件"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    // 保存
    saveAct = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), tr("保存(&S)"), this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setStatusTip(tr("保存当前文件"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    // 另存为
    saveAsAct = new QAction(tr("另存为(&A)..."), this);
    saveAsAct->setStatusTip(tr("以新文件名保存"));
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);

    // 退出
    exitAct = new QAction(tr("退出(&X)"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    exitAct->setStatusTip(tr("退出应用程序"));
    connect(exitAct, &QAction::triggered, qApp, &QApplication::closeAllWindows);

    // 剪切
    cutAct = new QAction(style()->standardIcon(QStyle::SP_CommandLink), tr("剪切(&T)"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setStatusTip(tr("剪切选中的内容到剪贴板"));
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);

    // 复制
    copyAct = new QAction(style()->standardIcon(QStyle::SP_FileDialogDetailedView), tr("复制(&C)"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setStatusTip(tr("复制选中的内容到剪贴板"));
    connect(copyAct, &QAction::triggered, this, &MainWindow::copy);

    // 粘贴
    pasteAct = new QAction(style()->standardIcon(QStyle::SP_FileDialogStart), tr("粘贴(&P)"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("从剪贴板粘贴内容"));
    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);

    // 关闭窗口
    closeAct = new QAction(tr("关闭(&C)"), this);
    closeAct->setShortcut(QKeySequence::Close);
    closeAct->setStatusTip(tr("关闭当前文档"));
    connect(closeAct, &QAction::triggered,
            mdiArea, &QMdiArea::closeActiveSubWindow);

    // 关闭全部
    closeAllAct = new QAction(tr("关闭全部(&L)"), this);
    closeAllAct->setStatusTip(tr("关闭所有文档"));
    connect(closeAllAct, &QAction::triggered,
            mdiArea, &QMdiArea::closeAllSubWindows);

    // 平铺
    tileAct = new QAction(tr("平铺(&T)"), this);
    tileAct->setStatusTip(tr("平铺显示所有窗口"));
    connect(tileAct, &QAction::triggered, mdiArea, &QMdiArea::tileSubWindows);

    // 层叠
    cascadeAct = new QAction(tr("层叠(&S)"), this);
    cascadeAct->setStatusTip(tr("层叠显示所有窗口"));
    connect(cascadeAct, &QAction::triggered,
            mdiArea, &QMdiArea::cascadeSubWindows);

    // 下一个
    nextAct = new QAction(tr("下一个(&X)"), this);
    nextAct->setShortcut(QKeySequence::NextChild);
    nextAct->setStatusTip(tr("切换到下一个子窗口"));
    connect(nextAct, &QAction::triggered,
            mdiArea, &QMdiArea::activateNextSubWindow);

    // 上一个
    previousAct = new QAction(tr("上一个(&R)"), this);
    previousAct->setShortcut(QKeySequence::PreviousChild);
    previousAct->setStatusTip(tr("切换到上一个子窗口"));
    connect(previousAct, &QAction::triggered,
            mdiArea, &QMdiArea::activatePreviousSubWindow);

    // 关于
    aboutAct = new QAction(tr("关于(&A)"), this);
    aboutAct->setStatusTip(tr("显示程序信息"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus()
{
    // 文件菜单
    fileMenu = menuBar()->addMenu(tr("文件(&F)"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    // 编辑菜单
    editMenu = menuBar()->addMenu(tr("编辑(&E)"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

    // 窗口菜单
    windowMenu = menuBar()->addMenu(tr("窗口(&W)"));
    updateWindowMenu();
    connect(windowMenu, &QMenu::aboutToShow, this, &MainWindow::updateWindowMenu);

    // 帮助菜单
    helpMenu = menuBar()->addMenu(tr("帮助(&H)"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::createToolBars()
{
    // 文件工具栏
    fileToolBar = addToolBar(tr("文件"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);

    // 编辑工具栏
    editToolBar = addToolBar(tr("编辑"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("就绪"));
}

void MainWindow::newFile()
{
    MdiChild *child = createMdiChild();
    child->newFile();
    child->show();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), QString(),
        tr("文本文件 (*.txt);;所有文件 (*)"));
    if (!fileName.isEmpty()) {
        QMdiSubWindow *existing = findMdiChild(fileName);
        if (existing) {
            mdiArea->setActiveSubWindow(existing);
            return;
        }
        MdiChild *child = createMdiChild();
        if (child->loadFile(fileName)) {
            statusBar()->showMessage(tr("文件已加载"), 2000);
            child->show();
        } else {
            child->close();
        }
    }
}

void MainWindow::save()
{
    MdiChild *child = activeMdiChild();
    if (child)
        child->save();
}

void MainWindow::saveAs()
{
    MdiChild *child = activeMdiChild();
    if (child)
        child->saveAs();
}

void MainWindow::cut()
{
    MdiChild *child = activeMdiChild();
    if (child)
        child->cut();
}

void MainWindow::copy()
{
    MdiChild *child = activeMdiChild();
    if (child)
        child->copy();
}

void MainWindow::paste()
{
    MdiChild *child = activeMdiChild();
    if (child)
        child->paste();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("关于MDI记事本"),
                       tr("Qt MDI多文档记事本应用程序\n"
                          "软件设计实习 - 第四次"));
}

void MainWindow::updateMenus()
{
    bool hasMdiChild = (activeMdiChild() != nullptr);
    saveAct->setEnabled(hasMdiChild);
    saveAsAct->setEnabled(hasMdiChild);
    cutAct->setEnabled(hasMdiChild);
    copyAct->setEnabled(hasMdiChild);
    pasteAct->setEnabled(hasMdiChild);
    closeAct->setEnabled(hasMdiChild);
    closeAllAct->setEnabled(hasMdiChild);
    tileAct->setEnabled(hasMdiChild);
    cascadeAct->setEnabled(hasMdiChild);
    nextAct->setEnabled(hasMdiChild);
    previousAct->setEnabled(hasMdiChild);
}

void MainWindow::updateWindowMenu()
{
    windowMenu->clear();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAct);
    windowMenu->addAction(previousAct);

    // 列出所有子窗口
    QList<QMdiSubWindow *> windows = mdiArea->subWindowList();
    separatorAct = windowMenu->addSeparator();

    for (int i = 0; i < windows.size(); ++i) {
        MdiChild *child = qobject_cast<MdiChild *>(windows.at(i)->widget());
        QString text;
        if (i < 9) {
            text = tr("&%1 %2").arg(i + 1)
                               .arg(child->userFriendlyCurrentFile());
        } else {
            text = tr("%1 %2").arg(i + 1)
                              .arg(child->userFriendlyCurrentFile());
        }
        QAction *action = windowMenu->addAction(text);
        action->setCheckable(true);
        action->setChecked(child == activeMdiChild());
        QMdiSubWindow *window = windows.at(i);
        connect(action, &QAction::triggered, this, [this, window]() {
            setActiveSubWindow(window);
        });
    }
}

MdiChild *MainWindow::createMdiChild()
{
    MdiChild *child = new MdiChild;
    mdiArea->addSubWindow(child);

    return child;
}

void MainWindow::switchLayoutDirection()
{
    if (layoutDirection() == Qt::LeftToRight)
        QApplication::setLayoutDirection(Qt::RightToLeft);
    else
        QApplication::setLayoutDirection(Qt::LeftToRight);
}

void MainWindow::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

MdiChild *MainWindow::activeMdiChild()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    if (activeSubWindow)
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    return nullptr;
}

QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName)
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    for (auto *window : mdiArea->subWindowList()) {
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
        if (mdiChild && mdiChild->currentFile() == canonicalFilePath)
            return window;
    }
    return nullptr;
}
