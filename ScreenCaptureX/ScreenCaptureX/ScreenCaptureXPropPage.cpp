// ScreenCaptureXPropPage.cpp : CScreenCaptureXPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "ScreenCaptureX.h"
#include "ScreenCaptureXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CScreenCaptureXPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CScreenCaptureXPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CScreenCaptureXPropPage, "SCREENCAPTUREX.ScreenCaptureXPropPage.1",
	0x51d1744b, 0x756e, 0x45b2, 0x8d, 0x74, 0x51, 0x4a, 0x8a, 0x90, 0x3d, 0xdc)



// CScreenCaptureXPropPage::CScreenCaptureXPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CScreenCaptureXPropPage ��ϵͳע�����

BOOL CScreenCaptureXPropPage::CScreenCaptureXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SCREENCAPTUREX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CScreenCaptureXPropPage::CScreenCaptureXPropPage - ���캯��

CScreenCaptureXPropPage::CScreenCaptureXPropPage() :
	COlePropertyPage(IDD, IDS_SCREENCAPTUREX_PPG_CAPTION)
{
}



// CScreenCaptureXPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CScreenCaptureXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CScreenCaptureXPropPage ��Ϣ�������
