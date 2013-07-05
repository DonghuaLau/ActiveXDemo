// CatchScreenDlg.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
//#include "CatchScreen.h"
#include "CatchScreenDlg.h"
#include <afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*

int SaveHBITMAP2File(LPTSTR pszFile, HBITMAP hBMP, HDC hDC)
{
	PBITMAPINFO pbi = CreateBitmapInfoStruct(hBMP);

    HANDLE hf;                 // file handle 
    BITMAPFILEHEADER hdr;       // bitmap file-header 
    PBITMAPINFOHEADER pbih;     // bitmap info-header 
    LPBYTE lpBits;              // memory pointer 
    DWORD dwTotal;              // total count of bytes 
    DWORD cb;                   // incremental count of bytes 
    BYTE *hp;                   // byte pointer 
    DWORD dwTmp; 

    pbih = (PBITMAPINFOHEADER) pbi; 
    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

    if (!lpBits) 
         return 1;//errhandler("GlobalAlloc", hwnd); 

    // Retrieve the color table (RGBQUAD array) and the bits 
    // (array of palette indices) from the DIB. 
    if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, 
        DIB_RGB_COLORS)) 
    {
        return 2;//errhandler("GetDIBits", hwnd); 
    }

    // Create the .BMP file. 
    hf = CreateFile(pszFile, 
                   GENERIC_READ | GENERIC_WRITE, 
                   (DWORD) 0, 
                    NULL, 
                   CREATE_ALWAYS, 
                   FILE_ATTRIBUTE_NORMAL, 
                   (HANDLE) NULL); 
    if (hf == INVALID_HANDLE_VALUE) 
        return 3;//errhandler("CreateFile", hwnd); 
    hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
    // Compute the size of the entire file. 
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
                 pbih->biSize + pbih->biClrUsed 
                 * sizeof(RGBQUAD) + pbih->biSizeImage); 
    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 

    // Compute the offset to the array of color indices. 
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
                    pbih->biSize + pbih->biClrUsed 
                    * sizeof (RGBQUAD); 

    // Copy the BITMAPFILEHEADER into the .BMP file. 
    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
        (LPDWORD) &dwTmp,  NULL)) 
    {
       return 4;//errhandler("WriteFile", hwnd); 
    }

    // Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
                  + pbih->biClrUsed * sizeof (RGBQUAD), 
                  (LPDWORD) &dwTmp, ( NULL)))
	{
		return 5;//errhandler("WriteFile", hwnd); 
	}
        

    // Copy the array of color indices into the .BMP file. 
    dwTotal = cb = pbih->biSizeImage; 
    hp = lpBits; 
    if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)) 
	{
         return 6;//errhandler("WriteFile", hwnd); 
	}

    // Close the .BMP file. 
     if (!CloseHandle(hf)) 
           return 7;//errhandler("CloseHandle", hwnd); 

    // Free memory. 
    GlobalFree((HGLOBAL)lpBits);

	return 0;
}

//����һ��BMP�ļ�ͷ����
PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp)
{
	BITMAP bmp; 
    PBITMAPINFO pbmi; 
    WORD    cClrBits; 

    // Retrieve the bitmap color format, width, and height. 
    if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) 
        return NULL;//errhandler("GetObject", hwnd); 

    // Convert the color format to a count of bits. 
    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
    if (cClrBits == 1) 
        cClrBits = 1; 
    else if (cClrBits <= 4) 
        cClrBits = 4; 
    else if (cClrBits <= 8) 
        cClrBits = 8; 
    else if (cClrBits <= 16) 
        cClrBits = 16; 
    else if (cClrBits <= 24) 
        cClrBits = 24; 
    else cClrBits = 32; 

    // Allocate memory for the BITMAPINFO structure. (This structure 
    // contains a BITMAPINFOHEADER structure and an array of RGBQUAD 
    // data structures.) 

     if (cClrBits != 24) 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER) + 
                    sizeof(RGBQUAD) * (1<< cClrBits)); 

     // There is no RGBQUAD array for the 24-bit-per-pixel format. 

     else 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER)); 

    // Initialize the fields in the BITMAPINFO structure. 

    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmi->bmiHeader.biWidth = bmp.bmWidth; 
    pbmi->bmiHeader.biHeight = bmp.bmHeight; 
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
    if (cClrBits < 24) 
        pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 

    // If the bitmap is not compressed, set the BI_RGB flag. 
    pbmi->bmiHeader.biCompression = BI_RGB; 

    // Compute the number of bytes in the array of color 
    // indices and store the result in biSizeImage. 
    // For Windows NT, the width must be DWORD aligned unless 
    // the bitmap is RLE compressed. This example shows this. 
    // For Windows 95/98/Me, the width must be WORD aligned unless the 
    // bitmap is RLE compressed.
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8
                                  * pbmi->bmiHeader.biHeight; 
    // Set biClrImportant to 0, indicating that all of the 
    // device colors are important. 
     pbmi->bmiHeader.biClrImportant = 0; 
     return pbmi; 
}
*/

