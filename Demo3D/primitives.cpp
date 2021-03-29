// ================================================================
// Filename: Primitives.cpp
// Description: Demonstrates different primitive types
//
//				This source corresponds to 32Bits.co.uk DirectX
//				Basics Series 3 part 2, DirectX 9 Edition.
// ================================================================


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>
#include <mmsystem.h>

#include "D3DFuncs.h"

// Function declarations
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

HRESULT GameInit();
HRESULT GameLoop();
HRESULT GameShutDown(const int);
HRESULT Render();


// Globals
static char strAppname[]="Direct3D Primitives";
LPDIRECT3D9 g_pD3D;
LPDIRECT3DDEVICE9 g_pDevice;
LPDIRECT3DSURFACE9 g_pBackSurface;
HWND g_hWnd;

D3DCURRENTSETTINGS g_D3DSettings;

// Globals specifically for this source

const int no=12;
LPDIRECT3DVERTEXBUFFER9 g_pVBTriFan[no];
LPDIRECT3DINDEXBUFFER9 g_pIBTriFan;


typedef struct _tagSimpleVertex
{
	float		x,y,z;
	//float		rhw;
	D3DCOLOR	dwDiffuse;
} SIMPLEVERTEX;

#define FVF_SIMPLEVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE )

void GenerateVertex(const int, float, float, float, float, int, int, int);
void GenerateIndex(const int ,const int);



//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
	
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize=sizeof(WNDCLASSEX);						// size of the window struct in bytes
	wc.style=CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// window styles to use
	wc.lpfnWndProc=MsgProc;								// function name of event handler
	wc.hInstance=hInstance;								// handle to this apps instance
	wc.hbrBackground=(HBRUSH)GetStockObject(GRAY_BRUSH);// background colour of window
	wc.hIcon= LoadIcon(NULL, IDI_APPLICATION);			// icon for the app window
	wc.hIconSm=LoadIcon(NULL, IDI_APPLICATION);			// icon when minimized to taskbar
	wc.hCursor=LoadCursor(NULL, IDC_ARROW);				// cursor to use for this window
	wc.lpszClassName=strAppname;						// name for this class

    // Register the window class
    RegisterClassEx( &wc );

	g_D3DSettings.m_nDeviceWidth=800;
	g_D3DSettings.m_nDeviceHeight=600;
	//g_D3DSettings.m_fScreenAspect=(float)g_D3DSettings.m_nDeviceWidth / (float)g_D3DSettings.m_nDeviceHeight;

    // Create the application's window
    g_hWnd = CreateWindow(strAppname, strAppname, WS_OVERLAPPEDWINDOW, 10, 10,
						  g_D3DSettings.m_nDeviceWidth, g_D3DSettings.m_nDeviceHeight,
						  NULL, NULL, wc.hInstance, NULL );

	// Show the window
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);
	
	if(FAILED(GameInit()))
	{
		UnregisterClass( strAppname, wc.hInstance );
		return -1;
	}

	// Enter the message loop
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	int count=0;
	while( msg.message!=WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			GameLoop();
		}
	}

	GameShutDown(1);
	UnregisterClass( strAppname, wc.hInstance );
    return 0;
}


//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	HDC hDC;
	PAINTSTRUCT PaintStruct;


    switch( msg )
    {
	case WM_PAINT:
		{
			hDC=BeginPaint(hWnd, &PaintStruct);		// Tell windows we want to update the window

			// Do GDI drawing here

			EndPaint(hWnd, &PaintStruct);
			return 0;
		}
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
				
			case VK_SPACE:
			case VK_ESCAPE:
				{
					PostQuitMessage( 0 );
					return 0;			
				}
			default:	
				return DefWindowProc( hWnd, msg, wParam, lParam );
			}
			return 0;
		}
	
	case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			return 0;
		}
		
	default:	
		return DefWindowProc( hWnd, msg, wParam, lParam );
    }
	
}


// =====================================================================================
//  High level functions for initialization, loop and shutdown
// =====================================================================================

