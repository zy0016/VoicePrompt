                 // VoicePromptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VoicePrompt.h"
#include "VoicePromptDlg.h"
#include "voicepromptinfo.h"
#include <wininet.h>
#include "zlib.h"
#pragma comment(lib,"wininet.lib")



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
// CVoicePromptDlg dialog

CVoicePromptDlg::CVoicePromptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVoicePromptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVoicePromptDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVoicePromptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVoicePromptDlg)
	DDX_Control(pDX, IDC_STATIC_LANGUAGEINFO, m_Static_LanguageCount);
	DDX_Control(pDX, IDC_BUTTON_MOVEBELOW, m_Language_MoveDown);
	DDX_Control(pDX, IDC_BUTTON_MOVETOP, m_Language_MoveTop);
	DDX_Control(pDX, IDC_STATIC_ALLSIZE, m_Static_Filesize);
	DDX_Control(pDX, IDC_BUTTON_DELETELANGUAGE, m_DeleteLanguage);
	DDX_Control(pDX, IDC_LIST_ENUMINFO, m_VoicePromptListCtrl);
	DDX_Control(pDX, IDC_BUTTON_LANGUAGEDOWN, m_Language_Down);
	DDX_Control(pDX, IDC_BUTTON_LANGUAGEUP, m_Language_Up);
	DDX_Control(pDX, IDC_BUTTON_ADDLANGUAGE, m_Button_AddLanguage);
	DDX_Control(pDX, IDC_EDIT_LANGUAGE, m_Edit_Language);
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_LIST_LANGUAGE, m_ctlCheckList);
}

