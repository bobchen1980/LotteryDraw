; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLotteryDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Lottery.h"

ClassCount=3
Class1=CLotteryApp
Class2=CLotteryDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_LOTTERY_DIALOG

[CLS:CLotteryApp]
Type=0
HeaderFile=Lottery.h
ImplementationFile=Lottery.cpp
Filter=N

[CLS:CLotteryDlg]
Type=0
HeaderFile=LotteryDlg.h
ImplementationFile=LotteryDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CAboutDlg]
Type=0
HeaderFile=LotteryDlg.h
ImplementationFile=LotteryDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LOTTERY_DIALOG]
Type=1
Class=CLotteryDlg
ControlCount=4
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_EDIT1,edit,1342249984
Control3=IDC_COMBO1,combobox,1344340227
Control4=IDC_EDIT2,edit,1342242821

