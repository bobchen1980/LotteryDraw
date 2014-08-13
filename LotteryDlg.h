// LotteryDlg.h : header file
//

#if !defined(AFX_LOTTERYDLG_H__B85BD091_E2F5_4117_A1DF_5B46F219FE66__INCLUDED_)
#define AFX_LOTTERYDLG_H__B85BD091_E2F5_4117_A1DF_5B46F219FE66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxwin.h"

#include "Skin/CDialogSK.h"
#include "Controls/BtnST.h"
#include "Controls/Label.h"
#include "Controls/editex.hxx"
#include "Function/meStringArray.h"
#include "Controls/CJFlatComboBox.h"
#include "Skin/FullScreenTitleBar.h"
#include "Controls/Ini.h"
#include "Controls/Picture.h"
#include "ximage.h"
#include <Mmsystem.h>

/////////////////////////////////////////////////////////////////////////////
// CLotteryDlg dialog

class CLotteryDlg : public CDialogSK
{
// Construction
public:
	CLotteryDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CLotteryDlg();
// Dialog Data
	//{{AFX_DATA(CLotteryDlg)
	enum { IDD = IDD_LOTTERY_DIALOG };
	CTitleBar m_TitleBar;
	CCJFlatComboBox	m_btnScroll;
	CButtonST	m_btnAward;
	CEditEx	m_eContent;
	CEditEx 	m_eShow;
	CEditEx m_Gongxi;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLotteryDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnWriteToSetting(CString szLine);
	CString m_fSettingFile;
	CString m_fLotteryFile;
	CString m_fAwardFile;
	CString m_fRecordFile;
	CString m_fShortMesFile;
	CString m_sPicturPath;
	CPicture  m_Picture; 
	//CxImage  m_Picture; 
	CxImage  m_AwPicture; 
	//CPicture m_AwPicture; 
	CRect m_rectFlashText;
	CRect m_rectFlashPicture;
	CRect m_rectAwardButton;
	CRect m_rectAwardSelect;
	CRect m_rectAwardPicture;
	CRect m_rectAwardText;
	CRect m_rectGongxi;
	void OnReadToCombox(CString sFile,int nCurSel);
	BOOL m_bIsStarted;
	BOOL m_bIsShortMes;
	void OnInitControl();
	void OnEnd();
	void OnStart();
	int GetRandNum(int nMax);
	meStringArray m_arrayRecord;
	meStringArray m_arrayPerNum;
	meStringArray m_arrayShortMes;
	CString m_exePath;
	void OnReadInRecord(CString sFile,CStringArray& aRecord);
	HICON m_hIcon;
	int SplitStringToArray( CString strSrc, CString strSeparator, CStringArray &saResult, BOOL bIgnoreZeroLength );

	// Generated message map functions
	//{{AFX_MSG(CLotteryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnButtonAward();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CIni m_iniFile;

protected:
	void OnReadInPicture(CString picFile);
public:
	CStatic m_tFlash;
protected:
	bool OnInitParam();
private:
	CString m_BackImage;
private:
	CString m_AwardMode;
	CString m_fPictureFile;
private:
	CString m_ShortMes;
private:
	CString m_ShortText;
private:
	int m_WindowWidth;
	int m_WindowHeight;
private:
	CStatic m_tAwardPic;
private:
	CString m_AwardPicPath;
private:
	CString m_SoundPath;
private:
	CString m_flashSound;
private:
	CString m_awardSound;
	HBITMAP m_awardBitmap;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_GongxiText;
	CString m_mainTitle;
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOTTERYDLG_H__B85BD091_E2F5_4117_A1DF_5B46F219FE66__INCLUDED_)