/////////////////////////////////////////////////////////////////////////////
// CCatchScreenDlg dialog

CCatchScreenDlg::CCatchScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCatchScreenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCatchScreenDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32

//*******************************************************************************
    //��ʼ����Ƥ����,������resizeMiddle ����
	m_rectTracker.m_nStyle=CMyTracker::resizeMiddle|CMyTracker::solidLine;  
	m_rectTracker.m_rect.SetRect(-1,-2,-3,-4);
	//���þ�����ɫ
	m_rectTracker.SetRectColor(RGB(10,100,130));
	//���þ��ε���ʱ���,Ĭ�ϵ�̫С��,Ū�˸�����
	m_rectTracker.SetResizeCursor(IDC_CURSOR6,IDC_CURSOR5,IDC_CURSOR2,IDC_CURSOR3,IDC_CURSOR4);

    m_hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR1);  
    
	
	m_bDraw=FALSE;
	m_bFirstDraw=FALSE;
	m_bQuit=FALSE;
	m_bShowMsg=FALSE;
    m_startPt=0;
    
	//��ȡ��Ļ�ֱ���
	m_xScreen = GetSystemMetrics(SM_CXSCREEN);
	m_yScreen = GetSystemMetrics(SM_CYSCREEN);

	//��ȡ��Ļ��λͼ��
	CRect rect(0, 0,m_xScreen,m_yScreen);
	m_pBitmap=CBitmap::FromHandle(CopyScreenToBitmap(&rect));
    
	//��ʼ��ˢ�´������� m_rgn
    m_rgn.CreateRectRgn(0,0,50,50);
//*******************************************************************************

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCatchScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCatchScreenDlg)
	DDX_Control(pDX, IDC_EDIT1, m_tipEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCatchScreenDlg, CDialog)
	//{{AFX_MSG_MAP(CCatchScreenDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_RBUTTONUP()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCatchScreenDlg message handlers

BOOL CCatchScreenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
//**************************************************************************
	//�ѶԻ������ó�ȫ�����㴰��
	SetWindowPos(&wndTopMost,0,0,m_xScreen,m_yScreen,SWP_SHOWWINDOW);
    
	//�ƶ�������ʾ����
	CRect rect;
	m_tipEdit.GetWindowRect(&rect);
    m_tipEdit.MoveWindow(10,10,rect.Width(),rect.Height());

	//��ʾ������ʾ��������
	DrawTip();
	
	//���񰴼���Ϣ����,���Ի���ľ�����ݵ�CCatchScreenApp��
	//((CCatchScreenApp *)AfxGetApp())->m_hwndDlg=m_hWnd;
//**************************************************************************

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//KillTimer(1001);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCatchScreenDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
//**************************************************************************
		CPaintDC dc(this);
         
		//��ʾ��ȡ���δ�С��Ϣ
		if(m_bShowMsg&&m_bFirstDraw)
		{
			//�õ���ǰ���δ�С
			CRect rect;
			m_rectTracker.GetTrueRect(&rect);
			//����CPaintDC ��Ϊ�˲����˴����ϻ���Ϣ
			DrawMessage(rect,&dc);
		}

		//������Ƥ�����
		if(m_bFirstDraw)
		{
			m_rectTracker.Draw(&dc);
		}

//*************************************************************************
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCatchScreenDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCatchScreenDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CCatchScreenDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
//***************************************************************
	if(m_bFirstDraw)
	{
		//ȡ���ѻ����α���
		m_bFirstDraw=FALSE;
		m_bDraw=FALSE;
		m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
		PaintWindow();
	}
	else
	{
		CDialog::OnCancel();
	}
//*******************************************************************
}

void CCatchScreenDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//**************************************************************************************
	   if(m_bDraw)
	   {
			//��̬�������δ�С,��ˢ�»���
		    m_rectTracker.m_rect.SetRect(m_startPt.x+4,m_startPt.y+4,point.x,point.y);
			PaintWindow();
	   }
	   
	   //�ֲ�������С��λ��ʱ,���ղ���MouseMove��Ϣ
	   CRect rect;
	   m_tipEdit.GetWindowRect(&rect);
	   if(rect.PtInRect(point))
	   m_tipEdit.SendMessage(WM_MOUSEMOVE);
       
	   ChangeRGB();
//*****************************************************************************************
	CDialog::OnMouseMove(nFlags, point);
}

void CCatchScreenDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//*****************************************************************************************
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);

    //�жϻ���λ��
	if(nHitTest<0)
	{
		if(!m_bFirstDraw)
		{
			//��һ�λ�����
			m_startPt=point;
			m_bDraw=TRUE;
			m_bFirstDraw=TRUE;
			//���õ�����갴��ʱ��С�ľ��δ�С
			m_rectTracker.m_rect.SetRect(point.x,point.y,point.x+4,point.y+4);	
			
			//��֤����굱��ʱ������ʾ��Ϣ
			if(m_bFirstDraw)
			  m_bShowMsg=TRUE;		
			DrawTip();
			PaintWindow();
		}
	}
	else
	{
		//��֤����굱��ʱ������ʾ��Ϣ
		m_bShowMsg=TRUE;		
		PaintWindow();
		
		if(m_bFirstDraw)
		{
			//������Сʱ,Track���Զ��������δ�С,��Щ�ڼ�,��Ϣ��CRectTracker�ڲ�����
			m_rectTracker.Track(this,point,TRUE);
			//SendMessage(WM_LBUTTONUP,NULL,NULL);
			PaintWindow();

		}
	}
//****************************************************************************************
	CDialog::OnLButtonDown(nFlags, point);
}

void CCatchScreenDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//****************************************************************************************
    
	m_bShowMsg=FALSE;
	m_bDraw=FALSE;
	DrawTip();

	PaintWindow();
//****************************************************************************************
	CDialog::OnLButtonUp(nFlags, point);
}

void CCatchScreenDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);
    //������Ǿ����ڲ�˫��
	if(nHitTest==8)      
	{
        //����λͼ��ճ������,bSave ΪTRUE,
		CopyScreenToBitmap(m_rectTracker.m_rect,TRUE);
	    PostQuitMessage(0);
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CCatchScreenDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//****************************************************************************************
	if(m_bFirstDraw)
	{
		//����Ѿ���ȡ���������ȡ����
		m_bFirstDraw=FALSE;
		//������δ�С
		m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
		DrawTip();
		PaintWindow();
	}
	else
	{
		 //�رճ���
		 PostQuitMessage(0);
	}
//****************************************************************************************
	CDialog::OnRButtonUp(nFlags, point);
}

HBRUSH CCatchScreenDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	// TODO: Return a different brush if the default is not desired
//***********************************************************
	//���ò�����ʾ�����ı���ɫ
	if(pWnd->GetDlgCtrlID()==IDC_EDIT1)
	{
		pDC->SetTextColor(RGB(255,255,255));
	}
//***************************************************************
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CCatchScreenDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//**************************************************************************************
	//�������������ȫ���Ի��򱳾�
	BITMAP bmp;
	m_pBitmap->GetBitmap(&bmp);

	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);

	dcCompatible.SelectObject(m_pBitmap);

	CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);

	return TRUE;
//**************************************************************************************
	//return CDialog::OnEraseBkgnd(pDC);
}

BOOL CCatchScreenDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
//***********************************************************************
	//���øı��ȡ���δ�Сʱ���
	if (pWnd == this &&m_rectTracker.SetCursor(this, nHitTest)
		             &&!m_bDraw &&m_bFirstDraw) //�˴��жϱ���ȡʱ����ʼ��Ϊ��ɫ���
    {
		return TRUE; 
	}

	//���ò�ɫ���
	SetCursor(m_hCursor);
	return TRUE;

//*******************************************************************
	//return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


