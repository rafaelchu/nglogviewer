// NGFindDialog.cpp : implementation file
//

#include "stdafx.h"
#include "NGLogViewApp.h"
#include "NGLogViewAppView.h"
#include "MainFrm.h"
#include "NGFindDialog.h"

static UINT WM_FINDREPLACE = ::RegisterWindowMessage( FINDMSGSTRING );

// CNGFindDialog

IMPLEMENT_DYNAMIC(CNGFindDialog, CFindReplaceDialog)

CNGFindDialog::CNGFindDialog()
{

}

CNGFindDialog::~CNGFindDialog()
{
}


BEGIN_MESSAGE_MAP(CNGFindDialog, CFindReplaceDialog)
	ON_BN_CLICKED(IDC_BOOKMARK_ALL, OnBookmarkAll)
END_MESSAGE_MAP()

// CNGFindDialog message handlers
void CNGFindDialog::OnBookmarkAll()
{

	CString strFind = _T("");
	GetDlgItemTextW(1152, strFind);
	dprintf(L"OnBookmarkAll, find text=%s", strFind);

	DWORD dwFlags = 0;
	//Match whole word
	CButton* pCheckBox = (CButton*)GetDlgItem(1040);
	if (pCheckBox->GetCheck() == BST_CHECKED)
		dwFlags |= FR_WHOLEWORD;

	//Match case
	pCheckBox = (CButton*)GetDlgItem(1041);
	if (pCheckBox->GetCheck() == BST_CHECKED)
		dwFlags |= FR_MATCHCASE;

	FINDREPLACE fr;
	ZeroMemory(&fr, sizeof(FINDREPLACE));
	fr.lpstrFindWhat = strFind.GetBuffer();
	fr.Flags = dwFlags;	
	
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CNGLogViewAppView* pListView = (CNGLogViewAppView*)pFrame->GetActiveView();
	pListView->SendMessage(WM_FINDREPLACE, WM_USER_SET_BOOKMARK_ALL, (LPARAM)&fr);
	
	return;
} 
