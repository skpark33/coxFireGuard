// EventTriggerInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "EventTriggerInfoDlg.h"


// CEventTriggerInfoDlg dialog

IMPLEMENT_DYNCREATE(CEventTriggerInfoDlg, CDialog)

CEventTriggerInfoDlg::CEventTriggerInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEventTriggerInfoDlg::IDD, pParent)
{

}

CEventTriggerInfoDlg::~CEventTriggerInfoDlg()
{
}

void CEventTriggerInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_EVENT_TYPE, m_Combo_EventType);
	DDX_Control(pDX, IDC_COMBO_NOTIFY_METHOD, m_Combo_NotifyMethod);
	DDX_Control(pDX, IDC_TREE_TRIGGER, m_TreeTrigger);
}

BOOL CEventTriggerInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();



	m_Combo_EventType.ResetContent();
	m_Combo_EventType.AddString(("IO"));
	m_Combo_EventType.AddString(("VMD"));
	m_Combo_EventType.AddString(("videoloss"));
	m_Combo_EventType.AddString(("raidfailure"));
	m_Combo_EventType.AddString(("recordingfailure"));
	m_Combo_EventType.AddString(("badvideo"));
	m_Combo_EventType.AddString(("POS"));
	m_Combo_EventType.AddString(("analytics"));
	m_Combo_EventType.AddString(("fanfailure"));
	m_Combo_EventType.AddString(("overheat"));
	m_Combo_EventType.SetCurSel(0);



	
	m_Combo_NotifyMethod.ResetContent();
	m_Combo_NotifyMethod.AddString(("email"));
	m_Combo_NotifyMethod.AddString(("IM"));
	m_Combo_NotifyMethod.AddString(("IO"));
	m_Combo_NotifyMethod.AddString(("syslog"));
	m_Combo_NotifyMethod.AddString(("HTTP"));
	m_Combo_NotifyMethod.AddString(("FTP"));
	m_Combo_NotifyMethod.SetCurSel(0);



	InitInfo();



	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CEventTriggerInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_NOTIFY, &CEventTriggerInfoDlg::OnBnClickedButtonModifyNotify)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_TRIGGER, &CEventTriggerInfoDlg::OnTvnSelchangedTreeTrigger)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_TRIGGER, &CEventTriggerInfoDlg::OnBnClickedButtonModifyTrigger)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CEventTriggerInfoDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CEventTriggerInfoDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_ADD_NOTIFY, &CEventTriggerInfoDlg::OnBnClickedButtonAddNotify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_NOTIFY, &CEventTriggerInfoDlg::OnBnClickedButtonDeleteNotify)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_TRIGGER, &CEventTriggerInfoDlg::OnNMDblclkTreeTrigger)
END_MESSAGE_MAP()

// CEventTriggerInfoDlg message handlers

void CEventTriggerInfoDlg::OnTvnSelchangedTreeTrigger(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	DisplayInfo();

	*pResult = 0;
}

