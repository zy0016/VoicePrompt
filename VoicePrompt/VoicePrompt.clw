; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAddBatchInfor
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "voiceprompt.h"
LastPage=0

ClassCount=15
Class1=cOutputFiles
Class2=CEnumInfo
Class3=CFileDialogEx
Class4=CLanguagePackInfo
Class5=CMyProgressCtrl
Class6=CVoicePromptApp
Class7=CVoicePrompt_Option
Class8=CAboutDlg
Class9=CVoicePromptDlg
Class10=CVoicePromptList
Class11=CVoicePromptListCtrl

ResourceCount=18
Resource1=IDD_DIALOG_FILESIZECOUNT (English (U.S.))
Resource2=IDD_DIALOG_BATCHADD (English (U.S.))
Resource3=IDD_DIALOG_OPTION (English (U.S.))
Resource4=IDD_DIALOG_ENUMINFO (English (U.S.))
Resource5=IDD_VOICEPROMPT_DIALOG (English (U.S.))
Resource6=IDD_DIALOG_OUTFILES (English (U.S.))
Resource7=IDD_VOICEPROMPT_DIALOG
Resource8=IDD_DIALOG_BATCHOUTPUTFILES
Resource9=IDD_DIALOG_OPTION
Resource10=IDD_DIALOG_OUTFILES
Resource11=IDD_DIALOG_BATCHADD
Resource12=IDD_ABOUTBOX
Class12=BatchOutput
Class13=BatchListCtrl
Resource13=IDD_DIALOG_ENUMINFO
Class14=CAddBatchInfor
Resource14=IDD_DIALOG_FILESIZECOUNT
Class15=BatchOutputOption
Resource15=IDD_DIALOG_BATCH_OUTPUT_OPTION
Resource16=IDD_DIALOG_BATCHOUTPUTFILES (English (U.S.))
Resource17=IDD_ABOUTBOX (English (U.S.))
Resource18=IDD_DIALOG_BATCH_OUTPUT_OPTION (English (U.S.))

[CLS:cOutputFiles]
Type=0
BaseClass=CDialog
HeaderFile=cOutputFiles.h
ImplementationFile=cOutputFiles.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CEnumInfo]
Type=0
BaseClass=CDialog
HeaderFile=EnumInfo.h
ImplementationFile=EnumInfo.cpp
LastObject=IDCANCEL
Filter=D

[CLS:CFileDialogEx]
Type=0
BaseClass=CFileDialog
HeaderFile=FileDialogEx.h
ImplementationFile=FileDialogEx.cpp
Filter=D
LastObject=CFileDialogEx

[CLS:CLanguagePackInfo]
Type=0
BaseClass=CDialog
HeaderFile=LanguagePackInfo.h
ImplementationFile=LanguagePackInfo.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_LANGUAGEPACKINFORMATION

[CLS:CMyProgressCtrl]
Type=0
BaseClass=CProgressCtrl
HeaderFile=MyProgressCtrl.h
ImplementationFile=MyProgressCtrl.cpp
LastObject=CMyProgressCtrl
Filter=W

[CLS:CVoicePromptApp]
Type=0
BaseClass=CWinApp
HeaderFile=VoicePrompt.h
ImplementationFile=VoicePrompt.cpp
Filter=N
LastObject=CVoicePromptApp

[CLS:CVoicePrompt_Option]
Type=0
BaseClass=CDialog
HeaderFile=VoicePrompt_Option.h
ImplementationFile=VoicePrompt_Option.cpp
Filter=D
LastObject=IDOK

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=VoicePromptDlg.cpp
ImplementationFile=VoicePromptDlg.cpp
LastObject=CAboutDlg

[CLS:CVoicePromptDlg]
Type=0
BaseClass=CDialog
HeaderFile=VoicePromptDlg.h
ImplementationFile=VoicePromptDlg.cpp
LastObject=IDC_LIST_LANGUAGE
Filter=D
VirtualFilter=dWC

[CLS:CVoicePromptList]
Type=0
BaseClass=CListCtrl
HeaderFile=VoicePromptList.h
ImplementationFile=VoicePromptList.cpp
Filter=W
LastObject=CVoicePromptList

[CLS:CVoicePromptListCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=VoicePromptListCtrl.h
ImplementationFile=VoicePromptListCtrl.cpp
Filter=W
LastObject=CVoicePromptListCtrl
VirtualFilter=FWC

[DLG:IDD_DIALOG_OUTFILES]
Type=1
Class=cOutputFiles
ControlCount=9
Control1=IDC_COMBO_SELECTPATH,combobox,1344340034
Control2=IDC_BUTTON_SELECTPAHT,button,1342242816
Control3=IDC_RADIO_ALLFILES,button,1342177289
Control4=IDC_RADIO_NEEDFILES,button,1342177289
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_PROGRESS_OUTPUT,msctls_progress32,1350565889
Control9=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOG_ENUMINFO]
Type=1
Class=CEnumInfo
ControlCount=7
Control1=IDC_COMBO_ENUM,combobox,1344340034
Control2=IDC_COMBO_FILENAME,combobox,1344340034
Control3=IDC_BUTTON_PATH,button,1342242816
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_FILESIZECOUNT]
Type=1
Class=CLanguagePackInfo
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_LANGUAGEPACKINFORMATION,edit,1353779204
Control3=IDC_BUTTON_COPY,button,1342242816

