// OSPeekDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OSPeek.h"
#include "OSPeekDlg.h"
#include "winsock2.h"
#include "ws2tcpip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

OSINFO osinfo[MAXN];

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COSPeekDlg dialog

COSPeekDlg::COSPeekDlg(CWnd* pParent /*=NULL*/)
: CDialog(COSPeekDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COSPeekDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hThread = NULL;
	iTot = -1;
	iPos = 0;
}

void COSPeekDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COSPeekDlg)
	DDX_Control(pDX, IDC_LIST1, m_ctrList);
	DDX_Control(pDX, IDC_LIST2, m_lstBox);
	DDX_Control(pDX, IDB_STOP, m_btnStop);
	DDX_Control(pDX, IDB_START, m_btnStart);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COSPeekDlg, CDialog)
//{{AFX_MSG_MAP(COSPeekDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDB_START, OnStart)
	ON_BN_CLICKED(IDB_STOP, OnStop)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COSPeekDlg message handlers

BOOL COSPeekDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	m_ctrList.InsertColumn(0, "Operating  System  Type", LVCFMT_LEFT, 250, -1);
	m_ctrList.InsertColumn(0, "Address", LVCFMT_LEFT, 150, -1);
	//m_ctrList.SetBkColor(RGB(0, 255, 255));
	//m_ctrList.SetTextBkColor(RGB(255, 0, 255));
	DWORD NewStyle = m_ctrList.GetExtendedStyle();
	NewStyle |= LVS_EX_GRIDLINES;
	m_ctrList.SetExtendedStyle(NewStyle);
	
   //SetWindowPos(&CWnd::wndBottom, 0, 0, 0, 0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_btnStop.EnableWindow(FALSE);

	CFont * f; 
	f = new CFont; 
	f -> CreateFont(13,						// nHeight 
						0,							// nWidth 
						0,							// nEscapement 
						0,							// nOrientation 
						FW_NORMAL,				// nWeight 
						FALSE,					// bItalic 
						FALSE,					// bUnderline 
						0,							// cStrikeOut 
						ANSI_CHARSET,			// nCharSet 
						OUT_DEFAULT_PRECIS,	// nOutPrecision 
						CLIP_DEFAULT_PRECIS, // nClipPrecision 
						DEFAULT_QUALITY,		// nQuality 
						DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
						_T("宋体"));			// lpszFac 
	m_lstBox.AddString("");
	m_lstBox.AddString("");
	m_lstBox.AddString("");
	m_lstBox.AddString("                              Operating System Type Peeker          ");
	m_lstBox.AddString("");
	m_lstBox.AddString("                        using passive OS fingerprinting technology  ");

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COSPeekDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void COSPeekDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COSPeekDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//填充finger数组
void COSPeekDlg::Fingerprint_push(char *finger, int param, int value)
{
   char tmp[10];
   switch (param)
	{
	case FINGER_WINDOW:
		_snprintf(tmp, sizeof(tmp), "%04X", value);
		strncpy(finger + FINGER_WINDOW, tmp, 4);
		break;
	case FINGER_MSS:
		_snprintf(tmp, sizeof(tmp), "%04X", value);
		strncpy(finger + FINGER_MSS, tmp, 4);
		break;
	case FINGER_TTL:
		_snprintf(tmp, sizeof(tmp), "%02X", TTL_PREDICTOR(value));
		strncpy(finger + FINGER_TTL, tmp, 2);
		break;
	case FINGER_WS:
		_snprintf(tmp, sizeof(tmp), "%02X", value);
		strncpy(finger + FINGER_WS, tmp, 2);
		break;
	case FINGER_SACK:
		_snprintf(tmp, sizeof(tmp), "%d", value);
		strncpy(finger + FINGER_SACK, tmp, 1);
		break;
	case FINGER_NOP:
		_snprintf(tmp, sizeof(tmp), "%d", value);
		strncpy(finger + FINGER_NOP, tmp, 1);
		break;
	case FINGER_DF:
		_snprintf(tmp, sizeof(tmp), "%d", value);
		strncpy(finger + FINGER_DF, tmp, 1);
		break;
	case FINGER_TIMESTAMP:
		_snprintf(tmp, sizeof(tmp), "%d", value);
		strncpy(finger + FINGER_TIMESTAMP, tmp, 1);
		break;
	case FINGER_TCPFLAG:
		if (value == 1)
			strncpy(finger + FINGER_TCPFLAG, "A", 1);
		else
			strncpy(finger + FINGER_TCPFLAG, "S", 1);
		break;
	case FINGER_LT:
		_snprintf(tmp, sizeof(tmp), "%02X", value);
		strncpy(finger + FINGER_LT, tmp, 2);
		break;                                 
   }
}