void CEventTriggerInfoDlg::DisplayInfo()
{
	HTREEITEM hItem = m_TreeTrigger.GetSelectedItem();

	if(hItem)
	{
		int nNotifyIndex = 0;

		if(m_TreeTrigger.GetParentItem(hItem))
		{
			nNotifyIndex = m_TreeTrigger.GetItemData(hItem);
			hItem = m_TreeTrigger.GetParentItem(hItem);
		}

		int nTriggerIndex = m_TreeTrigger.GetItemData(hItem);
		if(nTriggerIndex < m_vInfo.size())
		{
			ST_SPIDER_EVENT_TRIGGER_INFO stTrigger = m_vInfo.at(nTriggerIndex);

			unsigned int notifycount = SPIDER_GetEventTriggerNotifyCount(theApp.m_hSelectCamera, nTriggerIndex);
			if(nNotifyIndex < notifycount)
			{
				ST_SPIDER_EVENT_TRIGGER_NOTIFY_INFO stNotify;
				long lret = SPIDER_GetEventTriggerNotifyInfo(theApp.m_hSelectCamera, nTriggerIndex, nNotifyIndex, &stNotify);
				if(lret != E_CTRL_OK)
				{
					MessageBox(GetErrorString(lret), ("Fail"));
				}
				else
				{
					CString sztext;

					
					_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_EVENT_DESC), stTrigger.strEventDesc, sztext);
					_VALID_WND_WITH_VAL(m_Combo_EventType, stTrigger.nsEventType, NULL);
					_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_IOINPUTID), stTrigger.strIoInputID, sztext);
					_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_EVENT_INTERVAL), stTrigger.nIntervalOfEvent, sztext);

					_VALID_WND_WITH_VAL(m_Combo_NotifyMethod, stNotify.nsNotyMethod, NULL);

					_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_IOOUTPUTID), stNotify.strIoOutputID, sztext);
					_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_NOTIFY_INTERVAL), stNotify.nNotyInterval, sztext);

					GetDlgItem(IDC_RADIO_BEGIN)->EnableWindow(true);
					GetDlgItem(IDC_RADIO_BEGIN_END)->EnableWindow(true);
					GetDlgItem(IDC_RADIO_RECURRING)->EnableWindow(true);

					GetDlgItem(IDC_RADIO_BEGIN)->SendMessage(BM_SETCHECK);
					GetDlgItem(IDC_RADIO_BEGIN_END)->SendMessage(BM_SETCHECK);
					GetDlgItem(IDC_RADIO_RECURRING)->SendMessage(BM_SETCHECK);

					switch(stNotify.nsNotyRecurrence)
					{
					case 0: //XPM_EVENT_NOTY_RECUR_BEGIN:
						GetDlgItem(IDC_RADIO_BEGIN)->SendMessage(BM_SETCHECK, BST_CHECKED);
						GetDlgItem(IDC_RADIO_BEGIN_END)->SendMessage(BM_SETCHECK);
						GetDlgItem(IDC_RADIO_RECURRING)->SendMessage(BM_SETCHECK);
						GetDlgItem(IDC_EDIT_NOTIFY_INTERVAL)->EnableWindow(false);
						break;
					case 1: //XPM_EVENT_NOTY_RECUR_BEGIN_END:
						GetDlgItem(IDC_RADIO_BEGIN_END)->SendMessage(BM_SETCHECK, BST_CHECKED);
						GetDlgItem(IDC_RADIO_BEGIN)->SendMessage(BM_SETCHECK);
						GetDlgItem(IDC_RADIO_RECURRING)->SendMessage(BM_SETCHECK);
						GetDlgItem(IDC_EDIT_NOTIFY_INTERVAL)->EnableWindow(false);
						break;
					case 2: //XPM_EVENT_NOTY_RECUR_RECUR:
						GetDlgItem(IDC_RADIO_RECURRING)->SendMessage(BM_SETCHECK, BST_CHECKED);
						GetDlgItem(IDC_RADIO_BEGIN)->SendMessage(BM_SETCHECK);
						GetDlgItem(IDC_RADIO_BEGIN_END)->SendMessage(BM_SETCHECK);
						break;
					default:
						GetDlgItem(IDC_RADIO_BEGIN)->EnableWindow(false);
						GetDlgItem(IDC_RADIO_BEGIN_END)->EnableWindow(false);
						GetDlgItem(IDC_RADIO_RECURRING)->EnableWindow(false);
						break;
					}
				}
			}
		}
	}
}