[DLG:IDD_DIALOG_OPTION]
Type=1
Class=CVoicePrompt_Option
ControlCount=16
Control1=IDC_EDIT_DATA_FILENAME,edit,1350631552
Control2=IDC_EDIT_DATA_VARIABLE,edit,1350631552
Control3=IDC_EDIT_DATA_PREPARE_CONTENT,edit,1353777156
Control4=IDC_EDIT_POS_FILENAME,edit,1350631552
Control5=IDC_EDIT_POS_VARIABLE,edit,1350631552
Control6=IDC_EDIT_POS_PREPARE_CONTENT,edit,1353777156
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,button,1342177287

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_VOICEPROMPT_DIALOG]
Type=1
Class=CVoicePromptDlg
ControlCount=23
Control1=IDC_EDIT_LANGUAGE,edit,1350631552
Control2=IDC_LIST_LANGUAGE,listbox,1352728913
Control3=IDC_BUTTON_MOVETOP,button,1342242944
Control4=IDC_BUTTON_LANGUAGEUP,button,1342242944
Control5=IDC_BUTTON_LANGUAGEDOWN,button,1342242944
Control6=IDC_BUTTON_MOVEBELOW,button,1342242944
Control7=IDC_BUTTON_ADDLANGUAGE,button,1342242816
Control8=IDC_BUTTON_DELETELANGUAGE,button,1342242816
Control9=IDC_BUTTON_CLEARALL,button,1342242816
Control10=IDC_BUTTON_RESET,button,1342242816
Control11=IDC_LIST_ENUMINFO,SysListView32,1350631429
Control12=IDC_BUTTON_COUNTLANGUAGESSIZE,button,1342242816
Control13=IDC_BUTTON_OUTPUTFILES,button,1342242816
Control14=IDC_BUTTON_OPTION,button,1342242816
Control15=IDCANCEL,button,1342242817
Control16=IDC_STATIC_LANGUAGEINFO,static,1342308353
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC_ALLSIZE,static,1342308354
Control19=IDC_BUTTON_CHECKFILE,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_BUTTON_COUNTALLLANGUAGES,button,1342242816
Control22=IDC_BUTTON_COUNTSILENT,button,1342242816
Control23=IDC_BUTTON_BATCHOUTPUTFILES,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_VOICEPROMPT_DIALOG (English (U.S.))]
Type=1
Class=CVoicePromptDlg
ControlCount=23
Control1=IDC_EDIT_LANGUAGE,edit,1350631552
Control2=IDC_LIST_LANGUAGE,listbox,1352728913
Control3=IDC_BUTTON_MOVETOP,button,1342242944
Control4=IDC_BUTTON_LANGUAGEUP,button,1342242944
Control5=IDC_BUTTON_LANGUAGEDOWN,button,1342242944
Control6=IDC_BUTTON_MOVEBELOW,button,1342242944
Control7=IDC_BUTTON_ADDLANGUAGE,button,1342242816
Control8=IDC_BUTTON_DELETELANGUAGE,button,1342242816
Control9=IDC_BUTTON_CLEARALL,button,1342242816
Control10=IDC_BUTTON_RESET,button,1342242816
Control11=IDC_LIST_ENUMINFO,SysListView32,1350631429
Control12=IDC_BUTTON_COUNTLANGUAGESSIZE,button,1342242816
Control13=IDC_BUTTON_OUTPUTFILES,button,1342242816
Control14=IDC_BUTTON_OPTION,button,1342242816
Control15=IDCANCEL,button,1342242817
Control16=IDC_STATIC_LANGUAGEINFO,static,1342308353
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC_ALLSIZE,static,1342308354
Control19=IDC_BUTTON_CHECKFILE,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_BUTTON_COUNTALLLANGUAGES,button,1342242816
Control22=IDC_BUTTON_COUNTSILENT,button,1342242816
Control23=IDC_BUTTON_BATCHOUTPUTFILES,button,1342242816

[DLG:IDD_DIALOG_ENUMINFO (English (U.S.))]
Type=1
Class=CEnumInfo
ControlCount=7
Control1=IDC_COMBO_ENUM,combobox,1344340034
Control2=IDC_COMBO_FILENAME,combobox,1344340034
Control3=IDC_BUTTON_PATH,button,1342242816
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_OPTION (English (U.S.))]
Type=1
Class=CVoicePrompt_Option
ControlCount=16
Control1=IDC_EDIT_DATA_FILENAME,edit,1350631552
Control2=IDC_EDIT_DATA_VARIABLE,edit,1350631552
Control3=IDC_EDIT_DATA_PREPARE_CONTENT,edit,1353777156
Control4=IDC_EDIT_POS_FILENAME,edit,1350631552
Control5=IDC_EDIT_POS_VARIABLE,edit,1350631552
Control6=IDC_EDIT_POS_PREPARE_CONTENT,edit,1353777156
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOG_FILESIZECOUNT (English (U.S.))]
Type=1
Class=CLanguagePackInfo
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_LANGUAGEPACKINFORMATION,edit,1353779204
Control3=IDC_BUTTON_COPY,button,1342242816

