// AddBatchInfor.cpp : implementation file
//

#include "stdafx.h"
#include "voiceprompt.h"
#include "AddBatchInfor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
static const CString csSlash = CONFIGFILE_CSTRINGSLASH;
/////////////////////////////////////////////////////////////////////////////
// CAddBatchInfor dialog
#define BIF_USENEWUI                0x0050

CAddBatchInfor::CAddBatchInfor(CWnd* pParent /*=NULL*/)
	: CDialog(CAddBatchInfor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddBatchInfor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAddBatchInfor::CAddBatchInfor(CWnd* pParent /*=NULL*/,CString csLanguages,BATCH_DIALOG_TYPE eDialogtype,
                               CString csInitFilename,CString csInitFold)
	: CDialog(CAddBatchInfor::IDD, pParent)
{
	cLanguages = csLanguages;
    eDialogType = eDialogtype;
    csInitFile = csInitFilename;
    csInitPath = csInitFold;
}

void CAddBatchInfor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddBatchInfor)
	DDX_Control(pDX, IDC_COMBO_SELECTPATH, m_Combo_SelectPath);
	DDX_Control(pDX, IDC_COMBO_SELECTFILE, m_Combo_Filename);
	DDX_Control(pDX, IDC_STATIC_LANGUAGES, m_Static_Language);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddBatchInfor, CDialog)
	//{{AFX_MSG_MAP(CAddBatchInfor)
	ON_BN_CLICKED(IDC_BUTTON_BATCHSELFILE, OnButtonBatchselfile)
	ON_BN_CLICKED(IDC_BUTTON_SELECTFOLD, OnButtonSelectfold)
	ON_CBN_DROPDOWN(IDC_COMBO_SELECTFILE, OnDropdownComboSelectfile)
	ON_CBN_DROPDOWN(IDC_COMBO_SELECTPATH, OnDropdownComboSelectpath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddBatchInfor message handlers

BOOL CAddBatchInfor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CStdioFile	file;
    CString     cFileName,bufRead;
    BATCH_SCAN_TYPE eScanType = BATCH_SCAN_NONE;

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAMEBATCH;

    if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
    {
        while (file.ReadString(bufRead))
        {
            while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
                bufRead = bufRead.Left(bufRead.GetLength() - 1);

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
                csChooseFileName = bufRead;
                continue;
            }
            if (eScanType == BATCH_SCAN_ROOTFOLD)
            {
                csRootFoldName = bufRead;
                continue;
            }
        }
        file.Close();
    }
    //////////////////////////////////////////////////////////////////////////
    CString csLan,csContent,csTitle,csLanReplace;

    csLanReplace = CONFIGFILE_QUOTATION + cLanguages;
    if (cLanguages.Find(LANGUAGE_SEPARATOR) == -1)
    {
        csLanReplace = csLanReplace + CONFIGFILE_QUOTATION;
    }
    else
    {
        CString cAnd;
        cAnd.LoadString(IDS_STRING_ANDSTRING);
        csLanReplace.Replace(LANGUAGE_SEPARATOR,cAnd);
        csLanReplace = csLanReplace + CONFIGFILE_QUOTATION;
    }

    csLan.LoadString(IDS_STRING_SELECTLANGUAGE);
    csContent.Format(csLan,csLanReplace);
	m_Static_Language.SetWindowText(csContent);

    if (csInitFile == "")
        m_Combo_Filename.SetWindowText(csChooseFileName);
    else
        m_Combo_Filename.SetWindowText(csInitFile);

    if (csInitPath == "")
        m_Combo_SelectPath.SetWindowText(csRootFoldName);
    else
        m_Combo_SelectPath.SetWindowText(csInitPath);

    if (eDialogType == BATCH_MODIFY_ADD)
        csTitle.LoadString(IDS_STRING_BATCH_ADD_DIALOG);
    else
        csTitle.LoadString(IDS_STRING_BATCH_MODIFY);

    SetWindowText(csTitle);
    //////////////////////////////////////////////////////////////////////////
    VoiceDataManage vdm;
    vdm.SetSubfoldToComboBox(m_Combo_SelectPath,csRootFoldName);
    vdm.SetSubfoldFileToComboBox(m_Combo_Filename,csChooseFileName);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddBatchInfor::OnButtonBatchselfile() 
{
	// TODO: Add your control notification handler code here
	CString cFilename;
    CString cInitDir = "";

    m_Combo_Filename.GetWindowText(cFilename);

    if (cFilename != "")
    {
        int iExtName = cFilename.ReverseFind(_T('.'));//_T('.')
        //查找combox控件的文字中是否包含文件扩展名,如果包含扩展名,则认为包含文件名
        
        if (iExtName != -1)//包含文件名
        {
            int iReverseFind = cFilename.ReverseFind(_T('\\'));//_T('\\')
            cInitDir = (iReverseFind != -1) ? cFilename.Left(iReverseFind) : cFilename;
        }
        else//不包含文件名,则认为commbox控件中的内容可能是目录
        {
            cInitDir = cFilename;
        }
    }
    else
    {
        cInitDir = csChooseFileName;
    }
    
    CString cSelectFile,cFilter,cdefext;
    cSelectFile.LoadString(IDS_STRING_SELECTFILE);
    cFilter.LoadString(IDS_STRING_FILTER);
    cdefext.LoadString(IDS_STRING_DEFAULT_EXTENTNAME);
    
    CFileDialogEx open(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_EXTENSIONDIFFERENT,cFilter);
    
    open.m_ofn.lpstrTitle		= cSelectFile;//"选择文件";
    open.m_ofn.lpstrInitialDir	= cInitDir;
    open.m_ofn.lpstrDefExt		= cdefext;//"*.c;*.cpp;*.h";
    if (open.DoModal() == IDOK)
    {
        cFilename = open.GetPathName();
        m_Combo_Filename.SetWindowText(cFilename);
    }
}