void CEventTriggerInfoDlg::InitInfo()
{

	m_TreeTrigger.DeleteAllItems();


	m_vInfo.clear();
	long nCount = SPIDER_GetEventTriggerCount(theApp.m_hSelectCamera);
	for(int i = 0; i < nCount; i++)
	{
		ST_SPIDER_EVENT_TRIGGER_INFO stInfo = {0};
		long lret = SPIDER_GetEventTriggerInfo(theApp.m_hSelectCamera, i, &stInfo);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vInfo.push_back(stInfo);
		
		CString sztext;
		sztext = "[";
		sztext += stInfo.strID;
		sztext += "] ";
		switch(stInfo.nsEventType)
		{
		case 0: sztext += ("IO");					break;
		case 1: sztext += ("VMD");		break;
		case 2: sztext += ("videoloss");		break;
		case 3: sztext += ("raidfailure");		break;
		case 4: sztext += ("recordingfailure");		break;
		case 5: sztext += ("badvideo");		break;
		case 6: sztext += ("POS");		break;
		case 7: sztext += ("analytics");		break;
		case 8: sztext += ("fanfailure");		break;
		case 9: sztext += ("overheat");		break;
		default: sztext += "none";		break;
		}

		sztext += " (";
		sztext += stInfo.strEventDesc;
		sztext += ")";


		HTREEITEM hTrigger = m_TreeTrigger.InsertItem(sztext);
		m_TreeTrigger.SetItemData(hTrigger, i);


		unsigned int notifycount = SPIDER_GetEventTriggerNotifyCount(theApp.m_hSelectCamera, i);
		for(unsigned int notify = 0; notify < notifycount; notify++)
		{
			ST_SPIDER_EVENT_TRIGGER_NOTIFY_INFO stNotify;
			lret = SPIDER_GetEventTriggerNotifyInfo(theApp.m_hSelectCamera, i, notify, &stNotify);
			if(lret != E_CTRL_OK)
			{
				MessageBox(GetErrorString(lret), ("Fail"));
				break;
			}


			sztext = "[";
			sztext += stNotify.strID;
			sztext += "] ";

			CString method;
			method = "none";
			switch(stNotify.nsNotyMethod)
			{
			case	0:	method = ("email");		break;
			case	1:	method = ("IM");		break;
			case	2:	method = ("IO");		break;
			case	3:	method = ("syslog");	break;
			case	4:	method = ("HTTP");		break;
			case	5:	method = ("FTP");		break;
			}
			sztext += method;

			HTREEITEM hNotify = m_TreeTrigger.InsertItem(sztext, hTrigger);
			m_TreeTrigger.SetItemData(hNotify, notify);
		}

		m_TreeTrigger.Expand(hTrigger, TVE_EXPAND);
	}

	m_TreeTrigger.Select(m_TreeTrigger.GetRootItem(), TVGN_CARET);

	DisplayInfo();
}

void CEventTriggerInfoDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here

	ST_SPIDER_EVENT_TRIGGER_INFO stNew = {0};

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

	GetDlgItem(IDC_EDIT_EVENT_DESC)->GetWindowText(sztext);
	if(strcmp(stNew.strEventDesc, "NA"))
		StringCopyTo(sztext, stNew.strEventDesc);

	GetDlgItem(IDC_EDIT_IOINPUTID)->GetWindowText(sztext);
	if(strcmp(stNew.strIoInputID, "NA"))
		StringCopyTo(sztext, stNew.strIoInputID);

	if(stNew.nsEventType != 0xFFFF && stNew.nsEventType != 0xFFFFFFFF)
		stNew.nsEventType = m_Combo_EventType.GetCurSel();

	int nValue = 0;
	GetDlgItem(IDC_EDIT_EVENT_INTERVAL)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nIntervalOfEvent != 0xFFFF && stNew.nIntervalOfEvent != 0xFFFFFFFF)
		stNew.nIntervalOfEvent = nValue;



	stNew.nNotificationNum = 0;
	long lret = SPIDER_AddEventTriggerInfo(theApp.m_hSelectCamera, stNew, 0, NULL);


	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();
}

void CEventTriggerInfoDlg::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_TreeTrigger.GetSelectedItem();

	if(hItem == NULL)
		return;

	int nNotifyIndex = 0;

	if(m_TreeTrigger.GetParentItem(hItem))
	{
		nNotifyIndex = m_TreeTrigger.GetItemData(hItem);
		hItem = m_TreeTrigger.GetParentItem(hItem);
	}

	int nTriggerIndex = m_TreeTrigger.GetItemData(hItem);
	if(nTriggerIndex >= m_vInfo.size())
		return;

	int nDeleteIndex = nTriggerIndex;

	long lret = SPIDER_DeleteEventTriggerInfo(theApp.m_hSelectCamera, nDeleteIndex);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();

}

