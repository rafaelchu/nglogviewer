// NGLogViewAppView.cpp : implementation of the CNGLogViewAppView class
//

#include "stdafx.h"
#include "NGLogViewApp.h"

#include "NGLogViewAppDoc.h"
#include "NGLogViewAppView.h"
#include "..\Utility\Debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNGLogViewAppView

IMPLEMENT_DYNCREATE(CNGLogViewAppView, CListView)

BEGIN_MESSAGE_MAP(CNGLogViewAppView, CListView)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS, &CNGLogViewAppView::OnFileSaveAs)
	ON_COMMAND(ID_EDIT_FONT, &CNGLogViewAppView::OnEditFont)
END_MESSAGE_MAP()

// CNGLogViewAppView construction/destruction

CNGLogViewAppView::CNGLogViewAppView()
{
	// TODO: add construction code here
	m_pLogFileLoader = NULL;
}

CNGLogViewAppView::~CNGLogViewAppView()
{
	if(m_pLogFileLoader)
	{
		delete m_pLogFileLoader;
		m_pLogFileLoader = NULL;
	}
}

BOOL CNGLogViewAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	OutputDebugString(L"PreCreateWindow()\n");
	if (!CListView::PreCreateWindow (cs))
		return FALSE;

	cs.style &= ~LVS_TYPEMASK;
	cs.style |= LVS_REPORT;
	return TRUE;

}

void CNGLogViewAppView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
	
	// Add column
	GetListCtrl().InsertColumn(0, _T("Index"), LVCFMT_CENTER, 55);
	GetListCtrl().InsertColumn(1, _T("Line"), LVCFMT_CENTER, 55);
	GetListCtrl().InsertColumn(2, _T ("PID"), LVCFMT_CENTER, 45);
	GetListCtrl().InsertColumn(3, _T("Time"), LVCFMT_CENTER, 75);
	GetListCtrl().InsertColumn(4, _T("Message"), LVCFMT_LEFT, 2048);

	// Add data
	//	Refresh();
	
}
void CNGLogViewAppView::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*) pNMHDR;

	if (pDispInfo->item.mask & LVIF_TEXT) {
		ITEMINFO* pItem = (ITEMINFO*)pDispInfo->item.lParam;

		switch (pDispInfo->item.iSubItem) {

		case 0: // nIndex
			{
				CString string;
				string.Format (_T ("%u"), pItem->nIndex);
				::lstrcpy (pDispInfo->item.pszText, string);			
			}
			break;
		case 1: // line number
			{
				CString string;
				string.Format (_T ("%u"), pItem->nLineNumber);
				::lstrcpy (pDispInfo->item.pszText, string);
			}
			break;
		case 2: // PID
			{
				CString string;
				string.Format (_T ("%u"), pItem->nProcessID);
				::lstrcpy (pDispInfo->item.pszText, string);			
			}
			break;
		case 3: // Time
			{
				CString string;
				string.Format(_T("%f"), pItem->fTime);
				::lstrcpy (pDispInfo->item.pszText, string);			
			}
			break;
		case 4: // message
			{
				::lstrcpyn(pDispInfo->item.pszText, pItem->wstrMessage, _MAX_PATH);
			}
			break;
		}
	}
	*pResult = 0;
}

