    // cOutputFiles.cpp : implementation file
//

#include "stdafx.h"
#include "voiceprompt.h"
#include "cOutputFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BIF_USENEWUI                0x0050
static const CString csSlash = CONFIGFILE_CSTRINGSLASH;
static const float fKunit = CONFIGFILE_KUNIT;
/////////////////////////////////////////////////////////////////////////////
// cOutputFiles dialog


cOutputFiles::cOutputFiles(CWnd* pParent /*=NULL*/)
	: CDialog(cOutputFiles::IDD, pParent)
{
	//{{AFX_DATA_INIT(cOutputFiles)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

cOutputFiles::cOutputFiles(CWnd* pParent /*=NULL*/,
                           CString clanguageD,CString clanguageU,int iLanCount,int iOutLanguageCount)
	: CDialog(cOutputFiles::IDD, pParent)
{
	csLanguage_Define = clanguageD;
    csLanguage_Undef = clanguageU;
    iLanguageCount = iLanCount;
    iOutputLanguageOut = iOutLanguageCount;

    bSelectLanguagePos = FALSE;
    bSelectLanguageData = FALSE;
    iFileIndexPos = 0;
    iFileIndexData = 0;
#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
    iTimes = 0;
    iFileTimes = 0;
    iCountConfigTimes = 0;
    int iSpace;
    iSpace = clanguageD.Find(LANGUAGE_SEPARATOR);
    if (iSpace == -1)
        csDefaultLanguage = clanguageD;
    else
        csDefaultLanguage = clanguageD.Left(iSpace);
#endif
}

void cOutputFiles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(cOutputFiles)
	DDX_Control(pDX, IDC_PROGRESS_OUTPUT, m_Progress);
	DDX_Control(pDX, IDC_COMBO_SELECTPATH, m_Combo_SelectPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(cOutputFiles, CDialog)
	//{{AFX_MSG_MAP(cOutputFiles)
	ON_BN_CLICKED(IDC_BUTTON_SELECTPAHT, OnButtonSelectpaht)
	ON_CBN_DROPDOWN(IDC_COMBO_SELECTPATH, OnDropdownComboSelectpath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cOutputFiles message handlers

void cOutputFiles::OnButtonSelectpaht() 
{
	// TODO: Add your control notification handler code here
	CString cItemName;//项目名    
    CString cSelectFold;
    BROWSEINFO bi;         
    TCHAR Dir[MAX_PATH];
    ITEMIDLIST * pidl;
    cSelectFold.LoadString(IDS_STRING_SELECTFOLD);
    
    m_Combo_SelectPath.GetWindowText(cItemName);//获得commbox控件中的内容

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
int CALLBACK cOutputFiles::SetSelProc(HWND hWnd, UINT uMsg, LPARAM /*lParam*/, LPARAM lpData)
{
    if (uMsg == BFFM_INITIALIZED)
        ::SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData);

    return 0;
}

void cOutputFiles::OnOK() 
{
	// TODO: Add extra validation here
	CString csPath,cClew;

    m_Combo_SelectPath.GetWindowText(csPath);

    cClew.LoadString(IDS_STRING_CLEW);

    if (csPath == "")
    {
        CString cClewPath;
        cClewPath.LoadString(IDS_STRING_INPUTPATH);//请输入源目录
        MessageBox(cClewPath,cClew,MB_ICONASTERISK |MB_OK);
        m_Combo_SelectPath.SetFocus();
        return;
    }
    TCHAR cCurDirBak[256] = "";
    GetCurrentDirectory(sizeof(cCurDirBak),cCurDirBak);
    if (!SetCurrentDirectory(csPath))
    {
        CString cOpenFail,cue,csCreatePath;
        cOpenFail.LoadString(IDS_STRING_FINDSOURFOLDFAIL);
        cue.Format(cOpenFail,csPath);
        if (MessageBox(cue,cClew,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON1) == IDYES)
        {
            if (csPath.Right(1) != csSlash)
                csCreatePath = csPath + csSlash;
            CreateDirectoryFromString(csCreatePath);
        }
        else
        {
            m_Combo_SelectPath.SetFocus();
            SetCurrentDirectory(cCurDirBak);
            return;
        }
    }
    SetCurrentDirectory(cCurDirBak);
    //////////////////////////////////////////////////////////////////////////
    //output files
    BOOL bfData,bfPos;
	CStdioFile fData,fPos;
    CString fDataFilename,fPosFilename;

    fDataFilename = csPath + csSlash + csDataFilename;
    fPosFilename = csPath + csSlash + csPosFilename;

    bfData = fData.Open(fDataFilename,CFile::modeWrite|CFile::modeCreate,NULL);
    bfPos  = fPos.Open(fPosFilename,CFile::modeWrite|CFile::modeCreate,NULL);
    if (!bfData || !bfPos)
    {
        CString cCannotWritefile,csContentClew;

        if ((bfData) && (!bfPos))
        {
            cCannotWritefile.LoadString(IDS_STRING_CANNOTWRITEFILE);
            csContentClew.Format(cCannotWritefile,fPosFilename);
            MessageBox(csContentClew,cClew,MB_ICONASTERISK |MB_OK);
            fData.Close();
            return;
        }
        if ((bfPos) && (!bfData))
        {
            cCannotWritefile.LoadString(IDS_STRING_CANNOTWRITEFILE);
            csContentClew.Format(cCannotWritefile,fDataFilename);
            MessageBox(csContentClew,cClew,MB_ICONASTERISK |MB_OK);
            fPos.Close();
            return;
        }
        cCannotWritefile.LoadString(IDS_STRING_CANNOTWRITEFILES);
        csContentClew.Format(cCannotWritefile,fDataFilename,fPosFilename);
        MessageBox(csContentClew,cClew,MB_ICONASTERISK |MB_OK);
        return;
    }
    CWaitCursor wait;
    //////////////////////////////////////////////////////////////////////////
    //Progress
    CButton	* pOutputNecessaryFiles = ((CButton *)(GetDlgItem(IDC_RADIO_NEEDFILES)));
    if (pOutputNecessaryFiles->GetCheck() == 1)
    {
        iLanguageCount = iOutputLanguageOut;
    }
    m_Progress.ShowWindow(SW_SHOW);
    m_Progress.SetRange(0,iLanguageCount + 4);
    m_Progress.SetStep(0);
    m_Progress.SetProgressFillColor(RGB(255,0,0));
    m_Progress.SetProgressTextColor(RGB(0,0,255));
    m_Progress.ShowPreText(TRUE);
    //////////////////////////////////////////////////////////////////////////
    //out the file size file
    OutputFilesSizeInfor(csLanguage_Define);
    m_Progress.SetPos(1);
    //////////////////////////////////////////////////////////////////////////
    //out the config file
    OutputConfigFile();
    m_Progress.SetPos(2);
    //////////////////////////////////////////////////////////////////////////
    //output the fDataFilename files
    CString csDataString = "";
    csDataString = csDataContent + GetDefineLanguageList(csLanguage_Define,TRUE);
    csDataString = csDataString + GetDefineLanguageList(csLanguage_Undef,FALSE);
    csDataString = csDataString + CONFIG_NEWLINE + CONFIG_NEWLINE + 
        "const unsigned char " + csDataVariable + "[] =" + CONFIG_NEWLINE + "{";

    csDataString = csDataString + GetIncludeLanguage(csLanguage_Define) + GetIncludeLanguage(csLanguage_Undef);
    csDataString = csDataString + "};" + CONFIG_NEWLINE;
    fData.WriteString(csDataString);
    fData.Close();

    m_Progress.SetPos(3);
    //////////////////////////////////////////////////////////////////////////
    //output the fPosFilename file
    CString csPosString = "";
    csPosString = csPosContent + CONFIG_NEWLINE + "const unsigned long " + csPosVariable + "[][2] =" + 
        CONFIG_NEWLINE + "{";
    csPosString = csPosString + GetLanguagePosString(csLanguage_Define) + CONFIG_NEWLINE + "};" + CONFIG_NEWLINE;
    fPos.WriteString(csPosString);
    fPos.Close();

    m_Progress.SetPos(4);
    iOutFileCount = 4;
    //////////////////////////////////////////////////////////////////////////
    //output all the language data file
    OutputLanguageFilesData(csPath);
    //////////////////////////////////////////////////////////////////////////
    m_Progress.ShowWindow(SW_HIDE);
    //////////////////////////////////////////////////////////////////////////
    CString cOutComplete;
    cOutComplete.LoadString(IDS_STRING_OUTPUTCOMPLETE);
    MessageBox(cOutComplete,cClew,MB_ICONASTERISK |MB_OK);
	CDialog::OnOK();
}

BOOL cOutputFiles::OutputFilesSizeInfor(CString csLanString)
{
    CString csResult = "",cSingleLanguage;
    int iSpace = 0,icount = 0,iFileCount = 0,iSelCount = 0;
    DWORD dsize = 0,dLanguagePackSize = 0;

    if (csLanString == "")
        return FALSE;
    while (1)
    {
        iSpace = csLanString.Find(LANGUAGE_SEPARATOR);
        if (-1 == iSpace)
        {
            if (csLanString == "")
                return FALSE;

            csResult = csResult + GetLanguagePackSize(csLanString,&icount,&dsize);
            iFileCount += icount;
            dLanguagePackSize += dsize;
            iSelCount++;
            break;
        }
        cSingleLanguage = csLanString.Left(iSpace);
        csLanString = csLanString.Right(csLanString.GetLength() - iSpace - 1);

        csResult = csResult + GetLanguagePackSize(cSingleLanguage,&icount,&dsize);

        iFileCount += icount;
        dLanguagePackSize += dsize;
        iSelCount++;
#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
        iFileTimes++;
#endif
    }
    CString csLanguageCountResult,csConfigPath,cCurrentPath,fOutConfigFilename,csLanguageAccount;
    CStdioFile  file;

    csLanguageAccount.LoadString(IDS_STRING_LANGUAGEACCOUNT);
    csLanguageCountResult.Format(csLanguageAccount,
        csResult,iSelCount,iFileCount,dLanguagePackSize,dLanguagePackSize / fKunit);

    cCurrentPath = GetCurrentAppPath();
    csConfigPath = GetLanguagePacePath(csLanguage_Define);
    fOutConfigFilename = cCurrentPath + csSlash + CONFIGFILE_OUTPUTFILENAME + 
        csSlash + csConfigPath + csSlash + csConfigPath + CONFIGFILE_FILESIZEINFORMATION;

    if (file.Open(fOutConfigFilename,CFile::modeWrite|CFile::modeCreate,NULL))//打开成功
    {
        file.WriteString(csLanguageCountResult);
        file.Close();
        return TRUE;
    }

    return FALSE;
}

CString cOutputFiles::GetLanguagePackSize(CString csLanguage,int * pFileCount,DWORD * pAllFilesize)
{
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead;
    CString     bufLanguage;
    ConfigType  eConfigtype = CONFIGTYPE_NONE;
    int         iFileCount = 0;
    DWORD       dAllFilesize = 0;
    CString     csFileinfo,cFilePath,CurrentAppPath;

#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
    int iFileIndex = 0;
#endif

    CurrentAppPath = GetCurrentAppPath();
    cFileName = CurrentAppPath + csSlash + CONFIGFILENAME;
    bufLanguage = CONFIGFILE_LANGUAGE_FILE_BEGIN + csLanguage;

    if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
    {
        while (file.ReadString(bufRead))
        {
            while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
				bufRead = bufRead.Left(bufRead.GetLength() - 1);

            if (bufRead == "")
            {
                eConfigtype = CONFIGTYPE_NONE;
                continue;
            }
            if (bufRead == bufLanguage)
            {
                eConfigtype = CONFIGTYPE_FILEINFO;
                continue;
            }
            if (CONFIGTYPE_FILEINFO == eConfigtype)
            {
                cFilePath = CurrentAppPath + csSlash + bufRead;
                if (FileIfExist(cFilePath))
                {
                    iFileCount++;
#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
                    if (iFileTimes > 0)
                    {
                        if (iFileIndex == CONFIGFILE_AUTOFILEINDEX)
                        {
                            dAllFilesize++;
                            iFileIndex++;
                            continue;
                        }
                    }
                    iFileIndex++;
#endif
                    dAllFilesize += VoicePromptGetFileSize(cFilePath);;
                }
            }
        }
        file.Close();
        if (pFileCount != NULL)
            * pFileCount = iFileCount;

        if (pAllFilesize != NULL)
            * pAllFilesize = dAllFilesize;

        CString csSingleLanguageInformation;
        csSingleLanguageInformation.LoadString(IDS_STRING_SINGLELANACCOUNT);
        csFileinfo.Format(csSingleLanguageInformation,csLanguage,iFileCount,
            dAllFilesize,dAllFilesize / fKunit);
        return csFileinfo;
    }
    else
    {
        return "";
    }
}

BOOL cOutputFiles::OutputConfigFile(void)
{
    CStdioFile  file;
    CString		bufRead,fOutConfigFilename;
    CString     csResult = "", cCurrentPath,csConfigPath;
    
    cCurrentPath = GetCurrentAppPath();
    csConfigPath = GetLanguagePacePath(csLanguage_Define);
    fOutConfigFilename = cCurrentPath + csSlash + CONFIGFILE_OUTPUTFILENAME + 
        csSlash + csConfigPath + csSlash + csConfigPath + CONFIGFILE_ACCESSIONALFILEPATULOUSNAME;

    if (file.Open(fOutConfigFilename,CFile::modeWrite|CFile::modeCreate,NULL))//打开成功
    {
        csResult = GetConfigLanguageList(csLanguage_Define,TRUE);
        csResult = csResult + GetConfigLanguageList(csLanguage_Undef,FALSE);

        file.WriteString(csResult);
        file.Close();
        return TRUE;
    }
    return FALSE;
}

CString cOutputFiles::GetConfigSingleLanguageInfo(CString csSingleLanguage,BOOL bDefine)
{
    CStdioFile	file;
    CString     cFileName,csCurrentPath;
    CString		bufRead;
    CString     bufLanguage;
    CString     cFilePath;
    CString     csResult = "";
    ConfigType  eConfigtype = CONFIGTYPE_NONE;
#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
    int iFileIndex = 0;
#endif

    csCurrentPath = GetCurrentAppPath();
    cFileName = csCurrentPath + csSlash + CONFIGFILENAME;
    bufLanguage = CONFIGFILE_LANGUAGE_FILE_BEGIN + csSingleLanguage;

    if (bDefine)
        csResult = CONFIGFILE_DEFINE + csSingleLanguage + CONFIG_NEWLINE;
    else
        csResult = CONFIGFILE_UNDEF + csSingleLanguage + CONFIG_NEWLINE;

    if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
	{
        eConfigtype = CONFIGTYPE_NONE;
		while (file.ReadString(bufRead))
		{
			while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
				bufRead = bufRead.Left(bufRead.GetLength() - 1);

            if (bufRead == bufLanguage)
            {
                eConfigtype = CONFIGTYPE_FILEINFO;
                continue;
            }
            if ((bufRead == "") || (bufRead == CONFIGFILE_LANGUAGE_FILE_END))
            {
                eConfigtype = CONFIGTYPE_NONE;
                continue;
            }
            if (CONFIGTYPE_FILEINFO == eConfigtype)
            {
#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
                if (iCountConfigTimes > 0)
                {
                    if (iFileIndex == CONFIGFILE_AUTOFILEINDEX)
                        cFilePath = csCurrentPath + csSlash + csSingleLanguage + csSlash + CONFIGFILE_PLACEFILENAME;
                    else
                        cFilePath = csCurrentPath + csSlash + bufRead;

                    iFileIndex++;
                }
                else
#endif
                cFilePath = csCurrentPath + csSlash + bufRead;
                csResult = csResult + cFilePath + CONFIG_NEWLINE;
            }
		}
		file.Close();
        csResult = csResult + CONFIGFILE_ENDIF + CONFIG_NEWLINE;
	}
#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
    iCountConfigTimes++;
#endif
    return csResult;
}
CString cOutputFiles::GetConfigLanguageList(CString csLanString,BOOL bDefine)
{
    CString csResult = "",cSingleLanguage;
    int iSpace;

    if (csLanString == "")
        return csResult;
    while (1)
    {
        iSpace = csLanString.Find(LANGUAGE_SEPARATOR);
        if (-1 == iSpace)
        {
            if (csLanString == "")
                return csResult;

            csResult = csResult + GetConfigSingleLanguageInfo(csLanString,bDefine);
            return csResult;
        }
        cSingleLanguage = csLanString.Left(iSpace);
        csLanString = csLanString.Right(csLanString.GetLength() - iSpace - 1);

        csResult = csResult + GetConfigSingleLanguageInfo(cSingleLanguage,bDefine);
    }
}

void cOutputFiles::OutputLanguageFilesData(CString cLanguagePath)//output all the language data file
{
    CStdioFile	file,fOutfile;
    CString     cFileName;
    CString		bufRead,cHeadFilename,csLanguageName;
    CString     csResult = "", cCurrentPath,cAmrfilename ;
    int iSpace,iLanPrefixLen = strlen(CONFIGFILE_LANGUAGE_FILE_BEGIN);
    CButton	* pOutputNecessaryFiles = ((CButton *)(GetDlgItem(IDC_RADIO_NEEDFILES)));
    typedef enum
    {
        OUTFILES_OUTFILE,
        OUTFILES_NONE
    }OUTPUTLANGUAGEFILES;
    OUTPUTLANGUAGEFILES eOutputType = OUTFILES_NONE;

#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
    int iFileIndex = 0;
#endif

    cCurrentPath = GetCurrentAppPath();
    cFileName = cCurrentPath + csSlash + CONFIGFILENAME;
    
    if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
    {
        while (file.ReadString(bufRead))
        {
            while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
				bufRead = bufRead.Left(bufRead.GetLength() - 1);

            if (bufRead == CONFIGFILE_LANGUAGE_FILE_END)
            {
                eOutputType = OUTFILES_NONE;
                if ((fOutfile != NULL) && (fOutfile.m_pStream != NULL))
                {
                    fOutfile.WriteString(csResult);
                    fOutfile.Close();
                    csResult = "";
#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
                    iFileIndex = 0;
#endif
                    m_Progress.SetPos(iOutFileCount++);
                }
                continue;
            }
            iSpace = bufRead.Find(CONFIGFILE_LANGUAGE_FILE_BEGIN);
            if (iSpace != -1)
            {
                eOutputType = OUTFILES_OUTFILE;
                csLanguageName = bufRead.Right(bufRead.GetLength() - iLanPrefixLen);

                if (pOutputNecessaryFiles->GetCheck() == 1)//Output necessary files
                {
                    if (csLanguage_Define.Find(csLanguageName) == -1)//Can't find the language
                    {
                        eOutputType = OUTFILES_NONE;
                        continue;
                    }
                }
                cHeadFilename = cLanguagePath + csSlash + csLanguageName + ".h";
                if (!fOutfile.Open(cHeadFilename,CFile::modeCreate|CFile::modeWrite,NULL))
                {
                    CString cClew,cWrite,csContentClew;
                    cWrite.LoadString(IDS_STRING_CANNOTWRITEFILE);
                    csContentClew.Format(cWrite,cHeadFilename);
                    cClew.LoadString(IDS_STRING_CLEW);
                    MessageBox(csContentClew,cClew,MB_ICONASTERISK |MB_OK);
                }
                continue;
            }
            if (eOutputType == OUTFILES_OUTFILE)
            {
                cAmrfilename = cCurrentPath + csSlash + bufRead;
#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
                if ((csLanguageName != csDefaultLanguage) && (iFileIndex == CONFIGFILE_AUTOFILEINDEX))
                    csResult = csResult + CONFIG_NEWLINE + "/*" + cAmrfilename + "*/" + CONFIG_NEWLINE + "0x00,";
                else
#endif
                csResult += OutputSingleLanguageFile(cAmrfilename);
#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
                iFileIndex++;
#endif
            }
        }
        file.Close();
    }
}

CString cOutputFiles::OutputSingleLanguageFile(CString cSingleLanguage)//output single language data file
{
    CStdioFile fSourfile;
    CString csResult = "";
    DWORD dFilesize,i;

    if (!fSourfile.Open(cSingleLanguage,CFile::typeBinary|CFile::modeRead,NULL))
    {
        CString cClew,csRead,csContentClew;
        csRead.LoadString(IDS_STRING_CANNOTREADFILE);
        cClew.LoadString(IDS_STRING_CLEW);
        csContentClew.Format(csRead,cSingleLanguage);
        MessageBox(csContentClew,cClew,MB_ICONASTERISK |MB_OK);
        return csResult;
    }
    dFilesize = fSourfile.GetLength();
    unsigned char * pFileContent = new unsigned char[dFilesize];
    char cNum[10] = "";
    int iComma = 0;

    memset(pFileContent,0x00,dFilesize);
    //fSourfile.ReadHuge((void*)pFileContent,dFilesize);//for vs 2005
    fSourfile.Close();

    csResult = CONFIG_NEWLINE;
    csResult = csResult + "/*" + cSingleLanguage + "*/" + CONFIG_NEWLINE;

    for (i = 0;i < dFilesize;i++)
    {
        sprintf(cNum,"0x%02x,",pFileContent[i]);
        csResult += cNum;
        if ((i + 1) % 16 == 0)
            csResult += CONFIG_NEWLINE;
    }
    delete pFileContent;
    return csResult;
}

CString cOutputFiles::GetSingleLanguagePosString(CString cSingleLanguage,
                                                 unsigned long uDataPosInit,unsigned long * pDataPosResult)
{
    CStdioFile	file;
    CString     csResult = "";
    CString     cFileName,cSinglePosString;
    CString		bufRead;
    CString     bufLanguage;
    CString     cFilePath;
    ConfigType  eConfigtype = CONFIGTYPE_NONE;
    unsigned long iDataPos = uDataPosInit,iFilelen;
    int         iNewPlace = 0,iComma = 0;

#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
    int iFileIndex = 0;
#endif

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;
    if (!file.Open(cFileName,CFile::modeRead,NULL))
    {
        CString cClew,csWrite,csContentClew;
        cClew.LoadString(IDS_STRING_CLEW);
        csWrite.LoadString(IDS_STRING_CANNOTWRITEFILE);
        csContentClew.Format(csWrite,cFileName);
        MessageBox(csContentClew,cClew,MB_ICONASTERISK |MB_OK);
        return csResult;
    }
    bufLanguage = CONFIGFILE_LANGUAGE_FILE_BEGIN + cSingleLanguage;
    csResult = csResult + CONFIG_NEWLINE + "/*" + cSingleLanguage + "*/" + CONFIG_NEWLINE;

    while (file.ReadString(bufRead))
    {
        while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
            bufRead = bufRead.Left(bufRead.GetLength() - 1);
        
        if (bufRead == bufLanguage)
        {
            eConfigtype = CONFIGTYPE_FILEINFO;
            continue;
        }
        if ((bufRead == "") || (bufRead == CONFIGFILE_LANGUAGE_FILE_END))
        {
            eConfigtype = CONFIGTYPE_NONE;
            continue;
        }
        if (CONFIGTYPE_FILEINFO == eConfigtype)
        {
            cFilePath = GetCurrentAppPath() + csSlash + bufRead;
            iFilelen = VoicePromptGetFileSize(cFilePath);
#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
            if (iTimes > 0)
            {
                if (iFileIndex == CONFIGFILE_AUTOFILEINDEX)
                {
                    iFilelen = 1;
                }
                iFileIndex++;
            }
#endif
            if (iFilelen != -1)
            {
                cSinglePosString.Format(" { %ld , %ld } ",iDataPos,iFilelen);

                if (iComma == 0)
                    iComma = 1;
                else
                    csResult += ",";

                iDataPos += iFilelen;
                csResult += cSinglePosString;

                iNewPlace++;
                if (iNewPlace % 4 == 0)
                {
                    csResult = csResult + "," + CONFIG_NEWLINE;
                    iComma = 0;
                }
            }
            else
            {
                CString cClew,csRead,csContentClew;
                cClew.LoadString(IDS_STRING_CLEW);
                csRead.LoadString(IDS_STRING_CANNOTOPENFOLD);
                csContentClew.Format(csRead,cFilePath);
                MessageBox(csContentClew,cClew,MB_ICONINFORMATION|MB_OK);
            }
        }
    }
    file.Close();
    if (pDataPosResult != NULL)
        * pDataPosResult = iDataPos;

#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
    iTimes++;
#endif

    return csResult;
}

CString cOutputFiles::GetLanguagePosString(CString csLanString)
{
    CString csResult = "",cSingleLanguage;
    int iSpace;
    unsigned long uDataPosInit = 0,uDataPosResult = 0;

    if (csLanString == "")
        return csResult;

    while (1)
    {
        iSpace = csLanString.Find(LANGUAGE_SEPARATOR);
        if (-1 == iSpace)
        {
            if (csLanString == "")
                return csResult;

            csResult = csResult + GetSingleLanguagePosString(csLanString,uDataPosInit,&uDataPosResult);
            return csResult;
        }
        cSingleLanguage = csLanString.Left(iSpace);
        csLanString = csLanString.Right(csLanString.GetLength() - iSpace - 1);

        csResult = csResult + GetSingleLanguagePosString(cSingleLanguage,uDataPosInit,&uDataPosResult) + ",";
        uDataPosInit = uDataPosResult;
    }
}


CString cOutputFiles::GetIncludeLanguage(CString csLanString)
{
    CString csResult = "",cSingleLanguage;
    int iSpace;

    if (csLanString == "")
        return csResult;
    while (1)
    {
        iSpace = csLanString.Find(LANGUAGE_SEPARATOR);
        if (-1 == iSpace)
        {
            if (csLanString == "")
                return csResult;

            csResult = csResult + CONFIG_NEWLINE + CONFIGFILE_INDEF + csLanString + CONFIG_NEWLINE + 
                "#include \"" + csLanString + ".h\"" + CONFIG_NEWLINE + CONFIGFILE_ENDIF + CONFIG_NEWLINE;
            return csResult;
        }
        cSingleLanguage = csLanString.Left(iSpace);
        csLanString = csLanString.Right(csLanString.GetLength() - iSpace - 1);

        csResult = csResult + CONFIG_NEWLINE + CONFIGFILE_INDEF + cSingleLanguage + CONFIG_NEWLINE +
            "#include \"" + cSingleLanguage + ".h\"" + CONFIG_NEWLINE + CONFIGFILE_ENDIF + CONFIG_NEWLINE;
    }
}


CString cOutputFiles::GetDefineLanguageList(CString csLanString,BOOL bDefine)
{
    CString csResult = "",cSingleLanguage;
    int iSpace;

    if (csLanString == "")
        return csResult;
    while (1)
    {
        iSpace = csLanString.Find(LANGUAGE_SEPARATOR);
        if (-1 == iSpace)
        {
            if (csLanString == "")
                return csResult;

            if (bDefine)
                csResult = csResult + CONFIG_NEWLINE + CONFIGFILE_DEFINE + csLanString;
            else
                csResult = csResult + CONFIG_NEWLINE + CONFIGFILE_COMMENTDEFINE + csLanString;

            return csResult;
        }
        cSingleLanguage = csLanString.Left(iSpace);
        csLanString = csLanString.Right(csLanString.GetLength() - iSpace - 1);

        if (bDefine)
            csResult = csResult + CONFIG_NEWLINE + CONFIGFILE_DEFINE + cSingleLanguage;
        else
            csResult = csResult + CONFIG_NEWLINE + CONFIGFILE_COMMENTDEFINE + cSingleLanguage;
    }
}

CString cOutputFiles::GetLanguagePacePath(CString csLanguageString)
{
    CString csResult = "",cSingleLanguage;
    int iSpace;

    if (csLanguageString == "")
        return csResult;
    while (1)
    {
        iSpace = csLanguageString.Find(LANGUAGE_SEPARATOR);
        if (-1 == iSpace)
        {
            if (csLanguageString == "")
                return csResult;

            if (csResult != "")
                csResult = csResult + CONFIGFILE_UNDERLINE + csLanguageString;
            else
                csResult = csLanguageString;

            return csResult;
        }
        cSingleLanguage = csLanguageString.Left(iSpace);
        csLanguageString = csLanguageString.Right(csLanguageString.GetLength() - iSpace - 1);

        if (csResult == "")
            csResult = cSingleLanguage;
        else
            csResult = csResult + CONFIGFILE_UNDERLINE + cSingleLanguage;
    }
}

BOOL cOutputFiles::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CStdioFile	file;
    CString     cFileName;
    CString		bufRead,cCurrentPath;
    typedef enum
    {
        VOICETYPE_DATAFILENAME,
        VOICETYPE_DATAVARIABLE,
        VOICETYPE_DATACONTENT,
        VOICETYPE_POSFILENAME,
        VOICETYPE_POSVARIABLE,
        VOICETYPE_POSCONTENT,
        VOICETYPE_NONE
    }VOICETYPE;
    TCHAR cCurDirBak[256] = "";

    m_Progress.ShowWindow(SW_HIDE);
    GetCurrentDirectory(sizeof(cCurDirBak),cCurDirBak);

    cCurrentPath = GetCurrentAppPath() + csSlash + CONFIGFILE_OUTPUTFILENAME + csSlash + 
        GetLanguagePacePath(csLanguage_Define);

    m_Combo_SelectPath.SetWindowText(cCurrentPath);
    
    VOICETYPE eVoiceType = VOICETYPE_NONE;

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;

	if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
	{
		while (file.ReadString(bufRead))
		{
			while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
				bufRead = bufRead.Left(bufRead.GetLength() - 1);

            if (bufRead == CONFIGFILE_VOICEPROMPT_DATA_FILENAME)
            {
                eVoiceType = VOICETYPE_DATAFILENAME;
                continue;
            }
            else if (bufRead == CONFIGFILE_VOICEPROMPT_DATA_VARIABLE_NAME)
            {
                eVoiceType = VOICETYPE_DATAVARIABLE;
                continue;
            }
            else if (bufRead == CONFIGFILE_VOICEPROMPT_DATA_PREPARE_CONTENT_BEGIN)
            {
                eVoiceType = VOICETYPE_DATACONTENT;
                continue;
            }
            else if (bufRead == CONFIGFILE_VOICEPROMPT_POS_FILENAME)
            {
                eVoiceType = VOICETYPE_POSFILENAME;
                continue;
            }
            else if (bufRead == CONFIGFILE_VOICEPROMPT_POS_VARIABLE_NAME)
            {
                eVoiceType = VOICETYPE_POSVARIABLE;
                continue;
            }
            else if (bufRead == CONFIGFILE_VOICEPROMPT_POS_PREPARE_CONTENT_BEGIN)
            {
                eVoiceType = VOICETYPE_POSCONTENT;
                continue;
            }
            else if (bufRead == CONFIGFILE_VOICEPROMPT_POS_PREPARE_CONTENT_END)
            {
                eVoiceType = VOICETYPE_NONE;
                continue;
            }
            else if (bufRead == CONFIGFILE_VOICEPROMPT_DATA_PREPARE_CONTENT_END)
            {
                eVoiceType = VOICETYPE_NONE;
                continue;
            }
            else
            {
                switch (eVoiceType)
                {
                case VOICETYPE_DATAFILENAME:
                    eVoiceType = VOICETYPE_NONE;
                    csDataFilename = bufRead;
                    break;
                case VOICETYPE_DATAVARIABLE:
                    eVoiceType = VOICETYPE_NONE;
                    csDataVariable = bufRead;
                    break;
                case VOICETYPE_DATACONTENT:
                    csDataContent = csDataContent + bufRead + CONFIG_NEWLINE;
                    continue;

                case VOICETYPE_POSFILENAME:
                    eVoiceType = VOICETYPE_NONE;
                    csPosFilename = bufRead;
                    break;
                case VOICETYPE_POSVARIABLE:
                    eVoiceType = VOICETYPE_NONE;
                    csPosVariable = bufRead;
                    break;
                case VOICETYPE_POSCONTENT:
                    csPosContent = csPosContent + bufRead + CONFIG_NEWLINE;
                    continue;
                }
                eVoiceType = VOICETYPE_NONE;
                continue;
            }
		}
		file.Close();
	}

    //////////////////////////////////////////////////////////////////////////
    CFileFind   find;
    CString     csSearchPath,strFilePath;
    BOOL        bWorking;

    csSearchPath = GetCurrentAppPath() + csSlash + CONFIGFILE_OUTPUTFILENAME + CONFIGFILE_SEARCHFILE;

    bWorking = find.FindFile(csSearchPath);
    while (bWorking)
    {
        bWorking    = find.FindNextFile();
        strFilePath = find.GetFilePath();
        
        if (find.IsDots())
            continue;
        
        if (find.IsDirectory())
        {
            m_Combo_SelectPath.AddString(strFilePath);
            continue;
        }
    }
    find.Close();
    //////////////////////////////////////////////////////////////////////////
    CButton	* pOutputAllFiles = ((CButton *)(GetDlgItem(IDC_RADIO_ALLFILES)));
    CButton	* pOutputNecessaryFiles = ((CButton *)(GetDlgItem(IDC_RADIO_NEEDFILES)));
    pOutputAllFiles->SetCheck(1);
    pOutputNecessaryFiles->SetCheck(0);

    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void cOutputFiles::OnDropdownComboSelectpath() 
{
	// TODO: Add your control notification handler code here
    VoiceDataManage vdm;
	vdm.SetComboWidth(m_Combo_SelectPath);
}
