# 2026 实习项目 - 目录说明

本仓库包含2026年实习项目的全部代码，基于 Qt/C++ 框架（除 Win32MessageBoxApp 外），涵盖从基础控件、信号槽机制到数据库管理、MDI 多文档等综合应用。

| 文件夹 | 功能简介 |
|---|---|
| **BaseConverter** | 十进制到二进制/八进制/十六进制的进制转换器，带计算器风格按键面板 |
| **BookDatabaseApp** | 图书数据库管理系统，基于 SQLite + QSqlTableModel，支持增删改查与数据映射导航 |
| **DisplayWidgetsDemo** | Qt 显示部件综合演示 — QLabel/GIF动画/QTextBrowser/日历/LCD/进度条/滑动条 |
| **FileListViewer** | 文件列表查看器，支持字体、文本颜色与背景颜色自定义 |
| **ImageZoomer** | 图片缩放查看器，通过 QScrollArea + QDockWidget 实现 0.1x~5.0x 缩放 |
| **MDI_Notepad** | 多文档界面 (MDI) 记事本，支持多标签页文本编辑与文件操作 |
| **QtGuiInteractionDemo** | GUI 基础交互演示（标签显隐、文字同步）+ 登录验证应用（SHA-256 密码哈希） |
| **QtWindowTypesDemo** | 三种 Qt 窗口类型对比展示 — QWidget / QMainWindow / QDialog |
| **SalesRecordApp** | 销售记录管理系统，支持销售员业绩录入与总营业额自动统计 |
| **SignalSlotDemo** | 控制台程序，演示 Qt 信号与槽的一对多连接、多对一连接及重载信号 |
| **StandardItemModelDemo** | 学生信息管理系统，基于 QStandardItemModel + 自定义委托，支持 CSV 导入导出 |
| **StudentInfoEntry** | 学生信息录入系统，演示自定义信号/槽、列表项增删与上限控制 |
| **Win32MessageBoxApp** | 纯 Win32 API 桌面程序（无 Qt），显示"你好"消息框 |

> 各文件夹名已按英文命名概括其核心功能，便于按字母序快速定位。