HRESULT GameInit()
{
	HRESULT rslt=0;

	g_pD3D=Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D==NULL)
	{
		return D3DError(E_FAIL, __LINE__, __FILE__, "Failed to create a D3D9 object.");
	}


	// Populate our struct with how we want to set up D3D...
	g_D3DSettings.m_bWindowed=TRUE;
	g_D3DSettings.m_bMultiSampling=FALSE;
	g_D3DSettings.m_D3DFormat=D3DFMT_X8R8G8B8;

	// ...and pass it to our function to create the device!
	rslt=InitDirect3DDevice(g_hWnd, g_D3DSettings, g_pD3D, &g_pDevice);
	if(FAILED(rslt))
	{
		return E_FAIL;
	}


	// ===================================================================================
	// Set up our Projection, View and World transformations
	// ===================================================================================
	
	// Create a matrix to store our Projection transform. Null all the fields.
	D3DXMATRIX matProjection;
	ZeroMemory(&matProjection, sizeof(matProjection));

	// Use D3DX to create a left handed cartesian Field Of View transform
	D3DXMatrixPerspectiveFovLH(&matProjection, D3DX_PI/4, (float)g_D3DSettings.m_nDeviceWidth/(float)g_D3DSettings.m_nDeviceHeight,
							   1.0f, 30.0f);
	
	// Tell D3D to use our Projection matrix for the projection transformation stage
	rslt=g_pDevice->SetTransform(D3DTS_PROJECTION, &matProjection);
	if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Failed to set Projection Transform."); }


	

	// Create a matrix to store our View transform. Null all the fields.
	D3DXMATRIX matView;
	ZeroMemory(&matView, sizeof(matView));

	// Use D3DX to create a Look At matrix from eye, lookat and up vectors.
	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(0.0f, 0.0f, -15.0f),
								 &D3DXVECTOR3(0.0f, 0.0f,  0.0f),
								 &D3DXVECTOR3(0.0f, 1.0f,  0.0f));

	// Tell D3D to use our View matrix for the view transformation stage
	g_pDevice->SetTransform(D3DTS_VIEW, &matView);
	if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Failed to set View Transform."); }




	// Create a matrix to store our World transform
	D3DXMATRIX matWorld, matTemp;
	// Set the matrix to an identity matrix (one that makes no change)
	D3DXMatrixIdentity(&matWorld);

	// Tell D3D to use our World matrix for the world transformation stage
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Failed to set World Transform."); }


	// ===================================================================================
	// Set up our primitives and vertex buffers
	// ===================================================================================

	// Set our culling renderstate
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	// Create 3 arrays, one for our TriList, TriStrip and TriFan

	

	// -TriFan----------------------------------------------------------------->
	
	const int nRings = 50;
	const int nSegments = 50;
	const int VertCont= (nRings+1)*(nSegments+1);
	const int IndexCont= nRings * (nSegments+1)* 2;

	
	
		
		
	
	

	// Top Page
	GenerateVertex( 0, 1, -4, 4, 0, 255, 255, 0);
	GenerateIndex(nRings, nSegments);	

	GenerateVertex( 1, 1, -2, 4, 3.46, 200, 200, 200);
	GenerateVertex( 2, 1, -2, 4, -3.46, 200, 200, 200);
	GenerateVertex( 3, 1, 2, 4, 3.46, 200, 200, 200);
	GenerateVertex( 4, 1, 2, 4, -3.46, 200, 200, 200);
	GenerateVertex( 5, 1, 4, 4, 0, 200, 200, 200);
	
	//Botton Page
	GenerateVertex( 6, 1, -4, -4, 0, 200, 200, 200);
	GenerateVertex( 7, 1, -2, -4, 3.46, 200, 200, 200);
	GenerateVertex( 8, 1, -2, -4, -3.46, 200, 200, 200);
	GenerateVertex( 9, 1, 2, -4, 3.46, 200, 200, 200);
	GenerateVertex( 10, 1, 2, -4, -3.46, 200, 200, 200);
	GenerateVertex( 11, 1, 4, -4, 0, 200, 200, 200);

		

	

