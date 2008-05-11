// NGLogViewAppView.cpp : implementation of the CNGLogViewAppView class
//

#include "stdafx.h"
#include "NGLogViewApp.h"

#include "NGLogViewAppDoc.h"
#include "NGLogViewAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNGLogViewAppView

IMPLEMENT_DYNCREATE(CNGLogViewAppView, CListView)

BEGIN_MESSAGE_MAP(CNGLogViewAppView, CListView)
END_MESSAGE_MAP()

// CNGLogViewAppView construction/destruction

CNGLogViewAppView::CNGLogViewAppView()
{
	// TODO: add construction code here

}

CNGLogViewAppView::~CNGLogViewAppView()
{
}

BOOL CNGLogViewAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CNGLogViewAppView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
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
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNGLogViewAppDoc)));
	return (CNGLogViewAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CNGLogViewAppView message handlers
