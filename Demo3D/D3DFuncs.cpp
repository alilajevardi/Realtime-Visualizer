// ================================================================
// Filename: D3DFuncs.cpp
// Description: Misc wrapper and utility functions for D3D
//
//				This source corresponds to 32Bits.co.uk DirectX
//				Basics tutorial 2 part 5 DX 9 Edition.
// ================================================================

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>

#include "D3DFuncs.h"


// =====================================================================================
// Function Name: InitDirect3DDevice
//		 Purpose: Encapsulates the setup of D3D
// =====================================================================================

int InitDirect3DDevice(HWND hWndTarget, D3DCURRENTSETTINGS& d3dcurrentsettings, LPDIRECT3D9 pD3D,
					   LPDIRECT3DDEVICE9* ppDevice)
{
	// PresentParams struct to hold info about the rendering method
	D3DPRESENT_PARAMETERS d3dpp;

	// Struct to hold info about the current display mode
	D3DDISPLAYMODE d3ddm;

	HRESULT rslt=0;

	// If ppDevice is a valid pointer, release it before we continue
	if(*ppDevice)
		(*ppDevice)->Release();

	// Empty out the structure
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	// Get the settings for the current display mode. This gives us hints on how to setup our
	// Present Parameters struct
	rslt=pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	if(FAILED(rslt))
	{
		return E_FAIL;
	}

    

	// Now set up the Present Parameters struct

	// The Width of the back buffer in pixels
	d3dpp.BackBufferWidth=d3dcurrentsettings.m_nDeviceWidth;

	// The height of the back buffer in pixels
	d3dpp.BackBufferHeight=d3dcurrentsettings.m_nDeviceHeight;
	
	// The Format of the backbuffer
	d3dpp.BackBufferFormat = d3dcurrentsettings.m_bWindowed ? d3ddm.Format : d3dcurrentsettings.m_D3DFormat;

	// Handle to render target window
	d3dpp.hDeviceWindow=hWndTarget;
	
	// Window or Fullscreen
	d3dpp.Windowed=d3dcurrentsettings.m_bWindowed;

	// Number of back buffers
	d3dpp.BackBufferCount=1;

	// Swap method
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// Type of multisampling
	if(d3dcurrentsettings.m_bMultiSampling)
	{
		// CheckDeviceMultiSampleType() has gained an additional parameter from DX8. The last param,
		// pQualityLevels, gives us some information about the multisampling. We don't need it, so we
		// can pass NULL for this param.
		if( SUCCEEDED(pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
													   d3dpp.BackBufferFormat, 
													   d3dcurrentsettings.m_bWindowed, 
													   D3DMULTISAMPLE_2_SAMPLES, NULL)))
		{
			d3dpp.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
		}
		else
			d3dpp.MultiSampleType=D3DMULTISAMPLE_NONE;
	}
	else
		d3dpp.MultiSampleType=D3DMULTISAMPLE_NONE;

	// Let D3D manage the depth buffer
	d3dpp.EnableAutoDepthStencil=TRUE;

	// Set the depth buffer format to 16bits
	d3dpp.AutoDepthStencilFormat=D3DFMT_D16;
	
	// Use default refresh rate
	d3dpp.FullScreen_RefreshRateInHz=0;

	// Present the information as fast as possible
	// PresentationInterval used to be named FullScreen_PresentationInterval in DX8, this is only a name change.
	d3dpp.PresentationInterval = d3dcurrentsettings.m_bWindowed ? 0 : D3DPRESENT_INTERVAL_IMMEDIATE;

	// Allow the back buffer to be accessed for 2D work
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// Get a pointer to the IDirect3DDevice9 interface
	// First try to create a device using Hardware vertex processing (fast!). If that fails,
	// fall back to software vertex processing. If that fails, we've got a problem!
	rslt=pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWndTarget,
						 D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, ppDevice);
	if(FAILED(rslt))
	{
		rslt=pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWndTarget,
							    D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, ppDevice);
		if(FAILED(rslt))
		{
			return E_FAIL;
		}
	}

	d3dcurrentsettings.m_PresentParams=d3dpp;
	if(d3dcurrentsettings.m_bWindowed)
		d3dcurrentsettings.m_D3DFormat=d3dpp.BackBufferFormat;
	
	return S_OK;
}


// =====================================================================================
// Function Name: ValidateDevice
//		 Purpose: Ensures we have control of the display adapter in the multitasking
//				  win32 environment.
// =====================================================================================

HRESULT ValidateDevice(LPDIRECT3DDEVICE9& pDevice, LPDIRECT3DSURFACE9& pBackSurface, D3DCURRENTSETTINGS& d3dcurrentsettings)
{
	HRESULT rslt=NULL;

	// Test the current state of the device
	rslt=pDevice->TestCooperativeLevel();
	if(FAILED(rslt))
	{
		// if the device is lost, then return a fail
		if(rslt==D3DERR_DEVICELOST)
			return E_FAIL;

		// if the device is ready to be reset, then try it
		if(rslt==D3DERR_DEVICENOTRESET)
		{
			// Release the back surface so it can be re-created
			if(pBackSurface)
				pBackSurface->Release();
			
			// reset the device
			rslt=pDevice->Reset(&d3dcurrentsettings.m_PresentParams);
			if(FAILED(rslt))
			{
				// If the device was not reset, then exit
				PostQuitMessage(0);
				return E_FAIL;
			}

			// reacquire a pointer to the new back buffer
			// GetBackBuffer takes an extra parameter - parameter 1 is an integer specifying the "swap chain".
			// We're only interested in swap chain 1.
			rslt=pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackSurface);
			if(FAILED(rslt))
			{
				PostQuitMessage(0);
				return E_FAIL;
			}
		}

	}
	return S_OK;
}


// =====================================================================================
// Function Name: D3DError
//		 Purpose: Reports information on failed function calls.
// =====================================================================================


HRESULT D3DError(HRESULT hrCode, int nLine, char* szFile, char* szExtraInfo)
{
	::OutputDebugString("-------------------------------------------32Bits.co.uk Error Handling-\n");
	char pszError[256];
	wsprintf(pszError, "The following error occurred on line %d of %s\n", nLine, szFile);
	::OutputDebugString(pszError);
	::OutputDebugString(DXGetErrorString9(hrCode));
	::OutputDebugString("\n");
	if(szExtraInfo)
	{
		::OutputDebugString("Extra information: ");
		::OutputDebugString(szExtraInfo);
		::OutputDebugString("\n");
	}

	return hrCode;
}