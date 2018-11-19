// EnumInfo.cpp : implementation file
//

#include "stdafx.h"
#include "VoicePrompt.h"
#include "EnumInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnumInfo dialog
static const CString csSlash = CONFIGFILE_CSTRINGSLASH;

CEnumInfo::CEnumInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CEnumInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnumInfo)
	//}}AFX_DATA_INIT
}

CEnumInfo::CEnumInfo(CWnd* pParent /*= NULL*/,
                     OPERATETYPE eOperatetype,CString csEnum,CString csFilename)
    : CDialog(CEnumInfo::IDD, pParent)
{
    OperateType = eOperatetype;
    Item_Enum = csEnum;
    Item_Filename = csFilename;

    Item_File = csFilename;
    CString cPath = GetCurrentAppPath();
    Item_File = Item_File.Right(csFilename.GetLength() - cPath.GetLength() - 1);
}

void CEnumInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnumInfo)
	DDX_Control(pDX, IDC_COMBO_FILENAME, m_Combo_Filename);
	DDX_Control(pDX, IDC_COMBO_ENUM, m_Combo_Enum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnumInfo, CDialog)
	//{{AFX_MSG_MAP(CEnumInfo)
	ON_BN_CLICKED(IDC_BUTTON_PATH, OnButtonPath)
	ON_CBN_DROPDOWN(IDC_COMBO_ENUM, OnDropdownComboEnum)
	ON_CBN_DROPDOWN(IDC_COMBO_FILENAME, OnDropdownComboFilename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnumInfo message handlers

BOOL CEnumInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    CString cTitle;
	// TODO: Add extra initialization here
	if (OperateType == OPERATETYPE_EDIT)
    {
        m_Combo_Enum.SetWindowText(Item_Enum);
        m_Combo_Filename.SetWindowText(Item_Filename);
        m_Combo_Enum.EnableWindow(FALSE);
        cTitle.LoadString(IDS_STRING_MENUMODIFY);
    }
    else
    {
        cTitle.LoadString(IDS_STRING_MENUADD);
    }
    SetWindowText(cTitle);

    CString cPlaceFilename;
    int ispace;
    ispace = Item_Filename.ReverseFind(_T('\\'));
#if 0
    
    cPlaceFilename = Item_Filename.Left(ispace) + csSlash + CONFIGFILE_PLACEFILENAME;
    m_Combo_Filename.AddString(cPlaceFilename);
#else
    VoiceDataManage vdm;
    cPlaceFilename = Item_Filename.Left(ispace);
    vdm.SetSubfoldFileToComboBox(m_Combo_Filename,cPlaceFilename);
#endif
    ReadEnumFileInformation();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEnumInfo::OnButtonPath() 
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

void CEnumInfo::OnDropdownComboEnum() 
{
	// TODO: Add your control notification handler code here
    VoiceDataManage vdm;
	vdm.SetComboWidth(m_Combo_Enum);
}

void CEnumInfo::OnDropdownComboFilename() 
{
	// TODO: Add your control notification handler code here
    VoiceDataManage vdm;
	vdm.SetComboWidth(m_Combo_Filename);
}

void CEnumInfo::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CEnumInfo::GetEnumFileName(CString & csEnum,CString & cFileName)//
{
    csEnum = Item_Enum;
    cFileName = Item_Filename;
}

void CEnumInfo::OnOK() 
{
	// TODO: Add extra validation here
	CString csEnum,csFilename,cClew;
    CStdioFile	file;

    m_Combo_Enum.GetWindowText(csEnum);
    m_Combo_Filename.GetWindowText(csFilename);

    cClew.LoadString(IDS_STRING_CLEW);
    if (csEnum == "")
    {
        CString cSour;
        cSour.LoadString(IDS_STRING_INPUTENUM);
        MessageBox(cSour,cClew,MB_ICONASTERISK |MB_OK);
        m_Combo_Enum.SetFocus();
        return;
    }
    if (csFilename == "")
    {
        CString cDes;
        cDes.LoadString(IDS_STRING_INPUTFILENAME);
        MessageBox(cDes,cClew,MB_ICONASTERISK |MB_OK);
        m_Combo_Filename.SetFocus();
        return;
    }
    
    if (!file.Open(csFilename,CFile::modeRead,NULL))
    {
        CString cOpenFail,cue;
        cOpenFail.LoadString(IDS_STRING_FINDSOURFILEFAIL);
        cue.Format(cOpenFail,csFilename);
        MessageBox(cue,cClew,MB_ICONASTERISK |MB_OK);
        m_Combo_Filename.SetFocus();
        return;
    }
    file.Close();

    //////////////////////////////////////////////////////////////////////////
    if (csEnum != Item_Enum)
    {
        int i,iListCount = m_Combo_Enum.GetCount();
        CString cListContent;
        for (i = 0;i < iListCount;i++)
        {
            m_Combo_Enum.GetLBText(i,cListContent);
            if ((csEnum == cListContent) && (cListContent != Item_Enum))
            {
                CString cEnumClew;
                cEnumClew.LoadString(IDS_STRING_ENUMEXIST);
                MessageBox(cEnumClew,cClew,MB_ICONASTERISK |MB_OK);
                m_Combo_Enum.SetFocus();
                return;
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////
    //Save file
    CString     cFileName;
    CString		bufRead,csFileContent = "";
    CString cPath = GetCurrentAppPath();
    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;
    CString cSaveString;
    cSaveString = csFilename.Right(csFilename.GetLength() - cPath.GetLength() - 1);

    if (OperateType == OPERATETYPE_EDIT)
    {
        if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
        {
            while (file.ReadString(bufRead))
            {
                while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
                    bufRead = bufRead.Left(bufRead.GetLength() - 1);
                
                if (bufRead == Item_File)
                {
                    csFileContent = csFileContent + cSaveString + CONFIG_NEWLINE;
                }
                else
                {
                    csFileContent = csFileContent + bufRead + CONFIG_NEWLINE;
                }
            }
            file.Close();
        }
        if (file.Open(cFileName,CFile::modeReadWrite,NULL))//打开成功
        {
            file.WriteString(csFileContent);
            file.Close();
        }
    }
    else
    {
        int iEnumCount = m_Combo_Enum.GetCount();
        CString csLastEnum,cLanguage = CONFIGFILE_LANGUAGE_FILE_BEGIN + GetVoicePromptLanguage();
        m_Combo_Enum.GetLBText(iEnumCount - 1,csLastEnum);

        if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
        {
            BOOL bLanguage = FALSE;
            while (file.ReadString(bufRead))
            {
                while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
                    bufRead = bufRead.Left(bufRead.GetLength() - 1);
                
                if (bufRead == csLastEnum)
                {
                    csFileContent = csFileContent + bufRead + CONFIG_NEWLINE + csEnum + CONFIG_NEWLINE;
                }
                else if (bufRead == cLanguage)
                {
                    bLanguage = TRUE;
                    csFileContent = csFileContent + bufRead + CONFIG_NEWLINE;
                }
                else if ((bufRead == CONFIGFILE_LANGUAGE_FILE_END) && (bLanguage))
                {
                    csFileContent = csFileContent + cSaveString + CONFIG_NEWLINE + 
                        CONFIGFILE_LANGUAGE_FILE_END + CONFIG_NEWLINE;
                    bLanguage = FALSE;
                }
                else
                {
                    csFileContent = csFileContent + bufRead + CONFIG_NEWLINE;
                }
            }
            file.Close();
        }
        if (file.Open(cFileName,CFile::modeReadWrite,NULL))//打开成功
        {
            file.WriteString(csFileContent);
            file.Close();
        }
    }
    //////////////////////////////////////////////////////////////////////////
    Item_Enum = csEnum;
    Item_Filename = csFilename;
	CDialog::OnOK();
}

void CEnumInfo::ReadEnumFileInformation(void)
{
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead;
    BOOL        bRead = FALSE;

    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;

	if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
	{
		while (file.ReadString(bufRead))
		{
			while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
				bufRead = bufRead.Left(bufRead.GetLength() - 1);

            if (bufRead == CONFIGFILE_ENUM_BEGIN)
            {
                bRead = TRUE;
                continue;
            }
            if ((bufRead == CONFIGFILE_ENUM_END) || (bufRead == ""))
            {
                bRead = FALSE;
                continue;
            }
            if (bRead)
                m_Combo_Enum.AddString(bufRead);
            else
                continue;
		}
		file.Close();
	}
}