UCHAR COSPeekDlg::TTL_PREDICTOR(UCHAR x)
{                            
	register UCHAR i = x;
	register UCHAR j = 1;
	register UCHAR c = 0;
	
   do{
      c += i & 1;
      j <<= 1;
   }while ( i >>= 1 );
	
   if( 1 == c)
      return x;
   else
      return ( j ? j : 0xff );
}

DWORD WINAPI ThreadProc(PVOID pArg)
{
	COSPeekDlg* pDlg = (COSPeekDlg*)pArg;
	WSADATA	WSAData;
	BOOL		flag = true;
	char		LocalName[MAXN];
	struct hostent *pHost;
	SOCKET   sock;
	SOCKADDR_IN	addr_in;
	IP       ip;
	TCP      tcp;
	char     RecvBuf[BUFFER_SIZE];
	
	// 检查 Winsock 版本号
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
		return 0;
	
	// 初始化 Raw Socket
   if((sock=WSASocket(AF_INET,SOCK_RAW,IPPROTO_IP,NULL,0,WSA_FLAG_OVERLAPPED))==INVALID_SOCKET)
		return 0;
	
	// 设置IP头操作选项
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(flag)) == SOCKET_ERROR)
		return 0;
	
	// 获取本机名
	if (gethostname((char*)LocalName, sizeof(LocalName)-1) == SOCKET_ERROR)
		return 0;
	
	// 获取本地 IP 地址
	if ((pHost = gethostbyname((char*)LocalName)) == NULL)
		return 0;
	
	addr_in.sin_addr		= *(in_addr *)pHost->h_addr_list[0]; //IP
	addr_in.sin_family	= AF_INET;
   addr_in.sin_port		= htons(57274);
	
	// 把 sock 绑定到本地地址上
	if (bind(sock, (PSOCKADDR)&addr_in, sizeof(addr_in)) == SOCKET_ERROR)
		return 0;
	
	DWORD dwBufferLen[100];
	DWORD dwBufferInLen = 1;
	DWORD dwBytesReturned = 0;
	
	//将网卡置为混杂模式
	if(WSAIoctl(sock, SIO_RCVALL, &dwBufferInLen, sizeof(dwBufferInLen), &dwBufferLen,
					sizeof(dwBufferLen), &dwBytesReturned, NULL, NULL) != 0)
		return 0;
	
	while(!pDlg->m_bShutDown)
	{
		int ret=0;
		memset(RecvBuf, 0, BUFFER_SIZE);
		ret = recv(sock, RecvBuf, BUFFER_SIZE, 0);
		if(ret>0)
		{			
			ip = *(IP*)RecvBuf; 
			if(ip.Protocol == 6)
			{			
				tcp = *(TCP*)(RecvBuf + (ip.HdrLen) * 4);
				if( !(tcp.Flags & TH_SYN))continue;							  
				char r_finger[FINGER_LEN + 1];
				//WWWW:MSS:TTL:WS:S:N:D:T:F:LEN:OS
				strcpy(r_finger, "0000:_MSS:TT:WS:0:0:0:0:F:LT");  
				//strcpy(r_finger, "0000:_MSS:80:WS:0:0:0:0:A:LT");
				//WWWW
				pDlg -> Fingerprint_push(r_finger, FINGER_WINDOW, ntohs(tcp.Window));
				//TTL
				pDlg -> Fingerprint_push(r_finger, FINGER_TTL, ip.TimeToLive);
				//LEN
				pDlg -> Fingerprint_push(r_finger, FINGER_LT, ntohs(ip.TotalLen));
				//D
				strncpy(r_finger + FINGER_DF, "0", 1);
				if(ip.Flags_and_FragOff & 0x40)
					strncpy(r_finger + FINGER_DF, "1", 1);
				//F
				if(tcp.Flags&TH_ACK)
					pDlg -> Fingerprint_push(r_finger, FINGER_TCPFLAG, 1);
				else
					pDlg -> Fingerprint_push(r_finger, FINGER_TCPFLAG, 0);
				char *opt_start,*opt_end;
				opt_start = RecvBuf + ip.HdrLen * 4 + 20;
				opt_end = RecvBuf + ip.HdrLen * 4 + (tcp.DataOff >> 4 & 0xf) * 4 - 1;
				while (opt_start < opt_end)
				{
					switch (*opt_start)
					{
					case TCPOPT_EOL: 
						/* end option EXIT */
						opt_start = opt_end;
						break;
					case TCPOPT_NOP:
						pDlg -> Fingerprint_push(r_finger, FINGER_NOP, 1);
						opt_start++;
						break;
					case TCPOPT_SACKOK:
						pDlg -> Fingerprint_push(r_finger, FINGER_SACK, 1);
						opt_start += 2;
						break;
					case TCPOPT_MAXSEG:
						opt_start += 2;
						WORD MSS;
						MSS = *opt_start++;
						MSS = MSS << 8 | 0X00FF;
						MSS = *opt_start++ & MSS;
						pDlg -> Fingerprint_push(r_finger, FINGER_MSS, MSS);
						//opt_start += 2;
						break;
					case TCPOPT_WSCALE:
						opt_start += 2;
						pDlg -> Fingerprint_push(r_finger, FINGER_WS, *opt_start);
						opt_start++;
						break;
					case TCPOPT_TIMESTAMP:
						pDlg -> Fingerprint_push(r_finger, FINGER_TIMESTAMP, 1);
						opt_start++;
						opt_start += (*opt_start - 1);
						break;
					default:
						opt_start++;
						if (*opt_start > 0)
							opt_start += (*opt_start - 1);
						break;
					}
				}
				r_finger[4] = ':';
				r_finger[9] = ':';
				r_finger[12] = ':';
				r_finger[15] = ':';
				r_finger[17] = ':';
				r_finger[19] = ':';
				r_finger[21] = ':';
				r_finger[23] = ':';
				r_finger[25] = ':';
				r_finger[FINGER_LEN]= '\0';
				char os[OS_LEN + 1];
				char finger[FINGER_LEN + 1];
				char line[100];
				FILE *f;
				int a = 0;
				CString src,dest,ostype,osneartype;
				src.Format("%s", inet_ntoa(*(in_addr*) & ip.SrcAddr));
				dest.Format("%s", inet_ntoa(*(in_addr*) & ip.DstAddr));
				
				//strcpy(r_finger,"FFFF:0580:80:WS:1:1:1:0:A:30");
				if( (f = fopen( "etter.finger.os", "r" )) != NULL )
				{
					while(fgets(line,100,f)!=0)
					{
						
						strncpy(finger, line, FINGER_LEN);
						finger[FINGER_LEN] = '\0';
						if(0 == memcmp(finger, r_finger, FINGER_LEN))
						{
							
							strncpy(os, line + FINGER_LEN + 1, OS_LEN);
							a = 1;
							break;
						}//end of memcmp
					}//end of while
					fclose(f);
				}//end of ifopen
				// FINGER_MSS
				if(!a && (f = fopen( "etter.finger.os", "r" )) != NULL)
				{
					char r_finger_cmp[FINGER_LEN + 1];
					strncpy(r_finger_cmp, r_finger, FINGER_LEN);
					strncpy(r_finger_cmp + FINGER_MSS, "****", 4);
					r_finger_cmp[FINGER_LEN] = '\0';
					while(fgets(line,100,f) != 0)
					{
						strncpy(finger, line, FINGER_LEN);
						finger[FINGER_LEN] = '\0';
						char win[FINGER_MSS];
						strncpy(win, r_finger, FINGER_MSS);
						win[FINGER_MSS - 1] = '\0';
						if(!strncmp(finger, win, 4))
						{
							if (strncmp(finger, r_finger, FINGER_LEN) > 0)
							{
								strncpy(finger + FINGER_MSS, "****", 4);
								if(0 == memcmp(finger,r_finger_cmp,FINGER_LEN))
								{
									a = 2;
									strncpy(os, line + FINGER_LEN + 1, OS_LEN);
									break;
								}
							}
						}
					}//end of while
					fclose(f);
				}//end of if FFFF:0580:80:WS:1:1:1:0:A:30
				CString finger_real;
				finger_real.Format("%s", r_finger);
				ostype = "unkown";
				if(1 == a)
				{
					ostype.Format("%s", os);
					ostype = ostype;
				}
				else if(2 == a)
				{
					osneartype.Format("%s", os);
					ostype = "nearest:" + osneartype;
				}
				if(ostype == "unkown")
				{
					if(pDlg -> TTL_PREDICTOR(ip.TimeToLive) == 32)
						ostype = "Linux 2.2.x Intel /Solaris 8 Intel/Sparc(TTL)";
					else if(pDlg -> TTL_PREDICTOR(ip.TimeToLive) == 60)
						ostype = "Digital Unix 4.0 Alpha /AIX 4.3.x IBM/RS6000(TTL)";
					else if(pDlg -> TTL_PREDICTOR(ip.TimeToLive) == 64)
						ostype = "Window XP";
					else if(pDlg -> TTL_PREDICTOR(ip.TimeToLive) == 128)
						ostype = "Windows Server/NT/2000/Windows7 Intel(TTL)";
					else if(pDlg -> TTL_PREDICTOR(ip.TimeToLive) == 255)
						ostype = "Cisco 12.0 2514 (unix)(TTL)";
					if(pDlg -> TTL_PREDICTOR(ip.Protocol) == 17 &&(pDlg -> TTL_PREDICTOR(ip.TimeToLive) == 64||pDlg -> TTL_PREDICTOR(ip.TimeToLive) == 1))
						ostype = "Xbox";
					if(pDlg -> TTL_PREDICTOR(ip.Protocol) == 6)
						ostype = "PS游戏机";
				}
				if(ostype == "unkown")
				{
					if(ntohs(tcp.Window) == 0x3F25)
						ostype = "AIX";
					else if(ntohs(tcp.Window) == 0x402E)
						ostype = "Windows|OpenBSD|FreeBSD";
					else if(ntohs(tcp.Window) == 53270 || ntohs(tcp.Window) == 0x7f53)
						ostype = "linux series(windowsize)";
					else if(ntohs(tcp.Window) == 0x40eb || ntohs(tcp.Window) == 0x5b8e
								|| ntohs(tcp.Window) == 0xfaf0 || ntohs(tcp.Window) == 0x7fff
								|| ntohs(tcp.Window) == 0)
						ostype = "windows series(windowsize)";
				}
				if(ostype == "unkown")
				{
					if(ip.ServiceType == 0xc0)
						ostype = "linux series(tos)";
				}
				if(ostype == "unkown")
					ostype.Format("%s", r_finger);
				bool reshow = false;
				int nIndex;
				LVFINDINFO info;
				info.flags = LVFI_PARTIAL | LVFI_STRING;
				info.psz = src;
				if(nIndex = pDlg -> m_ctrList.FindItem(&info, -1) != -1)
				{
					pDlg->m_ctrList.SetItem(nIndex,2,LVIF_TEXT,ostype,0,0,0,0);
					reshow=true;
				}
				if(!reshow)
					pDlg -> AddData(src, ostype);
				pDlg -> AddOsinfo(src, ostype, finger_real);
			}//end of if tcp
		}//end of ret
		//Sleep(1000);
	}//end of while
	WSACleanup();  
	return 0;
}

