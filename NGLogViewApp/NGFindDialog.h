#pragma once


// CNGFindDialog

class CNGFindDialog : public CFindReplaceDialog
{
	DECLARE_DYNAMIC(CNGFindDialog)

public:
	enum { IDD = IDD_NGFINDDIALOG };
	CNGFindDialog();
	virtual ~CNGFindDialog();
	void OnBookmarkAll();

protected:
	DECLARE_MESSAGE_MAP()
};


