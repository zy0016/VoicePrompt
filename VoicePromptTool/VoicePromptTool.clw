; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=BatchListCtrl
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "voiceprompttool.h"
LastPage=0

ClassCount=5
Class1=BatchListCtrl
Class2=CVoicePromptToolApp
Class3=CAboutDlg
Class4=CVoicePromptToolDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDD_VOICEPROMPTTOOL_DIALOG (English (U.S.))
Class5=BatchOutputOption
Resource3=IDD_DIALOG_BATCH_OUTPUT_OPTION

[CLS:BatchListCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=BatchListCtrl.h
ImplementationFile=BatchListCtrl.cpp
LastObject=BatchListCtrl

[CLS:CVoicePromptToolApp]
Type=0
BaseClass=CWinApp
HeaderFile=VoicePromptTool.h
ImplementationFile=VoicePromptTool.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=VoicePromptToolDlg.cpp
ImplementationFile=VoicePromptToolDlg.cpp

[CLS:CVoicePromptToolDlg]
Type=0
BaseClass=CDialog
HeaderFile=VoicePromptToolDlg.h
ImplementationFile=VoicePromptToolDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CVoicePromptToolDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_VOICEPROMPTTOOL_DIALOG]
Type=1
Class=CVoicePromptToolDlg

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_VOICEPROMPTTOOL_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_SEARCHLANGUAGE,edit,1350631552
Control4=IDC_LIST_LANGUAGE,listbox,1352728913
Control5=IDC_BUTTON_MOVETOP,button,1342242944
Control6=IDC_BUTTON_LANGUAGEUP,button,1342242944
Control7=IDC_BUTTON_LANGUAGEDOWN,button,1342242944
Control8=IDC_BUTTON_MOVEBELOW,button,1342242944
Control9=IDC_BUTTON_ADDBATCHITEM,button,1342242816
Control10=IDC_BUTTON_DELETE,button,1342242816
Control11=IDC_BUTTON_RESET,button,1342242816
Control12=IDC_BUTTON_LANGUAGEMANAGE,button,1342242816
Control13=IDC_LIST_BATCHOUTPUT,SysListView32,1350631425
Control14=IDC_STATIC_OUTPUTFILESCOUNT,static,1342308352
Control15=IDC_BUTTON_OPTION,button,1342242816
Control16=IDC_BUTTON_BATCHOUTPUT,button,1342242816
Control17=IDC_STATIC_LANGUAGEINFO,static,1342308352

[DLG:IDD_DIALOG_BATCH_OUTPUT_OPTION]
Type=1
Class=BatchOutputOption
ControlCount=8
Control1=IDC_EDIT_CHOOSELANGUAGE_FOLD,edit,1350631552
Control2=IDC_BUTTON_CHOOSEFOLD,button,1342242816
Control3=IDC_EDIT_BATCH_OUTPUTROOT_FOLD,edit,1350631552
Control4=IDC_BUTTON_LANGUAGEROOT_FOLD,button,1342242816
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:BatchOutputOption]
Type=0
HeaderFile=BatchOutputOption.h
ImplementationFile=BatchOutputOption.cpp
BaseClass=CDialog
Filter=D
LastObject=BatchOutputOption
VirtualFilter=dWC

