       // BatchOutput.cpp : implementation file
//

#include "stdafx.h"
#include "voiceprompt.h"
#include "BatchOutput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
static const CString csSlash = CONFIGFILE_CSTRINGSLASH;
/////////////////////////////////////////////////////////////////////////////
// BatchOutput dialog


BatchOutput::BatchOutput(CWnd* pParent /*=NULL*/)
	: CDialog(BatchOutput::IDD, pParent)
{
	//{{AFX_DATA_INIT(BatchOutput)
	//}}AFX_DATA_INIT
}


void BatchOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BatchOutput)
	DDX_Control(pDX, IDC_STATIC_OUTPUTFILESCOUNT, m_Static_OutputFileCount);
	DDX_Control(pDX, IDC_PROGRESS_BATCHOUTPUTFILES, m_Progress_BatchOutput);
	DDX_Control(pDX, IDC_LIST_BATCHOUTPUT, m_List_BatchOutput);
	DDX_Control(pDX, IDC_BUTTON_BATCHDOWN, m_Language_Down);
	DDX_Control(pDX, IDC_BUTTON_BATCH_UP, m_Language_Up);
	DDX_Control(pDX, IDC_BUTTON_BATCHBELOW, m_Language_MoveDown);
	DDX_Control(pDX, IDC_BUTTON_BATCH_TOP, m_Language_MoveTop);
	DDX_Control(pDX, IDC_LIST_BATCHLANGUAGE, m_ctlCheckList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BatchOutput, CDialog)
	//{{AFX_MSG_MAP(BatchOutput)
	ON_LBN_SELCHANGE(IDC_LIST_BATCHLANGUAGE, OnSelchangeListBatchlanguage)
	ON_BN_CLICKED(IDC_BUTTON_BATCH_TOP, OnButtonBatchTop)
	ON_BN_CLICKED(IDC_BUTTON_BATCHBELOW, OnButtonBatchbelow)
	ON_BN_CLICKED(IDC_BUTTON_BATCH_UP, OnButtonBatchUp)
	ON_BN_CLICKED(IDC_BUTTON_BATCHDOWN, OnButtonBatchdown)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_ADDBATCHITEM, OnButtonAddbatchitem)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_BATCHOUTPUT, OnButtonBatchoutput)
	ON_BN_CLICKED(IDC_BUTTON_OPTION, OnButtonOption)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BatchOutput message handlers

BOOL BatchOutput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CWaitCursor wait;
	ReadConfigFile();
    //////////////////////////////////////////////////////////////////////////
    VoiceDataManage vdm;
    vdm.InitButtonBitmap(m_Language_MoveTop,IDB_BITMAP_TOP);
    vdm.InitButtonBitmap(m_Language_MoveDown,IDB_BITMAP_BELOW);
    vdm.InitButtonBitmap(m_Language_Up,IDB_BITMAP_UP);
    vdm.InitButtonBitmap(m_Language_Down,IDB_BITMAP_DOWN);
    //////////////////////////////////////////////////////////////////////////
    m_Language_Up.EnableWindow(FALSE);
    m_Language_Down.EnableWindow(FALSE);
    m_Language_MoveTop.EnableWindow(FALSE);
    m_Language_MoveDown.EnableWindow(FALSE);
    //////////////////////////////////////////////////////////////////////////
    m_List_BatchOutput.SetListCtrlText();
    //////////////////////////////////////////////////////////////////////////
    ReadBatchOutputFile();
    //////////////////////////////////////////////////////////////////////////
    Voice_ReadParameter();
    //////////////////////////////////////////////////////////////////////////
    m_Progress_BatchOutput.ShowWindow(SW_HIDE);
    //////////////////////////////////////////////////////////////////////////
    ClewBatchOutputFileCount();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void BatchOutput::ClewBatchOutputFileCount(void)
{
    CString csOutput,csClew;
    int iFoldCount,iOutputFileCount;
    iOutputFileCount = Voice_GetOutputFilesCount();
    iFoldCount = m_List_BatchOutput.GetItemCount();
    csClew.LoadString(IDS_STRING_OUTPUTCLEW);
    csOutput.Format(csClew,iFoldCount,iOutputFileCount);
    m_Static_OutputFileCount.SetWindowText(csOutput);
}

