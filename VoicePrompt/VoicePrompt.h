// VoicePrompt.h : main header file for the VOICEPROMPT application
//

#if !defined(AFX_VOICEPROMPT_H__1B98795F_DEF6_4A14_AC2E_B817BA405B17__INCLUDED_)
#define AFX_VOICEPROMPT_H__1B98795F_DEF6_4A14_AC2E_B817BA405B17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVoicePromptApp:
// See VoicePrompt.cpp for the implementation of this class
//

class CVoicePromptApp : public CWinApp
{
public:
	CVoicePromptApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoicePromptApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVoicePromptApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOICEPROMPT_H__1B98795F_DEF6_4A14_AC2E_B817BA405B17__INCLUDED_)
