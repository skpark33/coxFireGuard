// MotionInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "MotionInfoDlg.h"


// CMotionInfoDlg dialog

IMPLEMENT_DYNCREATE(CMotionInfoDlg, CDialog)

CMotionInfoDlg::CMotionInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMotionInfoDlg::IDD, pParent)
{

}

CMotionInfoDlg::~CMotionInfoDlg()
{
}

void CMotionInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DIRECTION_SENSITIVITY, m_Combo_DirectionSensitivity);
	DDX_Control(pDX, IDC_COMBO_MOTION_ID, m_Combo_RegionID);
}

BOOL CMotionInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_Combo_DirectionSensitivity.ResetContent();
	m_Combo_DirectionSensitivity.AddString(("left-right"));
	m_Combo_DirectionSensitivity.AddString(("right-left"));
	m_Combo_DirectionSensitivity.AddString(("up-down"));
	m_Combo_DirectionSensitivity.AddString(("down-up"));
	m_Combo_DirectionSensitivity.SetCurSel(0);


	{
		ST_SPIDER_STREAM_RESOLUTION_INFO stMaxResolution = {0};
		SPIDER_GetStreamCapaMaxResolution(theApp.m_hSelectCamera, &stMaxResolution);

		CString sztext;
		sztext.Format(("%d x %d"), stMaxResolution.width, stMaxResolution.height);
		GetDlgItem(IDC_STATIC_RESOLUTION)->SetWindowText(sztext);
	}




	InitInfo();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CMotionInfoDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_MOTION_ID, &CMotionInfoDlg::OnCbnSelchangeComboMotionId)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_MOTION, &CMotionInfoDlg::OnBnClickedButtonModifyMotion)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_REGION, &CMotionInfoDlg::OnBnClickedButtonModifyRegion)
	ON_BN_CLICKED(IDC_BUTTON_ADD_REGION, &CMotionInfoDlg::OnBnClickedButtonAddRegion)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_REGION, &CMotionInfoDlg::OnBnClickedButtonDeleteRegion)
END_MESSAGE_MAP()

// CMotionInfoDlg message handlers


void CMotionInfoDlg::OnCbnSelchangeComboMotionId()
{
	// TODO: Add your control notification handler code here

	DisplayInfo();
}

void CMotionInfoDlg::DisplayInfo()
{
	int nRegion = m_Combo_RegionID.GetCurSel();

	if(nRegion != -1 && nRegion < m_vInfo.size())
	{
		CString sztext;


		ST_SPIDER_MOTION_REGION stInfo = m_vInfo.at(nRegion);
		int nCoordinate = 0;
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MOTION_X1), stInfo.Coordinate[nCoordinate].nPositionX, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MOTION_Y1), stInfo.Coordinate[nCoordinate].nPositionY, sztext);

		nCoordinate++;
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MOTION_X2), stInfo.Coordinate[nCoordinate].nPositionX, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MOTION_Y2), stInfo.Coordinate[nCoordinate].nPositionY, sztext);

		nCoordinate++;
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MOTION_X3), stInfo.Coordinate[nCoordinate].nPositionX, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MOTION_Y3), stInfo.Coordinate[nCoordinate].nPositionY, sztext);

		nCoordinate++;
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MOTION_X4), stInfo.Coordinate[nCoordinate].nPositionX, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MOTION_Y4), stInfo.Coordinate[nCoordinate].nPositionY, sztext);


		if(stInfo.nsMaskEnable == 1)
		{
			GetDlgItem(IDC_CHECK_ENABLE_MASK)->EnableWindow(true);
			GetDlgItem(IDC_CHECK_ENABLE_MASK)->SendMessage(BM_SETCHECK, BST_CHECKED);
		}
		else
		{
			GetDlgItem(IDC_CHECK_ENABLE_MASK)->SendMessage(BM_SETCHECK, BST_UNCHECKED);
			if(stInfo.nsMaskEnable == 0xFFFF || stInfo.nsMaskEnable == 0xFFFFFFFF)
			{
				GetDlgItem(IDC_CHECK_ENABLE_MASK)->EnableWindow(false);
			}
			else
			{
				GetDlgItem(IDC_CHECK_ENABLE_MASK)->EnableWindow(true);
			}
		}
		

		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_SENSITIVITY), stInfo.nsSensLevel, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_THRESHOLD), stInfo.nsDetectThreshold, sztext);

		if(stInfo.nsEnable == 1)
		{
			GetDlgItem(IDC_CHECK_ENABLE_REGION)->EnableWindow(true);
			GetDlgItem(IDC_CHECK_ENABLE_REGION)->SendMessage(BM_SETCHECK, BST_CHECKED);
		}
		else
		{
			GetDlgItem(IDC_CHECK_ENABLE_REGION)->SendMessage(BM_SETCHECK, BST_UNCHECKED);
			if(stInfo.nsEnable == 0xFFFF || stInfo.nsEnable == 0xFFFFFFFF)
			{
				GetDlgItem(IDC_CHECK_ENABLE_REGION)->EnableWindow(false);
			}
			else
			{
				GetDlgItem(IDC_CHECK_ENABLE_REGION)->EnableWindow(true);
			}
		}
	}
}


