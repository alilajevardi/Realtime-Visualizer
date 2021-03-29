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
static char strAppname[]="Direct3D C60    By:Alireza Lajevardipour";
LPDIRECT3D9 g_pD3D;
LPDIRECT3DDEVICE9 g_pDevice;
LPDIRECT3DSURFACE9 g_pBackSurface;
HWND g_hWnd;

D3DCURRENTSETTINGS g_D3DSettings;

// Globals specifically for this source

const int no=90;
LPDIRECT3DVERTEXBUFFER9 g_pVBTriFan[no];
LPDIRECT3DINDEXBUFFER9 g_pIBTriFan;
LPDIRECT3DVERTEXBUFFER9 g_pVBCylinder[no];



typedef struct _tagSimpleVertex
{
	float		x,y,z;
	//float		rhw;
	D3DCOLOR	dwDiffuse;
} SIMPLEVERTEX;

#define FVF_SIMPLEVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE )

void GenerateVertex(const int, float, float, float, float, int, int, int);
void GenerateIndex(const int ,const int);
void GenerateCylinder(const int, float, float, float, float, float, float, float, int, int, int);



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
							   1.0f, 50.0f);
	
	// Tell D3D to use our Projection matrix for the projection transformation stage
	rslt=g_pDevice->SetTransform(D3DTS_PROJECTION, &matProjection);
	if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Failed to set Projection Transform."); }


	

	// Create a matrix to store our View transform. Null all the fields.
	D3DXMATRIX matView;
	ZeroMemory(&matView, sizeof(matView));

	// Use D3DX to create a Look At matrix from eye, lookat and up vectors.
	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(0.0f, 0.0f, -30.0f),
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
	/* const int VertCont= (nRings+1)*(nSegments+1);
	   const int IndexCont= nRings * (nSegments+1)* 2; */

	
	int Red =155;
	int Green= 250;
	int Blue= 230;
	float Radial=0.9;
	
	int CRed =200;
	int CGreen= 255;
	int CBlue= 200;
	float CRadial=0.2;
	
	// Top Page
	GenerateIndex(nRings, nSegments);
	
	GenerateVertex( 0 , Radial,      0,      0,      0, Red, Green, Blue);
	GenerateVertex( 1 , Radial,  1.464,      0,      0, Red, Green, Blue);
	GenerateVertex( 2 , Radial,  1.916,  1.392,      0, Red, Green, Blue);
	GenerateVertex( 3 , Radial,  0.732,  2.253,      0, Red, Green, Blue);
	GenerateVertex( 4 , Radial, -0.452,  1.392,      0, Red, Green, Blue);
	
	GenerateVertex( 5 , Radial, -1.573,  1.756,  0.728, Red, Green, Blue);
	GenerateVertex( 6 , Radial, -0.692, -0.953,  0.728, Red, Green, Blue);
	GenerateVertex( 7 , Radial,  2.156, -0.953,  0.728, Red, Green, Blue);
	GenerateVertex( 8 , Radial,  3.036,  1.756,  0.728, Red, Green, Blue);
	GenerateVertex( 9 , Radial,  0.732,  3.431,  0.728, Red, Green, Blue);
	
	GenerateVertex( 10, Radial,  3.341, -0.568,  1.498, Red, Green, Blue);
	GenerateVertex( 11, Radial,  3.768,  0.749,  1.498, Red, Green, Blue);
	GenerateVertex( 12, Radial,  3.036,  3.001,  1.498, Red, Green, Blue);
	GenerateVertex( 13, Radial,  1.916,  3.815,  1.498, Red, Green, Blue);
	GenerateVertex( 14, Radial, -0.452,  3.815,  1.498, Red, Green, Blue);
	GenerateVertex( 15, Radial, -1.573,  3.002,  1.498, Red, Green, Blue);
	GenerateVertex( 16, Radial, -2.305,  0.749,  1.498, Red, Green, Blue);
	GenerateVertex( 17, Radial, -1.877, -0.568,  1.498, Red, Green, Blue);
	GenerateVertex( 18, Radial,  0.040, -1.960,  1.498, Red, Green, Blue);
	GenerateVertex( 19, Radial,  1.424, -1.960,  1.498, Red, Green, Blue);
	
	GenerateVertex( 20, Radial, -0.692, -2.198,  2.743, Red, Green, Blue);
	GenerateVertex( 21, Radial, -1.877, -1.338,  2.743, Red, Green, Blue);
	GenerateVertex( 22, Radial,  2.156, -2.198,  2.743, Red, Green, Blue);
	GenerateVertex( 23, Radial,  3.341, -1.338,  2.743, Red, Green, Blue);
	GenerateVertex( 24, Radial,  4.221,  1.371,  2.743, Red, Green, Blue);
	GenerateVertex( 25, Radial,  3.768,  2.764,  2.743, Red, Green, Blue);
	GenerateVertex( 26, Radial,  1.464,  4.438,  2.743, Red, Green, Blue);
	GenerateVertex( 27, Radial,      0,  4.438,  2.743, Red, Green, Blue);
	GenerateVertex( 28, Radial, -2.305,  2.764,  2.743, Red, Green, Blue);
	GenerateVertex( 29, Radial, -2.757,  1.371,  2.743, Red, Green, Blue);
	
	GenerateVertex( 30, Radial,      0, -2.423,  3.921, Red, Green, Blue);
	GenerateVertex( 31, Radial,  1.464, -2.423,  3.921, Red, Green, Blue);
	GenerateVertex( 32, Radial,  3.768, -0.749,  3.921, Red, Green, Blue);
	GenerateVertex( 33, Radial,  4.221,  0.643,  3.921, Red, Green, Blue);
	GenerateVertex( 34, Radial,  3.341,  3.353,  3.921, Red, Green, Blue);
	GenerateVertex( 35, Radial,  2.156,  4.213,  3.921, Red, Green, Blue);
	GenerateVertex( 36, Radial, -1.877,  3.353,  3.921, Red, Green, Blue);
	GenerateVertex( 37, Radial, -0.692,  4.213,  3.921, Red, Green, Blue);
	GenerateVertex( 38, Radial, -2.305, -0.749,  3.921, Red, Green, Blue);
	GenerateVertex( 39, Radial, -2.757,  0.643,  3.921, Red, Green, Blue);
	
	GenerateVertex( 40, Radial,  1.916, -1.801,  5.166, Red, Green, Blue);
	GenerateVertex( 41, Radial,  3.036, -0.987,  5.166, Red, Green, Blue);
	GenerateVertex( 42, Radial, -1.573, -0.987,  5.166, Red, Green, Blue);
	GenerateVertex( 43, Radial, -0.452, -1.801,  5.166, Red, Green, Blue);
	GenerateVertex( 44, Radial, -2.305,  1.266,  5.166, Red, Green, Blue);
	GenerateVertex( 45, Radial, -1.877,  2.583,  5.166, Red, Green, Blue);
	GenerateVertex( 46, Radial,   0.04,  3.975,  5.166, Red, Green, Blue);
	GenerateVertex( 47, Radial,  1.424,  3.975,  5.166, Red, Green, Blue);
	GenerateVertex( 48, Radial,  3.768,  1.266,  5.166, Red, Green, Blue);
	GenerateVertex( 49, Radial,  3.341,  2.583,  5.166, Red, Green, Blue);

	GenerateVertex( 50, Radial,  0.732, -1.416,  5.936, Red, Green, Blue);
	GenerateVertex( 51, Radial, -1.573,  0.259,  5.936, Red, Green, Blue);
	GenerateVertex( 52, Radial, -0.692,  2.968,  5.936, Red, Green, Blue);
	GenerateVertex( 53, Radial,  2.156,  2.968,  5.936, Red, Green, Blue);
	GenerateVertex( 54, Radial,  3.036,  0.259,  5.936, Red, Green, Blue);

	GenerateVertex( 55, Radial,      0,  2.015,  6.664, Red, Green, Blue);
	GenerateVertex( 56, Radial,  1.464,  2.015,  6.664, Red, Green, Blue);
	GenerateVertex( 57, Radial,  1.916,  0.623,  6.664, Red, Green, Blue);
	GenerateVertex( 58, Radial,  0.732, -0.238,  6.664, Red, Green, Blue);
	GenerateVertex( 59, Radial, -0.452,  0.623,  6.664, Red, Green, Blue);
	
	
	
	
	//Top Cylinder
	GenerateCylinder(0 , CRadial,      0,      0,      0,  1.464,      0,      0, CRed, CGreen, CBlue);
	GenerateCylinder(1 , CRadial,      0,      0,      0, -0.452,  1.392,      0, CRed, CGreen, CBlue);
	GenerateCylinder(2 , CRadial,      0,      0,      0, -0.692, -0.953,  0.728, CRed, CGreen, CBlue);
	
	GenerateCylinder(3 , CRadial,  1.464,      0,      0,  1.916,  1.392,      0, CRed, CGreen, CBlue);
	GenerateCylinder(4 , CRadial,  1.464,      0,      0,  2.156, -0.953,  0.728, CRed, CGreen, CBlue);

	GenerateCylinder(5 , CRadial,  1.916,  1.392,      0,  0.732,  2.253,      0, CRed, CGreen, CBlue);
	GenerateCylinder(6 , CRadial,  1.916,  1.392,      0,  3.036,  1.756,  0.728, CRed, CGreen, CBlue);
	
	GenerateCylinder(7 , CRadial,  0.732,  2.253,      0, -0.452,  1.392,      0, CRed, CGreen, CBlue);
	GenerateCylinder(8 , CRadial,  0.732,  2.253,      0,  0.732,  3.431,  0.728, CRed, CGreen, CBlue);

	GenerateCylinder(9 , CRadial, -0.452,  1.392,      0, -1.573,  1.756,  0.728, CRed, CGreen, CBlue);

	GenerateCylinder(10, CRadial, -1.573,  1.756,  0.728, -1.573,  3.002,  1.498, CRed, CGreen, CBlue);
	GenerateCylinder(11, CRadial, -1.573,  1.756,  0.728, -2.305,  0.749,  1.498, CRed, CGreen, CBlue);
	
	GenerateCylinder(12, CRadial, -0.692, -0.953,  0.728, -1.877, -0.568,  1.498, CRed, CGreen, CBlue);
	GenerateCylinder(13, CRadial, -0.692, -0.953,  0.728,  0.040, -1.960,  1.498, CRed, CGreen, CBlue);

	GenerateCylinder(14, CRadial,  2.156, -0.953,  0.728,  3.341, -0.568,  1.498, CRed, CGreen, CBlue);
	GenerateCylinder(15, CRadial,  2.156, -0.953,  0.728,  1.424, -1.960,  1.498, CRed, CGreen, CBlue);

	GenerateCylinder(16, CRadial,  3.036,  1.756,  0.728,  3.768,  0.749,  1.498, CRed, CGreen, CBlue);
	GenerateCylinder(17, CRadial,  3.036,  1.756,  0.728,  3.036,  3.001,  1.498, CRed, CGreen, CBlue);
	
	GenerateCylinder(18, CRadial,  0.732,  3.431,  0.728,  1.916,  3.815,  1.498, CRed, CGreen, CBlue);
	GenerateCylinder(19, CRadial,  0.732,  3.431,  0.728, -0.452,  3.815,  1.498, CRed, CGreen, CBlue);

	GenerateCylinder(20, CRadial,  3.341, -0.568,  1.498,  3.768,  0.749,  1.498, CRed, CGreen, CBlue);
	GenerateCylinder(21, CRadial,  3.341, -0.568,  1.498,  3.341, -1.338,  2.743, CRed, CGreen, CBlue);
	
	GenerateCylinder(22, CRadial,  3.768,  0.749,  1.498, 4.221,  1.371,  2.743, CRed, CGreen, CBlue);
	
	GenerateCylinder(23, CRadial,  3.036,  3.001,  1.498,  1.916,  3.815,  1.498, CRed, CGreen, CBlue);
	GenerateCylinder(24, CRadial,  3.036,  3.001,  1.498,  3.768,  2.764,  2.743, CRed, CGreen, CBlue);

	GenerateCylinder(25, CRadial,  1.916,  3.815,  1.498,  1.464,  4.438,  2.743, CRed, CGreen, CBlue);

	GenerateCylinder(26, CRadial, -0.452,  3.815,  1.498, -1.573,  3.002,  1.498, CRed, CGreen, CBlue);
	GenerateCylinder(27, CRadial, -0.452,  3.815,  1.498,      0,  4.438,  2.743, CRed, CGreen, CBlue);
		
	GenerateCylinder(28, CRadial, -1.573,  3.002,  1.498, -2.305,  2.764,  2.743, CRed, CGreen, CBlue);

	GenerateCylinder(29, CRadial, -2.305,  0.749,  1.498, -1.877, -0.568,  1.498, CRed, CGreen, CBlue);
	GenerateCylinder(30, CRadial, -2.305,  0.749,  1.498, -2.757,  1.371,  2.743, CRed, CGreen, CBlue);
	
	GenerateCylinder(31, CRadial, -1.877, -0.568,  1.498, -1.877, -1.338,  2.743, CRed, CGreen, CBlue);

	GenerateCylinder(32, CRadial,  0.040, -1.960,  1.498,  1.424, -1.960,  1.498, CRed, CGreen, CBlue);
	GenerateCylinder(33, CRadial,  0.040, -1.960,  1.498, -0.692, -2.198,  2.743, CRed, CGreen, CBlue);

	GenerateCylinder(34, CRadial,  1.424, -1.960,  1.498,  2.156, -2.198,  2.743, CRed, CGreen, CBlue);

	GenerateCylinder(35, CRadial, -0.692, -2.198,  2.743, -1.877, -1.338,  2.743, CRed, CGreen, CBlue);
	GenerateCylinder(36, CRadial, -0.692, -2.198,  2.743,      0, -2.423,  3.921, CRed, CGreen, CBlue);

	GenerateCylinder(37, CRadial, -1.877, -1.338,  2.743, -2.305, -0.749,  3.921, CRed, CGreen, CBlue);

	GenerateCylinder(38, CRadial,  2.156, -2.198,  2.743,  3.341, -1.338,  2.743, CRed, CGreen, CBlue);
	GenerateCylinder(39, CRadial,  2.156, -2.198,  2.743,  1.464, -2.423,  3.921, CRed, CGreen, CBlue);

	GenerateCylinder(40, CRadial,  3.341, -1.338,  2.743,  3.768, -0.749,  3.921, CRed, CGreen, CBlue);

	GenerateCylinder(41, CRadial,  4.221,  1.371,  2.743,  3.768,  2.764,  2.743, CRed, CGreen, CBlue);
	GenerateCylinder(42, CRadial,  4.221,  1.371,  2.743,  4.221,  0.643,  3.921, CRed, CGreen, CBlue);

	GenerateCylinder(43, CRadial,  3.768,  2.764,  2.743,  3.341,  3.353,  3.921, CRed, CGreen, CBlue);

	GenerateCylinder(44, CRadial,  1.464,  4.438,  2.743,      0,  4.438,  2.743, CRed, CGreen, CBlue);
	GenerateCylinder(45, CRadial,  1.464,  4.438,  2.743,  2.156,  4.213,  3.921, CRed, CGreen, CBlue);

	GenerateCylinder(46, CRadial,      0,  4.438,  2.743, -0.692,  4.213,  3.921, CRed, CGreen, CBlue);

	GenerateCylinder(47, CRadial, -2.305,  2.764,  2.743, -2.757,  1.371,  2.743, CRed, CGreen, CBlue);
	GenerateCylinder(48, CRadial, -2.305,  2.764,  2.743, -1.877,  3.353,  3.921, CRed, CGreen, CBlue);

	GenerateCylinder(49, CRadial, -2.757,  1.371,  2.743, -2.757,  0.643,  3.921, CRed, CGreen, CBlue);

	GenerateCylinder(50, CRadial,      0, -2.423,  3.921,  1.464, -2.423,  3.921, CRed, CGreen, CBlue);
	GenerateCylinder(51, CRadial,      0, -2.423,  3.921, -0.452, -1.801,  5.166, CRed, CGreen, CBlue);

	GenerateCylinder(52, CRadial,  1.464, -2.423,  3.921,  1.916, -1.801,  5.166, CRed, CGreen, CBlue);

