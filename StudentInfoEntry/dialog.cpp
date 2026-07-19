#include "dialog.h"
#include <QMessageBox>
#include <QFont>
#include <QFrame>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setWindowTitle("学生信息录入与显示");

    // 连接自定义信号和槽 —— 当列表满10条时触发
    connect(this, SIGNAL(listFull()), this, SLOT(onListFull()));

    // 连接双击删除
    connect(m_listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(onListDoubleClicked(QListWidgetItem*)));
}

Dialog::~Dialog()
{
}

void Dialog::setupUI()
{
    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 标题
    QLabel *titleLabel = new QLabel("学生信息录入与显示", this);
    QFont titleFont;
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // 信息输入区域 - 使用表单布局（QFormLayout）
    QGroupBox *inputGroup = new QGroupBox("请输入学生信息", this);
    QFormLayout *formLayout = new QFormLayout(inputGroup);

    // 姓名 - QLineEdit
    QLabel *nameLabel = new QLabel("姓名：", this);
    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setPlaceholderText("请输入姓名");
    m_nameEdit->setMinimumHeight(30);
    formLayout->addRow(nameLabel, m_nameEdit);

    // 性别 - QGroupBox + QRadioButton
    QLabel *genderLabel = new QLabel("性别：", this);
    m_genderGroup = new QGroupBox(this);
    QHBoxLayout *genderLayout = new QHBoxLayout(m_genderGroup);
    m_radioMale = new QRadioButton("男", this);
    m_radioFemale = new QRadioButton("女", this);
    m_radioMale->setChecked(true);  // 默认选中男
    genderLayout->addWidget(m_radioMale);
    genderLayout->addWidget(m_radioFemale);
    genderLayout->addStretch();
    formLayout->addRow(genderLabel, m_genderGroup);

    // 年龄 - QSpinBox（范围0-120）
    QLabel *ageLabel = new QLabel("年龄：", this);
    m_ageSpinBox = new QSpinBox(this);
    m_ageSpinBox->setMinimum(0);
    m_ageSpinBox->setMaximum(120);
    m_ageSpinBox->setValue(18);
    m_ageSpinBox->setMinimumHeight(30);
    formLayout->addRow(ageLabel, m_ageSpinBox);

    // 学院 - QComboBox
    QLabel *collegeLabel = new QLabel("学院：", this);
    m_collegeCombo = new QComboBox(this);
    m_collegeCombo->addItem("请选择学院");
    m_collegeCombo->addItem("计算机与人工智能学院");
    m_collegeCombo->addItem("信息科学与技术学院");
    m_collegeCombo->addItem("机械工程学院");
    m_collegeCombo->addItem("电气工程学院");
    m_collegeCombo->addItem("土木工程学院");
    m_collegeCombo->addItem("经济管理学院");
    m_collegeCombo->addItem("外国语学院");
    m_collegeCombo->addItem("数学学院");
    m_collegeCombo->addItem("物理科学与技术学院");
    m_collegeCombo->setMinimumHeight(30);
    formLayout->addRow(collegeLabel, m_collegeCombo);

    mainLayout->addWidget(inputGroup);

    // 说明标签
    QLabel *infoLabel = new QLabel("说明：年龄可选范围0-120岁，双击列表项可删除该记录。", this);
    infoLabel->setStyleSheet("color: #666; font-size: 12px;");
    mainLayout->addWidget(infoLabel);

    // 水平分隔线
    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(line);

    // 操作按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    m_addButton = new QPushButton("添加", this);
    m_addButton->setMinimumHeight(35);
    m_addButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 14px;");

    m_aboutButton = new QPushButton("关于", this);
    m_aboutButton->setMinimumHeight(35);
    m_aboutButton->setStyleSheet("background-color: #2196F3; color: white; font-size: 14px;");

    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_aboutButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    // 信息显示列表 - QListWidget
    QLabel *listLabel = new QLabel("已录入学生信息：", this);
    QFont listFont;
    listFont.setPointSize(11);
    listFont.setBold(true);
    listLabel->setFont(listFont);
    mainLayout->addWidget(listLabel);

    m_listWidget = new QListWidget(this);
    m_listWidget->setMinimumHeight(200);
    m_listWidget->setStyleSheet("QListWidget { border: 1px solid #ccc; }"
                                "QListWidget::item { padding: 5px; }");
    mainLayout->addWidget(m_listWidget);

    // 信号槽连接：使用信号槽编辑器方式建立关联（代码方式实现）
    connect(m_addButton, SIGNAL(clicked()), this, SLOT(onAddClicked()));
    connect(m_aboutButton, SIGNAL(clicked()), this, SLOT(onAboutClicked()));

    setLayout(mainLayout);
    resize(500, 650);
}

void Dialog::onAddClicked()
{
    // 获取输入的姓名
    QString name = m_nameEdit->text().trimmed();

    // 验证姓名是否为空
    if (name.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入学生姓名！");
        m_nameEdit->setFocus();
        return;
    }

    // 检查学院是否选择
    if (m_collegeCombo->currentIndex() == 0) {
        QMessageBox::warning(this, "输入错误", "请选择学院！");
        return;
    }

    // 检查列表是否已达上限（>=10个）
    if (m_listWidget->count() >= 10) {
        // 发射自定义信号 listFull()
        emit listFull();
        return;
    }

    // 获取性别
    QString gender = m_radioMale->isChecked() ? "男" : "女";

    // 获取年龄
    int age = m_ageSpinBox->value();

    // 获取学院
    QString college = m_collegeCombo->currentText();

    // 构造显示字符串
    QString studentInfo = QString("姓名：%1 | 性别：%2 | 年龄：%3岁 | 学院：%4")
                              .arg(name)
                              .arg(gender)
                              .arg(age)
                              .arg(college);

    // 添加到QListWidget
    m_listWidget->addItem(studentInfo);

    // 清空输入
    m_nameEdit->clear();
    m_ageSpinBox->setValue(18);
    m_collegeCombo->setCurrentIndex(0);
    m_radioMale->setChecked(true);
    m_nameEdit->setFocus();
}

void Dialog::onAboutClicked()
{
    // 弹出关于对话框，显示学号和姓名
    QMessageBox::about(this, "关于",
                       "学生信息录入系统\n\n"
                       "软件设计实习——第二讲");
}

void Dialog::onListDoubleClicked(QListWidgetItem *item)
{
    if (!item) return;

    // 确认是否删除
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
                                  QString("确定要删除该学生记录吗？\n\n%1").arg(item->text()),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 获取当前选中的行并删除
        int row = m_listWidget->currentRow();
        if (row >= 0) {
            delete m_listWidget->takeItem(row);
        }
    }
}

void Dialog::onListFull()
{
    // 自定义信号关联的槽函数：弹出警告对话框
    QMessageBox::warning(this, "提示",
                         "条目数已达10个最大值！\n"
                         "请先删除已有记录再添加。");
}