void BatchOutput::ReadBatchOutputFile(void)
{
    BOOL bNeedSort = FALSE;
    int iTypeIndex = 0,i,iListCount;
    CStdioFile	file;
    CString     cFileName,bufRead;
    typedef enum BatchFileReadType
    {
        BATCHFILE_BEGIN,
        BATCHFILE_END
    };
    BatchFileReadType eBatchType = BATCHFILE_END;
    CString csBatchLanguage,csFilename,csLanguagePath,csActualFilename,csActualFoldname,csPacksize;
    CString csAnd,csTemp,csSize;
    CString csLanguageSequence,csLanguageChoose,csLanguageFold,csLanguagePackSize;
    CString csOnlyFold,csOnlyFilename;
    VoiceDataManage cVoiceData;
    BATCH_SCAN_TYPE eScanType = BATCH_SCAN_NONE;

    csAnd.LoadString(IDS_STRING_ANDSTRING);
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
                csChooseFold = bufRead;
                continue;
            }
            if (eScanType == BATCH_SCAN_ROOTFOLD)
            {
                csRootFold = bufRead;
                continue;
            }

            if (bufRead == CONFIGFILE_BATCH_ITEMBEGIN)
            {
                eBatchType = BATCHFILE_BEGIN;
                iTypeIndex = 0;
                continue;
            }
            if ((bufRead == CONFIGFILE_BATCH_ITEMEND) || (bufRead == ""))
            {
                eBatchType = BATCHFILE_END;
                if (iTypeIndex == 3)
                {
                    DWORD dPacksize = 0;
                    iListCount = m_List_BatchOutput.GetItemCount();
                    if (csChooseFold.Right(1) != CONFIGFILE_CSTRINGSLASH)
                        csActualFilename = csChooseFold + csSlash + csFilename;
                    else
                        csActualFilename = csChooseFold + csFilename;

                    if (csActualFoldname.Right(1) != CONFIGFILE_CSTRINGSLASH)
                        csActualFoldname = csRootFold + csSlash + csLanguagePath;
                    else
                        csActualFoldname = csRootFold + csLanguagePath;

                    dPacksize = cVoiceData.Voice_GetAllLanguagePacksSize(csBatchLanguage,csActualFilename,csTemp);

                    csSize.LoadString(IDS_STRING_BATCH_SIZE_INFO);
                    csPacksize.Format(csSize,dPacksize,dPacksize / CONFIGFILE_KUNIT);

                    for (i = 0;i < iListCount;i++)
                    {
                        csLanguageSequence = m_List_BatchOutput.GetItemText(i,0);
                        csLanguageChoose   = m_List_BatchOutput.GetItemText(i,1);
                        csLanguageFold     = m_List_BatchOutput.GetItemText(i,2);
                        csLanguagePackSize = m_List_BatchOutput.GetItemText(i,3);

                        csOnlyFold = csLanguageFold.Right(csLanguageFold.GetLength() - csRootFold.GetLength() - 1);
                        if (csLanguagePath.CompareNoCase(csOnlyFold) < 0)
                        {
                            m_List_BatchOutput.InsertItem(i,csBatchLanguage);
                            m_List_BatchOutput.SetItemText(i,1,csActualFilename);
                            m_List_BatchOutput.SetItemText(i,2,csActualFoldname);
                            m_List_BatchOutput.SetItemText(i,3,csPacksize);
                            iTypeIndex = 0;
                            bNeedSort = TRUE;
                            break;
                        }
                    }
                    if (iTypeIndex != 0)
                    {
                        m_List_BatchOutput.InsertItem(iListCount,csBatchLanguage);
                        m_List_BatchOutput.SetItemText(iListCount,1,csActualFilename);
                        m_List_BatchOutput.SetItemText(iListCount,2,csActualFoldname);
                        m_List_BatchOutput.SetItemText(iListCount,3,csPacksize);
                        iTypeIndex = 0;
                    }
                }
                continue;
            }
            switch (iTypeIndex)
            {
            case 0:
                csBatchLanguage = bufRead;
                break;
            case 1:
                csFilename = bufRead;
                break;
            case 2:
                csLanguagePath = bufRead;
                break;
            }
            iTypeIndex++;
        }
        file.Close();
    }
    //////////////////////////////////////////////////////////////////////////
    if (bNeedSort)//sort the language fold sequence.
    {
        CString csResult = "";

        csResult = csResult + CONFIGFILE_BATCH_CHOOSELANGUAGEFOLDBEGIN + CONFIG_NEWLINE +
            csChooseFold + CONFIG_NEWLINE +
            CONFIGFILE_BATCH_CHOOSELANGUAGEFOLDEND + CONFIG_NEWLINE + CONFIG_NEWLINE +
            CONFIGFILE_BATCH_OUTPUTROOTFOLDBEGIN + CONFIG_NEWLINE +
            csRootFold + CONFIG_NEWLINE +
            CONFIGFILE_BATCH_OUTPUTROOTFOLDEND + CONFIG_NEWLINE + CONFIG_NEWLINE;

        iListCount = m_List_BatchOutput.GetItemCount();
        for (i = 0;i < iListCount;i++)
        {
            csLanguageSequence = m_List_BatchOutput.GetItemText(i,0);
            csLanguageChoose   = m_List_BatchOutput.GetItemText(i,1);
            csLanguageFold     = m_List_BatchOutput.GetItemText(i,2);

            csOnlyFilename  = csLanguageChoose.Right(csLanguageChoose.GetLength() - csChooseFold.GetLength() - 1);
            csOnlyFold      = csLanguageFold.Right(csLanguageFold.GetLength() - csRootFold.GetLength() - 1);

            csResult = csResult + CONFIGFILE_BATCH_ITEMBEGIN + CONFIG_NEWLINE +
                csLanguageSequence + CONFIG_NEWLINE +
                csOnlyFilename + CONFIG_NEWLINE +
                csOnlyFold + CONFIG_NEWLINE +
                CONFIGFILE_BATCH_ITEMEND + CONFIG_NEWLINE + CONFIG_NEWLINE;
        }
        CFile::Remove(cFileName);
        if (file.Open(cFileName,CFile::modeCreate|CFile::modeWrite,NULL))//打开成功
        {
            file.WriteString(csResult);
            file.Close();
        }
    }
}

