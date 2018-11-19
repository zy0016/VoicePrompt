#if !defined(AFX_BATCHOUTPUT_H__A71B0738_5996_4C56_ACDC_8523221C0AD5__INCLUDED_)
#define AFX_BATCHOUTPUT_H__A71B0738_5996_4C56_ACDC_8523221C0AD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatchOutput.h : header file
//
#include "voicepromptinfo.h"
#include "BatchListCtrl.h"
#include "AddBatchInfor.h"
#include "VoiceDataManage.h"
#include "BatchOutputOption.h"
#include "MyProgressCtrl.h"
#include "LanguagePackInfo.h"
/////////////////////////////////////////////////////////////////////////////
// BatchOutput dialog

class BatchOutput : public CDialog
{
// Construction
public:
	BatchOutput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BatchOutput)
	enum { IDD = IDD_DIALOG_BATCHOUTPUTFILES };
	CStatic	m_Static_OutputFileCount;
	CMyProgressCtrl	m_Progress_BatchOutput;
	BatchListCtrl	m_List_BatchOutput;
	CButton	m_Language_Down;
	CButton	m_Language_Up;
	CButton	m_Language_MoveDown;
	CButton	m_Language_MoveTop;
	CCheckListBox	m_ctlCheckList;
	//}}AFX_DATA

private:
    CString csDataContent,csPosContent,csDataFilename,csPosFilename,csDataVariable,csPosVariable;
    CString csChooseFold,csRootFold;
    void ClewBatchOutputFileCount(void);
    int Voice_GetOutputFilesCount(void);//Get output file count
    int Voice_GetLanguageCount(CString csLanguage);
    BOOL ReadConfigFile(void);
    void ReadBatchOutputFile(void);
    BOOL Voice_JustTheDataValid(CString csBatchLanguages,CString csFilename,CString csPathname);
    BOOL Voice_ReadParameter(void);
    BOOL Voice_JustTheFileProperties(CString csBatchLanguages,CString csFilename,CString csPathname,
        CString &csOutputCount);
    BOOL Voice_JustSingleFileProperties(CString csFilename);
    CString Voice_GetUndefineLanguage(CString csDefineLanguage);
    typedef enum ConfigType
    {
        CONFIGTYPE_LANGUAGE,
        CONFIGTYPE_NONE
    };
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BatchOutput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BatchOutput)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListBatchlanguage();
	afx_msg void OnButtonBatchTop();
	afx_msg void OnButtonBatchbelow();
	afx_msg void OnButtonBatchUp();
	afx_msg void OnButtonBatchdown();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonAddbatchitem();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonBatchoutput();
	afx_msg void OnButtonOption();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHOUTPUT_H__A71B0738_5996_4C56_ACDC_8523221C0AD5__INCLUDED_)
