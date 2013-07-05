#pragma once

// ScreenCaptureXCtrl.h : CScreenCaptureXCtrl ActiveX �ؼ����������
#include "CatchScreenDlg.h"

// CScreenCaptureXCtrl : �й�ʵ�ֵ���Ϣ������� ScreenCaptureXCtrl.cpp��

class CScreenCaptureXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CScreenCaptureXCtrl)

// ���캯��
public:
	CScreenCaptureXCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CScreenCaptureXCtrl();

	DECLARE_OLECREATE_EX(CScreenCaptureXCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CScreenCaptureXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CScreenCaptureXCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CScreenCaptureXCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();
	afx_msg void ShowDlg();
	afx_msg void CaptureFunc();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		dispidShowDlg = 1L,
		dispidInputParameter = 2L,
		dispidCaptureFunc = 3L,
		dispidUploadURL = 4L
	};
		
private:
	//CCatchScreenDlg m_CatchScreenDlg;
protected:

	CString m_InputParameter;
	void OnInputParameterChanged(void);
	CString m_UploadURL;
	void OnUploadURLChanged(void);
	//void ShowDlg(CString msg);
	//void ShowDlg();
};

// CHttpConnection �������ϴ