BOOL BatchOutput::Voice_ReadParameter(void)
{
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead;
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
    return TRUE;
}
void BatchOutput::OnButtonOption() 
{
	// TODO: Add your control notification handler code here
	BatchOutputOption cBatchOption;
    if (cBatchOption.DoModal() == IDOK)
    {
        m_List_BatchOutput.DeleteAllItems();
        ReadBatchOutputFile();
    }
}

BOOL BatchOutput::ReadConfigFile(void)//read langauge to listbox
{
    VoiceDataManage vdm;
    vdm.ReadConfigFile(m_ctlCheckList);
    return TRUE;
}

void BatchOutput::OnSelchangeListBatchlanguage() 
{
	// TODO: Add your control notification handler code here
	int iCount = m_ctlCheckList.GetCount();
    int i, iSelCount = 0;//m_ctlCheckList.GetSelCount();

    if (m_ctlCheckList.GetCurSel() == 0)
    {
        m_Language_Up.EnableWindow(FALSE);
        m_Language_Down.EnableWindow(TRUE);
        m_Language_MoveTop.EnableWindow(FALSE);
        m_Language_MoveDown.EnableWindow(TRUE);
    }
    else if (m_ctlCheckList.GetCurSel() == iCount - 1)
    {
        m_Language_Up.EnableWindow(TRUE);
        m_Language_Down.EnableWindow(FALSE);
        m_Language_MoveTop.EnableWindow(TRUE);
        m_Language_MoveDown.EnableWindow(FALSE);
    }
    else
    {
        m_Language_Up.EnableWindow(TRUE);
        m_Language_Down.EnableWindow(TRUE);
        m_Language_MoveTop.EnableWindow(TRUE);
        m_Language_MoveDown.EnableWindow(TRUE);
    }
    for (i = 0;i < iCount;i++)
    {
        if (m_ctlCheckList.GetCheck(i) == 1)
        {
            iSelCount++;
        }
    }
    if (iSelCount > 3)
    {
        CString cClew,cSelect3Lan;
        cClew.LoadString(IDS_STRING_CLEW);
        cSelect3Lan.LoadString(IDS_STRING1_SELECT3LANGUAGE);
        MessageBox(cSelect3Lan,cClew,MB_ICONINFORMATION|MB_OK);
        for (i = 0;i < iCount;i++)
        {
            if (m_ctlCheckList.GetCheck(i) == 1)
            {
                m_ctlCheckList.SetCheck(i,0);
                break;
            }
        }
        return;
    }
}