/*32-33*/	GenerateCylinder(53, CRadial,  3.768, -0.749,  3.921,  4.221,  0.643,  3.921, CRed, CGreen, CBlue);
/*32-41*/	GenerateCylinder(54, CRadial,  3.768, -0.749,  3.921,  3.036, -0.987,  5.166, CRed, CGreen, CBlue);

/*33-48*/	GenerateCylinder(55, CRadial,  4.221,  0.643,  3.921,  3.768,  1.266,  5.166, CRed, CGreen, CBlue);

/*34-35*/	GenerateCylinder(56, CRadial,  3.341,  3.353,  3.921,  2.156,  4.213,  3.921, CRed, CGreen, CBlue);
/*34-49*/	GenerateCylinder(57, CRadial,  3.341,  3.353,  3.921,  3.341,  2.583,  5.166, CRed, CGreen, CBlue);

/*35-47*/	GenerateCylinder(58, CRadial,  2.156,  4.213,  3.921,  1.424,  3.975,  5.166, CRed, CGreen, CBlue);

/*36-37*/	GenerateCylinder(59, CRadial, -1.877,  3.353,  3.921, -0.692,  4.213,  3.921, CRed, CGreen, CBlue);
/*36-45*/	GenerateCylinder(60, CRadial, -1.877,  3.353,  3.921, -1.877,  2.583,  5.166, CRed, CGreen, CBlue);

