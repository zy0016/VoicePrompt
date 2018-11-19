// VoicePromptToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VoicePromptTool.h"
#include "VoicePromptToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
static const CString csSlash = CONFIGFILE_CSTRINGSLASH;
static const CString DefaultEnumFileinformation[] =
{
    "\\9_insert_simcard.amr",
    "\\10_call_history.amr",
    "\\11_change_ringtone.amr",
    "\\12_set_alarm.amr",
    "\\13_change_time.amr",
    "\\14_send_a_message.amr",
    "\\15_read_messages.amr",
    "\\44_if_youd_like_to_hear_help.amr",
    "\\place.amr",
    "\\5_error.amr",
    "\\24_enter_sim_pin.amr",
    "\\4_press_up_to_delete.amr", 
    "\\46_press_right.amr",
    "\\17_write_your_message.amr",
    "\\18_Enter_number_or_press_phone.amr",
    "\\21_enter_new_sim_pin.amr",
    "\\25_wrong_code.amr",
    "\\27_enter_puk_code.amr",
    "\\28_write_name.amr",
    "\\29_enter_pin.amr",
    "\\35_enter_new_sim_pin.amr",
    "\\1_enter_time.amr",
    "\\47_new_sms.amr",
    "\\22_enter_subsidy_pin.amr",
    "\\32_enter_sms_prepaid_code.amr",
    "\\20_sim_disabled.amr",
    "\\2_am.amr",
    "\\2b_pm.amr",
    "\\3_no_calls.amr",
    "\\6_to_make_a_call.amr",
    "\\7_to_store_a_phone_number.amr", 
    "\\8_press_phonebook_button_to_call.amr",
    "\\8b_change_volume_alt.amr",
    "\\16_cant_display_message_in_this_language.amr",
    "\\33_enter_voicemail_number.amr",
    "\\37_new_voicemail.amr",
    "\\39_no_messages.amr",
    ""
};
static const float fKunit = CONFIGFILE_KUNIT;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoicePromptToolDlg dialog

CVoicePromptToolDlg::CVoicePromptToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVoicePromptToolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVoicePromptToolDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVoicePromptToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVoicePromptToolDlg)
	DDX_Control(pDX, IDC_STATIC_OUTPUTFILESCOUNT, m_Static_OutputFileCount);
	DDX_Control(pDX, IDC_LIST_BATCHOUTPUT, m_List_BatchOutput);
	DDX_Control(pDX, IDC_STATIC_LANGUAGEINFO, m_Static_LanguageCount);
	DDX_Control(pDX, IDC_EDIT_SEARCHLANGUAGE, m_Edit_Language);
	DDX_Control(pDX, IDC_BUTTON_LANGUAGEDOWN, m_Language_Down);
	DDX_Control(pDX, IDC_BUTTON_MOVEBELOW, m_Language_MoveDown);
	DDX_Control(pDX, IDC_BUTTON_MOVETOP, m_Language_MoveTop);
	DDX_Control(pDX, IDC_BUTTON_LANGUAGEUP, m_Language_Up);
    DDX_Control(pDX, IDC_LIST_LANGUAGE, m_ctlCheckList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVoicePromptToolDlg, CDialog)
	//{{AFX_MSG_MAP(CVoicePromptToolDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST_LANGUAGE, OnSelchangeListLanguage)
	ON_EN_CHANGE(IDC_EDIT_SEARCHLANGUAGE, OnChangeEditSearchlanguage)
	ON_BN_CLICKED(IDC_BUTTON_MOVETOP, OnButtonMovetop)
	ON_BN_CLICKED(IDC_BUTTON_LANGUAGEUP, OnButtonLanguageup)
	ON_BN_CLICKED(IDC_BUTTON_MOVEBELOW, OnButtonMovebelow)
	ON_BN_CLICKED(IDC_BUTTON_LANGUAGEDOWN, OnButtonLanguagedown)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_OPTION, OnButtonOption)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoicePromptToolDlg message handlers