void BatchOutput::OnButtonBatchTop() 
{
	// TODO: Add your control notification handler code here
    VoiceDataManage vdm;
    vdm.ListBox_MoveItemTop(m_ctlCheckList);
    OnSelchangeListBatchlanguage();
}

void BatchOutput::OnButtonBatchbelow() 
{
	// TODO: Add your control notification handler code here
    VoiceDataManage vdm;
    vdm.ListBox_MoveItemBelow(m_ctlCheckList);
    OnSelchangeListBatchlanguage();
}

void BatchOutput::OnButtonBatchUp() 
{
	// TODO: Add your control notification handler code here
    VoiceDataManage vdm;
    vdm.ListBox_MoveItemUp(m_ctlCheckList);
    OnSelchangeListBatchlanguage();
}

void BatchOutput::OnButtonBatchdown() 
{
	// TODO: Add your control notification handler code here
    VoiceDataManage vdm;
    vdm.ListBox_MoveItemDown(m_ctlCheckList);
    OnSelchangeListBatchlanguage();
}

void BatchOutput::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	ReadConfigFile();
    m_ctlCheckList.SetCurSel(0);
    OnSelchangeListBatchlanguage();
}

void BatchOutput::OnButtonAddbatchitem() 
{
	// TODO: Add your control notification handler code here
	int i, iSelCount = 0;
    int iCount = m_ctlCheckList.GetCount();
    CString cClew,csLanguage3,csLanguage1,csLanguage;
    CString csOutConfigName = "",csAnd;
    int iListCount = m_List_BatchOutput.GetItemCount();

    csAnd.LoadString(IDS_STRING_AND);
    for (i = 0;i < iCount;i++)
    {
        if (m_ctlCheckList.GetCheck(i) == 1)
        {
            m_ctlCheckList.GetText(i,csLanguage);
            if (iSelCount > 0)
                csOutConfigName = csOutConfigName + LANGUAGE_SEPARATOR + csLanguage;
            else
                csOutConfigName = csOutConfigName + csLanguage;

            iSelCount++;
        }
    }

    cClew.LoadString(IDS_STRING_CLEW);
    csLanguage1.LoadString(IDS_STRING_LANGUAGE1);
    csLanguage3.LoadString(IDS_STRING_LANGUAGE3);
    if (iSelCount > 3)
    {
        MessageBox(csLanguage3,cClew,MB_ICONINFORMATION|MB_OK);
        m_ctlCheckList.SetFocus();
        return;
    }
    if (iSelCount == 0)
    {
        MessageBox(csLanguage1,cClew,MB_ICONINFORMATION|MB_OK);
        m_ctlCheckList.SetFocus();
        return;
    }

    CAddBatchInfor cAddBatchInfo(NULL,csOutConfigName,BATCH_MODIFY_ADD,"","");
    CString csFilename,csFoldname;
    
    if (cAddBatchInfo.DoModal() == IDOK)
    {
        cAddBatchInfo.GetEnumFileName(csFilename,csFoldname);

        m_List_BatchOutput.InsertItem(iListCount,csOutConfigName);
        m_List_BatchOutput.SetItemText(iListCount,1,csFilename);
        m_List_BatchOutput.SetItemText(iListCount,2,csFoldname);

        ClewBatchOutputFileCount();
    }
}

