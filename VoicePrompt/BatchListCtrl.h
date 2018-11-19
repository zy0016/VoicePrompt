#if !defined(AFX_BATCHLISTCTRL_H__F916680D_E561_48AE_90B0_97D5882A07A5__INCLUDED_)
#define AFX_BATCHLISTCTRL_H__F916680D_E561_48AE_90B0_97D5882A07A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatchListCtrl.h : header file
//

#define IDC_TOOLTIP_ID			1

#define IDC_MENU_MODIFY         220//修改项目
#define IDC_MENU_DELETEFILE		210//删除项目
/////////////////////////////////////////////////////////////////////////////
// BatchListCtrl window
#include "AddBatchInfor.h"

class BatchListCtrl : public CListCtrl
{
// Construction
public:
	BatchListCtrl();

// Attributes
public:
    void SetListCtrlText(void);
private:
    CToolTipCtrl m_ToolTip;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BatchListCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~BatchListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(BatchListCtrl)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHLISTCTRL_H__F916680D_E561_48AE_90B0_97D5882A07A5__INCLUDED_)
