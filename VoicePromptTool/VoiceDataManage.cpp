          // VoiceDataManage.cpp: implementation of the VoiceDataManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "voiceprompt.h"
#include "VoiceDataManage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static const CString csSlash = CONFIGFILE_CSTRINGSLASH;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VoiceDataManage::VoiceDataManage()
{
    bFirstTime = TRUE;
}

VoiceDataManage::~VoiceDataManage()
{

}

BOOL VoiceDataManage::FileIfExist(CString cFilename)
{
    CStdioFile	file;
    if (file.Open(cFilename,CFile::modeRead,NULL))//打开成功
    {
        file.Close();
        return TRUE;
    }
    return FALSE;
}

DWORD VoiceDataManage::VoicePromptGetFileSize(CString cFilename)
{
    CStdioFile	file;
    DWORD       dSize;
    if (file.Open(cFilename,CFile::modeRead,NULL))//打开成功
    {
        dSize = file.GetLength();
        file.Close();
        return dSize;
    }
    return -1;
}

CString VoiceDataManage::GetCurrentAppPath(void)//返回当前应用所在路径
{
    TCHAR szBuf[512] = "";
    GetCurrentDirectory(sizeof(szBuf),szBuf);

    CString CurrentAppPath;
    CurrentAppPath = szBuf;
    return CurrentAppPath;
}
BOOL VoiceDataManage::FoldIfExist(CString cFoldname)
{
    TCHAR cCurDirBak[256] = "";
    GetCurrentDirectory(sizeof(cCurDirBak),cCurDirBak);
    if (SetCurrentDirectory(cFoldname))
    {
        SetCurrentDirectory(cCurDirBak);
        return TRUE;
    }
    else
    {
        SetCurrentDirectory(cCurDirBak);
        return FALSE;
    }
}

//根据传进来的文件名或者目录名创建所需的目录
BOOL VoiceDataManage::CreateDirectoryFromString(CString csPath)
{
    TCHAR CurrentDirectory[256];
    GetCurrentDirectory(sizeof(CurrentDirectory),CurrentDirectory);

    CString singlepath = "";
    int ispace;

    ispace = csPath.Find(csSlash);

    if (-1 == ispace)
    {
        SetCurrentDirectory(CurrentDirectory);
        return FALSE;
    }
    while (ispace != -1)
    {
        if (singlepath != "")
            singlepath = singlepath + csSlash + csPath.Left(ispace);//获得某一级目录名
        else
            singlepath = csPath.Left(ispace);//获得某一级目录名

        if (!SetCurrentDirectory(singlepath))//目录不存在
        {
            if (!CreateDirectory(singlepath,NULL))
            {
                SetCurrentDirectory(CurrentDirectory);
                return FALSE;
            }
        }
        csPath = csPath.Right(csPath.GetLength() - ispace - 1);
        ispace = csPath.Find(csSlash);
    }
    SetCurrentDirectory(CurrentDirectory);

    return TRUE;
}

