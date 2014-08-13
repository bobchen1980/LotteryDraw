// LotteryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Lottery.h"
#include "LotteryDlg.h"
#include "afxwin.h"

#include "Controls/MyHyperLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
public:
	CMyHyperLink  m_abtHyperLink;
public:
	virtual BOOL OnInitDialog();
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
	DDX_Control(pDX, IDC_HYPER, m_abtHyperLink);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_abtHyperLink.SetLinkUrl("www.ioa.ac.cn");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CLotteryDlg dialog

CLotteryDlg::CLotteryDlg(CWnd* pParent /*=NULL*/)
	: CDialogSK(CLotteryDlg::IDD, pParent)
	, m_BackImage(_T(""))
	, m_AwardMode(_T(""))
	, m_fPictureFile(_T(""))
	, m_ShortMes(_T(""))
	, m_ShortText(_T("NO"))
	, m_WindowWidth(0)
	, m_WindowHeight(0)
	, m_AwardPicPath(_T(""))
	, m_SoundPath(_T(""))
	, m_flashSound(_T(""))
	, m_awardSound(_T(""))
	, m_awardBitmap(NULL)
	, m_GongxiText(_T(""))
	, m_mainTitle(_T(""))
{
	//{{AFX_DATA_INIT(CLotteryDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CLotteryDlg::~CLotteryDlg()
{
}


void CLotteryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogSK::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLotteryDlg)
	DDX_Control(pDX, IDC_EDIT2, m_eContent);
	DDX_Control(pDX, IDC_COMBO1, m_btnScroll);
	DDX_Control(pDX, IDC_BUTTON1, m_btnAward);
	DDX_Control(pDX, IDC_EDIT1, m_eShow);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_FLASH, m_tFlash);
	DDX_Control(pDX, IDC_AWARDPIC, m_tAwardPic);
	DDX_Control(pDX, IDC_EDIT3, m_Gongxi);
}

BEGIN_MESSAGE_MAP(CLotteryDlg, CDialogSK)
	//{{AFX_MSG_MAP(CLotteryDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonAward)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLotteryDlg message handlers