[DLG:IDD_DIALOG_OUTFILES (English (U.S.))]
Type=1
Class=cOutputFiles
ControlCount=9
Control1=IDC_COMBO_SELECTPATH,combobox,1344340034
Control2=IDC_BUTTON_SELECTPAHT,button,1342242816
Control3=IDC_RADIO_ALLFILES,button,1342177289
Control4=IDC_RADIO_NEEDFILES,button,1342177289
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_PROGRESS_OUTPUT,msctls_progress32,1350565889
Control9=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOG_BATCHOUTPUTFILES]
Type=1
Class=BatchOutput
ControlCount=15
Control1=IDC_LIST_BATCHLANGUAGE,listbox,1352728913
Control2=IDC_BUTTON_BATCH_TOP,button,1342242944
Control3=IDC_BUTTON_BATCH_UP,button,1342242944
Control4=IDC_BUTTON_BATCHDOWN,button,1342242944
Control5=IDC_BUTTON_BATCHBELOW,button,1342242944
Control6=IDC_BUTTON_ADDBATCHITEM,button,1342242816
Control7=IDC_BUTTON_DELETE,button,1342242816
Control8=IDC_LIST_BATCHOUTPUT,SysListView32,1350631429
Control9=IDC_BUTTON_BATCHOUTPUT,button,1342242816
Control10=IDOK,button,1342242817
Control11=IDC_STATIC,static,1342308353
Control12=IDC_BUTTON_RESET,button,1342242816
Control13=IDC_BUTTON_OPTION,button,1342242816
Control14=IDC_PROGRESS_BATCHOUTPUTFILES,msctls_progress32,1350565889
Control15=IDC_STATIC_OUTPUTFILESCOUNT,static,1342308352

[CLS:BatchOutput]
Type=0
HeaderFile=BatchOutput.h
ImplementationFile=BatchOutput.cpp
BaseClass=CDialog
Filter=D
LastObject=BatchOutput
VirtualFilter=dWC

[CLS:BatchListCtrl]
Type=0
HeaderFile=BatchListCtrl.h
ImplementationFile=BatchListCtrl.cpp
BaseClass=CListCtrl
Filter=W
LastObject=BatchListCtrl
VirtualFilter=FWC

[DLG:IDD_DIALOG_BATCHADD]
Type=1
Class=CAddBatchInfor
ControlCount=9
Control1=IDC_COMBO_SELECTFILE,combobox,1344340034
Control2=IDC_BUTTON_BATCHSELFILE,button,1342242816
Control3=IDC_COMBO_SELECTPATH,combobox,1344340034
Control4=IDC_BUTTON_SELECTFOLD,button,1342242816
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC_LANGUAGES,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[CLS:CAddBatchInfor]
Type=0
HeaderFile=AddBatchInfor.h
ImplementationFile=AddBatchInfor.cpp
BaseClass=CDialog
Filter=D
LastObject=CAddBatchInfor
VirtualFilter=dWC

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

[DLG:IDD_DIALOG_BATCHADD (English (U.S.))]
Type=1
Class=?
ControlCount=9
Control1=IDC_COMBO_SELECTFILE,combobox,1344340034
Control2=IDC_BUTTON_BATCHSELFILE,button,1342242816
Control3=IDC_COMBO_SELECTPATH,combobox,1344340034
Control4=IDC_BUTTON_SELECTFOLD,button,1342242816
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC_LANGUAGES,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_BATCH_OUTPUT_OPTION (English (U.S.))]
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

[DLG:IDD_DIALOG_BATCHOUTPUTFILES (English (U.S.))]
Type=1
Class=BatchOutput
ControlCount=15
Control1=IDC_LIST_BATCHLANGUAGE,listbox,1352728913
Control2=IDC_BUTTON_BATCH_TOP,button,1342242944
Control3=IDC_BUTTON_BATCH_UP,button,1342242944
Control4=IDC_BUTTON_BATCHDOWN,button,1342242944
Control5=IDC_BUTTON_BATCHBELOW,button,1342242944
Control6=IDC_BUTTON_ADDBATCHITEM,button,1342242816
Control7=IDC_BUTTON_DELETE,button,1342242816
Control8=IDC_LIST_BATCHOUTPUT,SysListView32,1350631429
Control9=IDC_BUTTON_BATCHOUTPUT,button,1342242816
Control10=IDOK,button,1342242817
Control11=IDC_STATIC,static,1342308353
Control12=IDC_BUTTON_RESET,button,1342242816
Control13=IDC_BUTTON_OPTION,button,1342242816
Control14=IDC_PROGRESS_BATCHOUTPUTFILES,msctls_progress32,1350565889
Control15=IDC_STATIC_OUTPUTFILESCOUNT,static,1342308352