void CEventTriggerInfoDlg::OnBnClickedButtonAddNotify()
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_TreeTrigger.GetSelectedItem();

	if(hItem == NULL)
		return;

	if(m_TreeTrigger.GetParentItem(hItem))
	{
		hItem = m_TreeTrigger.GetParentItem(hItem);
	}

	int nTriggerIndex = m_TreeTrigger.GetItemData(hItem);
	if(nTriggerIndex >= m_vInfo.size())
		return;

	vector<ST_SPIDER_EVENT_TRIGGER_NOTIFY_INFO>		vNotify;
	unsigned int notifycount = SPIDER_GetEventTriggerNotifyCount(theApp.m_hSelectCamera, nTriggerIndex);
	for(int nNotifyIndex = 0; nNotifyIndex < notifycount; nNotifyIndex++)
	{
		ST_SPIDER_EVENT_TRIGGER_NOTIFY_INFO stNotify = {0};
		long lret = SPIDER_GetEventTriggerNotifyInfo(theApp.m_hSelectCamera, nTriggerIndex, nNotifyIndex, &stNotify);

		vNotify.push_back(stNotify);
	}


	ST_SPIDER_EVENT_TRIGGER_NOTIFY_INFO stNew = {0};

	if(vNotify.size())
		stNew = vNotify.at(0);


	//make new id
	bool bNext = true;
	int nID = 0;
	while(bNext == true)
	{
		sprintf(stNew.strID, "%d", nID);

		bNext = false;
		int nIndex = 0;
		while(nIndex < vNotify.size())
		{
			if(strcmp(stNew.strID, vNotify.at(nIndex).strID) == 0)
			{
				bNext = true;
				break;
			}

			nIndex++;
		}

		nID++;
	}



	CString sztext;

	if(stNew.nsNotyMethod != 0xFFFF && stNew.nsNotyMethod != 0xFFFFFFFF)
		stNew.nsNotyMethod = m_Combo_NotifyMethod.GetCurSel();

	GetDlgItem(IDC_EDIT_IOOUTPUTID)->GetWindowText(sztext);
	if(strcmp(stNew.strIoOutputID, "NA"))
		StringCopyTo(sztext, stNew.strIoOutputID);

	int nValue = 0;
	if(stNew.nsNotyRecurrence != 0xFFFF && stNew.nsNotyRecurrence != 0xFFFFFFFF)
	{
		if(GetDlgItem(IDC_RADIO_BEGIN)->SendMessage(BM_GETCHECK) == BST_CHECKED)
		{
			stNew.nsNotyRecurrence = 0; //begin
		}
		else if(GetDlgItem(IDC_RADIO_BEGIN_END)->SendMessage(BM_GETCHECK) == BST_CHECKED)
		{
			stNew.nsNotyRecurrence = 1; //begin and end
		}
		else if(GetDlgItem(IDC_RADIO_RECURRING)->SendMessage(BM_GETCHECK) == BST_CHECKED)
		{
			stNew.nsNotyRecurrence = 2; //recur
		}
	}

	long lret = SPIDER_AddEventTriggerNotifyInfo(theApp.m_hSelectCamera, nTriggerIndex, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

	InitInfo();
}

void CEventTriggerInfoDlg::OnBnClickedButtonDeleteNotify()
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_TreeTrigger.GetSelectedItem();

	if(hItem == NULL)
		return;

	int nNotifyIndex = 0;

	if(m_TreeTrigger.GetParentItem(hItem) == NULL)
		return;

	nNotifyIndex = m_TreeTrigger.GetItemData(hItem);
	hItem = m_TreeTrigger.GetParentItem(hItem);

	int nTriggerIndex = m_TreeTrigger.GetItemData(hItem);
	if(nTriggerIndex >= m_vInfo.size())
		return;
	
	int nDeleteIndex = nNotifyIndex;

	long lret = SPIDER_DeleteEventTriggerNotifyInfo(theApp.m_hSelectCamera, nTriggerIndex, nDeleteIndex);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();

}