void CMotionInfoDlg::InitInfo()
{

	m_Combo_RegionID.ResetContent();

	m_vInfo.clear();





	long lret = SPIDER_GetMotionInfo(theApp.m_hSelectCamera, &m_stInfo);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
	}
	else
	{
		CString sztext;

		ST_SPIDER_MOTION stMotion = m_stInfo;

		sztext = stMotion.strID;
		GetDlgItem(IDC_EDIT_ID)->SetWindowText(sztext);


		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_SAMPLING_INTERVAL), stMotion.nSamplingIntv, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_START_TRIGGER_TIME), stMotion.nStartTriggerTime, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_END_TRIGGER_TIME), stMotion.nEndTriggerTime, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MIN_PIXEL), stMotion.nMinObjectSize, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MAX_PIXEL), stMotion.nMaxObjectSize, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_ROW), stMotion.nGridRowGran, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_COLUMN), stMotion.nGridColGran, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MIN_HOR_RESOLUTION), stMotion.nMinRoiHResolution, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MIN_VER_RESOLUTION), stMotion.nMinRoiVResolution, sztext);
		_VALID_WND_WITH_VAL(m_Combo_DirectionSensitivity, stMotion.nsDirectionSensType, NULL);


		if(stMotion.nsRegionType == 0) //grid
		{
			CString szResolution;
			//szResolution.Format(("Column x Row : %d x %d"), m_RegionGrid.m_nChangeW, m_RegionGrid.m_nChangeH);
			GetDlgItem(IDC_STATIC_RESOLUTION)->SetWindowText(szResolution);

			//m_RegionGrid.ShowWindow(true);
			//m_RegionROI.ShowWindow(false);

			GetDlgItem(IDC_RADIO_ROI)->EnableWindow(true);
			GetDlgItem(IDC_RADIO_GRID)->EnableWindow(true);

			GetDlgItem(IDC_RADIO_ROI)->SendMessage(BM_SETCHECK);
			GetDlgItem(IDC_RADIO_GRID)->SendMessage(BM_SETCHECK, BST_CHECKED);

			GetDlgItem(IDC_EDIT_MIN_HOR_RESOLUTION)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_MIN_VER_RESOLUTION)->EnableWindow(false);
		}
		else if(stMotion.nsRegionType == 1) //roi
		{
			CString szResolution;
			//szResolution.Format(("Resolution : %d x %d"), m_RegionROI.m_uWidth, m_RegionROI.m_uHeight);
			GetDlgItem(IDC_STATIC_RESOLUTION)->SetWindowText(szResolution);

			//m_RegionGrid.ShowWindow(false);
			//m_RegionROI.ShowWindow(true);

			GetDlgItem(IDC_RADIO_ROI)->EnableWindow(true);
			GetDlgItem(IDC_RADIO_GRID)->EnableWindow(true);

			GetDlgItem(IDC_RADIO_ROI)->SendMessage(BM_SETCHECK, BST_CHECKED);
			GetDlgItem(IDC_RADIO_GRID)->SendMessage(BM_SETCHECK);

			GetDlgItem(IDC_EDIT_ROW)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_COLUMN)->EnableWindow(false);
		}
		else
		{
			CString szResolution;
			szResolution = "";
			GetDlgItem(IDC_STATIC_RESOLUTION)->SetWindowText(szResolution);

			//m_RegionGrid.ShowWindow(false);
			//m_RegionROI.ShowWindow(true);

			GetDlgItem(IDC_RADIO_ROI)->EnableWindow(false);
			GetDlgItem(IDC_RADIO_GRID)->EnableWindow(false);

			GetDlgItem(IDC_RADIO_ROI)->SendMessage(BM_SETCHECK);
			GetDlgItem(IDC_RADIO_GRID)->SendMessage(BM_SETCHECK);

			GetDlgItem(IDC_EDIT_MIN_HOR_RESOLUTION)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_MIN_VER_RESOLUTION)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_ROW)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_COLUMN)->EnableWindow(false);
		}
		
		if(stMotion.nsEnable == 1)
		{
			GetDlgItem(IDC_CHECK_ENABLE_MOTION)->SendMessage(BM_SETCHECK, BST_CHECKED);
			GetDlgItem(IDC_CHECK_ENABLE_MOTION)->EnableWindow(true);


			m_Combo_RegionID.EnableWindow(true);

			GetDlgItem(IDC_BUTTON_ADD_REGION)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_DELETE_REGION)->EnableWindow(true);
		}
		else
		{
			GetDlgItem(IDC_CHECK_ENABLE_MOTION)->SendMessage(BM_SETCHECK);
			if(stMotion.nsEnable == false)
			{
				m_Combo_RegionID.EnableWindow(true);
				GetDlgItem(IDC_CHECK_ENABLE_MOTION)->EnableWindow(true);

				GetDlgItem(IDC_BUTTON_ADD_REGION)->EnableWindow(true);
				GetDlgItem(IDC_BUTTON_DELETE_REGION)->EnableWindow(true);
				GetDlgItem(IDC_BUTTON_MODIFY)->EnableWindow(true);
			}
			else
			{
				m_Combo_RegionID.EnableWindow(false);
				GetDlgItem(IDC_CHECK_ENABLE_MOTION)->EnableWindow(false);

				GetDlgItem(IDC_BUTTON_ADD_REGION)->EnableWindow(0);
				GetDlgItem(IDC_BUTTON_DELETE_REGION)->EnableWindow(0);
				GetDlgItem(IDC_BUTTON_MODIFY)->EnableWindow(false);
			}
		}




		m_Combo_RegionID.ResetContent();
		m_vInfo.clear();
		long nCount = SPIDER_GetMotionRegionCount(theApp.m_hSelectCamera);
		for(int i = 0; i < nCount; i++)
		{
			ST_SPIDER_MOTION_REGION stInfo = {0};
			long lret = SPIDER_GetMotionRegionInfo(theApp.m_hSelectCamera, i, &stInfo);
			if(lret != E_CTRL_OK)
			{
				MessageBox(GetErrorString(lret), ("Fail"));
				break;
			}

			m_vInfo.push_back(stInfo);

			sztext = stInfo.strID;
			m_Combo_RegionID.AddString(sztext);
		}


		m_Combo_RegionID.SetCurSel(0);

		DisplayInfo();
	}
}

