// OSPeekDoc.cpp : implementation of the COSPeekDoc class
//

#include "stdafx.h"
#include "OSPeek.h"

#include "OSPeekDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COSPeekDoc

IMPLEMENT_DYNCREATE(COSPeekDoc, CDocument)

BEGIN_MESSAGE_MAP(COSPeekDoc, CDocument)
	//{{AFX_MSG_MAP(COSPeekDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COSPeekDoc construction/destruction

COSPeekDoc::COSPeekDoc()
{
	// TODO: add one-time construction code here

}

COSPeekDoc::~COSPeekDoc()
{
}

BOOL COSPeekDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COSPeekDoc serialization

void COSPeekDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// COSPeekDoc diagnostics

#ifdef _DEBUG
void COSPeekDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COSPeekDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COSPeekDoc commands