//*********************���ӵĺ���**********************************************************
//������Ļ,��δ������������� �Ǻ�
HBITMAP CCatchScreenDlg::CopyScreenToBitmap(LPRECT lpRect,BOOL bSave)
//lpRect ����ѡ������
{
	HDC       hScrDC, hMemDC;      
	// ��Ļ���ڴ��豸������
	HBITMAP    hBitmap, hOldBitmap;   
	// λͼ���
	int       nX, nY, nX2, nY2;      
	// ѡ����������
	int       nWidth, nHeight;
	
	// ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(lpRect))
		return NULL;
	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);

	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ����������
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;

	//ȷ��ѡ�������ǿɼ���
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > m_xScreen)
		nX2 = m_xScreen;
	if (nY2 > m_yScreen)
		nY2 = m_yScreen;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap = CreateCompatibleBitmap
		(hScrDC, nWidth, nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	if(bSave)
	{
		//����������DC,��bSaveΪ��ʱ�ѿ�ʼ�����ȫ��λͼ,����ȡ���δ�С����
		CDC dcCompatible;
		dcCompatible.CreateCompatibleDC(CDC::FromHandle(hMemDC));
		dcCompatible.SelectObject(m_pBitmap);
        
		BitBlt(hMemDC, 0, 0, nWidth, nHeight,
			dcCompatible, nX, nY, SRCCOPY);

	}
	else
	{
		BitBlt(hMemDC, 0, 0, nWidth, nHeight,
			hScrDC, nX, nY, SRCCOPY);
	}

	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	//�õ���Ļλͼ�ľ��
	//��� 
	
	
	if(bSave)
	{
		wchar_t tmppath[256], tmpfile[256];
		UINT ret = 0;
		CString msg, tmp;
		GetTempPath(256, tmppath);
		ret = GetTempFileName(tmppath, L"pic", 0, tmpfile);
		//tmp.Format(L"GetTempFileName[%d], ", GetLastError());
		//msg += tmp;
		//MessageBox(msg, L"��ʱĿ¼");
		wsprintf(tmppath, L"%s.png", tmpfile);
		m_Img.Attach(hBitmap);
		m_Img.Save(tmppath);
		m_Img.Detach();
		_wremove(tmpfile);
		m_CapPicTempFile = tmppath;
		//_wrename(tmpfile, tmppath);
		//tmp.Format(L"ImgSave[%d], tmpfile[%]", GetLastError(), tmpfile);
		//msg = tmp;
		//MessageBox(tmppath, L"��ʱĿ¼ - 2");

		/*	
		if (OpenClipboard()) 
		{
        //��ռ�����
        EmptyClipboard();
        //����Ļ����ճ������������,
        //hBitmap Ϊ�ղŵ���Ļλͼ���
        SetClipboardData(CF_BITMAP, hBitmap);
        //�رռ�����
        CloseClipboard();
		
		//save to file
		SaveHBITMAP2File(L"D:\\a.bmp", hBitmap,hMemDC);
      }
	  */
	}else{
		m_CapPicTempFile = "";
	}
	// ����λͼ���

	DeleteDC(hScrDC);
	DeleteDC(hMemDC);

	return hBitmap;
}

//��ʾ������ʾ��Ϣ
void CCatchScreenDlg::DrawTip()
{
    
    //�õ�ǰ��������,
	CPoint pt;
	GetCursorPos(&pt);
	
	//������ǰR,G,B,������ֵ
	COLORREF color;
	CClientDC dc(this);
	color=dc.GetPixel(pt);
	BYTE rValue,gValue,bValue;
	rValue=GetRValue(color);
	gValue=GetGValue(color);
	bValue=GetGValue(color);
	
	//����ʽ�ŷ��ַ���
	CString string;
	CString strTemp;
	string.Format(L"\r\n\r\n\r\n ����ǰ����RGB (%d,%d,%d)\r\n",rValue,gValue,bValue);
    
	if(!m_bDraw&&!m_bFirstDraw)
	{
		strTemp="\r\n ����������������ѡ���ȡ\r\n ��Χ\r\n\r\n ����ESC��������Ҽ��˳�";
	}
	else
	if(m_bDraw&&m_bFirstDraw)
	{
		strTemp="\r\n ���ɿ�������ȷ����ȡ��Χ\r\n\r\n ����ESC���˳�";
	}
	else
	if(m_bFirstDraw)
	{
		strTemp="\r\n ����������������ȡ��Χ��\r\n ��С��λ��\r\n\r\n ����ȡ��Χ��˫����������\r\n ��ͼ�񣬽�������\r\n\r\n ���������Ҽ�����ѡ��";
	}
	string+=strTemp;
	//��ʾ���༩����,������ʾ����
	m_tipEdit.SetWindowText(string);
}

