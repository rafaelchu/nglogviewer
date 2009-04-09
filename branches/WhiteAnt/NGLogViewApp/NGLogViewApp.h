// NGLogViewApp.h : main header file for the NGLogViewApp application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CNGLogViewAppApp:
// See NGLogViewApp.cpp for the implementation of this class
//

class CNGLogViewAppApp : public CWinApp
{
public:
	CNGLogViewAppApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNGLogViewAppApp theApp;