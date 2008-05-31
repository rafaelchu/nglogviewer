// NGLogViewAppView.h : interface of the CNGLogViewAppView class
//

#pragma once

#include "..\NGLogViewer\CLogFileLoader.h"
#include "..\Utility\CRegSetting.h"
#include "NGLogViewAppDoc.h"

typedef struct tagITEMINFO {
	INT         nIndex;
	INT			nLineNumber;
	INT			nProcessID;
	FLOAT		fTime;
	time_t		tTime;
	CString		wstrTag;
	CString		wstrMessage;
} ITEMINFO;

typedef struct tagPROPINFO {
	wchar_t wszExcludeList[_MAX_PATH];
	wchar_t wszIncludeList[_MAX_PATH];
	bool    bEnableEmptyString;
} PROPINFO;

class CNGLogViewAppView : public CListView
{
protected: // create from serialization only
	CNGLogViewAppView();
	DECLARE_DYNCREATE(CNGLogViewAppView)

// Attributes
public:
	CNGLogViewAppDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	int Refresh();
	virtual ~CNGLogViewAppView();
	bool SetStatusBarString(const char *szInput);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CLogFileLoader* m_pLogFileLoader;
	CRegSetting* m_pRecSetting;
	CString m_strPath;
	CFont   m_ft;
	PROPINFO m_props;
	BOOL AddItem(int nIndex, CLineBuffer* pCLineBuffer);
	void SetProperties(PROPINFO* props);
	afx_msg void OnDestroy();
	afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFileOpen();
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileSaveAs();
	afx_msg void OnEditFont();
	afx_msg void OnProperties();
};

#ifndef _DEBUG  // debug version in NGLogViewAppView.cpp
inline CNGLogViewAppDoc* CNGLogViewAppView::GetDocument() const
   { return reinterpret_cast<CNGLogViewAppDoc*>(m_pDocument); }
#endif

