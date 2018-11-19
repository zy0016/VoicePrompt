#if !defined(AFX_ADDBATCHINFOR_H__2ACF1071_EB71_47AE_96DB_CA4B398F9D3D__INCLUDED_)
#define AFX_ADDBATCHINFOR_H__2ACF1071_EB71_47AE_96DB_CA4B398F9D3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddBatchInfor.h : header file
//
#include "FileDialogEx.h"
#include "voicepromptinfo.h"
#include "VoiceDataManage.h"
/////////////////////////////////////////////////////////////////////////////
// CAddBatchInfor dialog

typedef enum
{
    BATCH_MODIFY_ADD,
    BATCH_MODIFY_MODIFY
}BATCH_DIALOG_TYPE;

class CAddBatchInfor : public CDialog
{
// Construction
public:
	CAddBatchInfor(CWnd* pParent = NULL);   // standard constructor

    CAddBatchInfor(CWnd* pParent /*= NULL*/,CString csLanguages,BATCH_DIALOG_TYPE eDialogtype,
        CString csInitFilename,CString csInitFold);

    void GetEnumFileName(CString & csFilename,CString & csPathname);
// Dialog Data
	//{{AFX_DATA(CAddBatchInfor)
	enum { IDD = IDD_DIALOG_BATCHADD };
	CComboBox	m_Combo_SelectPath;
	CComboBox	m_Combo_Filename;
	CStatic	m_Static_Language;
	//}}AFX_DATA


private:
    CString cLanguages;
    CString csSelectLanguageFilename,csLanguagesPackPath;
    CString csInitFile,csInitPath;

    CString csChooseFileName,csRootFoldName;

    BATCH_DIALOG_TYPE eDialogType;
    static int CALLBACK SetSelProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddBatchInfor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddBatchInfor)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBatchselfile();
	afx_msg void OnButtonSelectfold();
	virtual void OnOK();
	afx_msg void OnDropdownComboSelectfile();
	afx_msg void OnDropdownComboSelectpath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDBATCHINFOR_H__2ACF1071_EB71_47AE_96DB_CA4B398F9D3D__INCLUDED_)
