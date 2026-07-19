#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTextBrowser>
#include <QCalendarWidget>
#include <QLCDNumber>
#include <QProgressBar>
#include <QSlider>
#include <QFrame>
#include <QMovie>
#include <QTabWidget>
#include <QScrollBar>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void onSliderValueChanged(int value);
    void onProgressUpdate();

private:
    void setupUI();

    // 标签与图片
    QLabel *m_imageLabel;
    QLabel *m_animationLabel;
    QMovie *m_movie;

    // 文本浏览器
    QTextBrowser *m_textBrowser;

    // 日历
    QCalendarWidget *m_calendar;

    // 液晶数字
    QLCDNumber *m_lcdNumber;

    // 进度条
    QProgressBar *m_progressBar;

    // 滑动部件
    QSlider *m_slider;
    QScrollBar *m_scrollBar;

    // 水平线
    QFrame *m_horizontalLine;

    // 标签页
    QTabWidget *m_tabWidget;
};

#endif // DIALOG_H