BEGIN_MESSAGE_MAP(CVoicePromptDlg, CDialog)
	//{{AFX_MSG_MAP(CVoicePromptDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_LANGUAGE, OnChangeEditLanguage)
	ON_LBN_SELCHANGE(IDC_LIST_LANGUAGE, OnSelchangeListLanguage)
	ON_BN_CLICKED(IDC_BUTTON_ADDLANGUAGE, OnButtonAddlanguage)
	ON_BN_CLICKED(IDC_BUTTON_DELETELANGUAGE, OnButtonDeletelanguage)
	ON_BN_CLICKED(IDC_BUTTON_LANGUAGEUP, OnButtonLanguageup)
	ON_BN_CLICKED(IDC_BUTTON_LANGUAGEDOWN, OnButtonLanguagedown)
	ON_BN_CLICKED(IDC_BUTTON_OPTION, OnButtonOption)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUTFILES, OnButtonOutputfiles)
	ON_BN_CLICKED(IDC_BUTTON_COUNTLANGUAGESSIZE, OnButtonCountlanguagessize)
	ON_BN_CLICKED(IDC_BUTTON_CLEARALL, OnButtonClearall)
	ON_BN_CLICKED(IDC_BUTTON_MOVETOP, OnButtonMovetop)
	ON_BN_CLICKED(IDC_BUTTON_MOVEBELOW, OnButtonMovebelow)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_CHECKFILE, OnButtonCheckfile)
	ON_BN_CLICKED(IDC_BUTTON_COUNTALLLANGUAGES, OnButtonCountalllanguages)
	ON_BN_CLICKED(IDC_BUTTON_COUNTSILENT, OnButtonCountsilent)
	ON_BN_CLICKED(IDC_BUTTON_BATCHOUTPUTFILES, OnButtonBatchoutputfiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoicePromptDlg message handlers

BOOL CVoicePromptDlg::OnInitDialog()
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
	TCHAR szBuf[512] = "";
    //AFX_MANAGE_STATE(AfxGetStaticModuleState());
    //hins=AfxGetInstanceHandle();
    GetCurrentDirectory(sizeof(szBuf),szBuf);
    CurrentAppPath = szBuf;
    //GetModuleFileName(AfxGetInstanceHandle(),szBuf,sizeof(szBuf));//获得当前应用的具体名称,包括路径
    //GetModuleFileName(NULL,szBuf,sizeof(szBuf));//也可以    

    //**********************************************
    m_ctlCheckList.ResetContent();
	//m_ctlCheckList.SetCheckStyle( BS_AUTO3STATE );

    m_Language_Up.EnableWindow(FALSE);
    m_Language_Down.EnableWindow(FALSE);
    m_Language_MoveTop.EnableWindow(FALSE);
    m_Language_MoveDown.EnableWindow(FALSE);
    m_Button_AddLanguage.EnableWindow(FALSE);
    //**********************************************
    m_VoicePromptListCtrl.SetListCtrlText();

    ReadConfigFile();
    //////////////////////////////////////////////////////////////////////////
    VoiceDataManage vdm;
    vdm.InitButtonBitmap(m_Language_MoveTop,IDB_BITMAP_TOP);
    vdm.InitButtonBitmap(m_Language_MoveDown,IDB_BITMAP_BELOW);
    vdm.InitButtonBitmap(m_Language_Up,IDB_BITMAP_UP);
    vdm.InitButtonBitmap(m_Language_Down,IDB_BITMAP_DOWN);

    //////////////////////////////////////////////////////////////////////////
    DisplayLanguageCount();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

CString GetCurrentAppPath(void)//返回当前应用所在路径
{
    return CurrentAppPath;
}
BOOL FileIfExist(CString cFilename)
{
    CStdioFile	file;
    if (file.Open(cFilename,CFile::modeRead,NULL))//打开成功
    {
        file.Close();
        return TRUE;
    }
    return FALSE;
}
DWORD VoicePromptGetFileSize(CString cFilename)
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
//根据传进来的文件名或者目录名创建所需的目录
BOOL CreateDirectoryFromString(CString csPath)
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

//////////////////////////////////////////////////////////////////////////
BOOL CVoicePromptDlg::ReadConfigFile(void)
{
    VoiceDataManage vdm;
    vdm.ReadConfigFile(m_ctlCheckList);
    return TRUE;
}
void CVoicePromptDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVoicePromptDlg::OnPaint() 
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
HCURSOR CVoicePromptDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVoicePromptDlg::DisplayLanguageCount(void)
{
    int iLanguageCount;
    CString csLan,csLanguageCount;
    iLanguageCount = m_ctlCheckList.GetCount();
    csLan.LoadString(IDS_STRING_LANGUAGECOUNT);
    csLanguageCount.Format(csLan,iLanguageCount);
    m_Static_LanguageCount.SetWindowText(csLanguageCount);
}

void CVoicePromptDlg::OnChangeEditLanguage() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString cLanguage;

    m_Edit_Language.GetWindowText(cLanguage);
    if (cLanguage != "")
    {
        m_Button_AddLanguage.EnableWindow(TRUE);
    }
    else
    {
        m_Button_AddLanguage.EnableWindow(FALSE);
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

void CVoicePromptDlg::OnSelchangeListLanguage() 
{
	// TODO: Add your control notification handler code here
	CString cLanguage;

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
    //////////////////////////////////////////////////////////////////////////
    int iCursel = m_ctlCheckList.GetCurSel();
    if (iCursel < 0)
        return;
    m_ctlCheckList.GetText(iCursel,cLanguage);
    cSelectLanguage = cLanguage;
    ReadEnumFileInformation(cLanguage);
}

void CVoicePromptDlg::ReadEnumFileInformation(CString csLanguageIndex)
{
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead;
    CString     bufLanguage;
    CString     cFilePath,cFilesize;
    ConfigType  eConfigtype = CONFIGTYPE_NONE;
    int iIndex = 0;
    DWORD       dAllFilesize = 0,dFilesize;
    CString     csYes,csNo,csFilesize,csSingleLan;

    csYes.LoadString(IDS_STRING_YES);
    csNo.LoadString(IDS_STRING_NO);
    csFilesize.LoadString(IDS_STRING_FILESIZEINFO);

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;
    bufLanguage = CONFIGFILE_LANGUAGE_FILE_BEGIN + csLanguageIndex;

	if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
	{
        m_VoicePromptListCtrl.DeleteAllItems();
		while (file.ReadString(bufRead))
		{
			while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
				bufRead = bufRead.Left(bufRead.GetLength() - 1);

            if (bufRead == CONFIGFILE_ENUM_BEGIN)
            {
                eConfigtype = CONFIGTYPE_ENUM;
                continue;
            }
            if ((bufRead == CONFIGFILE_ENUM_END) || (bufRead == CONFIGFILE_LANGUAGE_FILE_END))
            {
                eConfigtype = CONFIGTYPE_NONE;
                continue;
            }
            if (bufRead == bufLanguage)
            {
                eConfigtype = CONFIGTYPE_FILEINFO;
                continue;
            }
            if (bufRead == "")
            {
                eConfigtype = CONFIGTYPE_NONE;
                continue;
            }
            if (CONFIGTYPE_ENUM == eConfigtype)
            {
                int iListCount = m_VoicePromptListCtrl.GetItemCount();
                m_VoicePromptListCtrl.InsertItem(iListCount,bufRead);
#if 0//Don't blink,but I can't confirm the operate don't arouse other problem now.
                if (iListCount < 37)
                    m_VoicePromptListCtrl.InsertItem(iListCount,bufRead);
#endif
            }
            else if (CONFIGTYPE_FILEINFO == eConfigtype)
            {
                cFilePath = CurrentAppPath + csSlash + bufRead;
                m_VoicePromptListCtrl.SetItemText(iIndex,1,cFilePath);
                if (FileIfExist(cFilePath))
                {
                    dFilesize = VoicePromptGetFileSize(cFilePath);
                    dAllFilesize += dFilesize;
                    cFilesize.Format(csFilesize,dFilesize);

                    m_VoicePromptListCtrl.SetItemText(iIndex,2,csYes);
                    m_VoicePromptListCtrl.SetItemText(iIndex,3,cFilesize);
                }
                else
                {
                    cFilesize.Format(csFilesize,0);
                    m_VoicePromptListCtrl.SetItemText(iIndex,2,csNo);
                    m_VoicePromptListCtrl.SetItemText(iIndex,3,cFilesize);
                }
                iIndex++;
            }
            else
            {
                continue;
            }
		}
		file.Close();

        csSingleLan.LoadString(IDS_STRING_SINGLELANINFO);
        cFilesize.Format(csSingleLan,iIndex,dAllFilesize,dAllFilesize / fKunit);
        m_Static_Filesize.SetWindowText(cFilesize);
	}
}


void CVoicePromptDlg::OnButtonAddlanguage() 
{
	// TODO: Add your control notification handler code here
	CString cSLanguage;
	int i,iListCount;
	CString cSList;
    CString cClew,cContentClew;

	m_Edit_Language.GetWindowText(cSLanguage);
	cSLanguage.TrimLeft();
	cSLanguage.TrimRight();

	if (cSLanguage == "")
	{
        cContentClew.LoadString(IDS_STRING_ENTERLANGUAGE);
        cClew.LoadString(IDS_STRING_CLEW);
		MessageBox(cContentClew,cClew,MB_ICONINFORMATION|MB_OK);
        m_Edit_Language.SetWindowText("");
		m_Edit_Language.SetFocus();
		return;
	}
	iListCount = m_ctlCheckList.GetCount();
	for (i = 0;i < iListCount;i++)
	{
		m_ctlCheckList.GetText(i,cSList);
		if (cSList == cSLanguage)
		{
            cContentClew.LoadString(IDS_STRING_LANGUAGEEXIST);
            cClew.LoadString(IDS_STRING_CLEW);
			MessageBox(cContentClew,cClew,MB_ICONINFORMATION|MB_OK);
			m_Edit_Language.SetSel(0,-1);
			m_Edit_Language.SetFocus();
			return;
		}
	}
	m_ctlCheckList.AddString(cSLanguage.GetBuffer(cSLanguage.GetLength()));
    cSLanguage.ReleaseBuffer();
	m_Edit_Language.SetWindowText("");
	m_Edit_Language.SetFocus();
    //////////////////////////////////////////////////////////////////////////
    //save langauge
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead,csFileContent = "";
    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;
    if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
    {
        while (file.ReadString(bufRead))
        {
            while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
                bufRead = bufRead.Left(bufRead.GetLength() - 1);

            if (bufRead == CONFIGFILE_LANGUAGE_END)
            {
                csFileContent = csFileContent + cSLanguage + CONFIG_NEWLINE + 
                    CONFIGFILE_LANGUAGE_END + CONFIG_NEWLINE;
            }
            else
            {
                csFileContent = csFileContent + bufRead + CONFIG_NEWLINE;
            }
        }
        file.Close();
        csFileContent = csFileContent + CONFIG_NEWLINE + 
            CONFIGFILE_LANGUAGE_FILE_BEGIN + cSLanguage + CONFIG_NEWLINE;
        i = 0;
        while (DefaultEnumFileinformation[i] != "")
        {
            csFileContent = csFileContent + cSLanguage + DefaultEnumFileinformation[i] + CONFIG_NEWLINE;
            i++;
        }
        csFileContent = csFileContent + CONFIGFILE_LANGUAGE_FILE_END + CONFIG_NEWLINE;
    }
    CFile::Remove(cFileName);
    if (file.Open(cFileName,CFile::modeCreate|CFile::modeWrite,NULL))//打开成功
    {
        file.WriteString(csFileContent);
        file.Close();
    }
    DisplayLanguageCount();
}

void CVoicePromptDlg::OnButtonDeletelanguage() 
{
	// TODO: Add your control notification handler code here
	CString cSLanguage;
	int i,iListCount;
    CString cClew,csDelete,csDeleteClew;
    cClew.LoadString(IDS_STRING_CLEW);

	iListCount = m_ctlCheckList.GetCount();
	for (i = 0;i < iListCount;i++)
	{
		if (m_ctlCheckList.GetSel(i) == 1)
		{
			m_ctlCheckList.GetText(i,cSLanguage);
            csDelete.LoadString(IDS_STRING_DELETELANGUAGE);
            csDeleteClew.Format(csDelete,cSLanguage);
			if (MessageBox(csDeleteClew, cClew, MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)==IDYES)
			{
				m_ctlCheckList.DeleteString(i);
				m_ctlCheckList.SetCurSel((i == iListCount - 1) ? i - 1 : i);
                if (m_ctlCheckList.GetCount() == 0)
                {
                    m_DeleteLanguage.EnableWindow(FALSE);
                }
                //////////////////////////////////////////////////////////////////////////
                //Delete language
                CStdioFile	file;
                CString     cFileName,csDeleteString;
                CString		bufRead,csFileContent = "";
                BOOL        bFindDeletelanguage = FALSE;
                cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;

                csDeleteString = CONFIGFILE_LANGUAGE_FILE_BEGIN + cSLanguage;
                if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
                {
                    while (file.ReadString(bufRead))
                    {
                        while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
                            bufRead = bufRead.Left(bufRead.GetLength() - 1);
                        
                        if (bufRead == cSLanguage)
                        {
                            continue;
                        }
                        else if (bufRead == csDeleteString)
                        {
                            bFindDeletelanguage = TRUE;
                            continue;
                        }
                        else if (bufRead == CONFIGFILE_LANGUAGE_FILE_END)
                        {
                            //if (!bFindDeletelanguage)
                            csFileContent = csFileContent + bufRead + CONFIG_NEWLINE;
                            bFindDeletelanguage = FALSE;
                            continue;
                        }
                        if (!bFindDeletelanguage)
                            csFileContent = csFileContent + bufRead + CONFIG_NEWLINE;
                        else
                            continue;
                    }
                    file.Close();
                }
                CFile::Remove(cFileName);
                if (file.Open(cFileName,CFile::modeCreate|CFile::modeReadWrite,NULL))//打开成功
                {
                    file.WriteString(csFileContent);
                    file.Close();
                }
                //////////////////////////////////////////////////////////////////////////
				break;
			}
		}
	}
    DisplayLanguageCount();
}

void CVoicePromptDlg::OnButtonLanguageup() 
{
	// TODO: Add your control notification handler code here
    VoiceDataManage vdm;
    vdm.ListBox_MoveItemUp(m_ctlCheckList);
    OnSelchangeListLanguage();
}

void CVoicePromptDlg::OnButtonLanguagedown() 
{
	// TODO: Add your control notification handler code here
    VoiceDataManage vdm;
    vdm.ListBox_MoveItemDown(m_ctlCheckList);
    OnSelchangeListLanguage();
}

void CVoicePromptDlg::OnButtonOption() 
{
	// TODO: Add your control notification handler code here
	cOptionDialog.DoModal();
}

CString GetVoicePromptLanguage(void)
{
    //CString csLanguage;
    //m_ctlCheckList.GetText(m_ctlCheckList.GetSel(),csLanguage);
    return cSelectLanguage;
}

void CVoicePromptDlg::OnButtonOutputfiles() 
{
	// TODO: Add your control notification handler code here
    int i, iSelCount = 0,iUnselcount = 0;
    int iCount = m_ctlCheckList.GetCount();
    CString cClew,csLanguage3,csLanguage1,csLanguage,csOutFilenameDefine = "",csOutFilenameUndef = "";
    CString cClewLanguage = "";
    CString csAnd;

    csAnd.LoadString(IDS_STRING_ANDSTRING);
    for (i = 0;i < iCount;i++)
    {
        m_ctlCheckList.GetText(i,csLanguage);
        if (m_ctlCheckList.GetCheck(i) == 1)
        {
            if (iSelCount > 0)
            {
                csOutFilenameDefine = csOutFilenameDefine + LANGUAGE_SEPARATOR + csLanguage;
                cClewLanguage = cClewLanguage + csAnd + csLanguage;
            }
            else
            {
                m_ctlCheckList.SetCurSel(i);
                OnSelchangeListLanguage();
                csOutFilenameDefine += csLanguage;
                cClewLanguage += csLanguage;
            }
            iSelCount++;
        }
        else
        {
            if (iUnselcount > 0)
                csOutFilenameUndef = csOutFilenameUndef + LANGUAGE_SEPARATOR + csLanguage;
            else
                csOutFilenameUndef += csLanguage;

            iUnselcount++;
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

    CString cLansequence11,cLansequence12,cLansequence2;
    cLansequence11.LoadString(IDS_STRING_LANSEQUENCE11);
    cLansequence12.LoadString(IDS_STRING_LANSEQUENCE12);
    cLansequence2.LoadString(IDS_STRING_LANSEQUENCE2);
    if (iSelCount == 1)
        cClewLanguage = cLansequence11 + cClewLanguage + cLansequence2;
    else
        cClewLanguage = cLansequence12 + cClewLanguage + cLansequence2;

    if (MessageBox(cClewLanguage,cClew,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON1) == IDNO)//The language sequence is right?
    {
        return;
    }

    if (!SelectLanguageConfirm(csOutFilenameDefine))//clew the select language file is right?
    {
        CString cSeleLan;
        cSeleLan.LoadString(IDS_STRING_CLEWSELLAN);
        MessageBox(cSeleLan,cClew,MB_ICONINFORMATION|MB_OK);

        CEnumInfo CDEnuminfo(NULL,OPERATETYPE_EDIT,m_VoicePromptListCtrl.GetItemText(CONFIGFILE_AUTOFILEINDEX,0),
            m_VoicePromptListCtrl.GetItemText(CONFIGFILE_AUTOFILEINDEX,1));
        if (CDEnuminfo.DoModal() == IDOK)
        {
            CString csEnum,csFilename;
            CDEnuminfo.GetEnumFileName(csEnum,csFilename);
            m_VoicePromptListCtrl.SetItemText(CONFIGFILE_AUTOFILEINDEX,0,csEnum);
            m_VoicePromptListCtrl.SetItemText(CONFIGFILE_AUTOFILEINDEX,1,csFilename);
        }
        return;
    }
    if (!JustTheFilesExist())
    {
        return;
    }

    cOutputFiles cOutfile(NULL,csOutFilenameDefine,csOutFilenameUndef,iCount,iSelCount);
    cOutfile.DoModal();
}

int CVoicePromptDlg::SelectLanguageConfirm(CString csLanDefine)
{
    CString cClew;
    cClew.LoadString(IDS_STRING_CLEW);
    if (csLanDefine == "")
    {
        CString csLanguage1;
        csLanguage1.LoadString(IDS_STRING_LANGUAGE1);
        MessageBox(csLanguage1,cClew,MB_ICONINFORMATION|MB_OK);
        return FALSE;
    }

    int iSpace;
    CString csFirstLan;
    iSpace = csLanDefine.Find(LANGUAGE_SEPARATOR);
    if (iSpace == -1)
        csFirstLan = csLanDefine;
    else
        csFirstLan = csLanDefine.Left(iSpace);

    CStdioFile	file;
    CString     cFileName;
    CString		bufRead,bufLanguage,cFilePath;
    ConfigType  eConfigtype = CONFIGTYPE_NONE;
    int         iFileIndex = 0;

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;
    bufLanguage = CONFIGFILE_LANGUAGE_FILE_BEGIN + csFirstLan;

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
                if (iFileIndex == CONFIGFILE_AUTOFILEINDEX)
                {
                    cFilePath = GetCurrentAppPath() + csSlash + bufRead;
                    break;
                }
                iFileIndex++;
            }
        }
    }
    file.Close();

    CString cCue,csFileLan;
    csFileLan.LoadString(IDS_STRING_CONFIRMLANFILE);
    cCue.Format(csFileLan,csFirstLan,cFilePath);
    return (MessageBox(cCue,cClew,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON1) == IDYES);
}

void CVoicePromptDlg::OnButtonCountlanguagessize() 
{
	// TODO: Add your control notification handler code here
	int i, iSelCount = 0,iFileCount = 0;
    int iCount = m_ctlCheckList.GetCount();
    CString cSLanguage,csCountResult = "";
    DWORD dLanguagePackSize = 0;

#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
    iTimes = 0;
#endif
    for (i = 0;i < iCount;i++)
    {
        if (m_ctlCheckList.GetCheck(i) == 1)
        {
            iSelCount++;
            //////////////////////////////////////////////////////////////////////////
            //Count language packs files size
            int icount;
            DWORD dsize;
            m_ctlCheckList.GetText(i,cSLanguage);
            csCountResult += GetLanguagePackSize(cSLanguage,&icount,&dsize);
            iFileCount += icount;
            dLanguagePackSize += dsize;

#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
            iTimes++;
#endif
        }
    }

    if ((1 <= iSelCount) && (iSelCount <= 3))
    {
        CString csLanguageCountResult,cLanguageAccount;

        cLanguageAccount.LoadString(IDS_STRING_LANGUAGEACCOUNT);
        csLanguageCountResult.Format(cLanguageAccount,
            csCountResult,iSelCount,iFileCount,dLanguagePackSize,dLanguagePackSize / fKunit);

        CLanguagePackInfo cDialogLanguageInfo(NULL,csLanguageCountResult,"");
        cDialogLanguageInfo.DoModal();
        return;
    }

    CString cClew,csLanguage3,csLanguage1;
    csLanguage1.LoadString(IDS_STRING_LANGUAGE1);
    csLanguage3.LoadString(IDS_STRING_LANGUAGE3);
    cClew.LoadString(IDS_STRING_CLEW);
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
}

CString CVoicePromptDlg::GetLanguagePackSize(CString csLanguage,int * pFileCount,DWORD * pAllFilesize)
{
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead;
    CString     bufLanguage;
    ConfigType  eConfigtype = CONFIGTYPE_NONE;
    int         iFileCount = 0;
    DWORD       dAllFilesize = 0;
    CString     csFileinfo,cFilePath;

#ifdef CONFIGFILE_AUTOSELECTLANGUAGE
    int iFileIndex = 0;
#endif
    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;
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
                    if (iTimes > 0)
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

        CString csSingleLanAccount;
        csSingleLanAccount.LoadString(IDS_STRING_SINGLELANACCOUNT);
        csFileinfo.Format(csSingleLanAccount,csLanguage,iFileCount,dAllFilesize,dAllFilesize / fKunit);
        return csFileinfo;
    }
    else
    {
        return _T("Error");
    }
}

