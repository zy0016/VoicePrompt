#if !defined(AFX_COUTPUTFILES_H__52D9B1B2_580A_4882_8420_AFC51FABA598__INCLUDED_)
#define AFX_COUTPUTFILES_H__52D9B1B2_580A_4882_8420_AFC51FABA598__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// cOutputFiles.h : header file
//
#include "voicepromptinfo.h"
#include "MyProgressCtrl.h"
#include "afxadv.h"
#include "VoiceDataManage.h"
/////////////////////////////////////////////////////////////////////////////
// cOutputFiles dialog

class cOutputFiles : public CDialog
{
// Construction
public:
	cOutputFiles(CWnd* pParent = NULL);   // standard constructor

    cOutputFiles(CWnd* pParent /*=NULL*/,
        CString clanguageD,CString clanguageU,int iLanCount,int iOutLanguageCount);
// Dialog Data
	//{{AFX_DATA(cOutputFiles)
	enum { IDD = IDD_DIALOG_OUTFILES };
	CMyProgressCtrl	m_Progress;
	CComboBox	m_Combo_SelectPath;
	//}}AFX_DATA

private:
    typedef enum ConfigType
    {
        CONFIGTYPE_LANGUAGE,
        CONFIGTYPE_ENUM,
        CONFIGTYPE_FILEINFO,
        CONFIGTYPE_NONE
    };
#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
    int iTimes,iFileTimes,iCountConfigTimes;
    CString csDefaultLanguage;
#endif
    //////////////////////////////////////////////////////////////////////////
    BOOL bSelectLanguagePos,bSelectLanguageData;
    int iFileIndexPos,iFileIndexData;
    //////////////////////////////////////////////////////////////////////////
    int iLanguageCount,iOutFileCount,iOutputLanguageOut;
    CString csLanguage_Define,csLanguage_Undef;
    CString csDataContent,csPosContent,csDataFilename,csPosFilename,csDataVariable,csPosVariable;

    BOOL OutputFilesSizeInfor(CString csLanString);
    CString GetLanguagePackSize(CString csLanguage,int * pFileCount,DWORD * pAllFilesize);

    void OutputLanguageFilesData(CString cLanguagePath);
    CString OutputSingleLanguageFile(CString cSingleLanguage);

    CString GetDefineLanguageList(CString csLanString,BOOL bDefine);
    CString GetIncludeLanguage(CString csLanString);

    CString GetSingleLanguagePosString(CString cSingleLanguage,
        unsigned long uDataPosInit,unsigned long * pDataPosResult);

    CString GetLanguagePosString(CString csLanString);
    CString GetLanguagePacePath(CString csLanguageString);
    
    CString GetConfigSingleLanguageInfo(CString csSingleLanguage,BOOL bDefine);
    BOOL OutputConfigFile(void);
    CString GetConfigLanguageList(CString csLanString,BOOL bDefine);

    static int CALLBACK SetSelProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cOutputFiles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(cOutputFiles)
	afx_msg void OnButtonSelectpaht();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDropdownComboSelectpath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COUTPUTFILES_H__52D9B1B2_580A_4882_8420_AFC51FABA598__INCLUDED_)
