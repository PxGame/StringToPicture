# include <afxwin.h>
# include <iostream>
# include <atlimage.h>
# include <GdiPlus.h>
using namespace std;
using namespace Gdiplus;

BOOL StringToPicture(CString msg, CString savePath)
{
	//��������
	CFont font; 
	LOGFONT logft;
	ZeroMemory(&logft, sizeof(logft));
	//CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT))->GetLogFont(&logft);//��ȡϵͳ����
	logft.lfWidth				= 14;							//������
	logft.lfHeight				= 25;							//����߶�
	logft.lfWeight				= FW_BLACK;						//�����ϸ
	logft.lfItalic				= FALSE;						//�Ƿ�б��
	logft.lfUnderline			= FALSE;						//�Ƿ����»���
	logft.lfStrikeOut			= FALSE;						//�Ƿ���ɾ����
	logft.lfCharSet				= ANSI_CHARSET;					//�ַ���
	logft.lfOutPrecision		= OUT_DEFAULT_PRECIS;			//�������
	logft.lfClipPrecision		= CLIP_DEFAULT_PRECIS;			//���о���
	logft.lfQuality				= DEFAULT_QUALITY;				//�������
	logft.lfPitchAndFamily		= DEFAULT_PITCH | FF_DONTCARE;	//����ļ��ͼ���
	wcscpy_s(logft.lfFaceName, 32, L"����");					//��������
	font.CreateFontIndirect(&logft);//��������

	HDC hdc = CreateCompatibleDC(NULL);		//��������DC
	//SetBkMode(hdc, TRANSPARENT);			//ʹ��͸������
	SetBkColor(hdc, RGB(255, 255, 255));	//���ñ�����ɫ
	SetTextColor(hdc, RGB(0, 0, 0));		//����������ɫ
	SelectObject(hdc, font);				//ѡ������

	SIZE size;
	::GetTextExtentPoint(hdc, msg.GetBuffer(msg.GetLength()), 
		msg.GetLength(), &size);//�����ַ�������

	//��ͼ
	CImage image;
	image.Create(size.cx, size.cy, 32, CImage::createAlphaChannel);//����ͼ��
	//image.SetTransparentColor(RGB(255, 255, 255));

	//����HBITMAP------------------------------
	HBITMAP hbit = image.Detach();

	SelectObject(hdc, hbit);
	TextOut(hdc, 0, 0, msg.GetBuffer(msg.GetLength()), msg.GetLength());//������ֵ�DC
	//����HBTIMAP------------------------------
	image.Attach(hbit);

	//����
	image.Save(savePath, ImageFormatPNG);

	ReleaseDC(NULL, hdc);
	return TRUE;
}

int main(int argc, char* argv[])
{
	StringToPicture(_T("����123456abcdABCD!@#$%^&+-/*"), _T("C:\\Users\\Administrator\\Desktop\\ftp\\vv.png"));
	return 0;
}