void CEventTriggerInfoDlg::OnBnClickedButtonModifyTrigger()
{
	HTREEITEM hItem = m_TreeTrigger.GetSelectedItem();

	if(hItem == NULL)
		return;

	int nNotifyIndex = 0;

	if(m_TreeTrigger.GetParentItem(hItem))
	{
		nNotifyIndex = m_TreeTrigger.GetItemData(hItem);
		hItem = m_TreeTrigger.GetParentItem(hItem);
	}

	int nTriggerIndex = m_TreeTrigger.GetItemData(hItem);
	if(nTriggerIndex >= m_vInfo.size())
		return;
	
	int nModifyIndex = nTriggerIndex;
	ST_SPIDER_EVENT_TRIGGER_INFO stNew = m_vInfo.at(nModifyIndex);

	CString sztext;

	GetDlgItem(IDC_EDIT_EVENT_DESC)->GetWindowText(sztext);
	if(strcmp(stNew.strEventDesc, "NA"))
		StringCopyTo(sztext, stNew.strEventDesc);

	GetDlgItem(IDC_EDIT_IOINPUTID)->GetWindowText(sztext);
	if(strcmp(stNew.strIoInputID, "NA"))
		StringCopyTo(sztext, stNew.strIoInputID);

	if(stNew.nsEventType != 0xFFFF && stNew.nsEventType != 0xFFFFFFFF)
		stNew.nsEventType = m_Combo_EventType.GetCurSel();

	int nValue = 0;
	GetDlgItem(IDC_EDIT_EVENT_INTERVAL)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nIntervalOfEvent != 0xFFFF && stNew.nIntervalOfEvent != 0xFFFFFFFF)
		stNew.nIntervalOfEvent = nValue;




	unsigned int notifycount = SPIDER_GetEventTriggerNotifyCount(theApp.m_hSelectCamera, nTriggerIndex);
	ST_SPIDER_EVENT_TRIGGER_NOTIFY_INFO* pNotifyList = new ST_SPIDER_EVENT_TRIGGER_NOTIFY_INFO[notifycount];
	for(int nNotifyIndex = 0; nNotifyIndex < notifycount; nNotifyIndex++)
	{
		long lret = SPIDER_GetEventTriggerNotifyInfo(theApp.m_hSelectCamera, nTriggerIndex, nNotifyIndex, &pNotifyList[nNotifyIndex]);
	}

	long lret = SPIDER_SetEventTriggerInfo(theApp.m_hSelectCamera, stNew, notifycount, pNotifyList);

	delete [] pNotifyList;

	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();
}

void CEventTriggerInfoDlg::OnBnClickedButtonModifyNotify()
{
	HTREEITEM hItem = m_TreeTrigger.GetSelectedItem();

	if(hItem == NULL)
		return;

	int nNotifyIndex = 0;

	if(m_TreeTrigger.GetParentItem(hItem))
	{
		nNotifyIndex = m_TreeTrigger.GetItemData(hItem);
		hItem = m_TreeTrigger.GetParentItem(hItem);
	}

	int nTriggerIndex = m_TreeTrigger.GetItemData(hItem);
	if(nTriggerIndex >= m_vInfo.size())
		return;
	
	ST_SPIDER_EVENT_TRIGGER_NOTIFY_INFO stNotify;
	long lret = SPIDER_GetEventTriggerNotifyInfo(theApp.m_hSelectCamera, nTriggerIndex, nNotifyIndex, &stNotify);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
		return;
	}
	

	int nModifyIndex = nNotifyIndex;
	ST_SPIDER_EVENT_TRIGGER_NOTIFY_INFO stNew = stNotify;

	CString sztext;

	if(stNew.nsNotyMethod != 0xFFFF && stNew.nsNotyMethod != 0xFFFFFFFF)
		stNew.nsNotyMethod = m_Combo_NotifyMethod.GetCurSel();

	GetDlgItem(IDC_EDIT_IOOUTPUTID)->GetWindowText(sztext);
	if(strcmp(stNew.strIoOutputID, "NA"))
		StringCopyTo(sztext, stNew.strIoOutputID);

	int nValue = 0;
	if(stNew.nsNotyRecurrence != 0xFFFF && stNew.nsNotyRecurrence != 0xFFFFFFFF)
	{
		if(GetDlgItem(IDC_RADIO_BEGIN)->SendMessage(BM_GETCHECK) == BST_CHECKED)
		{
			stNew.nsNotyRecurrence = 0; //begin
		}
		else if(GetDlgItem(IDC_RADIO_BEGIN_END)->SendMessage(BM_GETCHECK) == BST_CHECKED)
		{
			stNew.nsNotyRecurrence = 1; //begin and end
		}
		else if(GetDlgItem(IDC_RADIO_RECURRING)->SendMessage(BM_GETCHECK) == BST_CHECKED)
		{
			stNew.nsNotyRecurrence = 2; //recur
		}
	}

	lret = SPIDER_SetEventTriggerNotifyInfo(theApp.m_hSelectCamera, nTriggerIndex, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();
}

void CEventTriggerInfoDlg::OnNMDblclkTreeTrigger(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