/*37-46*/	GenerateCylinder(61, CRadial, -0.692,  4.213,  3.921,   0.04,  3.975,  5.166, CRed, CGreen, CBlue);

/*38-39*/	GenerateCylinder(62, CRadial, -2.305, -0.749,  3.921, -2.757,  0.643,  3.921, CRed, CGreen, CBlue);
/*38-42*/	GenerateCylinder(63, CRadial, -2.305, -0.749,  3.921, -1.573, -0.987,  5.166, CRed, CGreen, CBlue);

/*39-44*/	GenerateCylinder(64, CRadial, -2.757,  0.643,  3.921, -2.305,  1.266,  5.166, CRed, CGreen, CBlue);

/*40-41*/	GenerateCylinder(65, CRadial,  1.916, -1.801,  5.166,  3.036, -0.987,  5.166, CRed, CGreen, CBlue);
/*40-50*/	GenerateCylinder(66, CRadial,  1.916, -1.801,  5.166,  0.732, -1.416,  5.936, CRed, CGreen, CBlue);

/*41-54*/	GenerateCylinder(67, CRadial,  3.036, -0.987,  5.166,  3.036,  0.259,  5.936, CRed, CGreen, CBlue);

/*42-43*/	GenerateCylinder(68, CRadial, -1.573, -0.987,  5.166, -0.452, -1.801,  5.166, CRed, CGreen, CBlue);
/*42-51*/	GenerateCylinder(69, CRadial, -1.573, -0.987,  5.166, -1.573,  0.259,  5.936, CRed, CGreen, CBlue);