//��ʾ��ȡ������Ϣ
void CCatchScreenDlg::DrawMessage(CRect &inRect,CDC * pDC)
{
	//��ȡ���δ�С��Ϣ�������
	const int space=3;
    
	//����������ɫ��С
	
	CPoint pt;
	CPen pen(PS_SOLID,1,RGB(147,147,147));

	//dc.SetTextColor(RGB(147,147,147));
	CFont font;
	CFont * pOldFont;
	font.CreatePointFont(90,L"����");
	pOldFont=pDC->SelectObject(&font);

	//�õ������Ⱥ͸߶�
	GetCursorPos(&pt);
	int OldBkMode;
	OldBkMode=pDC->SetBkMode(TRANSPARENT);

	TEXTMETRIC tm;
	int charHeight;
	CSize size;
	int	lineLength;
	pDC->GetTextMetrics(&tm);
	charHeight = tm.tmHeight+tm.tmExternalLeading;
	size=pDC->GetTextExtent(L"����λ��  ",strlen("����λ��  "));
	lineLength=size.cx;
    
	//��ʼ������, �Ա�֤д����������
	CRect rect(pt.x+space,pt.y-charHeight*6-space,pt.x+lineLength+space,pt.y-space);
    
    //������ʱ����
    CRect rectTemp;
	//�����ε��������Եʱ��������ʹ�С
	if((pt.x+rect.Width())>=m_xScreen)
	{
		//�����Ϸ���ʾ���¾���
		rectTemp=rect;
		rectTemp.left=rect.left-rect.Width()-space*2;
		rectTemp.right=rect.right-rect.Width()-space*2;;
		rect=rectTemp;
	}

	if((pt.y-rect.Height())<=0)
	{
		//�����ҷ���ʾ���¾���
		rectTemp=rect;
		rectTemp.top=rect.top+rect.Height()+space*2;;
		rectTemp.bottom=rect.bottom+rect.Height()+space*2;;
		rect=rectTemp;
		
	}

	//�����ջ�ˢ������
	CBrush * pOldBrush;
    pOldBrush=pDC->SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)));
	
	pDC->Rectangle(rect);
   	rect.top+=2;
	//�ھ�������ʾ����
	CRect outRect(rect.left,rect.top,rect.left+lineLength,rect.top+charHeight);
	CString string("����λ��");
	pDC->DrawText(string,outRect,DT_CENTER);
    
	outRect.SetRect(rect.left,rect.top+charHeight,rect.left+lineLength,charHeight+rect.top+charHeight);
	string.Format(L"(%d,%d)",inRect.left,inRect.top);
	pDC->DrawText(string,outRect,DT_CENTER);
	

	outRect.SetRect(rect.left,rect.top+charHeight*2,rect.left+lineLength,charHeight+rect.top+charHeight*2);
	string="���δ�С";
	pDC->DrawText(string,outRect,DT_CENTER);

	outRect.SetRect(rect.left,rect.top+charHeight*3,rect.left+lineLength,charHeight+rect.top+charHeight*3);
	string.Format(L"(%d,%d)",inRect.Width(),inRect.Height());
    pDC->DrawText(string,outRect,DT_CENTER);

	outRect.SetRect(rect.left,rect.top+charHeight*4,rect.left+lineLength,charHeight+rect.top+charHeight*4);
	string="�������";
    pDC->DrawText(string,outRect,DT_CENTER);

	outRect.SetRect(rect.left,rect.top+charHeight*5,rect.left+lineLength,charHeight+rect.top+charHeight*5);
	string.Format(L"(%d,%d)",pt.x,pt.y);
	pDC->DrawText(string,outRect,DT_CENTER);
    
	pDC->SetBkMode(OldBkMode);
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldBrush);
	
}
//�ػ�����
void CCatchScreenDlg::PaintWindow()
{
	//��ȡ��ȫ���Ի��򴰿ڴ�С
	CRect rect1;
	GetWindowRect(rect1);

	//��ȡ�༭�򴰿ڴ�С
	CRect rect2;
	m_tipEdit.GetWindowRect(rect2);

	CRgn rgn1,rgn2;
	rgn1.CreateRectRgnIndirect(rect1);
	rgn2.CreateRectRgnIndirect(rect2);

	//��ȡ��������,���ǳ��˱༭�򴰿ڲ�����
	m_rgn.CombineRgn(&rgn1,&rgn2,RGN_DIFF);
	
	InvalidateRgn(&m_rgn);
}
//�ı������ʾ���ڵ�RGBֵ
void CCatchScreenDlg::ChangeRGB()
{
	//����ɵ�RGBֵ�ַ���
	static CString strOld("");

	CPoint pt;
	GetCursorPos(&pt);

	//������ǰR,G,B,������ֵ
	COLORREF color;
	CClientDC dc(this);
	color=dc.GetPixel(pt);
	BYTE rValue,gValue,bValue;
	rValue=GetRValue(color);
	gValue=GetGValue(color);
	bValue=GetGValue(color);
	
	//����ʽ�ŷ��ַ���
	CString string;
	string.Format(L"(%d,%d,%d)",rValue,gValue,bValue);
	//�����ǰ��ɫû����ˢ��RGBֵ,���ⴰ���и�����˸
    if(strOld!=string)
	{
	    //�õ�RGB�ı���һ�е��ı�����
		int LineLength=m_tipEdit.LineLength(6);
		//��ѡRGBֵ�ı�,Ҳ����(255,255,255)��ʽ
	    m_tipEdit.SetSel(20,LineLength+6);
        
		//�滻RGB����
		m_tipEdit.ReplaceSel(string);
    }
	
	strOld=string;

}

