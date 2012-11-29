// OSPeekDlg.h : header file
//

#if !defined(AFX_OSPEEKDLG_H__34F4B4BC_AC00_4205_83DB_86EEAF609704__INCLUDED_)
#define AFX_OSPEEKDLG_H__34F4B4BC_AC00_4205_83DB_86EEAF609704__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BUFFER_SIZE	65535
#define SIO_RCVALL	_WSAIOW(IOC_VENDOR,1)
const int MAXN = 1024;

typedef struct _OSINFO
{
	CString  dt_ip;
	CString  dt_os;
   CString  dt_finger;
}OSINFO;

typedef struct _IP{ 
	UCHAR HdrLen:4;                   //4λ�ײ�����
	UCHAR Version:4;                  //4λIP�汾��
	UCHAR ServiceType;                //8λ��������TOS 
	USHORT TotalLen;                  //16λ�ܳ��ȣ��ֽڣ� 
	USHORT ID;                        //16λ��ʶ 
	USHORT Flags_and_FragOff;         //3λ��־λ 
	UCHAR TimeToLive;                 //8λ����ʱ��TTL 
	UCHAR Protocol;                   //8λЭ�� (TCP, UDP ������) 
	USHORT HdrChksum;                 //16λIP�ײ�У��� 
	ULONG SrcAddr;                    //32λԴIP��ַ 
	ULONG DstAddr;                    //32λĿ��IP��ַ 
	UCHAR Options;                    //IPѡ��
}IP; 

typedef struct _TCP{
	USHORT SrcPort;                   // Դ�˿� 
	USHORT DstPort;                   // Ŀ�Ķ˿� 
	ULONG SeqNum;                     // ˳��� 
	ULONG AckNum;                     // ȷ�Ϻ� 
	UCHAR DataOff;                    // TCPͷ�� 
	UCHAR Flags;                      // ��־��URG��ACK�ȣ� 
	USHORT Window;                    // ���ڴ�С 
	USHORT Chksum;                    // У��� 
	USHORT UrgPtr;                    // ����ָ�� 
}TCP;

//ָ��ʶ�����ݿ�
enum {
			FINGER_LEN        = 28,
			OS_LEN            = 60,
			FINGER_WINDOW     = 0,
			FINGER_MSS        = 5,
			FINGER_TTL        = 10,
			FINGER_WS         = 13,
			FINGER_SACK       = 16,
			FINGER_NOP        = 18,
			FINGER_DF         = 20,
			FINGER_TIMESTAMP  = 22,
			FINGER_TCPFLAG    = 24,
			FINGER_LT         = 26,
}; 

/* tcp options */
#define TCPOPT_EOL              0
#define TCPOPT_NOP              1
#define TCPOPT_MAXSEG           2
#define TCPOPT_WSCALE           3
#define TCPOPT_SACKOK           4
#define TCPOPT_TIMESTAMP        8

//tcp flags
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PSH  0x08
#define TH_ACK  0x10
#define TH_URG  0x20

/////////////////////////////////////////////////////////////////////////////
// COSPeekDlg dialog

class COSPeekDlg : public CDialog
{
// Construction
public:
	void AddOsinfo(CString, CString, CString);
	bool m_bShutDown;
	int iTot;
	int iPos;
	HANDLE m_hThread;
	COSPeekDlg(CWnd* pParent = NULL);	// standard constructor
	void AddData(CString ,CString);
	void Fingerprint_push(char*, int, int);
	UCHAR TTL_PREDICTOR(UCHAR);

// Dialog Data
	//{{AFX_DATA(COSPeekDlg)
	enum { IDD = IDD_OSPEEK_DIALOG };
	CListCtrl	m_ctrList;
	CListBox	m_lstBox;
	CButton	m_btnStop;
	CButton	m_btnStart;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COSPeekDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COSPeekDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSPEEKDLG_H__34F4B4BC_AC00_4205_83DB_86EEAF609704__INCLUDED_)