BOOL CLotteryDlg::OnInitDialog()
{
	CDialogSK::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//EnableEasyMove();  
	//SetTransparentColor(RGB(255, 255, 255),true);
	
	// TODO: Add extra initialization here
	TCHAR cPath[MAX_PATH];
	GetModuleFileName( NULL, cPath, MAX_PATH );  //获取程序路径（包括程序名）
	int i = 0, j;
	while( cPath[i]!=0 )
	{
		if( cPath[i]=='\\' )
			j = i;
		i++;
	}
	cPath[j+1] = '\0';
	m_exePath.Format( "%s", cPath );    //分离路径名（去掉程序名）	

	m_fSettingFile = m_exePath+"Settings\\Setting.ini";

	CFileFind find; 
	if (!find.FindFile(m_fSettingFile)) 
	{
		AfxMessageBox(IDS_STRING104);
		PostMessage(WM_QUIT,0,0);
	}
	find.Close();

	OnInitParam();		

	//ShowWindow(SW_MAXIMIZE);
	SetWindowPos(NULL, 0, 0, m_WindowWidth, m_WindowHeight, SWP_NOZORDER|SWP_NOMOVE);
	SetBitmap( m_exePath+"Settings\\"+m_BackImage);
	//AfxMessageBox( m_exePath+"Settings\\"+m_BackImage);
	//SetBitmap(IDB_BITMAPBACKGROUND);
	m_TitleBar.Create(AfxGetInstanceHandle(), this->GetSafeHwnd());
	m_TitleBar.SetText(m_mainTitle.GetBuffer(m_mainTitle.GetLength()));
	SetWindowText(m_mainTitle);

	OnInitControl();
	//AfxMessageBox(m_AwardMode);
	if(m_AwardMode.CompareNoCase("Text") == 0)
	{
		OnReadInRecord(m_fRecordFile,m_arrayPerNum);
	}
	else
	{
		OnReadInRecord(m_fPictureFile,m_arrayPerNum);
	}

	if(m_ShortMes.CompareNoCase("YES") == 0)
	{
		m_bIsShortMes = TRUE;
		OnReadInRecord(m_fShortMesFile,m_arrayShortMes);
	}

	OnReadToCombox(m_fAwardFile,-1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CLotteryDlg::OnInitControl()
{

	m_btnScroll.SetWindowPos(NULL, m_rectAwardSelect.left, m_rectAwardSelect.top, m_rectAwardSelect.Width(), m_rectAwardSelect.Height(), SWP_NOZORDER);
	m_Gongxi.SetWindowPos(NULL, m_rectGongxi.left, m_rectGongxi.top, m_rectGongxi.Width(), m_rectGongxi.Height(), SWP_NOZORDER);
	m_Gongxi.bkColor( RGB(255,228,0) );
	m_Gongxi.textColor( RGB(255,0,0) );
	m_Gongxi.setFont( 30,FW_BOLD,FF_DONTCARE,"宋体");


	m_btnAward.SetWindowPos(NULL, m_rectAwardButton.left, m_rectAwardButton.top, m_rectAwardButton.Width(), m_rectAwardButton.Height(), SWP_NOZORDER);
	m_tAwardPic.SetWindowPos(NULL, m_rectAwardPicture.left, m_rectAwardPicture.top, m_rectAwardPicture.Width(), m_rectAwardPicture.Height(), SWP_NOZORDER);
	if(m_AwardMode.CompareNoCase("Text") == 0)
	{
		m_eShow.SetWindowPos(NULL, m_rectFlashText.left, m_rectFlashText.top, m_rectFlashText.Width(), m_rectFlashText.Height(), SWP_NOZORDER);
		m_eShow.SetWindowPos(NULL, 235, 170, 580, 120, SWP_NOZORDER);
		m_eShow.bkColor( RGB(254,228,0) );
		m_eShow.textColor( RGB(255,0,0) );
		m_eShow.setFont( 68,FW_BOLD,FF_DONTCARE,"宋体");
		m_eShow.SetReadOnly(TRUE);
		m_tFlash.ShowWindow(SW_HIDE);
	}
	else
	{
		m_tFlash.SetWindowPos(NULL, m_rectFlashPicture.left, m_rectFlashPicture.top, m_rectFlashPicture.Width(), m_rectFlashPicture.Height(), SWP_NOZORDER);
		m_eShow.ShowWindow(SW_HIDE);
	}

	m_btnAward.DrawTransparent();	
	//m_btnAward.SetBitmaps(IDB_BITMAP1,RGB(254,0,0));

	m_bIsStarted = FALSE;

	m_eContent.SetWindowPos(NULL, m_rectAwardText.left, m_rectAwardText.top, m_rectAwardText.Width(), m_rectAwardText.Height(), SWP_NOZORDER);
    //m_eContent.bkColor( RGB(66,165,230) );
	m_eContent.bkColor( RGB(254,0,0) );
    m_eContent.textColor( RGB(255,255,255) );
    m_eContent.setFont( 30,FW_BOLD,FF_DONTCARE,"幼圆");

	//m_eContent.SetReadOnly(TRUE);

}

void CLotteryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogSK::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLotteryDlg::OnPaint() 
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
		CDialogSK::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLotteryDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLotteryDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialogSK::OnOK();
}

void CLotteryDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CString szTitle , szContent;
	szTitle.LoadString(IDS_STRING106);
	szContent.LoadString(IDS_STRING105);

	if(MessageBox(szContent,szTitle,MB_OKCANCEL) != IDOK)
		return;

	if (m_awardBitmap) DeleteObject(m_awardBitmap);


	CString tmpStr;
	
	if(m_btnScroll.GetCurSel() <0)
	{
		m_arrayRecord.Append( m_arrayPerNum );
	}

	if(m_AwardMode.CompareNoCase("Text") == 0)
	{
		//::CopyFile(m_fRecordFile,m_fRecordFile+".bak",TRUE);
		CStdioFile recordFile( m_fRecordFile, CFile::modeCreate|CFile::modeWrite);
		for(int iLine = 0;iLine < m_arrayRecord.GetSize();iLine++)
		{
			tmpStr += m_arrayRecord.ElementAt(iLine);
			tmpStr += "\n";
		}
		recordFile.WriteString(tmpStr);
		recordFile.Close();
	}
	else
	{
		//::CopyFile(m_fPictureFile,m_fPictureFile+".bak",TRUE);
		CStdioFile picFile( m_fPictureFile, CFile::modeCreate|CFile::modeWrite);
		for(int iLine = 0;iLine < m_arrayRecord.GetSize();iLine++)
		{
			tmpStr += m_arrayRecord.ElementAt(iLine);
			tmpStr += "\n";
		}
		picFile.WriteString(tmpStr);
		picFile.Close();
	}

	
	CDialogSK::OnCancel();
}

