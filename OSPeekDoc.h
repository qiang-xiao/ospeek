// OSPeekDoc.h : interface of the COSPeekDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OSPEEKDOC_H__C5C7669F_EB29_4F38_9073_6ABB9FDEC42A__INCLUDED_)
#define AFX_OSPEEKDOC_H__C5C7669F_EB29_4F38_9073_6ABB9FDEC42A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COSPeekDoc : public CDocument
{
protected: // create from serialization only
	COSPeekDoc();
	DECLARE_DYNCREATE(COSPeekDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COSPeekDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COSPeekDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COSPeekDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSPEEKDOC_H__C5C7669F_EB29_4F38_9073_6ABB9FDEC42A__INCLUDED_)
