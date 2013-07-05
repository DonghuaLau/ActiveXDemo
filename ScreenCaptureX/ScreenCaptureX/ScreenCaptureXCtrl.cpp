// ScreenCaptureXCtrl.cpp : CScreenCaptureXCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "ScreenCaptureX.h"
#include "ScreenCaptureXCtrl.h"
#include "ScreenCaptureXPropPage.h"
#include "afxdialogex.h"
#include "MidClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CScreenCaptureXCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CScreenCaptureXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CScreenCaptureXCtrl, COleControl)
	DISP_PROPERTY_NOTIFY_ID(CScreenCaptureXCtrl, "InputParameter", dispidInputParameter, m_InputParameter, OnInputParameterChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CScreenCaptureXCtrl, "UploadURL", dispidUploadURL, m_UploadURL, OnUploadURLChanged, VT_BSTR)
	DISP_FUNCTION_ID(CScreenCaptureXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CScreenCaptureXCtrl, "ShowDlg", dispidShowDlg, ShowDlg, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CScreenCaptureXCtrl, "CaptureFunc", dispidCaptureFunc, CaptureFunc, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CScreenCaptureXCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CScreenCaptureXCtrl, 1)
	PROPPAGEID(CScreenCaptureXPropPage::guid)
END_PROPPAGEIDS(CScreenCaptureXCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CScreenCaptureXCtrl, "SCREENCAPTUREX.ScreenCaptureXCtrl.1",
	0x4e491dbb, 0xa221, 0x4b86, 0xa7, 0x40, 0x74, 0xcd, 0xc5, 0xaf, 0x53, 0xa5)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CScreenCaptureXCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID IID_DScreenCaptureX = { 0x23FA8459, 0x94D0, 0x43C1, { 0x81, 0x22, 0x9, 0xBD, 0xBF, 0x25, 0x21, 0x83 } };
const IID IID_DScreenCaptureXEvents = { 0xF0D0F0D8, 0xD8A2, 0x45D4, { 0x96, 0xB1, 0xA3, 0xAE, 0x62, 0xD9, 0xB7, 0xCC } };


// �ؼ�������Ϣ

static const DWORD _dwScreenCaptureXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CScreenCaptureXCtrl, IDS_SCREENCAPTUREX, _dwScreenCaptureXOleMisc)



// CScreenCaptureXCtrl::CScreenCaptureXCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CScreenCaptureXCtrl ��ϵͳע�����

BOOL CScreenCaptureXCtrl::CScreenCaptureXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_SCREENCAPTUREX,
			IDB_SCREENCAPTUREX,
			afxRegApartmentThreading,
			_dwScreenCaptureXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CScreenCaptureXCtrl::CScreenCaptureXCtrl - ���캯��

CScreenCaptureXCtrl::CScreenCaptureXCtrl()
{
	InitializeIIDs(&IID_DScreenCaptureX, &IID_DScreenCaptureXEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}



// CScreenCaptureXCtrl::~CScreenCaptureXCtrl - ��������

CScreenCaptureXCtrl::~CScreenCaptureXCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// CScreenCaptureXCtrl::OnDraw - ��ͼ����

void CScreenCaptureXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);
}



// CScreenCaptureXCtrl::DoPropExchange - �־���֧��

void CScreenCaptureXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CScreenCaptureXCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CScreenCaptureXCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CScreenCaptureXCtrl::AboutBox - ���û���ʾ�����ڡ���

void CScreenCaptureXCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_SCREENCAPTUREX);
	dlgAbout.DoModal();
}



// CScreenCaptureXCtrl ��Ϣ�������


void CScreenCaptureXCtrl::ShowDlg()
{
	//MessageBox(m_InputParameter, L"ABC");
	CMidClass dlg;
	dlg.DoModal();
}

void CScreenCaptureXCtrl::OnInputParameterChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}

void CScreenCaptureXCtrl::OnUploadURLChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}

void CScreenCaptureXCtrl::CaptureFunc()
{
	if(m_UploadURL.IsEmpty()){
		MessageBox(L"Upload URL is NULL", L"��ʾ");
		return ;
	}

	CCatchScreenDlg m_CatchScreenDlg;
	m_CatchScreenDlg.SetUploadURL(m_UploadURL);
	int nResponse = m_CatchScreenDlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	
}