///文件中不能出现空行
void CLotteryDlg::OnReadInRecord(CString sFile,CStringArray& aRecord)
{ 
	//AfxMessageBox(sFile);
	CStdioFile tmpFile( sFile, CFile::modeRead);
	for( CString tmpStr; tmpFile.ReadString( tmpStr);)
	{   
		aRecord.Add(tmpStr);
		}   
	
	tmpFile.Close();

}

void CLotteryDlg::OnReadToCombox(CString sFile,int nCurSel)
{
	CStdioFile tmpFile( sFile, CFile::modeRead);

	m_btnScroll.ResetContent();

	for( CString tmpStr; tmpFile.ReadString( tmpStr);)
	{   
		if(tmpStr.GetLength() > 0)
			m_btnScroll.AddString(tmpStr);
	}   
	
	m_btnScroll.SetCurSel(nCurSel);

	tmpFile.Close();


}
void CLotteryDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//if(m_AwardMode.CompareNoCase("Text") == 0)
		CString szRand = m_arrayRecord.ElementAt(GetRandNum(m_arrayRecord.GetSize()));
		m_eShow.SetWindowText(szRand);

		///以文本随机带图片，图片跟随文本随机
		OnReadInPicture(m_sPicturPath + szRand);

		sndPlaySound(m_flashSound,SND_ASYNC);


	CDialogSK::OnTimer(nIDEvent);
}

int CLotteryDlg::GetRandNum(int nMax)
{
	if( nMax <= 1  )
		return 0;
	int test = rand()%(nMax - 1);
	return test ;
}

BOOL CLotteryDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYUP) 
	{ 
		if(pMsg->wParam == VK_RETURN) 
		{ 
			return TRUE; 
		} 
		if(pMsg->wParam == VK_SPACE ) 
		{ 
			//AfxMessageBox("keyup");
			
			if(m_bIsStarted)
				OnEnd();
			else
				OnStart();

			return TRUE; 
			
		} 
	} 
	
	return CDialogSK::PreTranslateMessage(pMsg);
}

void CLotteryDlg::OnStart()
{
	if(m_btnScroll.GetLBTextLen(m_btnScroll.GetCurSel()) < 1 )
	{
		AfxMessageBox(IDS_STRING103);
		return;
	}
	if( m_arrayRecord.GetSize() > 0 )
	{
		SetTimer(1, 20, NULL);
		m_bIsStarted = TRUE;
	}
	else
	{
		if(m_bIsShortMes)
		{
			m_arrayShortMes.RemoveAll();
		}
		else
		{
			m_arrayPerNum.RemoveAll();
		}
		AfxMessageBox(IDS_STRING102);
	}
	m_Gongxi.ShowWindow(SW_HIDE);
}

