//===========================================================================
//	FullScreen Titlebar Constants
//	2004 - All rights reservered
//===========================================================================
//
//	Project/Product :	FullScreenTitlebar
//  FileName		:	FullScreenTitleBarConst.h
//	Author(s)		:	Lars Werner
//  Homepage		:	http://lars.werner.no
//
//	Description		:	All the consts used in the FullScreentitlebar
//                  
//	Classes			:	None
//
//	Information		:
//	  Compiler(s)	:	Visual C++ 6.0 Ent.
//	  Target(s)		:	Win32 / MFC
//	  Editor		  :	Microsoft Visual Studio 6.0 editor
//
//	History
//	Vers.  Date      Aut.  Type     Description
//  -----  --------  ----  -------  -----------------------------------------
//	1.00   22 01 04  LW    Create   Original
//===========================================================================

//Width and heigth for the toolbar
#define tbWidth				400
#define tbHeigth			32

//Default size on every picture used as buttons
#define tbcxPicture			28
#define tbcyPicture			26

//Margins for placing buttons on screen
#define tbTopSpace			1
#define tbLeftSpace			20
#define tbRightSpace		20
#define tbButtonSpace		1

//Color and layout
#define tbFont				"Arial"
#define tbFontSize			18
#define tbTextColor			RGB(220,40,40)
#define tbStartColor		RGB(255,255,255)
#define tbEndColor			RGB(255,175,0)
#define tbGradientWay		TRUE	//TRUE = Vertical, FALSE = Horiz
#define tbBorderPenColor	RGB(255,255,255)
#define tbBorderPenShadow	RGB(100,100,100)

//Triangularpoint is used to make the RGN so the window is not rectangular
#define tbTriangularPoint	10

//This is the width of the pen used to draw the border...
#define tbBorderWidth		2

//About showing the window
#define tbHideAtStartup		FALSE //Hide window when created
#define tbPinNotPushedIn	FALSE //Is the pin pushed in or out at startup (sorry for invertion!)
#define tbScrollWindow		TRUE //Animate window to scroll up/down
#define tbScrollDelay		20	//Timer variable for scrolling the window (cycletime) [ms]
#define tbAutoScrollTime	10	//* tbAutoScrollDelay milliseconds steps. Meaning if it is 10 then = 10 (steps) * 100ms (tbAutoScrollDelay) = 1000ms delay
#define tbScrollTimerID		1	//Timer id
#define tbAutoScrollTimer	2	//Timer id
#define tbAutoScrollDelay	100 //Timer variable for how many times the cursor is not over the window. If it is tbAutoScrollTime then it will hide if autohide

//=================================================
//Resource part
//=================================================

#define tbIDC_CLOSE			10
#define tbIDC_MAXIMIZE		20
#define tbIDC_MINIMIZE		30
#define tbIDC_PIN			40

//=================================================
// Windows Message part
//=================================================

//FALSE = Send a custon WM message, TRUE = Send Minimize, maximize and close to parent
#define tbDefault			TRUE

//Own defines messages
#define tbWM_CLOSE			WM_USER+1000
#define tbWM_MINIMIZE		WM_USER+1001
#define tbWM_MAXIMIZE		WM_USER+1002

//=================================================
// Menus with ID's and messages
//=================================================

#define tbMENUID			IDR_tbMENU //Resource name for the menu
#define tbWMCOMMANDIDStart	50000 //Start: This is the internal id number sendt into the WM_COMMAND on each item
#define tbWMCOMMANDIDEnd	51000 //End: This is the internal id number sendt into the WM_COMMAND on each item
#define tbWMUSERID			2000 //This is WM_USER+n setting. Eg: if first item is clicked you will get an WM_USER+n+0 to the parent, and WM_USER+n+1 for the next item ect ect
#define tbLastIsStandard	TRUE //TRUE = Bottom of the menu is close, minimize and maximize, FALSE = The menu does not contain anything
