#pragma once


// CMidClass �Ի���

class CMidClass : public CDialogEx
{
	DECLARE_DYNAMIC(CMidClass)

public:
	CMidClass(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMidClass();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
