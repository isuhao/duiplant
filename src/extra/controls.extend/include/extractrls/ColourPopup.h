#ifndef COLOURPOPUP_INCLUDED
#define COLOURPOPUP_INCLUDED
#pragma once 


// ColourPopup.h : header file
//
// Written by Chris Maunder (chrismaunder@codeguru.com)
// Extended by Alexander Bischofberger (bischofb@informatik.tu-muenchen.de)
// Copyright (c) 1998.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage whatsoever.
// It's free - so you get what you pay for.

#include <dui/extractrls/tooltipctrl.h>

namespace DuiEngine
{

struct IColorPicker{
	virtual void OnColorChanged(COLORREF cr)=0;
	virtual void OnColorEnd(BOOL bCancel,COLORREF cr)=0;
};

/////////////////////////////////////////////////////////////////////////////
// CColourPopup window

class CColourPopup : public CSimpleWnd , public CDuiMessageFilter
{
	// To hold the colours and their names
	typedef struct {
		COLORREF crColour;
		TCHAR    *szName;
	} ColourTableEntry;
// Construction
public:
    CColourPopup(HWND hOwner,IColorPicker *pColorPicker);

	virtual ~CColourPopup();

// Operations
public:
    BOOL Create(CPoint p, COLORREF crColour, LPCTSTR szDefaultText = NULL, LPCTSTR szCustomText = NULL);

	void SetDefColor(COLORREF crDef){m_crDef=crDef;}
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	void Initialise();
    BOOL GetCellRect(int nIndex, const LPRECT& rect);
    void FindCellFromColour(COLORREF crColour);
    void SetWindowSize();
    void CreateToolTips();
    void ChangeSelection(int nIndex);
    void EndSelection(int nMessage);
    void DrawCell(CDC* pDC, int nIndex);

    COLORREF GetColour(int nIndex)              { return m_crColours[nIndex].crColour; }
    LPCTSTR GetColourName(int nIndex)           { return m_crColours[nIndex].szName; }
    int  GetIndex(int row, int col) const;
    int  GetRow(int nIndex) const;
    int  GetColumn(int nIndex) const;

	BOOL MyChooseColor(COLORREF &cr);

// protected attributes
protected:
    static ColourTableEntry m_crColours[];
    int            m_nNumColours;
    int            m_nNumColumns, m_nNumRows;
    int            m_nBoxSize, m_nMargin;
    int            m_nCurrentSel;
    int            m_nChosenColourSel;
    CDuiStringT        m_strDefaultText;
    CDuiStringT        m_strCustomText;
    CRect          m_CustomTextRect, m_DefaultTextRect, m_WindowRect;
    CFont          m_Font;
    CPalette       m_Palette;
    COLORREF       m_crInitialColour, m_crColour;
	COLORREF		m_crDef;
    CSimpleToolTip   m_ToolTip;

	HWND			m_hOwner;
	IColorPicker	*m_pColorPicker;
    // Generated message map functions
protected:
    void OnLButtonUp(UINT nFlags, CPoint point);
    void OnPaint(HDC hdc);
    void OnMouseMove(UINT nFlags, CPoint point);
    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnKillFocus(HWND hNewWnd);
	void OnActivateApp(BOOL bActive, DWORD hTask);

	virtual void OnFinalMessage(HWND hWnd);

	BEGIN_MSG_MAP_EX(CColourPopup)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_KEYDOWN(OnKeyDown)
		MSG_WM_KILLFOCUS(OnKillFocus)
		MSG_WM_ACTIVATEAPP(OnActivateApp)
	END_MSG_MAP()
};


}//end of namespace

/////////////////////////////////////////////////////////////////////////////


#endif // !defined(AFX_COLOURPOPUP_H__D0B75902_9830_11D1_9C0F_00A0243D1382__INCLUDED_)
