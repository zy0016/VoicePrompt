 // VoicePrompt_Option.cpp : implementation file
//

#include "stdafx.h"
#include "voiceprompt.h"
#include "VoicePrompt_Option.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
static const CString csSlash = CONFIGFILE_CSTRINGSLASH;
static const CString cNewLine1 = "\r";
static const CString cNewLine2 = "\n";
/////////////////////////////////////////////////////////////////////////////
// CVoicePrompt_Option dialog


CVoicePrompt_Option::CVoicePrompt_Option(CWnd* pParent /*=NULL*/)
	: CDialog(CVoicePrompt_Option::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVoicePrompt_Option)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVoicePrompt_Option::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVoicePrompt_Option)
	DDX_Control(pDX, IDC_EDIT_POS_PREPARE_CONTENT, m_Edit_Pos_Content);
	DDX_Control(pDX, IDC_EDIT_DATA_PREPARE_CONTENT, m_Edit_Data_Content);
	DDX_Control(pDX, IDC_EDIT_POS_VARIABLE, m_Edit_Pos_Variable);
	DDX_Control(pDX, IDC_EDIT_POS_FILENAME, m_Edit_Pos_Filename);
	DDX_Control(pDX, IDC_EDIT_DATA_VARIABLE, m_Edit_Data_Variable);
	DDX_Control(pDX, IDC_EDIT_DATA_FILENAME, m_Edit_Data_Filename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVoicePrompt_Option, CDialog)
	//{{AFX_MSG_MAP(CVoicePrompt_Option)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoicePrompt_Option message handlers