void CLotteryDlg::OnEnd()
{	
	if(!m_bIsStarted)
		return;

	CString tmpLottery,strCombol,strTmp,strTmpCom,szLine;
	CStringArray strSplit;
	int nSplitNum;
	
	KillTimer(1);
	m_bIsStarted = FALSE;

	m_Gongxi.ShowWindow(SW_NORMAL);
	m_Gongxi.SetWindowText(m_GongxiText);

	
	if(m_AwardMode.CompareNoCase("Text") == 0)
	{
		m_eShow.GetWindowText(tmpLottery);
		m_arrayRecord.RemoveAt(m_arrayRecord.Find(tmpLottery));
	}else
	{
		m_eShow.GetWindowText(tmpLottery);
		m_arrayRecord.RemoveAt(m_arrayRecord.Find(tmpLottery));
	}


	CStdioFile tmpFile( m_fLotteryFile, CFile::modeWrite);
	tmpFile.SeekToEnd();
	m_btnScroll.GetLBText(m_btnScroll.GetCurSel(),strCombol);
	nSplitNum = SplitStringToArray(strCombol,"|",strSplit,TRUE);
	if(nSplitNum >0 )
	{
		strTmp = strSplit.ElementAt(0) + "::";
		strTmp += tmpLottery;
		strTmp += "\r\n";
		tmpFile.WriteString(strTmp);
		//AfxMessageBox(strSplit.ElementAt(nSplitNum-1));

	}
	tmpFile.Close();
	CString sFind = strCombol.Mid(0,strCombol.ReverseFind('|'));
	CString sFinal,sMiddle;
	int nLottNum = 0;
	sMiddle = strCombol.Mid(strCombol.ReverseFind('|')+1,strCombol.GetLength());
	nLottNum = atoi(sMiddle);

	sFinal.Format("%s|已抽取%d人",sFind,nLottNum+1);
	szLine.Format("%s|%d",sFind,nLottNum+1);
	OnWriteToSetting(szLine);
	//sFinal.Replace("|","\r\n");
	sFinal.Replace("$","\r\n");
	m_eContent.SetWindowText(sFinal);
	OnReadToCombox(m_fAwardFile,m_btnScroll.GetCurSel());

	sndPlaySound(m_awardSound,SND_ASYNC);

}


void CLotteryDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	CString tmpSelect,sStart,sMiddle,sFinal,szMidd;
	m_btnScroll.GetLBText(m_btnScroll.GetCurSel(),tmpSelect);
	
	if(m_arrayRecord.GetSize() > 0 )
	{
		if(m_bIsShortMes)
		{
			m_arrayShortMes.RemoveAll();
			m_arrayShortMes.Append(m_arrayRecord);
		}
		else
		{
			m_arrayPerNum.RemoveAll();
			m_arrayPerNum.Append(m_arrayRecord);
		}
	}
	m_arrayRecord.RemoveAll();
	
	if(tmpSelect.Find(m_ShortText,0) > -1)
	{
		if(m_arrayShortMes.GetSize() >0 )
			m_arrayRecord.Append(m_arrayShortMes);
		m_bIsShortMes = TRUE;
	}
	else
	{
		if(m_arrayPerNum.GetSize() >0 )
			m_arrayRecord.Append(m_arrayPerNum);
		m_bIsShortMes = FALSE;
	}


	sStart = tmpSelect.Mid(0,tmpSelect.ReverseFind('|'));
	sMiddle = tmpSelect.Mid(tmpSelect.ReverseFind('|')+1,tmpSelect.GetLength());
	int nLottNum = atoi(sMiddle);

	szMidd.LoadString(IDS_STRING107);
	sFinal.Format("%s%s%d人",sStart,szMidd,nLottNum);

	sFinal.Replace("$","\r\n");

	m_eContent.SetWindowText(sFinal);
	
	CString tmpFile;
	tmpFile.Format("%s%d.jpg",m_AwardPicPath,m_btnScroll.GetCurSel());
	CFileFind find; 
	//AfxMessageBox(tmpFile);
	if (find.FindFile(tmpFile) )
	{
		//AfxMessageBox("缺少配置文件，不能启动");
		//if(m_AwPicture.Load(tmpFile,CXIMAGE_FORMAT_JPG))
		if(m_AwPicture.Load(tmpFile))
		{
			//m_AwPicture.Show(m_tAwardPic.GetDC(), CRect(0,0,m_rectAwardPicture.Width()-4,m_rectAwardPicture.Height()-4)); 
			m_awardBitmap = m_AwPicture.MakeBitmap(m_tAwardPic.GetDC()->m_hDC);
			m_tAwardPic.SetBitmap(m_awardBitmap);
		}
	}
	find.Close();

	
}