void CVoicePromptDlg::OnButtonClearall() 
{
	// TODO: Add your control notification handler code here
	int i,iCount;

    iCount = m_ctlCheckList.GetCount();
    for (i = 0;i < iCount;i++)
    {
        if (m_ctlCheckList.GetCheck(i) == 1)
            m_ctlCheckList.SetCheck(i,0);
    }
}

BOOL CVoicePromptDlg::JustTheFilesExist(void)
{
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead,cHeadFilename,csLanguageName;
    CString     cCurrentPath,cAmrfilename ;
    int iSpace,iLanPrefixLen = strlen(CONFIGFILE_LANGUAGE_FILE_BEGIN);
    typedef enum
    {
        OUTFILES_OUTFILE,
        OUTFILES_NONE
    }OUTPUTLANGUAGEFILES;
    OUTPUTLANGUAGEFILES eOutputType = OUTFILES_NONE;

    CWaitCursor wait;

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
                continue;
            }
            iSpace = bufRead.Find(CONFIGFILE_LANGUAGE_FILE_BEGIN);
            if (iSpace != -1)
            {
                eOutputType = OUTFILES_OUTFILE;
                csLanguageName = bufRead.Right(bufRead.GetLength() - iLanPrefixLen);
                continue;
            }
            if (eOutputType == OUTFILES_OUTFILE)
            {
                cAmrfilename = cCurrentPath + csSlash + bufRead;
                if (!FileIfExist(cAmrfilename))
                {
                    CString cClew,csfile,csContent;;
                    cClew.LoadString(IDS_STRING_CLEW);
                    csfile.LoadString(IDS_STRING_CANNOTFINDFILE);
                    csContent.Format(csfile,cAmrfilename);
                    MessageBox(csContent,cClew,MB_ICONINFORMATION|MB_OK);
                    file.Close();
                    return FALSE;
                }
            }
        }
        file.Close();
    }
    return TRUE;
}

