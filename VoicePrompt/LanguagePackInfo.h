#if !defined(AFX_LANGUAGEPACKINFO_H__9131C97E_0698_4A70_A11C_2B169D8D02F4__INCLUDED_)
#define AFX_LANGUAGEPACKINFO_H__9131C97E_0698_4A70_A11C_2B169D8D02F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LanguagePackInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLanguagePackInfo dialog

class CLanguagePackInfo : public CDialog
{
// Construction
public:
	CLanguagePackInfo(CWnd* pParent = NULL);   // standard constructor

    CLanguagePackInfo(CWnd* pParent /*=NULL*/,CString csLanguageInfo,CString cTitle);
// Dialog Data
	//{{AFX_DATA(CLanguagePackInfo)
	enum { IDD = IDD_DIALOG_FILESIZECOUNT };
	CEdit	m_Edit_LanguagePackInfo;
	//}}AFX_DATA

private:
    CString csLanguagePackInfo,csTitle;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLanguagePackInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLanguagePackInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANGUAGEPACKINFO_H__9131C97E_0698_4A70_A11C_2B169D8D02F4__INCLUDED_)
