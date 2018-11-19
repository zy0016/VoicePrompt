  // VoicePromptDlg.h : header file
//

#if !defined(AFX_VOICEPROMPTDLG_H__D76628D9_107C_4F83_AA23_20767B97B72B__INCLUDED_)
#define AFX_VOICEPROMPTDLG_H__D76628D9_107C_4F83_AA23_20767B97B72B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VoicePromptListCtrl.h"
#include "VoicePrompt_Option.h"
#include "LanguagePackInfo.h"
#include "cOutputFiles.h"
#include "EnumInfo.h"
#include "BatchOutput.h"
#include "BatchOutputOption.h"
#include "VoiceDataManage.h"
/////////////////////////////////////////////////////////////////////////////
// CVoicePromptDlg dialog

CString GetCurrentAppPath(void);//返回当前应用所在路径
CString GetVoicePromptLanguage(void);
BOOL FileIfExist(CString cFilename);
static CString CurrentAppPath;//当前应用所在路径
static CString cSelectLanguage;

class CVoicePromptDlg : public CDialog
{
// Construction
public:
	CVoicePromptDlg(CWnd* pParent = NULL);	// standard constructor

    CCheckListBox	m_ctlCheckList;
// Dialog Data
	//{{AFX_DATA(CVoicePromptDlg)
	enum { IDD = IDD_VOICEPROMPT_DIALOG };
	CStatic	m_Static_LanguageCount;
	CButton	m_Language_MoveDown;
	CButton	m_Language_MoveTop;
	CStatic	m_Static_Filesize;
	CButton	m_DeleteLanguage;
	CVoicePromptListCtrl	m_VoicePromptListCtrl;
	CButton	m_Language_Down;
	CButton	m_Language_Up;
	CButton	m_Button_AddLanguage;
	CEdit	m_Edit_Language;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoicePromptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

    private:
		bool DownFile(LPCTSTR url,CString filename);
        BOOL CheckFilesExist(void);
        void DisplayLanguageCount(void);
        BOOL ReadConfigFile(void);
        void ReadEnumFileInformation(CString csLanguageIndex);
        CString GetLanguagePackSize(CString csLanguage,int * pFileCount,DWORD * pAllFilesize);
        CString GetFileListFromConfig(BOOL bDefine,CString csLanguage) ;
        BOOL JustTheFilesExist(void);
        BOOL SelectLanguageConfirm(CString csLanDefine);
        CString GetLanguagePackSizeActual(CString csLanguage,int * pFileCount,DWORD * pAllFilesize);
        CString GetLanguagePackSizeSilent(CString csLanguage);

#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
        int iTimes;
#endif
        CVoicePrompt_Option cOptionDialog;
        typedef enum ConfigType
        {
            CONFIGTYPE_LANGUAGE,
            CONFIGTYPE_ENUM,
            CONFIGTYPE_FILEINFO,
            CONFIGTYPE_NONE
        };
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVoicePromptDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEditLanguage();
	afx_msg void OnSelchangeListLanguage();
	afx_msg void OnButtonAddlanguage();
	afx_msg void OnButtonDeletelanguage();
	afx_msg void OnButtonLanguageup();
	afx_msg void OnButtonLanguagedown();
	afx_msg void OnButtonOption();
	afx_msg void OnButtonOutputfiles();
	afx_msg void OnButtonCountlanguagessize();
	afx_msg void OnButtonClearall();
	afx_msg void OnButtonMovetop();
	afx_msg void OnButtonMovebelow();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonCheckfile();
	afx_msg void OnButtonCountalllanguages();
	afx_msg void OnButtonCountsilent();
	afx_msg void OnButtonBatchoutputfiles();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonTest();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOICEPROMPTDLG_H__D76628D9_107C_4F83_AA23_20767B97B72B__INCLUDED_)
