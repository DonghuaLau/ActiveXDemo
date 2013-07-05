// ScreenCaptureX.cpp : CScreenCaptureXApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "ScreenCaptureX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CScreenCaptureXApp theApp;

const GUID CDECL _tlid = { 0xBE5A501, 0x1030, 0x48ED, { 0xA7, 0xCF, 0x67, 0x5D, 0xF8, 0xEC, 0xDE, 0x45 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CScreenCaptureXApp::InitInstance - DLL ��ʼ��

BOOL CScreenCaptureXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CScreenCaptureXApp::ExitInstance - DLL ��ֹ

int CScreenCaptureXApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