BOOL CNGLogViewAppView::AddItem(int nIndex, CLineBuffer* pCLineBuffer)
{
	ITEMINFO* pItem;
	try {
		pItem = new ITEMINFO;
	}
	catch (CMemoryException* e) {
		e->Delete ();
		return FALSE;
	}

	pItem->nIndex = nIndex;
	pItem->nLineNumber = pCLineBuffer->m_nLineNumber;
	pItem->nProcessID = pCLineBuffer->m_nProcess;
	pItem->fTime = pCLineBuffer->m_Time;
	pItem->wstrTag = pCLineBuffer->m_wstrTag.c_str();
	pItem->wstrMessage = pCLineBuffer->m_wstrMessage.c_str();
	

	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_PARAM;
	lvi.iItem = nIndex;
	lvi.iSubItem = 0;
	lvi.iImage = 0;
	lvi.pszText = LPSTR_TEXTCALLBACK;
	lvi.lParam = (LPARAM)pItem;

	if(GetListCtrl().InsertItem(&lvi) == -1)
		return FALSE;

	return TRUE;
}
void CNGLogViewAppView::OnDestroy()
{
	if(m_pLogFileLoader)
	{
		delete m_pLogFileLoader;
		m_pLogFileLoader = NULL;
	}
	FreeItemMemory ();
	CListView::OnDestroy ();
}
void CNGLogViewAppView::OnFileOpen()
{
	CFileDialog dlg (TRUE, _T("txt, log"), _T("all.LOG"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Log Files(*.log)|*.log|Text Files(*.txt)|*.txt|All Files(*.*)|*.*||"));
	if(dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();
		if(str.GetLength() > 0)
		{
			TCHAR tszBuffer[LINE_BUFFER_SIZE];
			wsprintf(tszBuffer,TEXT("%s"),str);
			// Create file loader
			if(m_pLogFileLoader)
			{
				delete m_pLogFileLoader;
				m_pLogFileLoader = NULL;
			}
			// Set title
			CString strTitle = _T ("NGLogViewer - ");
			strTitle += str;
			AfxGetMainWnd ()->SetWindowText (strTitle);
			Refresh(tszBuffer);
		}
	}
}
// CNGLogViewAppView diagnostics

#ifdef _DEBUG
void CNGLogViewAppView::AssertValid() const
{
	CListView::AssertValid();
}

void CNGLogViewAppView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CNGLogViewAppDoc* CNGLogViewAppView::GetDocument() const // non-debug version is inline
{
	return (CNGLogViewAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CNGLogViewAppView message handlers
int CNGLogViewAppView::Refresh(LPCWSTR lpwzPath)
{
	m_pLogFileLoader = new CLogFileLoader(lpwzPath);
	m_pLogFileLoader->PreProcessing();
	
	//List All Tags
/*	vector<wstring>::iterator vecWstrIter;
	int i =0;
	vector<wstring> vecWstrTags= m_pLogFileLoader->GetVecWstrTags();
	for ( vecWstrIter = vecWstrTags.begin(); vecWstrIter != vecWstrTags.end(), i < 10; ++vecWstrIter )
	{
		i++;
		wchar_t *wstrA;
		wstrA =(wchar_t *) (vecWstrIter->c_str());
		dprintf(L"%d:%s\n", i, wstrA);
		
	}
	
	//List All Process
	vector<int> vecProcessNumber= m_pLogFileLoader->GetVecIntProcessNumber();
	vector<int>::iterator veciIter;
	i=0;
	for (veciIter = vecProcessNumber.begin(); veciIter != vecProcessNumber.end(); ++veciIter)
	{
		i++;
		dprintf(L"%d:[%d]\n", i, *veciIter);
	}
*/
	vector<wstring> vec2;
	vec2.push_back(L"[CLSchMgr]");
	vec2.push_back(L"[CLRec4]");
	vec2.push_back(L"EPG");
	vec2.push_back(L"(SQL)");
	m_pLogFileLoader->SetTagsFilter(&vec2);
	m_pLogFileLoader->SetEnableFilterEmptyMessage(true);

	m_pLogFileLoader->RunFilterResult();
	int nTotal = m_pLogFileLoader->GetResultSize();

	CLineBuffer pBuffer;
	for (int i=0;i<nTotal;++i)
	{
		ZeroMemory(&pBuffer, sizeof(CLineBuffer));
		m_pLogFileLoader->GetResultLine(i, &pBuffer);
		AddItem(i, &pBuffer);
	}
	return nTotal;
}
void CNGLogViewAppView::FreeItemMemory()
{
	int nCount = GetListCtrl ().GetItemCount ();
	if (nCount) {
		for (int i=0; i<nCount; i++)
			delete (ITEMINFO*) GetListCtrl ().GetItemData (i);
	}
}

void CNGLogViewAppView::OnFileSaveAs()
{
	CFileDialog dlg (FALSE, _T("txt, log"), _T("all.LOG"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Log Files(*.log)|*.log|Text Files(*.txt)|*.txt|All Files(*.*)|*.*||"));
	if(dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();
		if(str.GetLength() > 0)
		{
			TCHAR tszBuffer[LINE_BUFFER_SIZE];
			wsprintf(tszBuffer,TEXT("%s"),str);
			if (m_pLogFileLoader)
				m_pLogFileLoader->SaveResultAs(tszBuffer);
		}
	}

}

void CNGLogViewAppView::OnEditFont()
{
	LOGFONT   lf;  
	CFontDialog cfd;
	if (cfd.DoModal()==IDOK)
	{
		cfd.GetCurrentFont(&lf);   
		m_ft.CreateFontIndirect(&lf);   
		GetListCtrl().SetFont(&m_ft, TRUE);
	}
}
