#if !defined(AFX_VOICEPROMPTLISTCTRL_H__0A38DEC4_2572_4D2D_8305_916BD5E80EF4__INCLUDED_)
#define AFX_VOICEPROMPTLISTCTRL_H__0A38DEC4_2572_4D2D_8305_916BD5E80EF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VoicePromptListCtrl.h : header file
//
#define IDC_TOOLTIP_ID			1
#define LISTCTRL_INIT_WPARAM    WM_USER + 100//初始化控件的wparam
#define LISTCTRL_INIT_LPARAM    WM_USER + 100//初始化控件的lparam

#define IDC_MENU_ADDFILES		200//添加项目
#define IDC_MENU_DELETEFILE		210//删除项目
#define IDC_MENU_MODIFY         220//修改项目

#include "EnumInfo.h"
/////////////////////////////////////////////////////////////////////////////
// CVoicePromptListCtrl window

class CVoicePromptListCtrl : public CListCtrl
{
// Construction
public:
	CVoicePromptListCtrl();

// Attributes
public:
    void SetListCtrlText(void);
private:
    CToolTipCtrl m_ToolTip;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoicePromptListCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVoicePromptListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVoicePromptListCtrl)
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOICEPROMPTLISTCTRL_H__0A38DEC4_2572_4D2D_8305_916BD5E80EF4__INCLUDED_)
