// NGLogViewAppDoc.h : interface of the CNGLogViewAppDoc class
//


#pragma once


class CNGLogViewAppDoc : public CDocument
{
protected: // create from serialization only
	CNGLogViewAppDoc();
	DECLARE_DYNCREATE(CNGLogViewAppDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CNGLogViewAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


