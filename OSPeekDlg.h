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
	UCHAR HdrLen:4;                   //4位首部长度
	UCHAR Version:4;                  //4位IP版本号
	UCHAR ServiceType;                //8位服务类型TOS 
	USHORT TotalLen;                  //16位总长度（字节） 
	USHORT ID;                        //16位标识 
	USHORT Flags_and_FragOff;         //3位标志位 
	UCHAR TimeToLive;                 //8位生存时间TTL 
	UCHAR Protocol;                   //8位协议 (TCP, UDP 或其他) 
	USHORT HdrChksum;                 //16位IP首部校验和 
	ULONG SrcAddr;                    //32位源IP地址 
	ULONG DstAddr;                    //32位目的IP地址 
	UCHAR Options;                    //IP选项
}IP; 

typedef struct _TCP{
	USHORT SrcPort;                   // 源端口 
	USHORT DstPort;                   // 目的端口 
	ULONG SeqNum;                     // 顺序号 
	ULONG AckNum;                     // 确认号 
	UCHAR DataOff;                    // TCP头长 
	UCHAR Flags;                      // 标志（URG、ACK等） 
	USHORT Window;                    // 窗口大小 
	USHORT Chksum;                    // 校验和 
	USHORT UrgPtr;                    // 紧急指针 
}TCP;

//指纹识别数据库
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
