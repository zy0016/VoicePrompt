    // VoicePromptListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "VoicePrompt.h"
#include "VoicePromptListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVoicePromptListCtrl

CVoicePromptListCtrl::CVoicePromptListCtrl()
{
}

CVoicePromptListCtrl::~CVoicePromptListCtrl()
{
}


BEGIN_MESSAGE_MAP(CVoicePromptListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CVoicePromptListCtrl)
    ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoicePromptListCtrl message handlers

void CVoicePromptListCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	//重新设置listctrl控件风格
	DWORD oldStyle = GetExtendedStyle();
	SetExtendedStyle(oldStyle |LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES);
    
    //发送消息,初始化列表,添加第一项
    PostMessage(WM_COMMAND,LISTCTRL_INIT_WPARAM,LISTCTRL_INIT_LPARAM);
    ////////////////////////////////////////////////////
	CListCtrl::PreSubclassWindow();

    RECT rListCtrl;
    GetClientRect(&rListCtrl);

    CString cClewToolTip;
    cClewToolTip.LoadString(IDS_STRING_MOUSECLEW);
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(this,cClewToolTip, &rListCtrl, IDC_TOOLTIP_ID);
}

void CVoicePromptListCtrl::SetListCtrlText(void)
{
    CString column1,column2,column3,column4;
    int iListCount = GetItemCount();

    column1.LoadString(IDS_STRING_ENUMNAME);
    column2.LoadString(IDS_STRING_FILENAME);
    column3.LoadString(IDS_STRING_FILEEXIST);
    column4.LoadString(IDS_STRING_FILESIZE);
    
    InsertColumn(0,column1,LVCFMT_LEFT,200,0);
    InsertColumn(1,column2,LVCFMT_LEFT,400,0);
    InsertColumn(2,column3,LVCFMT_LEFT,50,0);
    InsertColumn(3,column4,LVCFMT_LEFT,70,0);
}

BOOL CVoicePromptListCtrl::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
    if ((wParam == LISTCTRL_INIT_WPARAM) && (lParam == LISTCTRL_INIT_LPARAM))
    {   
        return TRUE;
    }

    POSITION pos = GetFirstSelectedItemPosition();
	int nSelectedItem = GetNextSelectedItem(pos);//获得列表框中当前选择的项目
    CString cFileSour,cFileDes;

    if (nSelectedItem == -1)//没有选择项目
        nSelectedItem = 0;

    switch(wParam) 
    {
    case IDC_MENU_ADDFILES://添加项目  
        {
            CString cClew,cEnumClew;
            cClew.LoadString(IDS_STRING_CLEW);
            cEnumClew.LoadString(IDS_STRING_ADDENUMCLEW);
            //if (MessageBox(cEnumClew,cClew,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2) == IDNO)
            MessageBox(cEnumClew,cClew,MB_ICONQUESTION);
            {
                break;
            }
            CEnumInfo CDEnuminfo(NULL,OPERATETYPE_ADD,"","");
            if (CDEnuminfo.DoModal() == IDOK)
            {
                CString csEnum,csFilename,csYes;
                int iListCount = GetItemCount();
                CDEnuminfo.GetEnumFileName(csEnum,csFilename);

                csYes.LoadString(IDS_STRING_YES);
                InsertItem(iListCount,csEnum);
                SetItemText(iListCount,1,csFilename);
                SetItemText(iListCount,2,csYes);
            }
        }
    	break;
    case IDC_MENU_DELETEFILE://删除项目
        if ((nSelectedItem != GetItemCount() - 1) && (nSelectedItem != -1))//删除一项
        {
            CString cFileSour,cDelClew,cClew,cue;
            cFileSour = GetItemText(nSelectedItem,0);

            if (MessageBox(cue,cClew,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2) == IDYES)
                DeleteItem(nSelectedItem);
        }
    	break;
    case IDC_MENU_MODIFY://修改项目
        {
            CEnumInfo CDEnuminfo(NULL,OPERATETYPE_EDIT,GetItemText(nSelectedItem,0),GetItemText(nSelectedItem,1));
            if (CDEnuminfo.DoModal() == IDOK)
            {
                CString csEnum,csFilename;
                CDEnuminfo.GetEnumFileName(csEnum,csFilename);
                SetItemText(nSelectedItem,0,csEnum);
                SetItemText(nSelectedItem,1,csFilename);
            }
        }
        break;
    }

	return CListCtrl::OnCommand(wParam, lParam);
}

BOOL CVoicePromptListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);
	return CListCtrl::PreTranslateMessage(pMsg);
}

void CVoicePromptListCtrl::OnContextMenu(CWnd*, CPoint point)
{
	// CG: This block was added by the Pop-up Menu component
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
            CBitmap	cAddFiles,cDelete;
            CString cAdd,cModify/*,csDelete*/;

            cAdd.LoadString(IDS_STRING_MENUADD);//添加项目(&A)
            cModify.LoadString(IDS_STRING_MENUMODIFY);//修改项目(&M)
            //csDelete.LoadString(IDS_STRING_MENUDELETE);//删除项目(&D)

            cAddFiles.LoadBitmap(IDB_BITMAP_NEW);
            cDelete.LoadBitmap(IDB_BITMAP_DELETE);
            
            m_Menu.CreatePopupMenu();
            m_Menu.AppendMenu( MF_STRING, IDC_MENU_ADDFILES, cAdd);
            m_Menu.AppendMenu( MF_STRING, IDC_MENU_MODIFY,cModify);
            //m_Menu.AppendMenu( MF_STRING, IDC_MENU_DELETEFILE,csDelete);
            
            m_Menu.SetMenuItemBitmaps(IDC_MENU_ADDFILES,MF_BYCOMMAND,&cAddFiles,&cAddFiles);
            //m_Menu.SetMenuItemBitmaps(IDC_MENU_DELETEFILE,MF_BYCOMMAND,&cDelete,&cDelete);

            POSITION pos = GetFirstSelectedItemPosition();
	        int nSelectedItem = GetNextSelectedItem(pos);//获得列表框中当前选择的项目
            int iCount = GetItemCount();

            if (nSelectedItem == -1)//没有选择项目
            {
                //EnableMenuItem(m_Menu,IDC_MENU_DELETEFILE,MF_GRAYED);
                EnableMenuItem(m_Menu,IDC_MENU_MODIFY,MF_GRAYED);
            }
            m_Menu.TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, cPoint.x, cPoint.y, this );
		}
	}
}

void CVoicePromptListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
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
