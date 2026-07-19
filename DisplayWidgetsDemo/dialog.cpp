#include "dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QFont>
#include <QTimer>
#include <QPixmap>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QCoreApplication>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setWindowTitle("2025112454-朱雅新-显示部件演示");
    resize(700, 600);
}

Dialog::~Dialog()
{
    if (m_movie) {
        m_movie->stop();
    }
}

// 向上逐级搜索文件，解决Qt Creator影子构建时CWD不在源码目录的问题
static QString findFile(const QString &fileName)
{
    // 1. 当前工作目录
    if (QFileInfo::exists(fileName))
        return fileName;

    // 2. 从当前目录逐级向父目录搜索（最多5层）
    QDir dir = QDir::currentPath();
    for (int i = 0; i < 5; i++) {
        if (QFileInfo::exists(dir.absoluteFilePath(fileName)))
            return dir.absoluteFilePath(fileName);

        // 同时检查当前目录的所有子目录（匹配项目文件夹名如"实习题目2_显示部件"）
        for (const QFileInfo &entry : dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
            QString subPath = entry.absoluteFilePath() + "/" + fileName;
            if (QFileInfo::exists(subPath))
                return subPath;
        }

        if (!dir.cdUp())
            break;
    }

    // 3. 可执行文件所在目录
    QString appPath = QCoreApplication::applicationDirPath() + "/" + fileName;
    if (QFileInfo::exists(appPath))
        return appPath;

    qDebug() << "找不到文件:" << fileName << "  CWD:" << QDir::currentPath();
    return fileName;
}

void Dialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 标题
    QLabel *titleLabel = new QLabel("显示部件演示", this);
    QFont titleFont;
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // 使用标签页组织不同部件
    m_tabWidget = new QTabWidget(this);

    // ---- 标签页1：图片与动画 ----
    QWidget *tab1 = new QWidget();
    QVBoxLayout *tab1Layout = new QVBoxLayout(tab1);

    // 图片标签
    QGroupBox *imageGroup = new QGroupBox("图片标签 (QLabel + QPixmap)");
    QVBoxLayout *imageLayout = new QVBoxLayout(imageGroup);

    m_imageLabel = new QLabel(this);
    m_imageLabel->setFixedSize(200, 200);
    m_imageLabel->setAlignment(Qt::AlignCenter);
    m_imageLabel->setScaledContents(true);  // 图片自动缩放铺满整个label
    m_imageLabel->setStyleSheet("border: 1px solid #ccc; background-color: #f9f9f9;");
    m_imageLabel->setText("图片显示区域\n(请将图片文件放在程序目录下)");
    QString imgPath = findFile("image.jpg");
    QPixmap pixmap(imgPath);
    if (!pixmap.isNull()) {
        m_imageLabel->setPixmap(pixmap);
    }
    imageLayout->addWidget(m_imageLabel);
    tab1Layout->addWidget(imageGroup);

    // 动画标签
    QGroupBox *animGroup = new QGroupBox("动画标签 (QLabel + QMovie)");
    QVBoxLayout *animLayout = new QVBoxLayout(animGroup);

    m_animationLabel = new QLabel(this);
    m_animationLabel->setFixedSize(200, 150);
    m_animationLabel->setAlignment(Qt::AlignCenter);
    m_animationLabel->setStyleSheet("border: 1px solid #ccc; background-color: #f9f9f9;");
    m_animationLabel->setText("动画显示区域\n(请将GIF文件放在程序目录下)");

    // 尝试加载GIF动画
    m_movie = new QMovie(findFile("animation.gif"));
    if (m_movie->isValid()) {
        m_animationLabel->setMovie(m_movie);
        m_movie->start();
    }
    animLayout->addWidget(m_animationLabel);
    tab1Layout->addWidget(animGroup);

    tab1Layout->addStretch();
    m_tabWidget->addTab(tab1, "图片 & 动画");

    // ---- 标签页2：文本浏览器与日历 ----
    QWidget *tab2 = new QWidget();
    QHBoxLayout *tab2Layout = new QHBoxLayout(tab2);

    // 文本浏览器
    QGroupBox *textGroup = new QGroupBox("文本浏览器 (QTextBrowser)");
    QVBoxLayout *textLayout = new QVBoxLayout(textGroup);

    m_textBrowser = new QTextBrowser(this);
    m_textBrowser->setHtml("<h2>欢迎使用显示部件演示</h2>"
                           "<p>这是一个 <b>QTextBrowser</b> 文本浏览器。</p>"
                           "<p>它可以显示 <font color='red'>富文本</font> 内容，</p>"
                           "<ul>"
                           "<li>HTML 格式</li>"
                           "<li>图片嵌入</li>"
                           "<li>超链接</li>"
                           "</ul>");
    m_textBrowser->setMinimumWidth(250);
    textLayout->addWidget(m_textBrowser);
    tab2Layout->addWidget(textGroup);

    // 日历部件
    QGroupBox *calGroup = new QGroupBox("日历 (QCalendarWidget)");
    QVBoxLayout *calLayout = new QVBoxLayout(calGroup);

    m_calendar = new QCalendarWidget(this);
    m_calendar->setGridVisible(true);
    m_calendar->setMinimumDate(QDate(2020, 1, 1));
    m_calendar->setMaximumDate(QDate(2030, 12, 31));
    calLayout->addWidget(m_calendar);
    tab2Layout->addWidget(calGroup);

    m_tabWidget->addTab(tab2, "文本浏览器 & 日历");

    // ---- 标签页3：液晶数字 & 进度条 & 滑动部件 ----
    QWidget *tab3 = new QWidget();
    QVBoxLayout *tab3Layout = new QVBoxLayout(tab3);

    // 液晶数字
    QGroupBox *lcdGroup = new QGroupBox("液晶数字 (QLCDNumber)");
    QVBoxLayout *lcdLayout = new QVBoxLayout(lcdGroup);

    m_lcdNumber = new QLCDNumber(this);
    m_lcdNumber->setDigitCount(8);
    m_lcdNumber->display(20240714);
    m_lcdNumber->setMinimumHeight(60);
    lcdLayout->addWidget(m_lcdNumber);
    tab3Layout->addWidget(lcdGroup);

    // 进度条
    QGroupBox *progressGroup = new QGroupBox("进度条 (QProgressBar)");
    QVBoxLayout *progressLayout = new QVBoxLayout(progressGroup);

    m_progressBar = new QProgressBar(this);
    m_progressBar->setMinimum(0);
    m_progressBar->setMaximum(100);
    m_progressBar->setValue(50);
    m_progressBar->setTextVisible(true);
    m_progressBar->setMinimumHeight(30);
    progressLayout->addWidget(m_progressBar);
    tab3Layout->addWidget(progressGroup);

    // 水平滑动条
    QGroupBox *sliderGroup = new QGroupBox("滑动条 (QSlider & QScrollBar)");
    QVBoxLayout *sliderLayout = new QVBoxLayout(sliderGroup);

    QLabel *sliderLabel = new QLabel("QSlider 水平滑动条：");
    sliderLayout->addWidget(sliderLabel);

    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setMinimum(0);
    m_slider->setMaximum(100);
    m_slider->setValue(50);
    m_slider->setTickPosition(QSlider::TicksBelow);
    m_slider->setTickInterval(10);
    sliderLayout->addWidget(m_slider);

    QLabel *scrollLabel = new QLabel("QScrollBar 滚动条：");
    sliderLayout->addWidget(scrollLabel);

    m_scrollBar = new QScrollBar(Qt::Horizontal, this);
    m_scrollBar->setMinimum(0);
    m_scrollBar->setMaximum(100);
    m_scrollBar->setValue(30);
    sliderLayout->addWidget(m_scrollBar);

    tab3Layout->addWidget(sliderGroup);

    // 水平线 (QFrame)
    m_horizontalLine = new QFrame(this);
    m_horizontalLine->setFrameShape(QFrame::HLine);
    m_horizontalLine->setFrameShadow(QFrame::Sunken);
    m_horizontalLine->setStyleSheet("color: #999;");
    tab3Layout->addWidget(m_horizontalLine);

    // 滑动值和液晶数字的联动显示
    QLabel *valueLabel = new QLabel("拖动滑块或滚动条，液晶数字会同步变化：");
    tab3Layout->addWidget(valueLabel);

    tab3Layout->addStretch();
    m_tabWidget->addTab(tab3, "液晶数字 & 进度条 & 滑动部件");

    mainLayout->addWidget(m_tabWidget);

    // 信号槽连接
    connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(onSliderValueChanged(int)));
    connect(m_scrollBar, SIGNAL(valueChanged(int)), this, SLOT(onSliderValueChanged(int)));

    // 使用定时器模拟进度条更新
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onProgressUpdate()));
    timer->start(100);

    setLayout(mainLayout);
}

void Dialog::onSliderValueChanged(int value)
{
    m_lcdNumber->display(value);
    m_progressBar->setValue(value);
}

void Dialog::onProgressUpdate()
{
    // 进度条自动增减演示
    static int direction = 1;
    int currentValue = m_progressBar->value();
    if (currentValue >= 100) {
        direction = -1;
    } else if (currentValue <= 0) {
        direction = 1;
    }
    m_progressBar->setValue(currentValue + direction);
}