void CMotionInfoDlg::OnBnClickedButtonModifyMotion()
{
	ST_SPIDER_MOTION stNew = m_stInfo;

	CString sztext;

	if(stNew.nsEnable != 0xFFFF && stNew.nsEnable != 0xFFFFFFFF)
		stNew.nsEnable = GetDlgItem(IDC_CHECK_ENABLE_MOTION)->SendMessage(BM_GETCHECK);

	int nValue = 0;
	GetDlgItem(IDC_EDIT_SAMPLING_INTERVAL)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nSamplingIntv != 0xFFFF && stNew.nSamplingIntv != 0xFFFFFFFF)
		stNew.nSamplingIntv = nValue;

	GetDlgItem(IDC_EDIT_START_TRIGGER_TIME)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nStartTriggerTime != 0xFFFF && stNew.nStartTriggerTime != 0xFFFFFFFF)
		stNew.nStartTriggerTime = nValue;

	GetDlgItem(IDC_EDIT_END_TRIGGER_TIME)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nEndTriggerTime != 0xFFFF && stNew.nEndTriggerTime != 0xFFFFFFFF)
		stNew.nEndTriggerTime = nValue;

	GetDlgItem(IDC_EDIT_MIN_PIXEL)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nMinObjectSize != 0xFFFF && stNew.nMinObjectSize != 0xFFFFFFFF)
		stNew.nMinObjectSize = nValue;

	GetDlgItem(IDC_EDIT_MAX_PIXEL)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nMaxObjectSize != 0xFFFF && stNew.nMaxObjectSize != 0xFFFFFFFF)
		stNew.nMaxObjectSize = nValue;

	GetDlgItem(IDC_EDIT_ROW)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nGridRowGran != 0xFFFF && stNew.nGridRowGran != 0xFFFFFFFF)
		stNew.nGridRowGran = nValue;

	GetDlgItem(IDC_EDIT_COLUMN)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nGridColGran != 0xFFFF && stNew.nGridColGran != 0xFFFFFFFF)
		stNew.nGridColGran = nValue;

	GetDlgItem(IDC_EDIT_MIN_HOR_RESOLUTION)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nMinRoiHResolution != 0xFFFF && stNew.nMinRoiHResolution != 0xFFFFFFFF)
		stNew.nMinRoiHResolution = nValue;

	GetDlgItem(IDC_EDIT_MIN_VER_RESOLUTION)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nMinRoiVResolution != 0xFFFF && stNew.nMinRoiVResolution != 0xFFFFFFFF)
		stNew.nMinRoiVResolution = nValue;


	if(stNew.nsDirectionSensType != 0xFFFF && stNew.nsDirectionSensType != 0xFFFFFFFF)
		stNew.nsDirectionSensType = m_Combo_DirectionSensitivity.GetCurSel();

	if(stNew.nsRegionType != 0xFFFF && stNew.nsRegionType != 0xFFFFFFFF)
	{
		if(GetDlgItem(IDC_RADIO_ROI)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			stNew.nsRegionType = 1;
		else if(GetDlgItem(IDC_RADIO_GRID)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			stNew.nsRegionType = 0;			
	}


	long lret = SPIDER_GetMotionInfo(theApp.m_hSelectCamera, &stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();
}

void CMotionInfoDlg::OnBnClickedButtonModifyRegion()
{
	int nModifyIndex = m_Combo_RegionID.GetCurSel();
	if(nModifyIndex >= m_vInfo.size())
		return;

	ST_SPIDER_MOTION_REGION stNew = m_vInfo.at(nModifyIndex);

	CString sztext;


	int nCoordinate = 0;
	int nValue = 0;
	GetDlgItem(IDC_EDIT_MOTION_X1)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionX = nValue;

	GetDlgItem(IDC_EDIT_MOTION_Y1)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionY = nValue;


	nCoordinate++;
	GetDlgItem(IDC_EDIT_MOTION_X2)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionX = nValue;

	GetDlgItem(IDC_EDIT_MOTION_Y2)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionY = nValue;



	nCoordinate++;
	GetDlgItem(IDC_EDIT_MOTION_X3)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionX = nValue;

	GetDlgItem(IDC_EDIT_MOTION_Y3)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionY = nValue;



	nCoordinate++;
	GetDlgItem(IDC_EDIT_MOTION_X4)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionX = nValue;

	GetDlgItem(IDC_EDIT_MOTION_Y4)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionY = nValue;



	if(stNew.nsMaskEnable != 0xFFFF && stNew.nsMaskEnable != 0xFFFFFFFF)
		stNew.nsMaskEnable = GetDlgItem(IDC_CHECK_ENABLE_MASK)->SendMessage(BM_GETCHECK);

	if(stNew.nsEnable != 0xFFFF && stNew.nsEnable != 0xFFFFFFFF)
		stNew.nsEnable = GetDlgItem(IDC_CHECK_ENABLE_REGION)->SendMessage(BM_GETCHECK);


	GetDlgItem(IDC_EDIT_SENSITIVITY)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsSensLevel != 0xFFFF && stNew.nsSensLevel != 0xFFFFFFFF)
		stNew.nsSensLevel = nValue;

	GetDlgItem(IDC_EDIT_THRESHOLD)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsDetectThreshold != 0xFFFF && stNew.nsDetectThreshold != 0xFFFFFFFF)
		stNew.nsDetectThreshold = nValue;



	long lret = SPIDER_SetMotionRegionInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

	InitInfo();

}

