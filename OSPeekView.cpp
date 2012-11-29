// OSPeekView.cpp : implementation of the COSPeekView class
//

#include "stdafx.h"
#include "OSPeek.h"

#include "OSPeekDoc.h"
#include "OSPeekView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COSPeekView

IMPLEMENT_DYNCREATE(COSPeekView, CView)

BEGIN_MESSAGE_MAP(COSPeekView, CView)
	//{{AFX_MSG_MAP(COSPeekView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COSPeekView construction/destruction

COSPeekView::COSPeekView()
{
	// TODO: add construction code here

}

COSPeekView::~COSPeekView()
{
}

BOOL COSPeekView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COSPeekView drawing

void COSPeekView::OnDraw(CDC* pDC)
{
	COSPeekDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COSPeekView printing

BOOL COSPeekView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COSPeekView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COSPeekView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COSPeekView diagnostics

#ifdef _DEBUG
void COSPeekView::AssertValid() const
{
	CView::AssertValid();
}

void COSPeekView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COSPeekDoc* COSPeekView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COSPeekDoc)));
	return (COSPeekDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COSPeekView message handlers
