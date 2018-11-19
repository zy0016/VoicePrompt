#if !defined(AFX_ENUMINFO_H__0892128D_C231_49B0_AA2D_7537C3904DC4__INCLUDED_)
#define AFX_ENUMINFO_H__0892128D_C231_49B0_AA2D_7537C3904DC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnumInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEnumInfo dialog
#include "FileDialogEx.h"
#include "voicepromptinfo.h"
#include "VoiceDataManage.h"
typedef enum
{
    OPERATETYPE_ADD,//添加项目
    OPERATETYPE_EDIT//编辑项目
}OPERATETYPE;       //操作类型
extern CString GetCurrentAppPath (void);
extern CString GetVoicePromptLanguage(void);

class CEnumInfo : public CDialog
{
// Construction
public:
	CEnumInfo(CWnd* pParent = NULL);   // standard constructor
    
    CEnumInfo(CWnd* pParent /*= NULL*/,OPERATETYPE eOperatetype,
        CString csEnum,CString csFilename);
    void GetEnumFileName(CString & csEnum,CString & cFileName);
// Dialog Data
	//{{AFX_DATA(CEnumInfo)
	enum { IDD = IDD_DIALOG_ENUMINFO };
	CComboBox	m_Combo_Filename;
	CComboBox	m_Combo_Enum;
	//}}AFX_DATA

private:
    OPERATETYPE OperateType;
    CString Item_Enum;
    CString Item_Filename;
    CString Item_File;

    void ReadEnumFileInformation(void);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnumInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnumInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonPath();
	afx_msg void OnDropdownComboEnum();
	afx_msg void OnDropdownComboFilename();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENUMINFO_H__0892128D_C231_49B0_AA2D_7537C3904DC4__INCLUDED_)