void BatchOutput::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	CStdioFile	file;
    CString     cFileName,csFileContent = "",csBatchLanguages,csFilename,csPathname;
    POSITION pos = m_List_BatchOutput.GetFirstSelectedItemPosition();
	int nSelectedItem = m_List_BatchOutput.GetNextSelectedItem(pos);//获得列表框中当前选择的项目
    int iListCount = m_List_BatchOutput.GetItemCount(),i;
    CString csActualFilename,csActualFoldname;
    VoiceDataManage vdm;
    
    if (nSelectedItem == -1)
        return;

    csBatchLanguages = m_List_BatchOutput.GetItemText(nSelectedItem,0);

    CString cClew,csDelete,csDeleteClew;
    cClew.LoadString(IDS_STRING_CLEW);
    csDelete.LoadString(IDS_STRING_BATCHDELETE);
    csDeleteClew.Format(csDelete,csBatchLanguages);
    if (MessageBox(csDeleteClew, cClew, MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)==IDNO)
    {
        return;
    }

    csFileContent = csFileContent + CONFIGFILE_BATCH_CHOOSELANGUAGEFOLDBEGIN + CONFIG_NEWLINE;
    csFileContent = csFileContent + csChooseFold + CONFIG_NEWLINE;
    csFileContent = csFileContent + CONFIGFILE_BATCH_CHOOSELANGUAGEFOLDEND + CONFIG_NEWLINE + CONFIG_NEWLINE;
    csFileContent = csFileContent + CONFIGFILE_BATCH_OUTPUTROOTFOLDBEGIN + CONFIG_NEWLINE;
    csFileContent = csFileContent + csRootFold + CONFIG_NEWLINE;
    csFileContent = csFileContent + CONFIGFILE_BATCH_OUTPUTROOTFOLDEND + CONFIG_NEWLINE + CONFIG_NEWLINE;

    for (i = 0;i < iListCount;i++)
    {
        if (i != nSelectedItem)
        {
            csBatchLanguages = m_List_BatchOutput.GetItemText(i,0);
            csFilename = m_List_BatchOutput.GetItemText(i,1);
            csPathname = m_List_BatchOutput.GetItemText(i,2);

            csActualFilename = csFilename.Right(csFilename.GetLength() - csChooseFold.GetLength() - 1);
            csActualFoldname = csPathname.Right(csPathname.GetLength() - csRootFold.GetLength() - 1);

            csBatchLanguages = vdm.GetBatchOutputLanguage(csBatchLanguages);

            csFileContent = csFileContent + CONFIGFILE_BATCH_ITEMBEGIN + CONFIG_NEWLINE;
            csFileContent = csFileContent + csBatchLanguages + CONFIG_NEWLINE;
            csFileContent = csFileContent + csActualFilename + CONFIG_NEWLINE;
            csFileContent = csFileContent + csActualFoldname + CONFIG_NEWLINE;
            csFileContent = csFileContent + CONFIGFILE_BATCH_ITEMEND + CONFIG_NEWLINE + CONFIG_NEWLINE;
        }
    }
    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAMEBATCH;
    CFile::Remove(cFileName);
    if (file.Open(cFileName,CFile::modeCreate|CFile::modeWrite,NULL))//打开成功
    {
        file.WriteString(csFileContent);
        file.Close();
    }
    m_List_BatchOutput.DeleteItem(nSelectedItem);
    ClewBatchOutputFileCount();
}

