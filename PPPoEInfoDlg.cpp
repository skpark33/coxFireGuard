// PPPoEInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestDlg.h"
#include "PPPoEInfoDlg.h"


// CPPPoEInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPPPoEInfoDlg, CDialog)

CPPPoEInfoDlg::CPPPoEInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPPPoEInfoDlg::IDD, pParent)
	, m_strID(_T(""))
	, m_strPwd(_T(""))
{

}

CPPPoEInfoDlg::~CPPPoEInfoDlg()
{
}

void CPPPoEInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, m_edtID);
	DDX_Control(pDX, IDC_EDIT_PWD, m_edtPwd);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDV_MaxChars(pDX, m_strID, 31);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	DDV_MaxChars(pDX, m_strPwd, 31);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_btnModify);
}


BEGIN_MESSAGE_MAP(CPPPoEInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CPPPoEInfoDlg::OnBnClickedButtonModify)
END_MESSAGE_MAP()


// CPPPoEInfoDlg 메시지 처리기입니다.


BOOL CPPPoEInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitPPPoE();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPPPoEInfoDlg::InitPPPoE()
{
	CHAR szID[32] = {NULL, };

	long ret = SPIDER_GetPPPoE(theApp.m_hSelectCamera, szID);
	if (ret == E_CTRL_OK) {
		USES_CONVERSION;
		m_strID = T2A(szID);
		UpdateData(FALSE);
	} else {
		m_edtID.EnableWindow(FALSE);
		m_edtPwd.EnableWindow(FALSE);
		m_btnModify.EnableWindow(FALSE);
	}
}

void CPPPoEInfoDlg::OnBnClickedButtonModify()
{
	UpdateData();

	CHAR szID[32] = {NULL, };
	CHAR szPwd[32] = {NULL, };

	USES_CONVERSION;
	strcpy(szID, T2A(m_strID.GetBuffer(0)));
	strcpy(szPwd, T2A(m_strPwd.GetBuffer(0)));

	long nlRet = SPIDER_SetPPPoE(theApp.m_hSelectCamera, szID, szPwd);
	if (nlRet != E_CTRL_OK) {
		MessageBox(GetErrorString(nlRet), _T("Fail"));
	} else {
		MessageBox(_T("Success."));
		OnOK();
	}
}
