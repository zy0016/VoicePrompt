#if !defined(AFX_VOICEPROMPT_OPTION_H__EEFAB82D_6456_43C5_A105_D919107F197E__INCLUDED_)
#define AFX_VOICEPROMPT_OPTION_H__EEFAB82D_6456_43C5_A105_D919107F197E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VoicePrompt_Option.h : header file
//
#include "voicepromptinfo.h"
/////////////////////////////////////////////////////////////////////////////
// CVoicePrompt_Option dialog
extern CString GetCurrentAppPath (void);

class CVoicePrompt_Option : public CDialog
{
// Construction
public:
	CVoicePrompt_Option(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVoicePrompt_Option)
	enum { IDD = IDD_DIALOG_OPTION };
	CEdit	m_Edit_Pos_Content;
	CEdit	m_Edit_Data_Content;
	CEdit	m_Edit_Pos_Variable;
	CEdit	m_Edit_Pos_Filename;
	CEdit	m_Edit_Data_Variable;
	CEdit	m_Edit_Data_Filename;
	//}}AFX_DATA

private:
    CString csData_Filename,csData_Variable,csData_Content,csPos_Filename,csPos_Variable,csPos_Content;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoicePrompt_Option)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVoicePrompt_Option)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOICEPROMPT_OPTION_H__EEFAB82D_6456_43C5_A105_D919107F197E__INCLUDED_)
