#pragma once

// ScreenCaptureXPropPage.h : CScreenCaptureXPropPage ����ҳ���������


// CScreenCaptureXPropPage : �й�ʵ�ֵ���Ϣ������� ScreenCaptureXPropPage.cpp��

class CScreenCaptureXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CScreenCaptureXPropPage)
	DECLARE_OLECREATE_EX(CScreenCaptureXPropPage)

// ���캯��
public:
	CScreenCaptureXPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_SCREENCAPTUREX };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