BOOL VoiceDataManage::FileIsSame(CString csFilename,CString csFileContent)
{
    CStdioFile	file;
    if (file.Open(csFilename,CFile::modeRead,NULL))
    {
        DWORD dFilesize,dcsFileConLen;
        dFilesize = file.GetLength();
        dcsFileConLen = csFileContent.GetLength();
        if (dFilesize != dcsFileConLen)
        {
            //file.Close();
            //return FALSE;
        }
        unsigned char* pBufFile = NULL;
        LPCWSTR     lpMultiByteStr = NULL;
        pBufFile = new unsigned char[dFilesize + 1];
        //file.ReadHuge(pBufFile,dFilesize);for vs2005
        file.Close();
        //////////////////////////////////////////////////////////////////////////
        lpMultiByteStr = (LPCWSTR)csFileContent.GetBuffer(csFileContent.GetLength());
        if (strncmp((const char*)lpMultiByteStr,(const char*)pBufFile,dFilesize) == 0)
        {
            csFileContent.ReleaseBuffer();
            delete pBufFile;
            return TRUE;
        }
        csFileContent.ReleaseBuffer();
        delete pBufFile;
    }
    return FALSE;
}
//////////////////////////////////////////////////////////////////////////
BOOL VoiceDataManage::Voice_GetOutputLanguage(CString csOutputLangauge,CString csLanguage)
{
    CString cSingleLanguage;
    int iSpace;

    csOutputLangauge.TrimLeft();
    csOutputLangauge.TrimRight();
    csLanguage.TrimLeft();
    csLanguage.TrimRight();
    if ((csLanguage == "") || (csOutputLangauge == ""))
        return FALSE;

    while (1)
    {
        iSpace = csOutputLangauge.Find(LANGUAGE_SEPARATOR);
        if (-1 == iSpace)
        {
            if (csOutputLangauge == "")
                return FALSE;

            if (csOutputLangauge == csLanguage)
                return TRUE;
            else
                return FALSE;
        }
        cSingleLanguage = csOutputLangauge.Left(iSpace);
        if (cSingleLanguage == csLanguage)
            return TRUE;
        csOutputLangauge = csOutputLangauge.Right(csOutputLangauge.GetLength() - iSpace - 1);
    }
    return FALSE;
}
//////////////////////////////////////////////////////////////////////////
BOOL VoiceDataManage::Voice_OutHeadFiles(CString csLanString,CString csRootPathname,CString csChooseLanguageFilename)
{
    CStdioFile	file,fOutfile;
    CString     cFileName;
    CString		bufRead,cHeadFilename,csLanguageName;
    CString     csResult = "", cCurrentPath,cAmrfilename;
    CString     csDefaultLanguage;
    int iSpace,iLanPrefixLen = strlen(CONFIGFILE_LANGUAGE_FILE_BEGIN);
    typedef enum
    {
        OUTFILES_OUTFILE,
        OUTFILES_NONE
    }OUTPUTLANGUAGEFILES;
    OUTPUTLANGUAGEFILES eOutputType = OUTFILES_NONE;
    int iFileIndex = 0;

    iSpace = csLanString.Find(LANGUAGE_SEPARATOR);
    if (iSpace == -1)
        csDefaultLanguage = csLanString;
    else
        csDefaultLanguage = csLanString.Left(iSpace);

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
                    iFileIndex = 0;
                }
                continue;
            }
            iSpace = bufRead.Find(CONFIGFILE_LANGUAGE_FILE_BEGIN);
            if (iSpace != -1)
            {
                eOutputType = OUTFILES_OUTFILE;
                csLanguageName = bufRead.Right(bufRead.GetLength() - iLanPrefixLen);

                if (!Voice_GetOutputLanguage(csLanString,csLanguageName))//if (csLanString.Find(csLanguageName) == -1)//Can't find the language
                {
                    eOutputType = OUTFILES_NONE;
                    continue;
                }
                cHeadFilename = csRootPathname + csSlash + csLanguageName + ".h";
                if (!fOutfile.Open(cHeadFilename,CFile::modeCreate|CFile::modeWrite,NULL))
                {
                    CString cWrite,csContentClew;
                    //cWrite.LoadString(IDS_STRING_CANNOTWRITEFILE);
                    csContentClew.Format(cWrite,cHeadFilename);
                    AfxMessageBox(csContentClew,MB_ICONASTERISK |MB_OK);
                }
                continue;
            }
            if (eOutputType == OUTFILES_OUTFILE)
            {
                cAmrfilename = cCurrentPath + csSlash + bufRead;

                if (csLanguageName == csDefaultLanguage)
                {
                    if (iFileIndex == CONFIGFILE_AUTOFILEINDEX)
                        csResult += OutputSingleLanguageFile(bufRead,csChooseLanguageFilename);
                    else
                        csResult += OutputSingleLanguageFile(bufRead,cAmrfilename);
                }
                else
                {
                    if (iFileIndex == CONFIGFILE_AUTOFILEINDEX)
                        csResult = csResult + CONFIG_NEWLINE + "/*" + CONFIGFILE_PLACEFILENAME + "*/" + CONFIG_NEWLINE + "0x00,";
                    else
                        csResult += OutputSingleLanguageFile(bufRead,cAmrfilename);
                }
                iFileIndex++;
            }
        }
        file.Close();
    }
    return TRUE;
}
CString VoiceDataManage::OutputSingleLanguageFile(CString csOnlyFilename,CString cSingleLanguage)//output single language data file
{
    CStdioFile fSourfile;
    CString csResult = "";
    DWORD dFilesize,i;

    if (!fSourfile.Open(cSingleLanguage,CFile::typeBinary|CFile::modeRead,NULL))
    {
        CString csRead,csContentClew;
        //csRead.LoadString(IDS_STRING_CANNOTREADFILE);
        csContentClew.Format(csRead,cSingleLanguage);
        AfxMessageBox(csContentClew,MB_ICONASTERISK |MB_OK);
        return csResult;
    }
    dFilesize = fSourfile.GetLength();
    unsigned char * pFileContent = new unsigned char[dFilesize];
    char cNum[10] = "";
    int iComma = 0;

    memset(pFileContent,0x00,dFilesize);
	//comment for vs2005
    //fSourfile.ReadHuge((void*)pFileContent,dFilesize);
    fSourfile.Close();

    csResult = CONFIG_NEWLINE;
    csResult = csResult + "/*" + csOnlyFilename + "*/" + CONFIG_NEWLINE;

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
//////////////////////////////////////////////////////////////////////////
BOOL VoiceDataManage::Voice_OutputVPPosFile(CString csDefineLanguage,CString csUndefineLanguage,
                                            CString csVPPosFilename,CString csVPPosVariable,CString csVPPosContent,
                                            CString csChooseLanguageFilename,CString csRootPathname)
{
    CStdioFile  file;
    CString csPosString = "",csFilename;

    csPosString = csVPPosContent + CONFIG_NEWLINE + "const unsigned long " + csVPPosVariable + "[][2] =" + 
        CONFIG_NEWLINE + "{";
    csPosString = csPosString + GetLanguagePosString(csDefineLanguage,csChooseLanguageFilename) + CONFIG_NEWLINE + "};" + CONFIG_NEWLINE;

    csFilename = csRootPathname + CONFIGFILE_CSTRINGSLASH + csVPPosFilename;
    if (file.Open(csFilename,CFile::modeWrite|CFile::modeCreate,NULL))//打开成功
    {
        file.WriteString(csPosString);
        file.Close();
        return TRUE;
    }
    return FALSE;
}
CString VoiceDataManage::GetLanguagePosString(CString csLanString,CString csChooseLanguageFilename)
{
    CString csResult = "",cSingleLanguage;
    int iSpace;
    unsigned long uDataPosInit = 0,uDataPosResult = 0;

    csLanString.TrimLeft();
    csLanString.TrimRight();
    if (csLanString == "")
        return csResult;

    bFirstTime = TRUE;
    while (1)
    {
        iSpace = csLanString.Find(LANGUAGE_SEPARATOR);
        if (-1 == iSpace)
        {
            if (csLanString == "")
                return csResult;

            csResult = csResult + GetSingleLanguagePosString(csLanString,uDataPosInit,&uDataPosResult,csChooseLanguageFilename);
            return csResult;
        }
        cSingleLanguage = csLanString.Left(iSpace);
        csLanString = csLanString.Right(csLanString.GetLength() - iSpace - 1);

        csResult = csResult + GetSingleLanguagePosString(cSingleLanguage,uDataPosInit,&uDataPosResult,csChooseLanguageFilename) + ",";
        uDataPosInit = uDataPosResult;
    }
}
CString VoiceDataManage::GetSingleLanguagePosString(CString cSingleLanguage,unsigned long uDataPosInit,
                                                    unsigned long * pDataPosResult,CString csChooseLanguageFilename)
{
    CStdioFile	file;
    CString     csResult = "";
    CString     cFileName,cSinglePosString;
    CString		bufRead;
    CString     bufLanguage;
    CString     cFilePath;
    ConfigType  eConfigtype;
    unsigned long iDataPos = uDataPosInit,iFilelen;
    int         iNewPlace = 0,iComma = 0;
    int         iFileIndex = 0;

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;
    if (!file.Open(cFileName,CFile::modeRead,NULL))
    {
        CString csWrite,csContentClew;
        //csWrite.LoadString(IDS_STRING_CANNOTWRITEFILE);
        csContentClew.Format(csWrite,cFileName);
        AfxMessageBox(csContentClew,MB_ICONASTERISK |MB_OK);
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
            if (iFileIndex == CONFIGFILE_AUTOFILEINDEX)
            {
                if (bFirstTime)
                {
                    cFilePath = csChooseLanguageFilename;
                    iFilelen = VoicePromptGetFileSize(cFilePath);
                    bFirstTime = FALSE;
                }
                else
                {
                    iFilelen = 1;
                }
            }
            else
            {
                cFilePath = GetCurrentAppPath() + csSlash + bufRead;
                iFilelen = VoicePromptGetFileSize(cFilePath);
            }
            iFileIndex++;

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
                CString csRead,csContentClew;
                //csRead.LoadString(IDS_STRING_CANNOTOPENFOLD);
                csContentClew.Format(csRead,cFilePath);
                AfxMessageBox(csContentClew,MB_ICONINFORMATION|MB_OK);
            }
        }
    }
    file.Close();
    if (pDataPosResult != NULL)
        * pDataPosResult = iDataPos;

    return csResult;
}
//////////////////////////////////////////////////////////////////////////
BOOL VoiceDataManage::Voice_OutputVPDataFile(CString csDefineLanguage,CString csUndefineLanguage,
                                             CString csVPFilename,CString csVPDataVariable,CString csDataContent,
                                             CString csRootPathname)
{
    CStdioFile  file;
    CString csDataString = "",csFilename;

    csDataString = csDataContent + Voice_GetDefineLanguageList(csDefineLanguage,TRUE);
    csDataString = csDataString + Voice_GetDefineLanguageList(csUndefineLanguage,FALSE);
    csDataString = csDataString + CONFIG_NEWLINE + CONFIG_NEWLINE + 
        "const unsigned char " + csVPDataVariable + "[] =" + CONFIG_NEWLINE + "{";

    csDataString = csDataString + Voice_GetIncludeLanguage(csDefineLanguage) + Voice_GetIncludeLanguage(csUndefineLanguage);
    csDataString = csDataString + "};" + CONFIG_NEWLINE;

    csFilename = csRootPathname + CONFIGFILE_CSTRINGSLASH + csVPFilename;
    if (file.Open(csFilename,CFile::modeWrite|CFile::modeCreate,NULL))//打开成功
    {
        file.WriteString(csDataString);
        file.Close();
        return TRUE;
    }
    return FALSE;
}
CString VoiceDataManage::Voice_GetDefineLanguageList(CString csLanString,BOOL bDefine)
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
CString VoiceDataManage::Voice_GetIncludeLanguage(CString csLanString)
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
//////////////////////////////////////////////////////////////////////////
BOOL VoiceDataManage::Voice_OutputLanguageConfigFile(CString csLanguage,CString csChooseLanguageFilename,
                                               CString csRootPathname,CString csLanguage_Undef)
{
    CStdioFile  file;
    CString		fOutConfigFilename,csResult = "";

    fOutConfigFilename = csLanguage;
    fOutConfigFilename.Replace(LANGUAGE_SEPARATOR,CONFIGFILE_UNDERLINE);
    fOutConfigFilename = csRootPathname + CONFIGFILE_CSTRINGSLASH + CONFIGFILE_BATCHOUTPUT;

    if (file.Open(fOutConfigFilename,CFile::modeWrite|CFile::modeCreate,NULL))//打开成功
    {
        csResult = Voice_GetConfigLanguageList(csLanguage,TRUE,csChooseLanguageFilename);
        csResult = csResult + Voice_GetConfigLanguageList(csLanguage_Undef,FALSE,csChooseLanguageFilename);

        file.WriteString(csResult);
        file.Close();
        return TRUE;
    }
    return FALSE;
}
CString VoiceDataManage::Voice_GetConfigLanguageList(CString csLanString,BOOL bDefine,
                                                     CString csChooseLanguageFilename)
{
    CString csResult = "",cSingleLanguage;
    int iSpace;

    csLanString.TrimLeft();
    csLanString.TrimRight();
    if (csLanString == "")
        return csResult;

    bFirstTime = TRUE;
    while (1)
    {
        iSpace = csLanString.Find(LANGUAGE_SEPARATOR);
        if (-1 == iSpace)
        {
            if (csLanString == "")
                return csResult;

            csResult = csResult + Voice_GetConfigSingleLanguageInfo(csLanString,bDefine,csChooseLanguageFilename);
            return csResult;
        }
        cSingleLanguage = csLanString.Left(iSpace);
        csLanString = csLanString.Right(csLanString.GetLength() - iSpace - 1);

        csResult = csResult + Voice_GetConfigSingleLanguageInfo(cSingleLanguage,bDefine,csChooseLanguageFilename);
    }
}
CString VoiceDataManage::Voice_GetConfigSingleLanguageInfo(CString csSingleLanguage,BOOL bDefine,
                                                           CString csChooseLanguageFilename)
{
    CStdioFile	file;
    CString     cFileName,csCurrentPath;
    CString		bufRead;
    CString     bufLanguage;
    CString     cFilePath;
    CString     csResult = "";
    ConfigType  eConfigtype;
    int iFileIndex = 0;

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
                if (iFileIndex == CONFIGFILE_AUTOFILEINDEX)
                {
                    if ((bFirstTime) && (bDefine))
                    {
                        cFilePath = csChooseLanguageFilename;
                        bFirstTime = FALSE;
                    }
                    else
                    {
                        cFilePath = csCurrentPath + csSlash + csSingleLanguage + csSlash + CONFIGFILE_PLACEFILENAME;
                    }
                    csResult = csResult + cFilePath + CONFIG_NEWLINE;
                }
                else
                {
                    cFilePath = csCurrentPath + csSlash + csSingleLanguage + csSlash + bufRead;
                    csResult = csResult + cFilePath + CONFIG_NEWLINE;
                }
                iFileIndex++;
            }
		}
		file.Close();
        csResult = csResult + CONFIGFILE_ENDIF + CONFIG_NEWLINE;
	}
    return csResult;
}
//////////////////////////////////////////////////////////////////////////
BOOL VoiceDataManage::Voice_OutputLanguagePack_FileSize(CString csLanguage,CString csChooseLanguageFilename,
                                               CString csRootPathname)
{
    CString csLanguageSizeResult,csFilenameSize;
    CStdioFile  file;

    csFilenameSize = csLanguage;
    csFilenameSize.Replace(LANGUAGE_SEPARATOR,CONFIGFILE_UNDERLINE);
    csFilenameSize = csRootPathname + CONFIGFILE_CSTRINGSLASH + csFilenameSize + CONFIGFILE_ACCESSIONALFILEPATULOUSNAME;
    Voice_GetAllLanguagePacksSize(csLanguage,csChooseLanguageFilename,csLanguageSizeResult);

    if (file.Open(csFilenameSize,CFile::modeWrite|CFile::modeCreate,NULL))//打开成功
    {
        file.WriteString(csLanguageSizeResult);
        file.Close();
        return TRUE;
    }
    return FALSE;
}
DWORD VoiceDataManage::Voice_GetAllLanguagePacksSize(CString csLanguage,CString csChooseLanguageFilename,
                                                     CString & csCountResult)
{
    CString cSingleLanguage = "",csSingleLanguageResult = "",csResult = "";
    int iSpace = 0,iFileCount = 0,iFileAmount = 0;
    DWORD dAllLanguagePackSize = 0,iSingleLanguageSize = 0;

    csLanguage.TrimLeft();
    csLanguage.TrimRight();
    if (csLanguage == "")
        return 0;

    bFirstTime = TRUE;
    while (1)
    {
        iSpace = csLanguage.Find(LANGUAGE_SEPARATOR);
        if (-1 == iSpace)
        {
            if (csLanguage == "")
                return dAllLanguagePackSize;

            iSingleLanguageSize = Voice_GetSingleLanguagePacksSize(csLanguage,csChooseLanguageFilename,
                &iFileCount,csSingleLanguageResult);

            dAllLanguagePackSize += iSingleLanguageSize;
            iFileAmount += iFileCount;
            csResult = csResult + csSingleLanguageResult;
            break;
        }
        cSingleLanguage = csLanguage.Left(iSpace);
        csLanguage = csLanguage.Right(csLanguage.GetLength() - iSpace - 1);

        iSingleLanguageSize = Voice_GetSingleLanguagePacksSize(cSingleLanguage,csChooseLanguageFilename,
            &iFileCount,csSingleLanguageResult);

        dAllLanguagePackSize += iSingleLanguageSize;
        iFileAmount += iFileCount;
        csResult = csResult + csSingleLanguageResult;
    }

    CString csLanguageCountResult,csConfigPath,cCurrentPath,fOutConfigFilename,csLanguageAccount;

    //csLanguageAccount.LoadString(IDS_STRING_LANGUAGEACCOUNT);
    csLanguageCountResult.Format(csLanguageAccount,
        csResult,iFileAmount,iFileCount,dAllLanguagePackSize,dAllLanguagePackSize / CONFIGFILE_KUNIT);

    csCountResult = csLanguageCountResult;
    return dAllLanguagePackSize;
}
DWORD VoiceDataManage::Voice_GetSingleLanguagePacksSize(CString csLanguage,CString csChooseLanguageFilename,
                                                        int * pFileCount,CString & csCountResult)
{
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead;
    CString     bufLanguage;
    ConfigType  eConfigtype;
    int         iFileIndex = 0;
    DWORD       dAllFilesize = 0;
    CString     cFilePath,CurrentAppPath;

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
                    if (iFileIndex == CONFIGFILE_AUTOFILEINDEX)
                    {
                        if (bFirstTime)
                        {
                            dAllFilesize += VoicePromptGetFileSize(csChooseLanguageFilename);
                            bFirstTime = FALSE;
                        }
                        else
                        {
                            dAllFilesize++;
                        }
                    }
                    else
                    {
                        dAllFilesize += VoicePromptGetFileSize(cFilePath);
                    }
                    iFileIndex++;
                }
            }
        }
        file.Close();
    }
    if (pFileCount != NULL)
        * pFileCount = iFileIndex;
    
    CString csSingleLanguageInformation,csFileinfo;
    //csSingleLanguageInformation.LoadString(IDS_STRING_SINGLELANACCOUNT);
    csFileinfo.Format(csSingleLanguageInformation,csLanguage,iFileIndex,
        dAllFilesize,dAllFilesize / CONFIGFILE_KUNIT);

    csCountResult = csFileinfo;
    return dAllFilesize;
}
//////////////////////////////////////////////////////////////////////////
void VoiceDataManage::ListBox_MoveItemTop(CCheckListBox & m_ctlCheckList)
{
    int icursel;
    BOOL bCheck;
    CString cSLanguage;

    icursel = m_ctlCheckList.GetCurSel();
    if (icursel == LB_ERR)
        return;

    if (m_ctlCheckList.GetSel(icursel) == 1)
    {
        bCheck = (m_ctlCheckList.GetCheck(icursel) == 1);
        m_ctlCheckList.GetText(icursel,cSLanguage);
        m_ctlCheckList.DeleteString(icursel);
        m_ctlCheckList.InsertString(0,cSLanguage);
        m_ctlCheckList.SetCurSel(0);
        if (bCheck)
            m_ctlCheckList.SetCheck(0,1);
    }
}
void VoiceDataManage::ListBox_MoveItemBelow(CCheckListBox & m_ctlCheckList)
{
    int iListCount,icursel;
    BOOL bCheck;
    CString cSLanguage;

    icursel = m_ctlCheckList.GetCurSel();
    if (icursel == LB_ERR)
        return;

    if (m_ctlCheckList.GetSel(icursel) == 1)
    {
        bCheck = (m_ctlCheckList.GetCheck(icursel) == 1);
        m_ctlCheckList.GetText(icursel,cSLanguage);
        m_ctlCheckList.DeleteString(icursel);
        m_ctlCheckList.AddString(cSLanguage);

        iListCount = m_ctlCheckList.GetCount();
        m_ctlCheckList.SetCurSel(iListCount - 1);
        if (bCheck)
            m_ctlCheckList.SetCheck(iListCount - 1,1);
    }
}
void VoiceDataManage::ListBox_MoveItemUp(CCheckListBox & m_ctlCheckList)
{
    int icursel;
    BOOL bCheck;
    CString cSLanguage;

    icursel = m_ctlCheckList.GetCurSel();
    if (icursel == LB_ERR)
        return;
    if (m_ctlCheckList.GetSel(icursel) == 1)
    {
        bCheck = (m_ctlCheckList.GetCheck(icursel) == 1);
        m_ctlCheckList.GetText(icursel,cSLanguage);
        m_ctlCheckList.DeleteString(icursel);
        m_ctlCheckList.InsertString(icursel - 1,cSLanguage);
        m_ctlCheckList.SetCurSel(icursel - 1);
        if (bCheck)
            m_ctlCheckList.SetCheck(icursel - 1,1);
    }
}
void VoiceDataManage::ListBox_MoveItemDown(CCheckListBox & m_ctlCheckList)
{
    int icursel;
    BOOL bCheck;
    CString cSLanguage;

    icursel = m_ctlCheckList.GetCurSel();
    if (icursel == LB_ERR)
        return;
    if (m_ctlCheckList.GetSel(icursel) == 1)
    {
        bCheck = (m_ctlCheckList.GetCheck(icursel) == 1);
        m_ctlCheckList.GetText(icursel,cSLanguage);
        m_ctlCheckList.DeleteString(icursel);
        m_ctlCheckList.InsertString(icursel + 1,cSLanguage);

        m_ctlCheckList.SetCurSel(icursel + 1);
        if (bCheck)
            m_ctlCheckList.SetCheck(icursel + 1,1);
    }
}
//////////////////////////////////////////////////////////////////////////
BOOL VoiceDataManage::ReadConfigFile(CCheckListBox & m_ctlCheckList)//read langauge to listbox
{
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead;
    typedef enum ConfigType
    {
        CONFIGTYPE_LANGUAGE,
        CONFIGTYPE_NONE
    };
    ConfigType  eConfigtype;

    m_ctlCheckList.ResetContent();

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;

	if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
	{
		while (file.ReadString(bufRead))
		{
			while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
				bufRead = bufRead.Left(bufRead.GetLength() - 1);

            if (bufRead == CONFIGFILE_LANGUAGE_BEGIN)
            {
                eConfigtype = CONFIGTYPE_LANGUAGE;
                continue;
            }
            if ((bufRead == CONFIGFILE_LANGUAGE_END) || (bufRead == ""))
            {
                eConfigtype = CONFIGTYPE_NONE;
                continue;
            }
            if (CONFIGTYPE_LANGUAGE == eConfigtype)
                m_ctlCheckList.AddString(bufRead);
            else
                break;
		}
		file.Close();
	}
    return TRUE;
}