/*43-50*/	GenerateCylinder(70, CRadial, -0.452, -1.801,  5.166,  0.732, -1.416,  5.936, CRed, CGreen, CBlue);

/*44-45*/	GenerateCylinder(71, CRadial, -2.305,  1.266,  5.166, -1.877,  2.583,  5.166, CRed, CGreen, CBlue);
/*44-51*/	GenerateCylinder(72, CRadial, -2.305,  1.266,  5.166, -1.573,  0.259,  5.936, CRed, CGreen, CBlue);

/*45-52*/	GenerateCylinder(73, CRadial, -1.877,  2.583,  5.166, -0.692,  2.968,  5.936, CRed, CGreen, CBlue);

/*46-47*/	GenerateCylinder(74, CRadial,   0.04,  3.975,  5.166,  1.424,  3.975,  5.166, CRed, CGreen, CBlue);
/*46-52*/	GenerateCylinder(75, CRadial,   0.04,  3.975,  5.166, -0.692,  2.968,  5.936, CRed, CGreen, CBlue);

/*47-53*/	GenerateCylinder(76, CRadial,  1.424,  3.975,  5.166,  2.156,  2.968,  5.936, CRed, CGreen, CBlue);

/*48-49*/	GenerateCylinder(77, CRadial,  3.768,  1.266,  5.166,  3.341,  2.583,  5.166, CRed, CGreen, CBlue);
/*48-54*/	GenerateCylinder(78, CRadial,  3.768,  1.266,  5.166,  3.036,  0.259,  5.936, CRed, CGreen, CBlue);