void CVoicePromptDlg::OnButtonMovetop() 
{
	// TODO: Add your control notification handler code here
    VoiceDataManage vdm;
    vdm.ListBox_MoveItemTop(m_ctlCheckList);
    OnSelchangeListLanguage();
}

void CVoicePromptDlg::OnButtonMovebelow() 
{
	// TODO: Add your control notification handler code here
    VoiceDataManage vdm;
    vdm.ListBox_MoveItemBelow(m_ctlCheckList);
    OnSelchangeListLanguage();
}

void CVoicePromptDlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	ReadConfigFile();
    m_ctlCheckList.SetCurSel(0);
    OnSelchangeListLanguage();
    //////////////////////////////////////////////////////////////////////////
    /*CStdioFile	file;
    CString     cFileName;
    CString		bufRead,csResult = "";

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;

	if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
	{
		while (file.ReadString(bufRead))
		{
			while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
				bufRead = bufRead.Left(bufRead.GetLength() - 1);

            csResult = csResult + bufRead + CONFIG_NEWLINE;
		}
		file.Close();
        //////////////////////////////////////////////////////////////////////////
        VoiceDataManage vdm;
        vdm.FileIsSame(cFileName,csResult);
	}*/
}

BOOL CVoicePromptDlg::CheckFilesExist(void)
{
    CStdioFile	file,filePlace;
    CString     cFileName;
    CString		bufRead;
    CString     bufLanguage,csLanguageIndex;
    CString     cFilePath,cClew;
    ConfigType  eConfigtype = CONFIGTYPE_NONE;
    int iCheckIndex = 0,i,iListCount = m_ctlCheckList.GetCount();
    BOOL bInvalidFile = FALSE;
    BOOL bCreatePlaceFile = FALSE;//whether find the file,if the file can't be found,prompt user create a place file.
    VoiceDataManage vdm;
    CWaitCursor wait;

    cClew.LoadString(IDS_STRING_CLEW);
    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;

    for (i = 0 ;i < iListCount;i++)
    {
        iCheckIndex = 0;
        m_ctlCheckList.GetText(i,csLanguageIndex);
        bufLanguage = CONFIGFILE_LANGUAGE_FILE_BEGIN + csLanguageIndex;

        if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
        {
            while (file.ReadString(bufRead))
            {
                while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
                    bufRead = bufRead.Left(bufRead.GetLength() - 1);

                if ((bufRead == CONFIGFILE_ENUM_END) || (bufRead == CONFIGFILE_LANGUAGE_FILE_END) || (bufRead == ""))
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
                    if (!FileIfExist(cFilePath))
                    {
                        CString csFileFix,csFileFixAct,csDesFilename;
                        int iSpace;
                        iSpace = DefaultEnumFileinformation[iCheckIndex].Find(CONFIGFILE_UNDERLINE);
                        if (-1 == iSpace)
                        {
                            if (DefaultEnumFileinformation[iCheckIndex] == csSlash + CONFIGFILE_PLACEFILENAME)
                            {
                                if (filePlace.Open(cFilePath,CFile::modeCreate|CFile::modeWrite,NULL))
                                {
                                    unsigned char cFileContent[2] = "";
                                    cFileContent[0] = 0x00;
                                    filePlace.Write((void*)cFileContent,1);
                                    filePlace.Close();
                                }
                            }
                            iCheckIndex++;
                            continue;
                        }
                        csDesFilename = DefaultEnumFileinformation[iCheckIndex].Right(DefaultEnumFileinformation[iCheckIndex].GetLength() - 1);
                        csFileFix = csDesFilename.Left(iSpace - 1);
                        //////////////////////////////////////////////////////////////////////////
                        bCreatePlaceFile = TRUE;
                        //////////////////////////////////////////////////////////////////////////
                        CFileFind   find;
                        CString     csSearchPath,strFilePath,csSourFilename;
                        BOOL        bWorking;
                        csSearchPath = GetCurrentAppPath() + csSlash + csLanguageIndex + CONFIGFILE_SEARCHFILE;

                        bWorking = find.FindFile(csSearchPath);
                        while (bWorking)
                        {
                            bWorking    = find.FindNextFile();
                            strFilePath = find.GetFilePath();

                            if (find.IsDots())
                                continue;

                            if (!find.IsDirectory())
                            {
                                csSourFilename = find.GetFileName();//获得文件名(包括路径)
                                iSpace = csSourFilename.Find(CONFIGFILE_UNDERLINE);
                                if (iSpace == -1)
                                    break;
                                csFileFixAct = csSourFilename.Left(iSpace);
                                if (csFileFixAct == csFileFix)
                                {
                                    CString csFileClew,cschangefilename;

                                    cschangefilename.LoadString(IDS_STRING_CHANGEFILENAME);
                                    csFileClew.Format(cschangefilename,csSourFilename,csDesFilename,csLanguageIndex);

                                    if (MessageBox(csFileClew,cClew,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON1) == IDYES)
                                    {
                                        CString csSourFile,csDesFile;
                                        csSourFile = CurrentAppPath + csSlash + csLanguageIndex + csSlash + csSourFilename;
                                        csDesFile = CurrentAppPath + csSlash + csLanguageIndex + csSlash + csDesFilename;
                                        if (FileIfExist(csSourFile))
                                        {
                                            TRY
                                            {
                                                CFile::Rename(csSourFile,csDesFile);
                                                bInvalidFile = TRUE;
                                                bCreatePlaceFile = FALSE;
                                            }
                                            CATCH( CFileException , e )
                                            {
                                                TRACE(csSourFile + _T(" Output fail!"));
                                            }
                                            END_CATCH
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        find.Close();
                        //////////////////////////////////////////////////////////////////////////
                        if (bCreatePlaceFile)
                        {
                            CString cFileclew,csClew;
                            cFileclew.LoadString(IDS_STRING_CREATE_PLACEFILE);
                            csClew.Format(cFileclew,cFilePath,csLanguageIndex);
                            if (MessageBox(csClew,cClew,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON1) == IDYES)
                            {
                                VoiceDataManage vdm;
                                vdm.Voice_CreatePlaceFile(cFilePath);
                            }
                        }
                    }
                    iCheckIndex++;
                }
            }
            file.Close();
        }
    }
    return (!bInvalidFile);
}



void CVoicePromptDlg::OnButtonCheckfile() 
{
	// TODO: Add your control notification handler code here
    CString cClew,cCheckComplete;
	
    if (CheckFilesExist())
    {
        cClew.LoadString(IDS_STRING_CLEW);
        cCheckComplete.LoadString(IDS_STRING_CHECKCOMPLETE);
        MessageBox(cCheckComplete,cClew,MB_ICONINFORMATION|MB_OK);
    }
}

void CVoicePromptDlg::OnButtonCountalllanguages() 
{
	// TODO: Add your control notification handler code here
	int i,iListcount,iSingleLanFileCount = 0,iFileCount = 0;
    CString cSLanguage,csCountResult = "";
    DWORD dLanguagePackSize = 0,dsize;
    CWaitCursor wait;

    iListcount = m_ctlCheckList.GetCount();

    for (i = 0;i < iListcount;i++)
    {
        m_ctlCheckList.GetText(i,cSLanguage);
        csCountResult += GetLanguagePackSizeActual(cSLanguage,&iSingleLanFileCount,&dsize);
        dLanguagePackSize += dsize;
        iFileCount += iSingleLanFileCount;
    }
    CString csLanguageCountResult,cLanguageAccount;
    
    cLanguageAccount.LoadString(IDS_STRING_LANGUAGEACCOUNT);
    csLanguageCountResult.Format(cLanguageAccount,
        csCountResult,iListcount,iFileCount,dLanguagePackSize,dLanguagePackSize / fKunit);
    
    CLanguagePackInfo cDialogLanguageInfo(NULL,csLanguageCountResult,"");
    cDialogLanguageInfo.DoModal();
}

CString CVoicePromptDlg::GetLanguagePackSizeActual(CString csLanguage,int * pFileCount,DWORD * pAllFilesize)
{
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead;
    CString     bufLanguage;
    ConfigType  eConfigtype = CONFIGTYPE_NONE;
    int         iFileCount = 0,iFileIndex = 0;
    DWORD       dAllFilesize = 0;
    CString     csFileinfo,cFilePath;

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;
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
                        iFileIndex++;
                        continue;
                    }
                    iFileCount++;
                    iFileIndex++;
                    dAllFilesize += VoicePromptGetFileSize(cFilePath);;
                }
            }
        }
        file.Close();
        if (pFileCount != NULL)
            * pFileCount = iFileCount;

        if (pAllFilesize != NULL)
            * pAllFilesize = dAllFilesize;

        CString csSingleLanAccount;
        csSingleLanAccount.LoadString(IDS_STRING_SINGLELANACCOUNT);
        csFileinfo.Format(csSingleLanAccount,csLanguage,iFileCount,dAllFilesize,dAllFilesize / fKunit);
        return csFileinfo;
    }
    else
    {
        return _T("Error");
    }
}