//Check the data's valid in listctrl.
BOOL BatchOutput::Voice_JustTheDataValid(CString csBatchLanguages,CString csFilename,CString csPathname)
{
    CString cClew,cContent,cConResult,csCreatePath;
    VoiceDataManage cVoiceData;

    cClew.LoadString(IDS_STRING_CLEW);

    csBatchLanguages.TrimLeft();
    csBatchLanguages.TrimRight();
    csFilename.TrimLeft();
    csFilename.TrimRight();
    csPathname.TrimLeft();
    csPathname.TrimRight();
    if (csBatchLanguages == "")
    {
        cContent.LoadString(IDS_STRING_BATCHINVALIDDATA);
        cConResult.Format(cContent,csBatchLanguages);
        MessageBox(cConResult,cClew,MB_ICONINFORMATION|MB_OK);
        return FALSE;
    }
    if (!FileIfExist(csFilename))
    {
        cContent.LoadString(IDS_STRING_CANNOTFINDFILE);
        cConResult.Format(cContent,csFilename);
        MessageBox(cConResult,cClew,MB_ICONINFORMATION|MB_OK);
        return FALSE;
    }
    if (!cVoiceData.FoldIfExist(csPathname))
    {
        //cContent.LoadString(IDS_STRING_FINDSOURFOLDFAIL);
        //cConResult.Format(cContent,csPathname);
        if (csPathname.Right(1) != csSlash)
            csCreatePath = csPathname + csSlash;
        return CreateDirectoryFromString(csCreatePath);
//        if (MessageBox(cConResult,cClew,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON1) == IDYES)//Create the fold?
//        {
//            if (csPathname.Right(1) != csSlash)
//                csCreatePath = csPathname + csSlash;
//            return CreateDirectoryFromString(csCreatePath);
//        }
//        else
//        {
//            return FALSE;
//        }
    }
    return TRUE;
}
//check single file's properties,if the file is readonly,clew the user to check out it.
BOOL BatchOutput::Voice_JustSingleFileProperties(CString csFilename)
{
    CFileStatus rStatus;
    CString cClew,cClew1,cClew2;

    if (FileIfExist(csFilename))
    {
        memset(&rStatus,0x00,sizeof(CFileStatus));
        if (CFile::GetStatus(csFilename,rStatus))//if (file.Open(csFilename,CFile::modeRead,NULL))
        {
            if (rStatus.m_attribute & CFile::readOnly)
            {
                rStatus.m_attribute = rStatus.m_attribute ^ CFile::readOnly;
                CFile::SetStatus(csFilename,rStatus);
                return TRUE;
            }
        }
    }
    return TRUE;
}
BOOL BatchOutput::Voice_JustTheFileProperties(CString csBatchLanguages,CString csFilename,CString csPathname,
                                              CString &csOutputCount)
{
    //csBatchLanguages:Bahasa_Indonesia English_UK Mandarin
    //just the UI_Flex_VP_Pos.c file and the UI_Flex_VP_Data.c is readonly?
    CString csVPPosFilename,csVPDataFilename,csSingleLan,csOutputHeadfilename,csSingleOutputCount = "";
    int ispace;

    csVPDataFilename = csPathname + csSlash + csDataFilename;
    if (!Voice_JustSingleFileProperties(csVPDataFilename))
        return FALSE;
    csSingleOutputCount = csSingleOutputCount + csVPDataFilename + CONFIG_NEWLINE1;
    //////////////////////////////////////////////////////////////////////////
    csVPPosFilename = csPathname + csSlash + csPosFilename;
    if (!Voice_JustSingleFileProperties(csVPPosFilename))
        return FALSE;
    csSingleOutputCount = csSingleOutputCount + csVPPosFilename + CONFIG_NEWLINE1;
    //////////////////////////////////////////////////////////////////////////
    while (1)
    {
        ispace = csBatchLanguages.Find(LANGUAGE_SEPARATOR);
        if (ispace == -1)
        {
            csOutputHeadfilename = csPathname + csSlash + csBatchLanguages + ".h";
            if (!Voice_JustSingleFileProperties(csOutputHeadfilename))
                return FALSE;
            csSingleOutputCount = csSingleOutputCount + csOutputHeadfilename + CONFIG_NEWLINE1;
            break;
        }
        csSingleLan = csBatchLanguages.Left(ispace);
        csBatchLanguages = csBatchLanguages.Right(csBatchLanguages.GetLength() - ispace - 1);

        csOutputHeadfilename = csPathname + csSlash + csSingleLan + ".h";
        if (!Voice_JustSingleFileProperties(csOutputHeadfilename))
            return FALSE;
        csSingleOutputCount = csSingleOutputCount + csOutputHeadfilename + CONFIG_NEWLINE1;
    }
    csOutputCount = csSingleOutputCount + CONFIG_NEWLINE1;
    return TRUE;
}

