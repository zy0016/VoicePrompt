// BatchOutputOption.cpp : implementation file
//

#include "stdafx.h"
#include "voiceprompttool.h"
#include "BatchOutputOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define BIF_USENEWUI                0x0050
static const CString csSlash = CONFIGFILE_CSTRINGSLASH;
/////////////////////////////////////////////////////////////////////////////
// BatchOutputOption dialog


BatchOutputOption::BatchOutputOption(CWnd* pParent /*=NULL*/)
	: CDialog(BatchOutputOption::IDD, pParent)
{
	//{{AFX_DATA_INIT(BatchOutputOption)
	//}}AFX_DATA_INIT
}


void BatchOutputOption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BatchOutputOption)
	DDX_Control(pDX, IDC_EDIT_CHOOSELANGUAGE_FOLD, m_Edit_ChooseLanguageFold);
	DDX_Control(pDX, IDC_EDIT_BATCH_OUTPUTROOT_FOLD, m_Edit_RootFold);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BatchOutputOption, CDialog)
	//{{AFX_MSG_MAP(BatchOutputOption)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSEFOLD, OnButtonChoosefold)
	ON_BN_CLICKED(IDC_BUTTON_LANGUAGEROOT_FOLD, OnButtonLanguagerootFold)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BatchOutputOption message handlers

BOOL BatchOutputOption::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CStdioFile	file;
    CString     cFileName;
    CString		bufRead,csChooseFold = "",csRootFold = "";
    BATCH_SCAN_TYPE eScanType = BATCH_SCAN_NONE;
    VoiceDataManage vdm;

    cFileName = vdm.GetCurrentAppPath() + csSlash + CONFIGFILENAMEBATCH;
    if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
    {
        while (file.ReadString(bufRead))
        {
            while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
				bufRead = bufRead.Left(bufRead.GetLength() - 1);

            if (bufRead == "")
                continue;

            if (bufRead == CONFIGFILE_BATCH_CHOOSELANGUAGEFOLDBEGIN)
            {
                eScanType = BATCH_SCAN_CHOOSEFOLD;
                continue;
            }
            if (bufRead == CONFIGFILE_BATCH_OUTPUTROOTFOLDBEGIN)
            {
                eScanType = BATCH_SCAN_ROOTFOLD;
                continue;
            }
            if ((bufRead == CONFIGFILE_BATCH_CHOOSELANGUAGEFOLDEND) || (bufRead == CONFIGFILE_BATCH_OUTPUTROOTFOLDEND))
            {
                eScanType = BATCH_SCAN_NONE;
                continue;
            }
            if (eScanType == BATCH_SCAN_CHOOSEFOLD)
            {
                csChooseFold = bufRead;
                continue;
            }
            if (eScanType == BATCH_SCAN_ROOTFOLD)
            {
                csRootFold = bufRead;
                continue;
            }
        }
        file.Close();
    }
    m_Edit_ChooseLanguageFold.SetWindowText(csChooseFold);
    m_Edit_RootFold.SetWindowText(csRootFold);
    //////////////////////////////////////////////////////////////////////////
    csChooseLanguageFold = csChooseFold;
    csRootFoldString = csRootFold;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
// BatchOutputOption message handlers
int CALLBACK BatchOutputOption::SetSelProc(HWND hWnd, UINT uMsg, LPARAM /*lParam*/, LPARAM lpData)
{
    if (uMsg == BFFM_INITIALIZED)
        ::SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData);

    return 0;
}

void BatchOutputOption::Voice_SetFold(CEdit & cEdit)
{
    CString cItemName;//项目名    
    CString cSelectFold = "Select fold and press [OK] button.";
    BROWSEINFO bi;         
    TCHAR Dir[MAX_PATH] = "";
    ITEMIDLIST * pidl;
    //cSelectFold.LoadString(IDS_STRING_SELECTFOLD);
    
    cEdit.GetWindowText(cItemName);//获得commbox控件中的内容

    bi.hwndOwner		= this->GetSafeHwnd();
    bi.pidlRoot			= NULL;
    bi.pszDisplayName	= Dir; 
    bi.lpszTitle		= cSelectFold;//"选择目录并按下[确定]按钮"; //选择目录
    bi.ulFlags			= BIF_USENEWUI;//BIF_RETURNONLYFSDIRS ; 
    bi.lpfn				= SetSelProc;
    bi.lParam			= (LPARAM)(LPCTSTR)cItemName;
    bi.iImage			= 0; 
    pidl                = SHBrowseForFolder(&bi);

    if (pidl == NULL) 
        memset(Dir,0,sizeof(MAX_PATH));
    if (SHGetPathFromIDList(pidl,Dir))/*Retrieve folder name from ITEMLIST structure.*/ 
    {
        cEdit.SetWindowText(Dir);
    }
}

