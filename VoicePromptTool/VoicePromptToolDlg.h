// VoicePromptToolDlg.h : header file
//

#if !defined(AFX_VOICEPROMPTTOOLDLG_H__FE2AE037_DACB_4F11_BE5E_A3A35BAF6389__INCLUDED_)
#define AFX_VOICEPROMPTTOOLDLG_H__FE2AE037_DACB_4F11_BE5E_A3A35BAF6389__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVoicePromptToolDlg dialog
#include "BatchListCtrl.h"
#include "VoiceDataManage.h"
#include "BatchOutputOption.h"
class CVoicePromptToolDlg : public CDialog
{
// Construction
public:
	CVoicePromptToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVoicePromptToolDlg)
	enum { IDD = IDD_VOICEPROMPTTOOL_DIALOG };
	CStatic	m_Static_OutputFileCount;
	BatchListCtrl	m_List_BatchOutput;
	CStatic	m_Static_LanguageCount;
	CEdit	m_Edit_Language;
	CButton	m_Language_Down;
	CButton	m_Language_MoveDown;
	CButton	m_Language_MoveTop;
	CButton	m_Language_Up;
    CCheckListBox	m_ctlCheckList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoicePromptToolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

private:
    CString csDataContent,csPosContent,csDataFilename,csPosFilename,csDataVariable,csPosVariable;
    CString csChooseFold,csRootFold;
    
    void DisplayLanguageCount(void);
    void ReadBatchOutputFile(void);
    BOOL Voice_ReadParameter(void);
    void ClewBatchOutputFileCount(void);
    int Voice_GetOutputFilesCount(void);//Get output file count
    int Voice_GetLanguageCount(CString csLanguage);
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVoicePromptToolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeListLanguage();
	afx_msg void OnChangeEditSearchlanguage();
	afx_msg void OnButtonMovetop();
	afx_msg void OnButtonLanguageup();
	afx_msg void OnButtonMovebelow();
	afx_msg void OnButtonLanguagedown();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonOption();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOICEPROMPTTOOLDLG_H__FE2AE037_DACB_4F11_BE5E_A3A35BAF6389__INCLUDED_)
