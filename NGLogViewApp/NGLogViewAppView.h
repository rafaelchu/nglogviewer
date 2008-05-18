// NGLogViewAppView.h : interface of the CNGLogViewAppView class
//

#pragma once

#include "CLogFileLoader.h"
typedef struct tagITEMINFO {
	INT         nIndex;
	CString     strData;
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
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CLogFileLoader* m_pLogFileLoader;
	void FreeItemMemory();
	BOOL AddItem(int nIndex, wchar_t* wstrBuffer);
	afx_msg void OnDestroy();
	afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFileOpen();

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in NGLogViewAppView.cpp
inline CNGLogViewAppDoc* CNGLogViewAppView::GetDocument() const
   { return reinterpret_cast<CNGLogViewAppDoc*>(m_pDocument); }
#endif

