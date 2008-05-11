// NGLogViewAppView.h : interface of the CNGLogViewAppView class
//


#pragma once


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
	virtual ~CNGLogViewAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in NGLogViewAppView.cpp
inline CNGLogViewAppDoc* CNGLogViewAppView::GetDocument() const
   { return reinterpret_cast<CNGLogViewAppDoc*>(m_pDocument); }
#endif

