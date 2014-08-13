// meStringArray.h: interface for the meStringArray class.
//
//	Purpose:	Extends the CStringArray with a Find method it also adds communication to and from
//				null terminated string arrays, like the one you use in CFileDialog to set the filter
//
//	Author:	Anders M Eriksson	
//	Date:	1999-11-23 18:35
//	email:	ame@swipnet.se
//			If you find this class usefull or find any bugs or have any comments, Please send me an email!
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESTRINGARRAY_H__28AA59B9_A199_11D3_B013_0060087534EB__INCLUDED_)
#define AFX_MESTRINGARRAY_H__28AA59B9_A199_11D3_B013_0060087534EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class meStringArray : public CStringArray  
{
public:
	meStringArray();
	virtual ~meStringArray();

	int AddBuf(char *buf);
	int Find(CString str);
	char * GetBuf();

	char * m_pBuf;

};

#endif // !defined(AFX_MESTRINGARRAY_H__28AA59B9_A199_11D3_B013_0060087534EB__INCLUDED_)