void COSPeekDlg::AddOsinfo(CString ip, CString os, CString finger)
{
	BOOL bFound = FALSE;
	for(int i=0; i <MAXN; i++)
	{
		if(strcmp(osinfo[i].dt_ip, ip) == 0)
		{
			osinfo[i].dt_os = os;
			osinfo[i].dt_finger = finger;
			bFound = TRUE;
			break;
		}
	}
	if(!bFound)
	{
		osinfo[iPos].dt_ip = ip;
		osinfo[iPos].dt_os = os;
		osinfo[iPos++].dt_finger = finger;
	}
}


void COSPeekDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i;
	CListCtrl* pList1 = (CListCtrl *)GetDlgItem(IDC_LIST1);
	CString ip_show = "*", os_show = "*", finger_show = "*";
	int iItem = pList1 -> GetNextItem(-1, LVNI_SELECTED);  
	ip_show = pList1 -> GetItemText(iItem, 0);  
   
	BOOL bFound = FALSE;
	for(i = 0; i < MAXN; i++)
	{
		if(strcmp(osinfo[i].dt_ip, ip_show) == 0)
		{
			bFound = TRUE;
			break;
		}
	}
	if(bFound)
	{
		os_show = osinfo[i].dt_os;
		finger_show = osinfo[i].dt_finger;
	}
	CFont * f; 
	f = new CFont; 
	f -> CreateFont(12,						// nHeight 
						0,							// nWidth 
						0,							// nEscapement 
						0,							// nOrientation 
						FW_NORMAL,				// nWeight 
						FALSE,					// bItalic 
						FALSE,					// bUnderline 
						0,							// cStrikeOut 
						ANSI_CHARSET,			// nCharSet 
						OUT_DEFAULT_PRECIS,	// nOutPrecision 
						CLIP_DEFAULT_PRECIS, // nClipPrecision 
						DEFAULT_QUALITY,		// nQuality 
						DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
						_T("宋体"));			// lpszFac 
	m_lstBox.SetFont(f,TRUE);
	m_lstBox.ResetContent();
	m_lstBox.AddString("");
	m_lstBox.AddString("                     ******** Detail information of this OS ********");
	m_lstBox.AddString("");
	m_lstBox.AddString("");
	m_lstBox.AddString("                   IP address       : " + ip_show);
	m_lstBox.AddString("                   OS type          : " + os_show);
	m_lstBox.AddString("                   Fingerprint data : ");
	m_lstBox.AddString(finger_show);
	*pResult = 0;
}

void COSPeekDlg::OnStart() 
{
	m_bShutDown = false;
	m_btnStart.EnableWindow(false);
	m_btnStop.EnableWindow(true);
	DWORD dwDownThread;
	m_hThread = CreateThread(NULL, 0, ThreadProc, this, 0, &dwDownThread);
}

void COSPeekDlg::OnStop() 
{
	m_bShutDown = true;
	m_btnStop.EnableWindow(false);
	m_btnStart.EnableWindow(true);
}

void COSPeekDlg :: AddData(CString s0,CString s1)
{
	int index;
	index = m_ctrList.InsertItem(iTot++, s0);
	m_ctrList.SetItem(index, 1, LVIF_TEXT, s1, 0, 0, 0, 0);
}