BOOL CVoicePrompt_Option::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CStdioFile	file;
    CString     cFileName;
    CString		bufRead,csDataContent = "",csPosContent = "";
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
                m_Edit_Pos_Content.SetWindowText(csPosContent);
                eVoiceType = VOICETYPE_NONE;
                csPos_Content = csPosContent;
                continue;
            }
            else if (bufRead == CONFIGFILE_VOICEPROMPT_DATA_PREPARE_CONTENT_END)
            {
                m_Edit_Data_Content.SetWindowText(csDataContent);
                eVoiceType = VOICETYPE_NONE;
                csData_Content = csDataContent;
                continue;
            }
            else
            {
                switch (eVoiceType)
                {
                case VOICETYPE_DATAFILENAME:
                    eVoiceType = VOICETYPE_NONE;
                    m_Edit_Data_Filename.SetWindowText(bufRead);
                    csData_Filename = bufRead;
                    break;
                case VOICETYPE_DATAVARIABLE:
                    eVoiceType = VOICETYPE_NONE;
                    m_Edit_Data_Variable.SetWindowText(bufRead);
                    csData_Variable = bufRead;
                    break;
                case VOICETYPE_DATACONTENT:
                    if (CONFIG_NEWLINE == cNewLine2)
                        csDataContent = csDataContent + bufRead + cNewLine1 + CONFIG_NEWLINE;
                    else if (CONFIG_NEWLINE == cNewLine1)
                        csDataContent = csDataContent + bufRead + CONFIG_NEWLINE + cNewLine2;
                    else
                        csDataContent = csDataContent + bufRead + CONFIG_NEWLINE;

                    continue;

                case VOICETYPE_POSFILENAME:
                    eVoiceType = VOICETYPE_NONE;
                    m_Edit_Pos_Filename.SetWindowText(bufRead);
                    csPos_Filename = bufRead;
                    break;
                case VOICETYPE_POSVARIABLE:
                    eVoiceType = VOICETYPE_NONE;
                    m_Edit_Pos_Variable.SetWindowText(bufRead);
                    csPos_Variable = bufRead;
                    break;
                case VOICETYPE_POSCONTENT:
                    if (CONFIG_NEWLINE == cNewLine2)
                        csPosContent = csPosContent + bufRead + cNewLine1 + CONFIG_NEWLINE;
                    else if (CONFIG_NEWLINE == cNewLine1)
                        csPosContent = csPosContent + bufRead + CONFIG_NEWLINE + cNewLine2;
                    else
                        csPosContent = csPosContent + bufRead + CONFIG_NEWLINE;

                    continue;
                }
                eVoiceType = VOICETYPE_NONE;
                continue;
            }
		}
		file.Close();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVoicePrompt_Option::OnOK() 
{
	// TODO: Add extra validation here
	CString csDataFilename,csDataVariable,csDataContent,csPosFilename,csPosVariable,csPosContent;
    m_Edit_Data_Filename.GetWindowText(csDataFilename);
    m_Edit_Data_Variable.GetWindowText(csDataVariable);
    m_Edit_Data_Content.GetWindowText(csDataContent);
    
    m_Edit_Pos_Filename.GetWindowText(csPosFilename);
    m_Edit_Pos_Variable.GetWindowText(csPosVariable);
    m_Edit_Pos_Content.GetWindowText(csPosContent);

    if ((csDataFilename == "") || (csDataVariable == "") || (csDataContent == "") || 
        (csPosFilename == "") || (csPosVariable == "") || (csPosContent == ""))
    {
        CString cClew,cOptionString;
        cOptionString.LoadString(IDS_STRING_OPTIONCLEW);
        cClew.LoadString(IDS_STRING_CLEW);
        MessageBox(cOptionString,cClew,MB_ICONINFORMATION|MB_OK);
        return;
    }
    if ((csDataFilename == csData_Filename) && (csDataVariable == csData_Variable) && (csDataContent == csData_Content) &&
        (csPosFilename == csPos_Filename) && (csPosVariable == csPos_Variable) && (csPosContent == csPos_Content))
    {
        CDialog::OnOK();
        return;
    }
    //////////////////////////////////////////////////////////////////////////
    //save file
    CStdioFile	file;
    CString     cFileName;
    CString		bufRead,csFileContent = "";
    BOOL        bFind = FALSE;
    cFileName = GetCurrentAppPath() + csSlash + CONFIGFILENAME;

    if (file.Open(cFileName,CFile::modeRead,NULL))//打开成功
    {
        while (file.ReadString(bufRead))
        {
            while(bufRead.Right(1) == CONFIG_LASTNEWLINE)//删除最后的回车符
                bufRead = bufRead.Left(bufRead.GetLength() - 1);

            if (bufRead == CONFIGFILE_VOICEPROMPT_DATA_FILENAME)
            {
                csFileContent = csFileContent + CONFIGFILE_VOICEPROMPT_DATA_FILENAME + CONFIG_NEWLINE + 
                    csDataFilename + CONFIG_NEWLINE + CONFIG_NEWLINE;
                csFileContent = csFileContent + CONFIGFILE_VOICEPROMPT_DATA_VARIABLE_NAME + CONFIG_NEWLINE + 
                    csDataVariable + CONFIG_NEWLINE + CONFIG_NEWLINE;
                csFileContent = csFileContent + CONFIGFILE_VOICEPROMPT_DATA_PREPARE_CONTENT_BEGIN + CONFIG_NEWLINE + 
                    csDataContent + CONFIG_NEWLINE + CONFIGFILE_VOICEPROMPT_DATA_PREPARE_CONTENT_END + CONFIG_NEWLINE + CONFIG_NEWLINE;

                csFileContent = csFileContent + CONFIGFILE_VOICEPROMPT_POS_FILENAME + CONFIG_NEWLINE + 
                    csPosFilename + CONFIG_NEWLINE + CONFIG_NEWLINE;
                csFileContent = csFileContent + CONFIGFILE_VOICEPROMPT_POS_VARIABLE_NAME + CONFIG_NEWLINE + 
                    csPosVariable + CONFIG_NEWLINE + CONFIG_NEWLINE;
                csFileContent = csFileContent + CONFIGFILE_VOICEPROMPT_POS_PREPARE_CONTENT_BEGIN + CONFIG_NEWLINE + 
                    csPosContent + CONFIG_NEWLINE + CONFIGFILE_VOICEPROMPT_POS_PREPARE_CONTENT_END + CONFIG_NEWLINE;

                bFind = TRUE;
            }
            if (bufRead == CONFIGFILE_VOICEPROMPT_POS_PREPARE_CONTENT_END)
            {
                bFind = FALSE;
                continue;
            }
            else
            {
                if (!bFind)
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
	CDialog::OnOK();
}