BOOL BatchOutputOption::Voice_ClewCreateFold(CString csFold)
{
    VoiceDataManage VoiceManage;
    CString csCreatePath;
    CString cClew,cClew1 = "Can't find the \"%s\" fold,do you want to create it?",cClew2;

    if (!VoiceManage.FoldIfExist(csFold))
    {
        cClew.LoadString(IDS_STRING_CLEW);
        //cClew1.LoadString(IDS_STRING_FINDSOURFOLDFAIL);
        cClew2.Format(cClew1,csFold);

        if (MessageBox(cClew2,cClew,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON1) == IDYES)
        {
            if (csFold.Right(1) != csSlash)
                csCreatePath = csFold + csSlash;
            return VoiceManage.CreateDirectoryFromString(csCreatePath);
        }
        else
        {
            return FALSE;
        }
    }
    return TRUE;
}

void BatchOutputOption::OnOK() 
{
	// TODO: Add extra validation here
	CString csChooseFold = "",csRootFold = "";
    CString cClew,cClew1 = "Please input path.",cClew2;
    VoiceDataManage VoiceManage;

    m_Edit_ChooseLanguageFold.GetWindowText(csChooseFold);
    m_Edit_RootFold.GetWindowText(csRootFold);

    csChooseFold.TrimLeft();
    csChooseFold.TrimRight();
    csRootFold.TrimLeft();
    csRootFold.TrimRight();

    cClew.LoadString(IDS_STRING_CLEW);
    if ((csChooseFold == "") || (csRootFold == ""))
    {
        //cClew1.LoadString(IDS_STRING_INPUTPATH);
        MessageBox(cClew1,cClew,MB_ICONASTERISK |MB_OK);
        if (csChooseFold == "")
            m_Edit_ChooseLanguageFold.SetFocus();
        else
            m_Edit_RootFold.SetFocus();

        return;
    }
    if ((csChooseLanguageFold == csChooseFold) && (csRootFoldString == csRootFold))
    {
        CDialog::OnCancel();//CDialog::OnOK();
        return;
    }
    csChooseLanguageFold = csChooseFold;
    csRootFoldString = csRootFold;
    //////////////////////////////////////////////////////////////////////////
    if (!Voice_ClewCreateFold(csChooseFold))
        return;
    if (!Voice_ClewCreateFold(csRootFold))
        return;

    //////////////////////////////////////////////////////////////////////////
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead,csResult = "";
    BATCH_SCAN_TYPE eScanType = BATCH_SCAN_NONE;

    cFileName = VoiceManage.GetCurrentAppPath() + csSlash + CONFIGFILENAMEBATCH;

    if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
    {
        while (file.ReadString(bufRead))
        {
            while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
				bufRead = bufRead.Left(bufRead.GetLength() - 1);

            if (bufRead == CONFIGFILE_BATCH_CHOOSELANGUAGEFOLDBEGIN)
            {
                eScanType = BATCH_SCAN_CHOOSEFOLD;
                csResult = csResult + bufRead + CONFIG_NEWLINE;
                continue;
            }
            if (bufRead == CONFIGFILE_BATCH_OUTPUTROOTFOLDBEGIN)
            {
                eScanType = BATCH_SCAN_ROOTFOLD;
                csResult = csResult + bufRead + CONFIG_NEWLINE;
                continue;
            }
            if ((bufRead == CONFIGFILE_BATCH_CHOOSELANGUAGEFOLDEND) || 
                (bufRead == CONFIGFILE_BATCH_OUTPUTROOTFOLDEND))
            {
                eScanType = BATCH_SCAN_NONE;
                csResult = csResult + bufRead + CONFIG_NEWLINE;
                continue;
            }
            if (eScanType == BATCH_SCAN_CHOOSEFOLD)
            {
                csResult = csResult + csChooseFold + CONFIG_NEWLINE;
                continue;
            }
            if (eScanType == BATCH_SCAN_ROOTFOLD)
            {
                csResult = csResult + csRootFold + CONFIG_NEWLINE;
                continue;
            }
            csResult = csResult + bufRead + CONFIG_NEWLINE;
        }
        file.Close();

        CFile::Remove(cFileName);
        if (file.Open(cFileName,CFile::modeCreate|CFile::modeWrite,NULL))//打开成功
        {
            file.WriteString(csResult);
            file.Close();
        }
    }
	CDialog::OnOK();
}

void BatchOutputOption::OnButtonChoosefold() 
{
	// TODO: Add your control notification handler code here
	Voice_SetFold(m_Edit_ChooseLanguageFold);
}

void BatchOutputOption::OnButtonLanguagerootFold() 
{
	// TODO: Add your control notification handler code here
	Voice_SetFold(m_Edit_RootFold);
}
