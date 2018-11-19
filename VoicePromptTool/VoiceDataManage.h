// VoiceDataManage.h: interface for the VoiceDataManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOICEDATAMANAGE_H__37F05CF8_BFCA_45A4_8BE6_6D829E1E2BCE__INCLUDED_)
#define AFX_VOICEDATAMANAGE_H__37F05CF8_BFCA_45A4_8BE6_6D829E1E2BCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "voicepromptinfo.h"

class VoiceDataManage  
{
private:
    BOOL bFirstTime;
    typedef enum ConfigType
    {
        CONFIGTYPE_LANGUAGE,
        CONFIGTYPE_ENUM,
        CONFIGTYPE_FILEINFO,
        CONFIGTYPE_NONE
    };
public:
    BOOL CreateDirectoryFromString(CString csPath);
	BOOL Voice_CreatePlaceFile(CString csFilename);
	VoiceDataManage();
	virtual ~VoiceDataManage();
    BOOL FileIsSame(CString csFilename,CString csFileContent);
    CString GetCurrentAppPath(void);//返回当前应用所在路径
    DWORD VoicePromptGetFileSize(CString cFilename);
    BOOL FileIfExist(CString cFilename);
    //////////////////////////////////////////////////////////////////////////
    BOOL Voice_OutHeadFiles(CString csLanString,CString csRootPathname,CString csChooseLanguageFilename);
    CString OutputSingleLanguageFile(CString csOnlyFilename,CString cSingleLanguage);//output single language data file
    //////////////////////////////////////////////////////////////////////////
    BOOL Voice_OutputVPPosFile(CString csDefineLanguage,CString csUndefineLanguage,
        CString csVPPosFilename,CString csVPPosVariable,CString csVPPosContent,
        CString csChooseLanguageFilename,CString csRootPathname);
    CString GetLanguagePosString(CString csLanString,CString csChooseLanguageFilename);
    CString GetSingleLanguagePosString(CString cSingleLanguage,unsigned long uDataPosInit,
        unsigned long * pDataPosResult,CString csChooseLanguageFilename);
    //////////////////////////////////////////////////////////////////////////
    BOOL Voice_OutputVPDataFile(CString csDefineLanguage,CString csUndefineLanguage,
        CString csVPFilename,CString csVPDataVariable,CString csDataContent,
        CString csRootPathname);
    CString Voice_GetDefineLanguageList(CString csLanString,BOOL bDefine);
    CString Voice_GetIncludeLanguage(CString csLanString);
    //////////////////////////////////////////////////////////////////////////
    BOOL Voice_OutputLanguageConfigFile(CString csLanguage,CString csChooseLanguageFilename,
                                               CString csRootPathname,CString csLanguage_Undef);
    CString Voice_GetConfigLanguageList(CString csLanString,BOOL bDefine,
                                                     CString csChooseLanguageFilename);
    CString Voice_GetConfigSingleLanguageInfo(CString csSingleLanguage,BOOL bDefine,CString csChooseLanguageFilename);
    //////////////////////////////////////////////////////////////////////////
    DWORD Voice_GetAllLanguagePacksSize(CString csLanguage,CString csChooseLanguageFilename,
                                                     CString & csCountResult);
    DWORD Voice_GetSingleLanguagePacksSize(CString csLanguage,CString csChooseLanguageFilename,
                                                        int * pFileCount,CString & csCountResult);

    BOOL Voice_OutputLanguagePack_FileSize(CString csLanguage,CString csChooseLanguageFilename,
                                               CString csRootPathname);
    //////////////////////////////////////////////////////////////////////////
    BOOL Voice_GetOutputLanguage(CString csOutputLangauge,CString csLanguage);
    void InitButtonBitmap(CButton & cB,int iBitmapID);
    CString GetBatchOutputLanguage(CString cLanguages);

    void ListBox_MoveItemTop(CCheckListBox & m_ctlCheckList);
    void ListBox_MoveItemBelow(CCheckListBox & m_ctlCheckList);
    void ListBox_MoveItemUp(CCheckListBox & m_ctlCheckList);
    void ListBox_MoveItemDown(CCheckListBox & m_ctlCheckList);

    BOOL FoldIfExist(CString cFoldname);
    BOOL ReadConfigFile(CCheckListBox &m_ctlCheckList);//read langauge to listbox

    void SetSubfoldToComboBox(CComboBox & m_Combo_SelectPath,CString strFilePath);
    void SetSubfoldFileToComboBox(CComboBox & m_Combo_SelectPath,CString strFilePath);
    void SetComboWidth(CComboBox & combox);//设置下拉列表部分的宽度
    ///////////////////////////////////////////////////////////////////
    int Voice_StringToInt(CString cSTring);
};

#endif // !defined(AFX_VOICEDATAMANAGE_H__37F05CF8_BFCA_45A4_8BE6_6D829E1E2BCE__INCLUDED_)
