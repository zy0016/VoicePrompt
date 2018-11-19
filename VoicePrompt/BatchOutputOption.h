#if !defined(AFX_BATCHOUTPUTOPTION_H__3F8ED1ED_E23A_43EF_B365_BB11B2839762__INCLUDED_)
#define AFX_BATCHOUTPUTOPTION_H__3F8ED1ED_E23A_43EF_B365_BB11B2839762__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatchOutputOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BatchOutputOption dialog
#include "voicepromptinfo.h"
#include "VoiceDataManage.h"
class BatchOutputOption : public CDialog
{
// Construction
public:
	BatchOutputOption(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BatchOutputOption)
	enum { IDD = IDD_DIALOG_BATCH_OUTPUT_OPTION };
	CEdit	m_Edit_ChooseLanguageFold;
	CEdit	m_Edit_RootFold;
	//}}AFX_DATA

private:
    CString csChooseLanguageFold,csRootFoldString;
    static int CALLBACK SetSelProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
    void Voice_SetFold(CEdit & cEdit);
    BOOL Voice_ClewCreateFold(CString csFold);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BatchOutputOption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BatchOutputOption)
	afx_msg void OnButtonChoosefold();
	afx_msg void OnButtonLanguagerootFold();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHOUTPUTOPTION_H__3F8ED1ED_E23A_43EF_B365_BB11B2839762__INCLUDED_)
