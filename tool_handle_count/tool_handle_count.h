
// tool_handle_count.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Ctool_handle_countApp:
// See tool_handle_count.cpp for the implementation of this class
//

class Ctool_handle_countApp : public CWinApp
{
public:
	Ctool_handle_countApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Ctool_handle_countApp theApp;