void CVoicePromptDlg::OnButtonCountsilent() 
{
	// TODO: Add your control notification handler code here
	int i,iListcount;
    CString cSLanguage,csCountResult = "";
    CWaitCursor wait;

    iListcount = m_ctlCheckList.GetCount();

    for (i = 0;i < iListcount;i++)
    {
        m_ctlCheckList.GetText(i,cSLanguage);
        csCountResult = csCountResult + GetLanguagePackSizeSilent(cSLanguage) + CONFIG_NEWLINE1;
    }
    
    CLanguagePackInfo cDialogLanguageInfo(NULL,csCountResult,"");
    cDialogLanguageInfo.DoModal();
}

CString CVoicePromptDlg::GetLanguagePackSizeSilent(CString csLanguage)
{
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead;
    CString     bufLanguage;
    ConfigType  eConfigtype = CONFIGTYPE_NONE;
    CString     csFileinfo = "",cFilePath = "",csSlientResult = "";
    int         iCount = 0;

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;
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
                if (VoicePromptGetFileSize(cFilePath) == CONFIGFILE_SILENTFILESIZE)
                {
                    int iSpace;
                    iSpace = bufRead.Find(CONFIGFILE_CSTRINGSLASH);
                    if (iSpace != -1)
                    {
                        CString csActuralFile;
                        csActuralFile = bufRead.Right(bufRead.GetLength() - iSpace - 1);
                        csFileinfo = csFileinfo + csActuralFile + CONFIG_NEWLINE1;
                        iCount++;
                    }
                }
            }
        }
        file.Close();

        csSlientResult.Format("%s%d files.\r\n",csLanguage + CONFIG_NEWLINE1 + csFileinfo,iCount) ;
        return csSlientResult;//return (csLanguage + CONFIG_NEWLINE1 + csFileinfo);
    }
    else
    {
        return _T("Error");
    }
}