/*49-53*/	GenerateCylinder(79, CRadial,  3.341,  2.583,  5.166,  2.156,  2.968,  5.936, CRed, CGreen, CBlue);

/*50-58*/	GenerateCylinder(80, CRadial,  0.732, -1.416,  5.936,  0.732, -0.238,  6.664, CRed, CGreen, CBlue);

/*51-59*/	GenerateCylinder(81, CRadial, -1.573,  0.259,  5.936, -0.452,  0.623,  6.664, CRed, CGreen, CBlue);

/*52-55*/	GenerateCylinder(82, CRadial, -0.692,  2.968,  5.936,      0,  2.015,  6.664, CRed, CGreen, CBlue);

/*53-56*/	GenerateCylinder(83, CRadial,  2.156,  2.968,  5.936,  1.464,  2.015,  6.664, CRed, CGreen, CBlue);

/*54-57*/	GenerateCylinder(84, CRadial,  3.036,  0.259,  5.936,  1.916,  0.623,  6.664, CRed, CGreen, CBlue);

/*55-56*/	GenerateCylinder(85, CRadial,      0,  2.015,  6.664,  1.464,  2.015,  6.664, CRed, CGreen, CBlue);
/*55-59*/	GenerateCylinder(86, CRadial,      0,  2.015,  6.664, -0.452,  0.623,  6.664, CRed, CGreen, CBlue);