BOOL CVoicePromptToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    //////////////////////////////////////////////////////////////////////////
	m_ctlCheckList.ResetContent();
    //////////////////////////////////////////////////////////////////////////
    m_Language_Up.EnableWindow(FALSE);
    m_Language_Down.EnableWindow(FALSE);
    m_Language_MoveTop.EnableWindow(FALSE);
    m_Language_MoveDown.EnableWindow(FALSE);
    //////////////////////////////////////////////////////////////////////////
    VoiceDataManage vdm;
    vdm.ReadConfigFile(m_ctlCheckList);
    //////////////////////////////////////////////////////////////////////////
    vdm.InitButtonBitmap(m_Language_MoveTop,IDB_BITMAP_TOP);
    vdm.InitButtonBitmap(m_Language_MoveDown,IDB_BITMAP_BELOW);
    vdm.InitButtonBitmap(m_Language_Up,IDB_BITMAP_UP);
    vdm.InitButtonBitmap(m_Language_Down,IDB_BITMAP_DOWN);
    //////////////////////////////////////////////////////////////////////////
    DisplayLanguageCount();
    //////////////////////////////////////////////////////////////////////////
    m_List_BatchOutput.SetListCtrlText();
    //////////////////////////////////////////////////////////////////////////
    ReadBatchOutputFile();
    //////////////////////////////////////////////////////////////////////////
    ClewBatchOutputFileCount();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVoicePromptToolDlg::ClewBatchOutputFileCount(void)
{
    CString csOutput,csClew = "Folds number is %d,%d files will be outputted.";
    int iFoldCount,iOutputFileCount;
    iOutputFileCount = Voice_GetOutputFilesCount();
    iFoldCount = m_List_BatchOutput.GetItemCount();
    //csClew.LoadString(IDS_STRING_OUTPUTCLEW);
    csOutput.Format(csClew,iFoldCount,iOutputFileCount);
    m_Static_OutputFileCount.SetWindowText(csOutput);
}
int CVoicePromptToolDlg::Voice_GetOutputFilesCount(void)//Get output file count
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
int CVoicePromptToolDlg::Voice_GetLanguageCount(CString csLanguage)
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


BOOL CVoicePromptToolDlg::Voice_ReadParameter(void)
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
    VoiceDataManage vdm;

    VOICETYPE eVoiceType = VOICETYPE_NONE;

    cFileName = vdm.GetCurrentAppPath() + csSlash + CONFIGFILENAME;

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

void CVoicePromptToolDlg::DisplayLanguageCount(void)
{
    int iLanguageCount;
    CString csLan,csLanguageCount;
    iLanguageCount = m_ctlCheckList.GetCount();
    csLan.LoadString(IDS_STRING_LANGUAGECOUNT);
    csLanguageCount.Format(csLan,iLanguageCount);
    m_Static_LanguageCount.SetWindowText(csLanguageCount);
}

void CVoicePromptToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVoicePromptToolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVoicePromptToolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVoicePromptToolDlg::OnSelchangeListLanguage() 
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

void CVoicePromptToolDlg::OnChangeEditSearchlanguage() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString cLanguage;

    m_Edit_Language.GetWindowText(cLanguage);
    if (cLanguage == "")
    {
        m_ctlCheckList.SetCurSel(-1);
        return;
    }
    int i,ilistcount,iFind;
    CString ListText;

    cLanguage.MakeLower();
    ilistcount = m_ctlCheckList.GetCount();
    for (i = 0;i < ilistcount;i++)
    {
        m_ctlCheckList.GetText(i,ListText);
        ListText.MakeLower();
        iFind = ListText.Find(cLanguage);
        if (iFind == 0)
        {
            m_ctlCheckList.SetCurSel(i);
            break;
        }
        else
        {
            m_ctlCheckList.SetCurSel(-1);
        }
    }
}

void CVoicePromptToolDlg::OnButtonMovetop() 
{
	// TODO: Add your control notification handler code here
	VoiceDataManage vdm;
    vdm.ListBox_MoveItemTop(m_ctlCheckList);
    OnSelchangeListLanguage();
}

void CVoicePromptToolDlg::OnButtonLanguageup() 
{
	// TODO: Add your control notification handler code here
	VoiceDataManage vdm;
    vdm.ListBox_MoveItemUp(m_ctlCheckList);
    OnSelchangeListLanguage();
}

void CVoicePromptToolDlg::OnButtonMovebelow() 
{
	// TODO: Add your control notification handler code here
	VoiceDataManage vdm;
    vdm.ListBox_MoveItemBelow(m_ctlCheckList);
    OnSelchangeListLanguage();
}

void CVoicePromptToolDlg::OnButtonLanguagedown() 
{
	// TODO: Add your control notification handler code here
	VoiceDataManage vdm;
    vdm.ListBox_MoveItemDown(m_ctlCheckList);
    OnSelchangeListLanguage();
}

void CVoicePromptToolDlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	VoiceDataManage vdm;
    vdm.ReadConfigFile(m_ctlCheckList);

    m_ctlCheckList.SetCurSel(0);
    OnSelchangeListLanguage();
}

void CVoicePromptToolDlg::ReadBatchOutputFile(void)
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
    CString csAnd = "\" and \"",csTemp,csSize = "%ldbyte %5.3fK";
    CString csLanguageSequence,csLanguageChoose,csLanguageFold,csLanguagePackSize;
    CString csOnlyFold,csOnlyFilename;
    VoiceDataManage cVoiceData;
    BATCH_SCAN_TYPE eScanType = BATCH_SCAN_NONE;

    cFileName = cVoiceData.GetCurrentAppPath() + csSlash + CONFIGFILENAMEBATCH;

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

                    //csSize.LoadString(IDS_STRING_BATCH_SIZE_INFO);
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

void CVoicePromptToolDlg::OnButtonOption() 
{
	// TODO: Add your control notification handler code here
	BatchOutputOption cBatchOption;
    if (cBatchOption.DoModal() == IDOK)
    {
        m_List_BatchOutput.DeleteAllItems();
        ReadBatchOutputFile();
    }
}
