// MSFlexGridSink.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "MSFlexGridSink.h"
#include "gpmsflexgrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSFlexGridSink

IMPLEMENT_DYNCREATE(CMSFlexGridSink, CCmdTarget)

CMSFlexGridSink::CMSFlexGridSink()
{
	EnableAutomation();
}

CMSFlexGridSink::~CMSFlexGridSink()
{
}


void CMSFlexGridSink::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CMSFlexGridSink, CCmdTarget)
	//{{AFX_MSG_MAP(CMSFlexGridSink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMSFlexGridSink, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CMSFlexGridSink)
    DISP_FUNCTION_ID(CMSFlexGridSink,"Click",-600,OnClickMsflexgrid, VT_EMPTY, VTS_NONE)
    DISP_FUNCTION_ID(CMSFlexGridSink,"KeyDown",-602, OnKeyDownMsflexgrid, VT_EMPTY,VTS_PI2 VTS_I2)
    DISP_FUNCTION_ID(CMSFlexGridSink,"DblClick",-601, OnDblClickMsflexgrid,VT_EMPTY, VTS_NONE)
    DISP_FUNCTION_ID(CMSFlexGridSink,"KeyPress",-603, OnKeyPressMsflexgrid,VT_EMPTY, VTS_PI2)
    DISP_FUNCTION_ID(CMSFlexGridSink,"KeyUp",-604, OnKeyUpMsflexgrid,VT_EMPTY, VTS_PI2 VTS_I2)
    DISP_FUNCTION_ID(CMSFlexGridSink,"MouseDown",-605, OnMouseDownMsflexgrid,VT_EMPTY, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
    DISP_FUNCTION_ID(CMSFlexGridSink,"MouseMove",-606, OnMouseMoveMsflexgrid,VT_EMPTY, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
    DISP_FUNCTION_ID(CMSFlexGridSink,"MouseUp",-607, OnMouseUpMsflexgrid,VT_EMPTY, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
    DISP_FUNCTION_ID(CMSFlexGridSink,"SelChange",69, OnSelChangeMsflexgrid,VT_EMPTY, VTS_NONE)
    DISP_FUNCTION_ID(CMSFlexGridSink,"RowColChange",70, OnRowColChangeMsflexgrid,VT_EMPTY, VTS_NONE)
    DISP_FUNCTION_ID(CMSFlexGridSink,"EnterCell",71, OnEnterCellMsflexgrid,VT_EMPTY, VTS_NONE)
    DISP_FUNCTION_ID(CMSFlexGridSink,"LeaveCell",72, OnLeaveCellMsflexgrid,VT_EMPTY, VTS_NONE)
    DISP_FUNCTION_ID(CMSFlexGridSink,"Scroll",73, OnScrollMsflexgrid,VT_EMPTY, VTS_NONE)
    DISP_FUNCTION_ID(CMSFlexGridSink,"Compare",74, OnCompareMsflexgrid,VT_EMPTY, VTS_I4 VTS_I4 VTS_PI2)
    DISP_FUNCTION_ID(CMSFlexGridSink,"OLEStartDrag",1550, OnOLEStartDragMsflexgrid,VT_EMPTY, VTS_PDISPATCH VTS_PI4)
    DISP_FUNCTION_ID(CMSFlexGridSink,"OLEGiveFeedback",1551, OnOLEGiveFeedbackMsflexgrid,VT_EMPTY, VTS_PI4 VTS_PBOOL)
    DISP_FUNCTION_ID(CMSFlexGridSink,"OLESetData",1552, OnOLESetDataMsflexgrid,VT_EMPTY, VTS_PDISPATCH VTS_PI2)
    DISP_FUNCTION_ID(CMSFlexGridSink,"OLECompleteDrag",1553, OnOLECompleteDragMsflexgrid,VT_EMPTY, VTS_PI4)
    DISP_FUNCTION_ID(CMSFlexGridSink,"OLEDragOver",1554, OnOLEDragOverMsflexgrid,VT_EMPTY, VTS_PDISPATCH VTS_PI4 VTS_PI2 VTS_PI2 VTS_PR4 VTS_PR4 VTS_PI2)
    DISP_FUNCTION_ID(CMSFlexGridSink,"OLEDragDrop",1555, OnOLEDragDropMsflexgrid,VT_EMPTY, VTS_PDISPATCH VTS_PI4 VTS_PI2 VTS_PI2 VTS_PR4 VTS_PR4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IMSFlexGridSink to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.
// {023F1A59-24CA-4585-BAD4-F1C8663A8938}
const IID CMSFlexGridSink::IID_IMSFlexGridSink =
{ 0x23f1a59, 0x24ca, 0x4585, { 0xba, 0xd4, 0xf1, 0xc8, 0x66, 0x3a, 0x89, 0x38 } };

BEGIN_INTERFACE_MAP(CMSFlexGridSink, CCmdTarget)
	INTERFACE_PART(CMSFlexGridSink, IID_IMSFlexGridSink, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSFlexGridSink message handlers
void CMSFlexGridSink::OnClickMsflexgrid() 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnClickMsflexgrid();	
}

void CMSFlexGridSink::OnKeyDownMsflexgrid(short FAR* KeyCode, short Shift) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnKeyDownMsflexgrid(KeyCode,Shift);	
}

void CMSFlexGridSink::OnDblClickMsflexgrid() 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnDblClickMsflexgrid();	
}

void CMSFlexGridSink::OnKeyPressMsflexgrid(short FAR* KeyAscii) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnKeyPressMsflexgrid(KeyAscii);	
}

void CMSFlexGridSink::OnKeyUpMsflexgrid(short FAR* KeyCode, short Shift) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnKeyUpMsflexgrid(KeyCode,Shift);	
}