/*56-57*/	GenerateCylinder(87, CRadial,  1.464,  2.015,  6.664,  1.916,  0.623,  6.664, CRed, CGreen, CBlue);

/*57-58*/	GenerateCylinder(88, CRadial,  1.916,  0.623,  6.664,  0.732, -0.238,  6.664, CRed, CGreen, CBlue);

/*58-59*/	GenerateCylinder(89, CRadial,  0.732, -0.238,  6.664, -0.452,  0.623,  6.664, CRed, CGreen, CBlue);

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

	for (int nno=0; nno< no; nno++)
	{
        	if(g_pVBCylinder[nno])
            g_pVBCylinder[nno]->Release();
	}
	
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
	D3DXMatrixRotationZ(&matZRotation, timeGetTime()/3500.0f);
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
        
        //g_pDevice->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0,0, 2601, 0, 5100);
		g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0, 2601, 0, 5100);
	};

	for (int dno=0; dno< no; dno++)
	{
        g_pDevice->SetStreamSource(0, g_pVBCylinder[dno], 0, sizeof(SIMPLEVERTEX));
        //g_pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 102);
		g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 102);
	}
	
	
	

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
			float y0 = yo*2+ Radial* cosf(nCurrentRing * Teta);

			//Generate the group of segments for the current ring
			for(int nCurrentSegment = 0; nCurrentSegment < nSegments0 + 1; nCurrentSegment++)
			{
				float x0 = xo*2+ r0 * sinf(nCurrentSegment * Phi);
				float z0 = zo*2+ r0 * cosf(nCurrentSegment * Phi);

	          
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

void GenerateCylinder(const int Cno, float CRadial, float O1x, float O1y, float O1z, float O2x, float O2y, float O2z, int Red, int Green, int Blue)
{
	SIMPLEVERTEX Cylinder[104];
	const int mSegments = 50;
			
	float a = (O2x-O1x)*2;
	float b = (O2y-O1y)*2;
	float c = (O2z-O1z)*2;
	float CLength=sqrt(powf(a,2)+powf(b,2)+powf(c,2));

	
	float Phi = (2.0f * D3DX_PI / mSegments);
	int k=0;

	if (c==0){
		 for(int mCurrentSegments = 0; mCurrentSegments <= mSegments +1 ; mCurrentSegments++)
		{
			
			float x0 = O1x*2- (b/sqrt(powf(a,2)+powf(b,2)))* CRadial *cosf(mCurrentSegments* Phi); 
			float y0 = O1y*2+ (a/sqrt(powf(a,2)+powf(b,2)))* CRadial *cosf(mCurrentSegments* Phi);
			float z0 = O1z*2+ CRadial*sinf(mCurrentSegments* Phi);
	          
				//Add one vertex to the strip which makes up the sphere
	            
				Cylinder[k].x = x0;
				Cylinder[k].y = y0;
				Cylinder[k].z = z0;
				Cylinder[k].dwDiffuse = D3DCOLOR_XRGB(5, 255, 5);
				/* Cylinder[k].dwDiffuse = D3DCOLOR_XRGB(int (Red* (1.0f - sinf(nCurrentRing * Teta/3))),
													int (Green*(1.0f - sinf(nCurrentRing * Teta/3))),
													int (Blue*(1.0f - sinf(nCurrentRing * Teta/3)))); */
				k++;
				
			float y1 = y0 - O1y*2 + O2y*2;
			float x1 = x0 - O1x*2 + O2x*2;
			float z1 = z0 - O1z*2 + O2z*2;
			
				Cylinder[k].x = x1;
				Cylinder[k].y = y1;
				Cylinder[k].z = z1;
				Cylinder[k].dwDiffuse = D3DCOLOR_XRGB(255, 255, 255);
				/* Cylinder[k].dwDiffuse = D3DCOLOR_XRGB(int (Red* (1.0f - sinf(nCurrentRing * Teta/3))),
													int (Green*(1.0f - sinf(nCurrentRing * Teta/3))),
													int (Blue*(1.0f - sinf(nCurrentRing * Teta/3)))); */
				k++;
			
		}
	}
	
	else{
        for(int mCurrentSegments = 0; mCurrentSegments <= mSegments/2 ; mCurrentSegments++)
		{
			
			float x0 = O1x*2 +(c/sqrt(powf(a,2)+powf(c,2)))* CRadial *cosf(mCurrentSegments* Phi); 
			
			float Delta =(powf(a*b,2)/(powf(c,2)*(powf(a,2)+powf(c,2))))* powf(CRadial*cosf(mCurrentSegments* Phi),2)+ 4*((powf(b,2)+powf(c,2))/powf(c,2))* powf(CRadial*sinf(mCurrentSegments* Phi),2);
			float y0 = O1y*2+ (-a*b/(c*(powf(a,2)+powf(c,2)))+ sqrt(Delta))/(2*(powf(b,2)+powf(c,2))/powf(c,2));
			float z0 = O1z*2- a/c * (x0-O1x*2)- b/c * (y0-O1y*2);
	          
				//Add one vertex to the strip which makes up the sphere
	            
				Cylinder[k].x = x0;
				Cylinder[k].y = y0;
				Cylinder[k].z = z0;
				Cylinder[k].dwDiffuse = D3DCOLOR_XRGB(5, 255, 5);
				/* Cylinder[k].dwDiffuse = D3DCOLOR_XRGB(int (Red* (1.0f - sinf(nCurrentRing * Teta/3))),
													int (Green*(1.0f - sinf(nCurrentRing * Teta/3))),
													int (Blue*(1.0f - sinf(nCurrentRing * Teta/3)))); */
				k++;
				
			float y1 = y0 - O1y*2 + O2y*2;
			float x1 = x0 - O1x*2 + O2x*2;
			float z1 = z0 - O1z*2 + O2z*2;
			
				Cylinder[k].x = x1;
				Cylinder[k].y = y1;
				Cylinder[k].z = z1;
				Cylinder[k].dwDiffuse = D3DCOLOR_XRGB(255, 255, 255);
				/* Cylinder[k].dwDiffuse = D3DCOLOR_XRGB(int (Red* (1.0f - sinf(nCurrentRing * Teta/3))),
													int (Green*(1.0f - sinf(nCurrentRing * Teta/3))),
													int (Blue*(1.0f - sinf(nCurrentRing * Teta/3)))); */
				k++;
			
		};
	for(int mCurrentSegments = mSegments/2 ; mCurrentSegments >=0 ; mCurrentSegments--)
		{
			
			float x0 = O1x*2 +(c/sqrt(powf(a,2)+powf(c,2)))* CRadial *cosf(mCurrentSegments* Phi); 
			
			float Delta =(powf(a*b,2)/(powf(c,2)*(powf(a,2)+powf(c,2))))* powf(CRadial*cosf(mCurrentSegments* Phi),2)+ 4*((powf(b,2)+powf(c,2))/powf(c,2))* powf(CRadial*sinf(mCurrentSegments* Phi),2);
			float y0 = O1y*2+ (-a*b/(c*(powf(a,2)+powf(c,2)))- sqrt(Delta))/(2*(powf(b,2)+powf(c,2))/powf(c,2));
			float z0 = O1z*2- a/c * (x0-O1x*2)- b/c * (y0-O1y*2);
	          
				//Add one vertex to the strip which makes up the sphere
	            
				Cylinder[k].x = x0;
				Cylinder[k].y = y0;
				Cylinder[k].z = z0;
				Cylinder[k].dwDiffuse = D3DCOLOR_XRGB(5, 255, 5);
				/* Cylinder[k].dwDiffuse = D3DCOLOR_XRGB(int (Red* (1.0f - sinf(nCurrentRing * Teta/3))),
													int (Green*(1.0f - sinf(nCurrentRing * Teta/3))),
													int (Blue*(1.0f - sinf(nCurrentRing * Teta/3)))); */
				k++;
				
			float y1 = y0 - O1y*2 + O2y*2;
			float x1 = x0 - O1x*2 + O2x*2;
			float z1 = z0 - O1z*2 + O2z*2;
			
				Cylinder[k].x = x1;
				Cylinder[k].y = y1;
				Cylinder[k].z = z1;
				Cylinder[k].dwDiffuse = D3DCOLOR_XRGB(255, 255, 255);
				/* Cylinder[k].dwDiffuse = D3DCOLOR_XRGB(int (Red* (1.0f - sinf(nCurrentRing * Teta/3))),
													int (Green*(1.0f - sinf(nCurrentRing * Teta/3))),
													int (Blue*(1.0f - sinf(nCurrentRing * Teta/3)))); */
				k++;
			
		}
		};
			
		g_pDevice->CreateVertexBuffer(sizeof(Cylinder), 0, FVF_SIMPLEVERTEX, D3DPOOL_DEFAULT,
																					   &g_pVBCylinder[Cno], NULL);
		//if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "TriFan CreateVertexBuffer() failed."); }
	
		
		BYTE* pVerticeLockCy=0;
		g_pVBCylinder[Cno]->Lock(0, sizeof(Cylinder), (void**)&pVerticeLockCy, 0);
		//if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Failed to lock TriFan Vertex Buffer."); }

		// ...wash...
		CopyMemory(pVerticeLockCy, &Cylinder, sizeof(Cylinder));

		// ...and repeat.
		g_pVBCylinder[Cno]->Unlock();
		
}

