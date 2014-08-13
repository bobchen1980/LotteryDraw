// meStringArray.cpp: implementation of the meStringArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "meStringArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

meStringArray::meStringArray()
{
	m_pBuf=NULL;
}

meStringArray::~meStringArray()
{
	delete[] m_pBuf;
}

// ==================================================================
// 
// FUNCTION :  meStringArray::AddBuf()
// 
// * Description :	Adds an array of null terminating strings into the meStringArray
// 
// 
// * Author : [Anders M Eriksson], Created : [1999-11-23 18:35:47]
// 
// * Returns : [int] -	The size of the array
// 
// * Function parameters : 
// [*buf] -		array of null terminating strings. Must end with two nulls
// 
// ==================================================================
int meStringArray::AddBuf(char *buf)
{
	int i=0;

	do
	{
		this->Add(buf+i);
		i += strlen(buf+i);
		i++;
	} while( buf[i]!='\0');

	return this->GetSize();

}

// ==================================================================
// 
// FUNCTION :  * meStringArray::GetBuf()
// 
// * Description :	Returns an array of null terminating strings
// 
// 
// * Author : [Anders M Eriksson], Created : [1999-11-23 18:38:41]
// 
// * Returns : [char] -	Array of Null terminated strings. Ends with two nulls
// 
// * Function parameters : 
// 
// ==================================================================
char * meStringArray::GetBuf()
{
	int len=0;
	int i,j;
	CString cs;
	int nSize=this->GetSize();

	for(i=0;i<nSize;i++)
		len += this->GetAt(i).GetLength();

	len=len+nSize+1;

	if(m_pBuf)
		delete[] m_pBuf;

	m_pBuf = new char[len];
	memset(m_pBuf,'\0',len);

	for(i=0,j=0;i<nSize;i++)
	{
		cs=this->GetAt(i);
		memcpy(m_pBuf+j,cs,cs.GetLength());
		j += cs.GetLength()+1;
	}
	return m_pBuf;
}

// ==================================================================
// 
// FUNCTION :  meStringArray::Find()
// 
// * Description :	Finds a string in the meStringArray and returns the pos in the array
// 
// 
// * Author : [Anders M Eriksson], Created : [1999-11-23 18:35:10]
// 
// * Returns : [int] -  pos in array
// 
// * Function parameters : 
// [str] -	string to find
// 
// ==================================================================
int meStringArray::Find(CString str)
{
	CString cs;
	int i,l;
	for(i=0,l=this->GetSize();i<l;i++)
	{
		cs=this->GetAt(i);
		if(cs.Find(str)>-1)
			return i;
	}
	return -1;
	
}