CString BatchOutput::Voice_GetUndefineLanguage(CString csDefineLanguage)
{
    CString csResult = "",cSingleLanguage;
    int i,iListCount;

    csDefineLanguage.TrimLeft();
    csDefineLanguage.TrimRight();
    if (csDefineLanguage == "")
        return csResult;

    iListCount = m_ctlCheckList.GetCount();
    for (i = 0;i < iListCount;i++)
    {
        m_ctlCheckList.GetText(i,cSingleLanguage);
        if (csDefineLanguage.Find(cSingleLanguage) == -1)
        {
            if (csResult == "")
                csResult = cSingleLanguage;
            else
                csResult = csResult + LANGUAGE_SEPARATOR + cSingleLanguage;
        }
    }
    return csResult;
}

//output files
void BatchOutput::OnButtonBatchoutput() 
{
	// TODO: Add your control notification handler code here
	int iListCount = m_List_BatchOutput.GetItemCount(),i;
    if (iListCount == 0)
        return;

    DWORD dPacksize;
    CString csBatchLanguages,csFilename,csPathname,csSingleLan,csBatchLanguages_bak,csTemp;
    VoiceDataManage cVoiceData;
    CString csOutputCount = "",csOutputSingleCount = "";
    CWaitCursor wait;
    //check the files that must be outputed,if the files aren't checked out,clew the user check out it.
    for (i = 0;i < iListCount;i++)
    {
        csBatchLanguages = m_List_BatchOutput.GetItemText(i,0);
        csFilename = m_List_BatchOutput.GetItemText(i,1);
        csPathname = m_List_BatchOutput.GetItemText(i,2);
        csBatchLanguages_bak = csBatchLanguages;

        if (!Voice_JustTheDataValid(csBatchLanguages,csFilename,csPathname))
            return;
        csBatchLanguages = cVoiceData.GetBatchOutputLanguage(csBatchLanguages);
        if (!Voice_JustTheFileProperties(csBatchLanguages,csFilename,csPathname,csOutputSingleCount))
            return;
        csOutputCount = csOutputCount + csOutputSingleCount + CONFIG_NEWLINE1;
        //////////////////////////////////////////////////////////////////////////
        //check the pack size,if the pack size is large more than 150k,clew the user.
        dPacksize = cVoiceData.Voice_GetAllLanguagePacksSize(csBatchLanguages,csFilename,csTemp);
        if (dPacksize > CONFIGFILE_PACKSIZELIMITION)
        {
            CString cClew,cClew1,cClew2;
            cClew.LoadString(IDS_STRING_CLEW);
            cClew1.LoadString(IDS_STRING_BATCHOUTPUT_PACKCLEW);
            cClew2.Format(cClew1,csBatchLanguages_bak);
            if (MessageBox(cClew2,cClew,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON1) == IDNO)
            {
                return;
            }
        }
    }
    //check end
    //////////////////////////////////////////////////////////////////////////
    int iOutputFilesCount,iOutputFileIndex = 0;
    iOutputFilesCount = Voice_GetOutputFilesCount();
    m_Progress_BatchOutput.ShowWindow(SW_SHOW);
    m_Progress_BatchOutput.SetRange(0,iOutputFilesCount);
    m_Progress_BatchOutput.SetStep(0);
    m_Progress_BatchOutput.SetProgressFillColor(RGB(255,0,0));
    m_Progress_BatchOutput.SetProgressTextColor(RGB(0,0,255));
    m_Progress_BatchOutput.ShowPreText(TRUE);
    //////////////////////////////////////////////////////////////////////////
    //begin output
    CString csUndefindLan = "";
    for (i = 0;i < iListCount;i++)
    {
        csBatchLanguages = m_List_BatchOutput.GetItemText(i,0);
        csFilename       = m_List_BatchOutput.GetItemText(i,1);
        csPathname       = m_List_BatchOutput.GetItemText(i,2);

        csBatchLanguages = cVoiceData.GetBatchOutputLanguage(csBatchLanguages);//English_UK;Hindi;Mandarin
        csUndefindLan    = Voice_GetUndefineLanguage(csBatchLanguages);
        //////////////////////////////////////////////////////////////////////////
        //output file size information
        cVoiceData.Voice_OutputLanguagePack_FileSize(csBatchLanguages,csFilename,csPathname);
        iOutputFileIndex++;
        m_Progress_BatchOutput.SetPos(iOutputFileIndex);
        //////////////////////////////////////////////////////////////////////////
        //output the config file.
        cVoiceData.Voice_OutputLanguageConfigFile(csBatchLanguages,csFilename,csPathname,csUndefindLan);
        iOutputFileIndex++;
        m_Progress_BatchOutput.SetPos(iOutputFileIndex);
        //////////////////////////////////////////////////////////////////////////
        //output the UI_Flex_VP_Data.c
        cVoiceData.Voice_OutputVPDataFile(csBatchLanguages,csUndefindLan,csDataFilename,csDataVariable,
            csDataContent,csPathname);
        iOutputFileIndex++;
        m_Progress_BatchOutput.SetPos(iOutputFileIndex);
        //////////////////////////////////////////////////////////////////////////
        //output the UI_Flex_VP_Pos.c
        cVoiceData.Voice_OutputVPPosFile(csBatchLanguages,csUndefindLan,csPosFilename,csPosVariable,
            csPosContent,csFilename,csPathname);
        iOutputFileIndex++;
        m_Progress_BatchOutput.SetPos(iOutputFileIndex);
        //////////////////////////////////////////////////////////////////////////
        //output head files
        cVoiceData.Voice_OutHeadFiles(csBatchLanguages,csPathname,csFilename);
        iOutputFileIndex = iOutputFileIndex + Voice_GetLanguageCount(csBatchLanguages);
        m_Progress_BatchOutput.SetPos(iOutputFileIndex);
    }
    m_Progress_BatchOutput.ShowWindow(SW_HIDE);

    CString csOutCount;
    csOutCount.LoadString(IDS_STRING_BATCHOUTPUTRESUTL);
    CLanguagePackInfo cDialogLanguageInfo(NULL,csOutputCount,csOutCount);
    cDialogLanguageInfo.DoModal();
}

int BatchOutput::Voice_GetOutputFilesCount(void)//Get output file count
{
    int iListCount = m_List_BatchOutput.GetItemCount(),i,iFileCount = 0;
    if (iListCount == 0)
        return 0;

    CString csBatchLanguages,csFilename,csPathname;
    VoiceDataManage cVoiceData;

    for (i = 0;i < iListCount;i++)
    {
        csBatchLanguages = m_List_BatchOutput.GetItemText(i,0);
        csFilename = m_List_BatchOutput.GetItemText(i,1);
        csPathname = m_List_BatchOutput.GetItemText(i,2);

        iFileCount = iFileCount + Voice_GetLanguageCount(csBatchLanguages) + 4;
        /*config.ini;file size file;UI_Flex_VP_Data.c;UI_Flex_VP_Pos.c;4 files*/
    }
    return iFileCount;
}

int BatchOutput::Voice_GetLanguageCount(CString csLanguage)
{
    int iCount = 0,ispace;

    while (1)
    {
        ispace = csLanguage.Find(LANGUAGE_SEPARATOR);
        if (ispace == -1)
            break;

        csLanguage = csLanguage.Left(ispace);
        iCount++;
    }
    return iCount;
}