int CLotteryDlg::SplitStringToArray(CString strSrc, CString strSeparator, CStringArray &saResult, BOOL bIgnoreZeroLength)
{
	int nResultCount = 0;
	
	CString strTemp; 
	while( strSrc.GetLength() > 0 )
	{
		BOOL bHasSeparator = FALSE;
		for( int i = 0; i < strSrc.GetLength(); ++i )
		{
			if( strSeparator.Find( strSrc.GetAt(i) ) >= 0 )
			{
				bHasSeparator = TRUE;
				strTemp = strSrc.Left(i);
				if( !( bIgnoreZeroLength && strTemp.GetLength() == 0 ) )
				{
					saResult.Add( strTemp );
					nResultCount++;
				}
				strSrc = strSrc.Mid( i + 1 );
				break;
			}
		}
		if( !bHasSeparator )
		{
			if( !( bIgnoreZeroLength && strSrc.GetLength() == 0 ) )
			{
				saResult.Add( strSrc );
				nResultCount++;
			}
			break;
		}
	}
	
	return nResultCount;
}

void CLotteryDlg::OnWriteToSetting(CString szLine)
{
	CString strAll;
	CStdioFile tmpFile( m_fAwardFile, CFile::modeReadWrite);
	CString sStart = szLine.Mid(0,szLine.ReverseFind('|'));
	for( CString tmpStr; tmpFile.ReadString( tmpStr);)
	{   
		if(tmpStr.Find(sStart,0) > -1)
		{
			strAll += szLine;
		}
		else
		{
			strAll += tmpStr;
		}
		strAll += "\n";
	}   
	tmpFile.SeekToBegin();
	tmpFile.WriteString(strAll);
	tmpFile.Close();

}

void CLotteryDlg::OnButtonAward() 
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL,"open",m_fLotteryFile,NULL,NULL,SW_SHOWNORMAL);
}


void CLotteryDlg::OnReadInPicture(CString picFile)
{
	if(m_Picture.Load(picFile))
	{
		//m_flashBitmap = m_Picture.MakeBitmap(m_tFlash.GetDC()->m_hDC);
		//m_tFlash.SetBitmap(m_flashBitmap);	
		//CDC* dc = m_tFlash.GetDC();
		//m_Picture.UpdateSizeOnDC(&dc); 
		//m_Picture.Show(&dc, CPoint(0,0),CPoint(m_Picture.m_Width, m_Picture.m_Height), 0,0);
		m_Picture.Show( m_tFlash.GetDC(), CRect(0,0,m_rectFlashPicture.Width()-4,m_rectFlashPicture.Height()-4)); 
	}
}