void CAddBatchInfor::OnButtonSelectfold() 
{
	// TODO: Add your control notification handler code here
	CString cItemName;//项目名    
    CString cSelectFold;
    BROWSEINFO bi;         
    TCHAR Dir[MAX_PATH] = "";
    ITEMIDLIST * pidl;
    cSelectFold.LoadString(IDS_STRING_SELECTFOLD);
    
    m_Combo_SelectPath.GetWindowText(cItemName);//获得commbox控件中的内容

    if (cItemName == "")
    {
        cItemName = csRootFoldName;
    }
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
        m_Combo_SelectPath.SetWindowText(Dir);
    }
}

int CALLBACK CAddBatchInfor::SetSelProc(HWND hWnd, UINT uMsg, LPARAM /*lParam*/, LPARAM lpData)
{
    if (uMsg == BFFM_INITIALIZED)
        ::SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData);

    return 0;
}

void CAddBatchInfor::OnOK() 
{
	// TODO: Add extra validation here
    VoiceDataManage cdm;
    CString cFilename,cItemName,cClew,cSour,cFilename_bak,cItemName_bak;
    m_Combo_Filename.GetWindowText(cFilename);
	m_Combo_SelectPath.GetWindowText(cItemName);//获得commbox控件中的内容

    cClew.LoadString(IDS_STRING_CLEW);
    if ((cFilename == "") || (cFilename == csChooseFileName))
    {
        cSour.LoadString(IDS_STRING_INPUTFILENAME);
        MessageBox(cSour,cClew,MB_ICONASTERISK |MB_OK);
        m_Combo_Filename.SetFocus();
        return;
    }
    if ((cItemName == "") || (cItemName == csRootFoldName))
    {
        cSour.LoadString(IDS_STRING_INPUTPATH);
        MessageBox(cSour,cClew,MB_ICONASTERISK |MB_OK);
        m_Combo_SelectPath.SetFocus();
        return;
    }

    if (!FileIfExist(cFilename))
    {
        CString cOpenFail,cue;
        cOpenFail.LoadString(IDS_STRING_FINDSOURFILEFAIL);
        cue.Format(cOpenFail,cFilename);
        MessageBox(cue,cClew,MB_ICONASTERISK |MB_OK);
        m_Combo_Filename.SetFocus();
        return;
    }

    if (!cdm.FoldIfExist(cItemName))
    {
        CString cOpenFail,cue,csCreatePath;
        cOpenFail.LoadString(IDS_STRING_FINDSOURFOLDFAIL);
        cue.Format(cOpenFail,cItemName);
        if (MessageBox(cue,cClew,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON1) == IDYES)
        {
            if (cItemName.Right(1) != csSlash)
                csCreatePath = cItemName + csSlash;
            CreateDirectoryFromString(csCreatePath);
        }
        else
        {
            m_Combo_SelectPath.SetFocus();
            return;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    cFilename_bak = cFilename;
    cItemName_bak = cItemName;
    cFilename = cFilename.Right(cFilename.GetLength() - csChooseFileName.GetLength() - 1);
    cItemName = cItemName.Right(cItemName.GetLength() - csRootFoldName.GetLength() - 1);
    //////////////////////////////////////////////////////////////////////////
    //save file
    CStdioFile	file;
    CString     cFileName,bufRead,csFileContent = "",csBatchLanguages;
    VoiceDataManage vdm;

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAMEBATCH;
    csBatchLanguages = vdm.GetBatchOutputLanguage(cLanguages);
    if (eDialogType == BATCH_MODIFY_ADD)//Add
    {
        if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
        {
            while (file.ReadString(bufRead))
            {
                while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
                    bufRead = bufRead.Left(bufRead.GetLength() - 1);

                csFileContent = csFileContent + bufRead + CONFIG_NEWLINE;
            }
            file.Close();
            csFileContent = csFileContent + CONFIG_NEWLINE + 
                CONFIGFILE_BATCH_ITEMBEGIN + CONFIG_NEWLINE + 
                csBatchLanguages + CONFIG_NEWLINE + 
                cFilename + CONFIG_NEWLINE + 
                cItemName + CONFIG_NEWLINE + 
                CONFIGFILE_BATCH_ITEMEND + CONFIG_NEWLINE;
        }
    }
    else//modify
    {
        if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
        {
            while (file.ReadString(bufRead))
            {
                while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
                    bufRead = bufRead.Left(bufRead.GetLength() - 1);

                if (bufRead == csBatchLanguages)
                {
                    csFileContent = csFileContent + bufRead + CONFIG_NEWLINE;
                    csFileContent = csFileContent + cFilename + CONFIG_NEWLINE + cItemName + CONFIG_NEWLINE;
                    if (file.ReadString(bufRead))
                    {
                        if (!file.ReadString(bufRead))
                            break;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    csFileContent = csFileContent + bufRead + CONFIG_NEWLINE;
                }
            }
            file.Close();
        }
    }
    CFile::Remove(cFileName);
    if (file.Open(cFileName,CFile::modeCreate|CFile::modeWrite,NULL))//打开成功
    {
        file.WriteString(csFileContent);
        file.Close();
    }
    csSelectLanguageFilename = cFilename_bak;
    csLanguagesPackPath = cItemName_bak;
	CDialog::OnOK();
}

void CAddBatchInfor::GetEnumFileName(CString & csFilename,CString & csPathname)
{
    csFilename = csSelectLanguageFilename;
    csPathname = csLanguagesPackPath;
}


void CAddBatchInfor::OnDropdownComboSelectfile() 
{
	// TODO: Add your control notification handler code here
	VoiceDataManage vdm;
    vdm.SetComboWidth(m_Combo_Filename);
}

void CAddBatchInfor::OnDropdownComboSelectpath() 
{
	// TODO: Add your control notification handler code here
	VoiceDataManage vdm;
    vdm.SetComboWidth(m_Combo_SelectPath);
}
