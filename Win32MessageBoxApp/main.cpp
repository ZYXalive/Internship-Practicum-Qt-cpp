#include <windows.h>

// WinMain 是Windows图形用户界面应用程序的入口点
// 取代了控制台程序的 main 函数
int WinMain(HINSTANCE hIns, HINSTANCE hPre, PSTR szCmdLine, int iCmdShow)
{
    // MessageBox: 创建一个消息框
    // 参数：父窗口句柄(NULL表示无父窗口), 显示文本, 标题, 按钮类型
    MessageBox(NULL,
               TEXT("你好，西南交通大学"),
               TEXT("消息框"),
               MB_OK);

    return 0;
}