void CMotionInfoDlg::OnBnClickedButtonAddRegion()
{
	// TODO: Add your control notification handler code here

	ST_SPIDER_MOTION_REGION stNew = {0};

	if(m_vInfo.size())
		stNew = m_vInfo.at(0);

	//make new id
	bool bNext = true;
	int nID = 0;
	while(bNext == true)
	{
		sprintf(stNew.strID, "%d", nID);

		bNext = false;
		int nIndex = 0;
		while(nIndex < m_vInfo.size())
		{
			if(strcmp(stNew.strID, m_vInfo.at(nIndex).strID) == 0)
			{
				bNext = true;
				break;
			}

			nIndex++;
		}

		nID++;
	}



	CString sztext;


	int nCoordinate = 0;
	int nValue = 0;
	GetDlgItem(IDC_EDIT_MOTION_X1)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionX = nValue;

	GetDlgItem(IDC_EDIT_MOTION_Y1)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionY = nValue;


	nCoordinate++;
	GetDlgItem(IDC_EDIT_MOTION_X2)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionX = nValue;

	GetDlgItem(IDC_EDIT_MOTION_Y2)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionY = nValue;



	nCoordinate++;
	GetDlgItem(IDC_EDIT_MOTION_X3)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionX = nValue;

	GetDlgItem(IDC_EDIT_MOTION_Y3)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionY = nValue;



	nCoordinate++;
	GetDlgItem(IDC_EDIT_MOTION_X4)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionX = nValue;

	GetDlgItem(IDC_EDIT_MOTION_Y4)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionY = nValue;



	if(stNew.nsMaskEnable != 0xFFFF && stNew.nsMaskEnable != 0xFFFFFFFF)
		stNew.nsMaskEnable = GetDlgItem(IDC_CHECK_ENABLE_MASK)->SendMessage(BM_GETCHECK);

	if(stNew.nsEnable != 0xFFFF && stNew.nsEnable != 0xFFFFFFFF)
		stNew.nsEnable = GetDlgItem(IDC_CHECK_ENABLE_REGION)->SendMessage(BM_GETCHECK);


	GetDlgItem(IDC_EDIT_SENSITIVITY)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsSensLevel != 0xFFFF && stNew.nsSensLevel != 0xFFFFFFFF)
		stNew.nsSensLevel = nValue;

	GetDlgItem(IDC_EDIT_THRESHOLD)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsDetectThreshold != 0xFFFF && stNew.nsDetectThreshold != 0xFFFFFFFF)
		stNew.nsDetectThreshold = nValue;



	long lret = SPIDER_AddMotionRegionInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();
}

void CMotionInfoDlg::OnBnClickedButtonDeleteRegion()
{
	// TODO: Add your control notification handler code here
	int nDeleteIndex = m_Combo_RegionID.GetCurSel();
	if(nDeleteIndex >= m_vInfo.size())
		return;

	long lret = SPIDER_DeleteMotionRegionInfo(theApp.m_hSelectCamera, nDeleteIndex);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();
}