/*	float Radial= 1;
	TriFan[0].x=0;
	TriFan[0].y=0;
	TriFan[0].z=0.0f;
	//TriFan[0].rhw=1.0f;
	TriFan[0].dwDiffuse=D3DCOLOR_XRGB(255,255,255);
	TriIndex[0]=0;

	// Programatically generate points on a circle for our TriFan
	for(int nIndex=4; nIndex <= 364; nIndex+=4)
	{
		TriFan[nIndex/4].x=(Radial*((float)cos(D3DXToRadian((float)nIndex))))+TriFan[0].x;
		TriFan[nIndex/4].y=(Radial*((float)sin(D3DXToRadian((float)nIndex))))+TriFan[0].y;
		TriFan[nIndex/4].z=0.0f;
		//TriFan[nIndex/4].rhw=1.0f;
		if (nIndex<=180) 
		TriFan[nIndex/4].dwDiffuse=D3DCOLOR_XRGB(nIndex/2,nIndex/2,nIndex/2);
		else 
		TriFan[nIndex/4].dwDiffuse=D3DCOLOR_XRGB((364-nIndex)/2,(364-nIndex)/2,(364-nIndex)/2);

		TriIndex[nIndex/4]=nIndex/4;
	} */


	

	// Now create a vertex buffer for each primitive array.
	// DX8 coders, remember the additional HANDLE parameter in DX9!

	
	
	


	


	
	
	
	
	


	return S_OK;
}

HRESULT GameLoop()
{
	return Render();
}

HRESULT GameShutDown(const int no)
{
	// Don't forget to release the vertex buffers - they are COM interfaces!
	for (int nno=0; nno< no; nno++)
	{
        if(g_pVBTriFan[nno])
		g_pVBTriFan[nno]->Release();
		
		
	};
	
	if(g_pIBTriFan)
		g_pIBTriFan->Release();
	
	if(g_pBackSurface)
		g_pBackSurface->Release();
	if(g_pDevice)
		g_pDevice->Release();
	if(g_pD3D)
		g_pD3D->Release();
	return S_OK;
}



// =====================================================================================
// Main render function to perform D3D drawing
// =====================================================================================

