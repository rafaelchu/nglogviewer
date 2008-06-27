// CNGListViewEx.h : interface of the CNGListViewEx class
#include <set>
using namespace std;

#define NG_COLOR_BOOKMARK_TEXT		0x000000FF
#define NG_COLOR_BOOKMARK_BK		0x0000FFFF

class CNGListViewEx : public CListView
{
	DECLARE_DYNCREATE(CNGListViewEx)

// Construction
public:
	CNGListViewEx();

// Attributes
protected:
	BOOL m_bFullRowSel;
	int  m_nSelectItem;

public:
	BOOL SetFullRowSel(BOOL bFillRowSel);
	BOOL GetFullRowSel();
	int  GetSelectItem(){return m_nSelectItem;};
	BOOL m_bClientWidthSel;
	bool SetBookmark(int nIndex);
	
// Overrides
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNGListViewEx)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNGListViewEx();
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	static LPCTSTR MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset);
	void RepaintSelectedItems();

// Implementation - client area width
	int m_cxClient;

// Implementation - list view colors
	COLORREF m_clrText;
	COLORREF m_clrTextBk;
	COLORREF m_clrBkgnd;
	afx_msg LRESULT OnSetTextColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetTextBkColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetBkColor(WPARAM wParam, LPARAM lParam);

// Generated message map functions
protected:
	//{{AFX_MSG(CListViewEx)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	set<int> m_setBookmarkIndex;
};

/////////////////////////////////////////////////////////////////////////////
