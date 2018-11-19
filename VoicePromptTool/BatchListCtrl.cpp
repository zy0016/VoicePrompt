// BatchListCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "voiceprompt.h"
#include "BatchListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BatchListCtrl

BatchListCtrl::BatchListCtrl()
{
}

BatchListCtrl::~BatchListCtrl()
{
}


BEGIN_MESSAGE_MAP(BatchListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(BatchListCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BatchListCtrl message handlers

void BatchListCtrl::SetListCtrlText(void)
{
    CString column1 = "Output Language",column2 = "Select Language file",column3 = "Output Path",column4 = "Size";
    int iListCount = GetItemCount();

    //column1.LoadString(IDS_STRING_BATCH_OUTPUTLAN);
    //column2.LoadString(IDS_STRING_BATCH_SELLANFILE);
    //column3.LoadString(IDS_STRING_BATCH_OUTFOLD);
    //column4.LoadString(IDS_STRING_FILESIZE);
   
    InsertColumn(0,column1,LVCFMT_LEFT,200,0);
    InsertColumn(1,column2,LVCFMT_LEFT,400,0);
    InsertColumn(2,column3,LVCFMT_LEFT,400,0);
    InsertColumn(3,column4,LVCFMT_LEFT,120,0);
}

void BatchListCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	DWORD oldStyle = GetExtendedStyle();
	SetExtendedStyle(oldStyle |LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES);
    
    ////////////////////////////////////////////////////
	CListCtrl::PreSubclassWindow();

    RECT rListCtrl;
    GetClientRect(&rListCtrl);

    CString cClewToolTip = "Click mouse right button";
    //cClewToolTip.LoadString(IDS_STRING_MOUSECLEW);
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(this,cClewToolTip, &rListCtrl, IDC_TOOLTIP_ID);
}

BOOL BatchListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);
	return CListCtrl::PreTranslateMessage(pMsg);
}

void BatchListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	POSITION pos = GetFirstSelectedItemPosition();
	int nSelectedItem = GetNextSelectedItem(pos);//获得列表框中当前选择的项目
    
    if (nSelectedItem != -1)
    {
        PostMessage(WM_COMMAND,IDC_MENU_MODIFY,0);
    }
	CListCtrl::OnLButtonDblClk(nFlags, point);
}

BOOL BatchListCtrl::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	POSITION pos = GetFirstSelectedItemPosition();
	int nSelectedItem = GetNextSelectedItem(pos);//获得列表框中当前选择的项目
    CString cFileSour,cFileDes;

    if (nSelectedItem == -1)//没有选择项目
        nSelectedItem = 0;
    
    switch(wParam) 
    {
    case IDC_MENU_MODIFY://修改项目
        /*{
            CAddBatchInfor cAddBatchInfo(NULL,GetItemText(nSelectedItem,0),BATCH_MODIFY_MODIFY,
                GetItemText(nSelectedItem,1),GetItemText(nSelectedItem,2));

            CString csFilename,csFoldname;

            if (cAddBatchInfo.DoModal() == IDOK)
            {
                cAddBatchInfo.GetEnumFileName(csFilename,csFoldname);
                SetItemText(nSelectedItem,1,csFilename);
                SetItemText(nSelectedItem,2,csFoldname);
            }
        }*/
        break;
    case IDC_MENU_DELETEFILE://delete
        break;
    }
	return CListCtrl::OnCommand(wParam, lParam);
}

void BatchListCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	{
        CRect rect;
	    GetClientRect(rect);
        ClientToScreen(rect);
		if (point.x == -1 && point.y == -1)
		{
			//keystroke invocation						
			point = rect.TopLeft();
			point.Offset(5, 5);
		}
        if (GetItemCount() == 0)//没有选择项目
        {
            return;
        }

		CPoint cPoint = point;

		{
            CMenu m_Menu;
            CBitmap	cDelete;
            CString cModify = "Modify",csDelete = "Delete";

            //csDelete.LoadString(IDS_STRING_MENUDELETE);
            //cModify.LoadString(IDS_STRING_MENUMODIFY);//修改项目(&M)

            //cDelete.LoadBitmap(IDB_BITMAP_DELETE);
            
            m_Menu.CreatePopupMenu();
            m_Menu.AppendMenu( MF_STRING, IDC_MENU_MODIFY,cModify);
            //m_Menu.AppendMenu( MF_STRING, IDC_MENU_DELETEFILE,csDelete);
            
            m_Menu.SetMenuItemBitmaps(IDC_MENU_DELETEFILE,MF_BYCOMMAND,&cDelete,&cDelete);

            POSITION pos = GetFirstSelectedItemPosition();
	        int nSelectedItem = GetNextSelectedItem(pos);//获得列表框中当前选择的项目
            int iCount = GetItemCount();

            if (nSelectedItem == -1)//没有选择项目
            {
                EnableMenuItem(m_Menu,IDC_MENU_DELETEFILE,MF_GRAYED);
                EnableMenuItem(m_Menu,IDC_MENU_MODIFY,MF_GRAYED);
            }
            m_Menu.TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, cPoint.x, cPoint.y, this );
		}
	}
}