void CMSFlexGridSink::OnMouseDownMsflexgrid(short Button, short Shift, long x, long y) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnMouseDownMsflexgrid(Button,Shift,x,y);	
}

void CMSFlexGridSink::OnMouseMoveMsflexgrid(short Button, short Shift, long x, long y) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnMouseMoveMsflexgrid(Button,Shift,x,y);	
}

void CMSFlexGridSink::OnMouseUpMsflexgrid(short Button, short Shift, long x, long y) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnMouseUpMsflexgrid(Button,Shift,x,y);	
}

void CMSFlexGridSink::OnSelChangeMsflexgrid() 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnSelChangeMsflexgrid();	
}

void CMSFlexGridSink::OnRowColChangeMsflexgrid() 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnRowColChangeMsflexgrid();	
}

void CMSFlexGridSink::OnEnterCellMsflexgrid() 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnEnterCellMsflexgrid();	
}

void CMSFlexGridSink::OnLeaveCellMsflexgrid() 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnLeaveCellMsflexgrid();	
}

void CMSFlexGridSink::OnScrollMsflexgrid() 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnScrollMsflexgrid();	
}

void CMSFlexGridSink::OnCompareMsflexgrid(long Row1, long Row2, short FAR* Cmp) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnCompareMsflexgrid(Row1,Row2,Cmp);	
}

void CMSFlexGridSink::OnOLEStartDragMsflexgrid(LPDISPATCH FAR* Data, long FAR* AllowedEffects) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnOLEStartDragMsflexgrid(Data,AllowedEffects);	
}

void CMSFlexGridSink::OnOLEGiveFeedbackMsflexgrid(long FAR* Effect, BOOL FAR* DefaultCursors) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnOLEGiveFeedbackMsflexgrid(Effect,DefaultCursors);	
}

void CMSFlexGridSink::OnOLESetDataMsflexgrid(LPDISPATCH FAR* Data, short FAR* DataFormat) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnOLESetDataMsflexgrid(Data,DataFormat);	
}

void CMSFlexGridSink::OnOLECompleteDragMsflexgrid(long FAR* Effect) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnOLECompleteDragMsflexgrid(Effect);	
}

void CMSFlexGridSink::OnOLEDragOverMsflexgrid(LPDISPATCH FAR* Data, long FAR* Effect, short FAR* Button, short FAR* Shift, float FAR* x, float FAR* y, short FAR* State) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnOLEDragOverMsflexgrid(Data,Effect,Button,Shift,x,y,State);	
}

void CMSFlexGridSink::OnOLEDragDropMsflexgrid(LPDISPATCH FAR* Data, long FAR* Effect, short FAR* Button, short FAR* Shift, float FAR* x, float FAR* y) 
{
	if (m_ptrGPMSFlex)
		((GPCMSFlexGrid *)m_ptrGPMSFlex)->OnOLEDragDropMsflexgrid(Data,Effect,Button,Shift,x,y);	
}

void CMSFlexGridSink::SetGPMSFlex(void *pt)
{
	m_ptrGPMSFlex=pt;
}