//*******************************************************************************************

BOOL CCatchScreenDlg::UploadFile(LPCTSTR strURL, //��������ϴ�������ҳ���URL
				 LPCTSTR strLocalFileName)  //���ϴ��ı����ļ�·��
{
	ASSERT(strURL != NULL && strLocalFileName != NULL);
	BOOL bResult = FALSE;
	DWORD dwType = 0;
	CString strServer;
	CString strObject;
	INTERNET_PORT wPort = 0;
	DWORD dwFileLength = 0;
	char * pFileBuff = NULL;
 
	CHttpConnection * pHC = NULL;
	CHttpFile * pHF = NULL;
	CInternetSession cis;
 
	bResult =  AfxParseURL(strURL, dwType, strServer, strObject, wPort);
	if(!bResult)
	return FALSE;
	CFile file;
	try
	{
		if(!file.Open(strLocalFileName, CFile::shareDenyNone | CFile::modeRead))
		return FALSE;
		dwFileLength = file.GetLength();
		if(dwFileLength <= 0)
		return FALSE;
		pFileBuff = new char[dwFileLength];
		memset(pFileBuff, 0, sizeof(char) * dwFileLength);
		file.Read(pFileBuff, dwFileLength);
  
		const int nTimeOut = 5000;
		cis.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //���ӳ�ʱ����
		cis.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);  //����1��
		pHC = cis.GetHttpConnection(strServer, wPort);  //ȡ��һ��Http����
  
		pHF = pHC->OpenRequest(CHttpConnection::HTTP_VERB_POST, strObject);
		{
			if(!pHF->SendRequest(NULL, 0, pFileBuff, dwFileLength))
				delete[]pFileBuff;
			pFileBuff = NULL;
			pHF->Close();
			pHC->Close();
			cis.Close();
			return FALSE;
		}

		//DWORD dwStateCode = 0;
		//pHF->QueryInfoStatusCode(dwStateCode);
		//if(dwStateCode == HTTP_STATUS_OK)
		//bResult = TRUE;

		CString ResponeStr;
		pHF->QueryInfo(HTTP_QUERY_FLAG_REQUEST_HEADERS, ResponeStr);
		
		if (OpenClipboard()) 
		{
			//��ռ�����
			EmptyClipboard();
			SetClipboardData(CF_TEXT, ResponeStr.GetBuffer());
			//�رռ�����
			CloseClipboard();
		}
	  
		
	}
	catch(CInternetException * pEx)
	{
		wchar_t sz[256] = L"";
		pEx->GetErrorMessage(sz, 25);
		CString str;
		str.Format(L"InternetException occur!\r\n%s", sz);
		AfxMessageBox(str);
	}
	catch(CFileException& fe)
	{
		CString str;
		str.Format(L"FileException occur!\r\n%d", fe.m_lOsError);
		AfxMessageBox(str);
	}
	catch(...)
	{
		DWORD dwError = GetLastError();
		CString str;
		str.Format(L"Unknow Exception occur!\r\n%d", dwError);
		AfxMessageBox(str);
	}
 
	delete[] pFileBuff;
	pFileBuff = NULL;
	file.Close();
	pHF->Close();
	pHC->Close();
	cis.Close();
	return bResult;
}