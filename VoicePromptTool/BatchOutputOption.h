#if !defined(AFX_BATCHOUTPUTOPTION_H__0560A75F_9BC0_4212_AB7C_FB9A5E2E91C6__INCLUDED_)
#define AFX_BATCHOUTPUTOPTION_H__0560A75F_9BC0_4212_AB7C_FB9A5E2E91C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatchOutputOption.h : header file
//
#include "voicepromptinfo.h"
#include "VoiceDataManage.h"
/////////////////////////////////////////////////////////////////////////////
// BatchOutputOption dialog

class BatchOutputOption : public CDialog
{
// Construction
public:
	BatchOutputOption(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BatchOutputOption)
	enum { IDD = IDD_DIALOG_BATCH_OUTPUT_OPTION };
	CEdit	m_Edit_RootFold;
	CEdit	m_Edit_ChooseLanguageFold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BatchOutputOption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
    private:
        CString csChooseLanguageFold,csRootFoldString;
        static int CALLBACK SetSelProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
        void Voice_SetFold(CEdit & cEdit);
        BOOL Voice_ClewCreateFold(CString csFold);
protected:

	// Generated message map functions
	//{{AFX_MSG(BatchOutputOption)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonChoosefold();
	afx_msg void OnButtonLanguagerootFold();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHOUTPUTOPTION_H__0560A75F_9BC0_4212_AB7C_FB9A5E2E91C6__INCLUDED_)
