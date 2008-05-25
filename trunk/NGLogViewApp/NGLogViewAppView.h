// NGLogViewAppView.h : interface of the CNGLogViewAppView class
//

#pragma once

#include "..\NGLogViewer\CLogFileLoader.h"

typedef struct tagITEMINFO {
	INT         nIndex;
	INT			nLineNumber;
	INT			nProcessID;
	FLOAT		fTime;
	CString		wstrTag;
	CString		wstrMessage;
} ITEMINFO;

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
	//int Refresh(LPCWSTR lpwzPath);
	int Refresh(LPCWSTR lpwzPath);
	virtual ~CNGLogViewAppView();
	bool SetStatusBarString(const char *szInput);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CLogFileLoader* m_pLogFileLoader;
	CFont   m_ft;
	void FreeItemMemory();
	BOOL AddItem(int nIndex, CLineBuffer* pCLineBuffer);
	afx_msg void OnDestroy();
	afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFileOpen();

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

