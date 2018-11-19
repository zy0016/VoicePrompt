// LanguagePackInfo.cpp : implementation file
//

#include "stdafx.h"
#include "voiceprompt.h"
#include "LanguagePackInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLanguagePackInfo dialog


CLanguagePackInfo::CLanguagePackInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CLanguagePackInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLanguagePackInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CLanguagePackInfo::CLanguagePackInfo(CWnd* pParent /*=NULL*/,CString cLanguageInfo,CString cTitle)
	: CDialog(CLanguagePackInfo::IDD, pParent)
{
    csLanguagePackInfo = cLanguageInfo;
    csTitle = cTitle;
    if (csTitle == "")
        csTitle.LoadString(IDS_STRING_LANGUAGESIZEINFO);
}


void CLanguagePackInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLanguagePackInfo)
	DDX_Control(pDX, IDC_EDIT_LANGUAGEPACKINFORMATION, m_Edit_LanguagePackInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLanguagePackInfo, CDialog)
	//{{AFX_MSG_MAP(CLanguagePackInfo)
	ON_BN_CLICKED(IDC_BUTTON_COPY, OnButtonCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLanguagePackInfo message handlers

BOOL CLanguagePackInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Edit_LanguagePackInfo.SetWindowText(csLanguagePackInfo);
    SetWindowText(csTitle);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLanguagePackInfo::OnButtonCopy() 
{
	// TODO: Add your control notification handler code here
	m_Edit_LanguagePackInfo.SetSel(0,-1,FALSE);
    m_Edit_LanguagePackInfo.Copy();
}