bool CLotteryDlg::OnInitParam()
{
	m_iniFile.SetPathName(m_fSettingFile);

	m_mainTitle = m_iniFile.GetString(_T("Settings"), _T("Title"), _T(","));
	m_BackImage = m_iniFile.GetString(_T("Settings"), _T("BgImage"), _T(","));
	m_AwardMode = m_iniFile.GetString(_T("Settings"), _T("AwardMode"), _T(","));
	m_ShortMes = m_iniFile.GetString(_T("Settings"), _T("ShortMes"), _T(","));
	m_ShortText = m_iniFile.GetString(_T("Settings"), _T("ShortText"), _T(","));

	m_GongxiText = m_iniFile.GetString(_T("Settings"), _T("GongxiText"), _T(","));

	m_fLotteryFile = m_exePath +"Records\\"+ m_iniFile.GetString(_T("Settings"), _T("LotteryRecord"), _T(","));
	m_fAwardFile = m_exePath +"Settings\\"+  m_iniFile.GetString(_T("Settings"), _T("AwardSetting"), _T(","));
	m_fRecordFile = m_exePath +"Records\\"+  m_iniFile.GetString(_T("Settings"), _T("TextData"), _T(","));
	m_fShortMesFile = m_exePath +"Records\\"+  m_iniFile.GetString(_T("Settings"), _T("ShortMesData"), _T(","));
	m_fPictureFile =  m_exePath +"Records\\"+ m_iniFile.GetString(_T("Settings"), _T("PictureData"), _T(","));

	m_sPicturPath = m_exePath + "Picture\\";
	m_AwardPicPath = m_exePath + "AwardPic\\";
	m_SoundPath = m_exePath + "Sound\\";
	
	//AfxMessageBox(m_fRecordFile);

	m_WindowWidth = m_iniFile.GetInt(_T("Positions"), _T("WindowWidth"), 1024 ,800);
	m_WindowHeight = m_iniFile.GetInt(_T("Positions"), _T("WindowHeight"), 768 ,600);
	//AfxMessageBox(m_ShortText);

	m_rectFlashText=m_iniFile.GetRect(_T("Positions"), _T("rectFlashText"),CRect(235, 170, 580, 120));
	m_rectFlashPicture=m_iniFile.GetRect(_T("Positions"), _T("rectFlashPicture"),CRect(235, 170, 580, 120));
	m_rectAwardButton=m_iniFile.GetRect(_T("Positions"), _T("rectAwardButton"),CRect(0,0,100,100));
	m_rectAwardSelect=m_iniFile.GetRect(_T("Positions"), _T("rectAwardSelect"),CRect(0,0,100,100));
	m_rectAwardPicture=m_iniFile.GetRect(_T("Positions"), _T("rectAwardPicture"),CRect(0,0,100,100));
	m_rectAwardText=m_iniFile.GetRect(_T("Positions"), _T("rectAwardText"),CRect(0,0,100,100));
	m_rectGongxi=m_iniFile.GetRect(_T("Positions"), _T("rectGongxi"),CRect(0,0,100,100));


	m_iniFile.WriteRect(_T("Positions"), _T("rectFlashText"),CRect(235, 170, 580, 120));
	m_iniFile.WriteRect(_T("Positions"), _T("rectFlashPicture"),CRect(235, 170, 580, 120));
	//m_iniFile.WriteRect(_T("Positions"), _T("rectAwardButton"),CRect(740, 670, 800, 690));
	//m_iniFile.WriteRect(_T("Positions"), _T("rectAwardSelect"),CRect(210, 670, 730, 760));
	//m_iniFile.WriteRect(_T("Positions"), _T("rectAwardPicture"),CRect(530, 450, 800, 660));
	//m_iniFile.WriteRect(_T("Positions"), _T("rectAwardText"),CRect(210, 450, 500, 660));
	//m_iniFile.WriteRect(_T("Positions"), _T("rectGongxi"),CRect(210, 395, 800, 430));
	//m_iniFile.WriteRect(_T("Positions"), _T("rectAwardPicture"),CRect(210, 453, 779, 615));
	//m_iniFile.WriteRect(_T("Positions"), _T("rectAwardText"),CRect(210, 630, 779, 665));

	m_flashSound = m_SoundPath + m_iniFile.GetString(_T("Sound"), _T("FlashSound"), _T(","));
	m_awardSound = m_SoundPath +  m_iniFile.GetString(_T("Sound"), _T("AwardSound"), _T(","));

	return true;
}


HBRUSH CLotteryDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogSK::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CLotteryDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();

	CDialogSK::OnRButtonUp(nFlags, point);
}

