// ================================================================
// Filename: D3DFuncs.h
// Description: Header file for D3DFuncs.cpp - general purpose
//				D3D functions.
//
//				This source corresponds to 32Bits.co.uk DirectX
//				Basics tutorial 2 part 5 DX 9 Edition.
// ================================================================

#ifndef _D3DFUNCS_H
#define _D3DFUNCS_H

typedef struct _D3DCurrentSettings
{
	int m_nDeviceHeight;
	int m_nDeviceWidth;
	//float m_fScreenAspect;
	BOOL m_bWindowed;
	BOOL m_bMultiSampling;
	D3DFORMAT m_D3DFormat;
	D3DPRESENT_PARAMETERS m_PresentParams;
} D3DCURRENTSETTINGS;


// Function Declarations

int InitDirect3DDevice(HWND hWndTarget, D3DCURRENTSETTINGS& d3dcurrentsettings, LPDIRECT3D9 pD3D, 
					   LPDIRECT3DDEVICE9* ppDevice);
HRESULT ValidateDevice(LPDIRECT3DDEVICE9& pDevice, LPDIRECT3DSURFACE9& pBackSurface,
					   D3DCURRENTSETTINGS& d3dcurrentsettings);

HRESULT D3DError(HRESULT hrCode, int nLine, char* szFile, char* szExtraInfo=NULL);


#endif //_D3DFUNCS_H