void CVoicePromptDlg::OnButtonBatchoutputfiles() 
{
	// TODO: Add your control notification handler code here
    if (!JustTheFilesExist())
    {
        return;
    }
    if (!CheckFilesExist())
    {
        return;
    }
    //////////////////////////////////////////////////////////////////////////
    //if the user must set the fold for batch output.
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead,csChooseFold = "",csRootFold = "";
    BATCH_SCAN_TYPE eScanType = BATCH_SCAN_NONE;

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAMEBATCH;
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
    csChooseFold.TrimLeft();
    csChooseFold.TrimRight();
    csRootFold.TrimLeft();
    csRootFold.TrimRight();
    if ((csChooseFold == "") || (csRootFold == ""))
    {
        CString cClew,cClew1;
        cClew.LoadString(IDS_STRING_CLEW);
        cClew1.LoadString(IDS_STRING_CLEW_SETFOLD);

        MessageBox(cClew1,cClew,MB_ICONINFORMATION|MB_OK);

        BatchOutputOption cBatchOption;
        cBatchOption.DoModal();
        return;
    }
    //////////////////////////////////////////////////////////////////////////
    BatchOutput cBatch;
    cBatch.DoModal();
}
bool CVoicePromptDlg::DownFile(LPCTSTR url,CString filename)
{
 bool result=false;
 try{

 //自定义http头信息
 char* headers="Accept:*/*\r\n"
  "Accept-Language:zh-cn\r\n"
  "User-Agent:VCTestClient\r\n";

 HINTERNET hNet = InternetOpen("Outlook",PRE_CONFIG_INTERNET_ACCESS,NULL,INTERNET_INVALID_PORT_NUMBER,0) ;

 HINTERNET hUrlFile = InternetOpenUrl(hNet,url,headers,strlen(headers),INTERNET_FLAG_RELOAD,0);

 char buffer[10*1024] ;
 DWORD dwBytesRead = 1;
 BOOL bRead=TRUE;
 CFile file;

 file.Open(filename,CFile::modeCreate|CFile::modeWrite);//创建本地文件,准备写入数据
 while(bRead&&dwBytesRead>0)
 {
  bRead = InternetReadFile(hUrlFile,buffer,sizeof(buffer),&dwBytesRead);
  if(dwBytesRead>0)
  file.Write(buffer,dwBytesRead);
 }
 InternetCloseHandle(hUrlFile) ;
 InternetCloseHandle(hNet) ;
 file.Close();
 result=true;
 }catch(CException *e)
 {
  result=false;
 }
 return result;
}
void CVoicePromptDlg::OnBnClickedButtonTest()
{
    // TODO: Add your control notification handler code here
    //CUnzip Unzip("D:\\Computer Files\\C&C++\\VoicePrompt\\test.zip");
    //Unzip.SwapSize("D:\\Computer Files\\C&C++\\VoicePrompt\\testresult");
    //CString Url = "http://compass.mot.com/cgi/doc/205000045/Arabic.zip";
	//DownFile(Url,"D:\\temp\\arabic.zip");
/*	{
		CString Url = "http://compass.mot.com//doc//205000045//Arabic.zip";
		HINTERNET hSession = InternetOpen(NULL,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
		HINTERNET hConnection = InternetOpenUrl(hSession,Url,NULL,0,0,0);
		if(hConnection == NULL)
			return ;//返回

		BYTE Buffer[51200] = "";
		DWORD Read = 0,i;

		HANDLE hFile = CreateFile("D:\\temp\\arabic.zip",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
		InternetReadFile(hConnection,Buffer,sizeof(Buffer),&Read);
		while(Read != 0)
		{
			WriteFile(hFile,Buffer,Read,&i,NULL);
			InternetReadFile(hConnection,Buffer,sizeof(Buffer),&Read);
		}
		CloseHandle(hFile);

		InternetCloseHandle(hConnection);
		InternetCloseHandle(hSession);
	}*/
}
