# include <afxwin.h>
# include <iostream>
# include <atlimage.h>
# include <GdiPlus.h>
using namespace std;
using namespace Gdiplus;

BOOL StringToPicture(CString msg, CString savePath)
{
	//设置字体
	CFont font; 
	LOGFONT logft;
	ZeroMemory(&logft, sizeof(logft));
	//CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT))->GetLogFont(&logft);//获取系统字体
	logft.lfWidth				= 14;							//字体宽度
	logft.lfHeight				= 25;							//字体高度
	logft.lfWeight				= FW_BLACK;						//字体粗细
	logft.lfItalic				= FALSE;						//是否斜体
	logft.lfUnderline			= FALSE;						//是否有下划线
	logft.lfStrikeOut			= FALSE;						//是否有删除线
	logft.lfCharSet				= ANSI_CHARSET;					//字符集
	logft.lfOutPrecision		= OUT_DEFAULT_PRECIS;			//输出精度
	logft.lfClipPrecision		= CLIP_DEFAULT_PRECIS;			//剪切精度
	logft.lfQuality				= DEFAULT_QUALITY;				//输出质量
	logft.lfPitchAndFamily		= DEFAULT_PITCH | FF_DONTCARE;	//字体的间距和家族
	wcscpy_s(logft.lfFaceName, 32, L"黑体");					//字体类型
	font.CreateFontIndirect(&logft);//设置字体

	HDC hdc = CreateCompatibleDC(NULL);		//创建兼容DC
	//SetBkMode(hdc, TRANSPARENT);			//使用透明背景
	SetBkColor(hdc, RGB(255, 255, 255));	//设置背景颜色
	SetTextColor(hdc, RGB(0, 0, 0));		//设置字体颜色
	SelectObject(hdc, font);				//选择字体

	SIZE size;
	::GetTextExtentPoint(hdc, msg.GetBuffer(msg.GetLength()), 
		msg.GetLength(), &size);//计算字符串像素

	//绘图
	CImage image;
	image.Create(size.cx, size.cy, 32, CImage::createAlphaChannel);//创建图像
	//image.SetTransparentColor(RGB(255, 255, 255));

	//分离HBITMAP------------------------------
	HBITMAP hbit = image.Detach();

	SelectObject(hdc, hbit);
	TextOut(hdc, 0, 0, msg.GetBuffer(msg.GetLength()), msg.GetLength());//输出文字到DC
	//附加HBTIMAP------------------------------
	image.Attach(hbit);

	//保存
	image.Save(savePath, ImageFormatPNG);

	ReleaseDC(NULL, hdc);
	return TRUE;
}

int main(int argc, char* argv[])
{
	StringToPicture(_T("向牧123456abcdABCD!@#$%^&+-/*"), _T("C:\\Users\\Administrator\\Desktop\\ftp\\vv.png"));
	return 0;
}