HRESULT Render()
{
	HRESULT rslt=NULL;
	
	
	// ====================================================================================
	// - Do all the usual checks to make sure we have the right pointers, etc...
	// ====================================================================================

	// Make sure we have a valid D3D Device
	if(!g_pDevice) { return E_FAIL;	}

	// Return if the device is not ready
	rslt=ValidateDevice(g_pDevice, g_pBackSurface, g_D3DSettings);
	if(FAILED(rslt)) { return rslt;	}

	// Clear the back buffer
	g_pDevice->Clear(0,0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,55), 1.0f, 0);

	// Get a pointer to the back buffer (remember, page flipping has taken place)
	rslt=g_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_pBackSurface);
	if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Failed to get the back buffer."); }




	D3DXMATRIX matXRotation, matYRotation, matZRotation, matWorld, pWorldMatrix;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&pWorldMatrix, -1.0f, 1.0f, 0.0f);
	D3DXMatrixMultiply(&matWorld, &matWorld, &pWorldMatrix);


	rslt=g_pDevice->BeginScene();
	if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "BeginScene() failed."); }

	// ====================================================================================
	// - Do our drawing operations
	// ====================================================================================

	// Do some nice rotations using the world transform

	

	D3DXMatrixRotationX(&matXRotation, timeGetTime()/5250.0f);
	D3DXMatrixRotationY(&matYRotation, timeGetTime()/1500.0f);
	D3DXMatrixRotationZ(&matZRotation, timeGetTime()/1500.0f);
	D3DXMatrixMultiply(&matWorld, &matWorld,&matXRotation);
	D3DXMatrixMultiply(&matWorld, &matWorld,&matYRotation);
	              // D3DXMatrixMultiply(&matWorld, &matXRotation, &matYRotation);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matZRotation);
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	
	// Tell D3D we want to use our custom FVF define.
	// DX8 coders, remember DX9 uses SetFVF instead of SetVertexShader().
	g_pDevice->SetFVF(FVF_SIMPLEVERTEX);
	// Tell D3D we want to use our TriFan VB as the "source stream"	
	

	// And finally tell D3D to draw our fan!
	//g_pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 90);
	
	for (int dno=0; dno< no; dno++)
	{
        g_pDevice->SetStreamSource(0, g_pVBTriFan[dno], 0, sizeof(SIMPLEVERTEX));
        
       // g_pDevice->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0,0, 2601, 0, 5100);
		g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0, 2601, 0, 5100);
	};

	
	
	

	// ====================================================================================
	// - Clean up and present the back buffer to be page flipped
	// ====================================================================================

	g_pDevice->EndScene();
	g_pBackSurface->Release();

	// Present the back buffer to the display adapter to be drawn
	g_pDevice->Present(NULL, NULL, NULL, NULL);


	return S_OK;
}
void GenerateVertex(const int no, float Radial, float xo, float yo, float zo, int Red, int Green, int Blue )
{
    	const int VertCont=2601;
		int nRings0 = 50;
		int nSegments0 = 50;
		int j = 0;
		SIMPLEVERTEX TriFan0[VertCont];
		

		float Teta = (D3DX_PI / nRings0);
		float Phi = (2.0f * D3DX_PI / nSegments0);


		for(int nCurrentRing = 0; nCurrentRing < nRings0 + 1; nCurrentRing++)
		{
			float r0 = Radial* sinf(nCurrentRing * Teta);
			float y0 = yo+ Radial* cosf(nCurrentRing * Teta);

			//Generate the group of segments for the current ring
			for(int nCurrentSegment = 0; nCurrentSegment < nSegments0 + 1; nCurrentSegment++)
			{
				float x0 = xo+ r0 * sinf(nCurrentSegment * Phi);
				float z0 = zo+ r0 * cosf(nCurrentSegment * Phi);

	          
				//Add one vertex to the strip which makes up the sphere
	            
				TriFan0[j].x = x0;
				TriFan0[j].y = y0;
				TriFan0[j].z = z0;
				
				//TriFan0[j].dwDiffuse = D3DCOLOR_XRGB(Red, Green, Blue);
				 TriFan0[j].dwDiffuse = D3DCOLOR_XRGB(int (Red* (1.0f - sinf(nCurrentRing * Teta/3))),
													int (Green*(1.0f - sinf(nCurrentRing * Teta/3))),
													int (Blue*(1.0f - sinf(nCurrentRing * Teta/3)))); 
				j++;

			}
		}
		
		g_pDevice->CreateVertexBuffer(sizeof(TriFan0), 0, FVF_SIMPLEVERTEX, D3DPOOL_DEFAULT,
																					   &g_pVBTriFan[no], NULL);
		//if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "TriFan CreateVertexBuffer() failed."); }
	
		
		BYTE* pVerticeLock=0;
		g_pVBTriFan[no]->Lock(0, sizeof(TriFan0), (void**)&pVerticeLock, 0);
		//if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Failed to lock TriFan Vertex Buffer."); }

		// ...wash...
		CopyMemory(pVerticeLock, &TriFan0, sizeof(TriFan0));

		// ...and repeat.
		g_pVBTriFan[no]->Unlock();
		

		//return TriFan0[2601];
	}

void GenerateIndex(const int nRings, const int nSegments)
{
	int wVertexIndex = 0;
	int i = 0;
	const int IndexCont=5100;
	WORD TriIndex0[IndexCont];
	
	for(int nCurrentRing = 0; nCurrentRing < nRings + 1; nCurrentRing++)
    {
		for(int nCurrentSegment = 0; nCurrentSegment < nSegments + 1; nCurrentSegment++)
        {
			 //Add two indices except for the last ring 
           if(nCurrentRing != nRings) 
           {
                TriIndex0[i] = wVertexIndex; 
                i++;
                
                TriIndex0[i] = wVertexIndex + (nSegments + 1); 
                i++;
                
                wVertexIndex++; 
           }
		}
	}
	g_pDevice->CreateIndexBuffer(sizeof(WORD)* IndexCont , 0, D3DFMT_INDEX16 , D3DPOOL_DEFAULT,
																						&g_pIBTriFan, NULL);
	//if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "TriFan CreateIndexBuffer() failed."); }
	
		
	BYTE* pIndicesLock =NULL;
	g_pIBTriFan->Lock(0, sizeof(TriIndex0), (void**)&pIndicesLock, 0);
	//if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Failed to lock TriFan Index Buffer."); }

	// ...wash...
	CopyMemory(pIndicesLock, &TriIndex0,sizeof(WORD)* IndexCont);

	// ...and repeat.
	g_pIBTriFan->Unlock();
	g_pDevice->SetIndices(g_pIBTriFan);
	//return TriIndex0[5100];
}