CString VoiceDataManage::GetBatchOutputLanguage(CString cLanguages)
{
    return cLanguages;
//    CString csLan,csReplace;
//
//    csReplace.LoadString(IDS_STRING_ANDSTRING);
//
//    csLan = cLanguages;
//    if (cLanguages.Find(csReplace) == -1)
//    {
//        csLan.Replace(CONFIGFILE_QUOTATION,"");
//        csLan += LANGUAGE_SEPARATOR;
//        return csLan;
//    }
//    csLan.Replace(csReplace,LANGUAGE_SEPARATOR);
//    csLan.Replace(CONFIGFILE_QUOTATION,"");
//    return csLan;
}

void VoiceDataManage::InitButtonBitmap(CButton & cB,int iBitmapID)
{
    HBITMAP hBitmapTop;
    HINSTANCE	hInstResource = NULL;
    hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(iBitmapID),RT_GROUP_ICON);
    hBitmapTop = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(iBitmapID), IMAGE_BITMAP, 0, 0, 0);
    cB.SetBitmap(hBitmapTop);
}
////////////////////////////////////////////////////////////////////
void VoiceDataManage::SetSubfoldToComboBox(CComboBox & m_Combo_SelectPath,CString strFilePath)
{
    CFileFind   find;
    CString     csSearchPath;
    BOOL        bWorking;

    csSearchPath = strFilePath + CONFIGFILE_SEARCHFILE;

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
}
void VoiceDataManage::SetSubfoldFileToComboBox(CComboBox & m_Combo_SelectPath,CString strFilePath)
{
    CFileFind   find;
    CString     csSearchPath;
    BOOL        bWorking;

    strFilePath.TrimLeft();
    strFilePath.TrimRight();
    if (strFilePath == "")
        return;
    csSearchPath = strFilePath + CONFIGFILE_SEARCHFILE;

    bWorking = find.FindFile(csSearchPath);
    while (bWorking)
    {
        bWorking    = find.FindNextFile();
        strFilePath = find.GetFilePath();
        
        if (find.IsDots())
            continue;
        
        if (find.IsDirectory())
            continue;

        m_Combo_SelectPath.AddString(find.GetFilePath());
    }
    find.Close();
}
//////////////////////////////////////////////////////////////////////////
void VoiceDataManage::SetComboWidth(CComboBox & combox)//设置下拉列表部分的宽度
{
    int		i,iComboxCount,iMaxLen;
	CString	csFoldList;

    iMaxLen      = 0;
	iComboxCount = combox.GetCount();
	for (i = iComboxCount - 1;i >= 0;i--)
	{
		combox.GetLBText(i,csFoldList);
		if (csFoldList.GetLength() > iMaxLen)
            iMaxLen = csFoldList.GetLength();
	}
    combox.SendMessage(CB_SETDROPPEDWIDTH,iMaxLen * 7,0);
}
//////////////////////////////////////////////////////////////////////////


BOOL VoiceDataManage::Voice_CreatePlaceFile(CString csFilename)
{
    CStdioFile filePlace;
    if (filePlace.Open(csFilename,CFile::modeCreate|CFile::modeWrite,NULL))
    {
        unsigned char cFileContent[2] = "";
        cFileContent[0] = 0x00;
        filePlace.Write((void*)cFileContent,1);
        filePlace.Close();
        return TRUE;
    }
    return FALSE;
}

int VoiceDataManage::Voice_StringToInt(CString cSTring)
{
    LPTSTR p;
    int iResult;
    p = cSTring.GetBuffer(cSTring.GetLength());
    iResult = atoi(p);
    cSTring.ReleaseBuffer(-1);
    return iResult;
}
