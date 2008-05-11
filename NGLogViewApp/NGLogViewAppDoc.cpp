// NGLogViewAppDoc.cpp : implementation of the CNGLogViewAppDoc class
//

#include "stdafx.h"
#include "NGLogViewApp.h"

#include "NGLogViewAppDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNGLogViewAppDoc

IMPLEMENT_DYNCREATE(CNGLogViewAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CNGLogViewAppDoc, CDocument)
END_MESSAGE_MAP()


// CNGLogViewAppDoc construction/destruction

CNGLogViewAppDoc::CNGLogViewAppDoc()
{
	// TODO: add one-time construction code here

}

CNGLogViewAppDoc::~CNGLogViewAppDoc()
{
}

BOOL CNGLogViewAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CNGLogViewAppDoc serialization

void CNGLogViewAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CNGLogViewAppDoc diagnostics

#ifdef _DEBUG
void CNGLogViewAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNGLogViewAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNGLogViewAppDoc commands
