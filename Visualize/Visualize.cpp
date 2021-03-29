// C60DLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Visualize.h"
// ================================================================
// Filename: C60.cpp
// Description: C60 construction
// By: Alireza Lajevardipour
// ================================================================


HINSTANCE GhInstance;
WNDCLASSEX wc;
int APIENTRY DllFunction (HINSTANCE, double [],double [],double [], int [], int [], int [], double [], int No, char []);




BOOL APIENTRY DllMain( HINSTANCE hInstance,DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    
switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
			GhInstance = hInstance;
	
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

			g_D3DSettings.m_nDeviceWidth=500;
			g_D3DSettings.m_nDeviceHeight=500;
			//g_D3DSettings.m_fScreenAspect=(float)g_D3DSettings.m_nDeviceWidth / (float)g_D3DSettings.m_nDeviceHeight;

			// Create the application's window
			g_hWnd = CreateWindow(strAppname, strAppname,WS_OVERLAPPEDWINDOW  , 300, 100,
								g_D3DSettings.m_nDeviceWidth, g_D3DSettings.m_nDeviceHeight,
								NULL, NULL, wc.hInstance, NULL ); //WS_OVERLAPPEDWINDOW

			// Show the window
			ShowWindow(g_hWnd, SW_SHOW);
			UpdateWindow(g_hWnd);

			if(FAILED(GameInit()))
			{
				UnregisterClass( strAppname, wc.hInstance );
				return -1;
			};


	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		/*GameShutDown(Sno, 2);
		UnregisterClass( strAppname, wc.hInstance );*/
		break;
	}

	
	return TRUE;
}

int APIENTRY DllFunction (HINSTANCE hInstance, double X[],double Y[],double Z[], int Red[], int Green[], int Blue[], double Radial[], int No, char string[])
{
	GameShutDown(No, 1);

	// -Sphere----------------------------------------------------------------->
	for(int i=0; i<No; i++)
	{
		
		GenerateVertex( i , Radial[i],  X[i],  Y[i],   Z[i], Red[i], Green[i], Blue[i]);
	};

	
	
	// Enter the message loop
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	int count=0;
	GameLoop(No,string);
	
	//while( msg.message!=WM_QUIT )
	//{
	//  if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE )== false )
	//	{
	//		TranslateMessage( &msg );
	//		DispatchMessage( &msg );
	//	}
	//  else
	//	{
	//		GameLoop(No,string);
	//	}
	//}

	if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ))
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
			if (msg.message == WM_QUIT)
			{
				GameShutDown(Sno, 2);
				UnregisterClass( strAppname, wc.hInstance );
				
			}
		}
		

	
	return 1;
}








//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------

/*int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
   
    return 0;
}*/


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
				
			//case VK_SPACE:
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
							   2.0f, 20.0f);
	
	// Tell D3D to use our Projection matrix for the projection transformation stage
	rslt=g_pDevice->SetTransform(D3DTS_PROJECTION, &matProjection);
	if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Failed to set Projection Transform."); }


	

	// Create a matrix to store our View transform. Null all the fields.
	D3DXMATRIX matView;
	ZeroMemory(&matView, sizeof(matView));

	// Use D3DX to create a Look At matrix from eye, lookat and up vectors.
	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(0.0f, 0.0f, -12.0f),
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
	g_pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	//Create Sphere Index
	GenerateIndex();

	//Create Font
	D3DXCreateFont(g_pDevice, 18, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		ANTIALIASED_QUALITY, DEFAULT_PITCH|FF_DONTCARE, "Arial", &g_Font);


	
	return S_OK;
}

HRESULT GameLoop(int No, char string [])
{
	
	return Render(No, string);
}


HRESULT GameShutDown(const int Pno, int Reason)
{
	// Don't forget to release the vertex buffers - they are COM interfaces!
	
	switch (Reason)
	{
		case 1:
            for (int nno=0; nno< Pno; nno++)
				{
					if(g_pVBSphere[nno])
						g_pVBSphere[nno]->Release();	
				};
			break;

		case 2:
			for (int nno=0; nno< Pno; nno++)
				{
					if(g_pVBSphere[nno])
					g_pVBSphere[nno]->Release();	
				};
					
			if(g_pIBSphere)
				g_pIBSphere->Release();

            if(g_pBackSurface)
				g_pBackSurface->Release();
            if(g_pDevice)
				g_pDevice->Release();
            if(g_pD3D)
				g_pD3D->Release();
			break;
	}
	return S_OK;
}



// =====================================================================================
// Main render function to perform D3D drawing
// =====================================================================================

HRESULT Render(int No, char string [])
{
	HRESULT rslt=NULL;
	
    RECT font_rect={0,0,g_D3DSettings.m_nDeviceWidth,g_D3DSettings.m_nDeviceHeight};
	
	// ====================================================================================
	// - Do all the usual checks to make sure we have the right pointers, etc...
	// ====================================================================================

	// Make sure we have a valid D3D Device
	if(!g_pDevice) { return E_FAIL;	}

	// Return if the device is not ready
	rslt=ValidateDevice(g_pDevice, g_pBackSurface, g_D3DSettings);
	if(FAILED(rslt)) { return rslt;	}

	// Clear the back buffer
	g_pDevice->Clear(0,0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);

	// Get a pointer to the back buffer (remember, page flipping has taken place)
	rslt=g_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_pBackSurface);
	if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Failed to get the back buffer."); }




	D3DXMATRIX matWorld;//, pWorldMatrix;

	D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixTranslation(&pWorldMatrix, -1.0f, 1.0f, 0.0f);
	//D3DXMatrixMultiply(&matWorld, &matWorld, &pWorldMatrix);


	rslt=g_pDevice->BeginScene();
	if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "BeginScene() failed."); }

	// ====================================================================================
	// - Do our drawing operations
	// ====================================================================================

	
	g_Font->DrawText(NULL,        //pSprite
                     string,   //pString
                     -1,          //Count
                     &font_rect,  //pRect
                     DT_LEFT|DT_NOCLIP,//Format,
                     D3DCOLOR_XRGB(0,255,0)); //Color
	
	
	// Do some nice rotations using the world transform

	

	//D3DXMatrixRotationX(&matXRotation, timeGetTime()/5250.0f);
	//D3DXMatrixRotationY(&matYRotation, timeGetTime()/1500.0f);
	//D3DXMatrixRotationZ(&matZRotation, timeGetTime()/3500.0f);
	//D3DXMatrixMultiply(&matWorld, &matWorld,&matXRotation);
	//D3DXMatrixMultiply(&matWorld, &matWorld,&matYRotation);
	              // D3DXMatrixMultiply(&matWorld, &matXRotation, &matYRotation);
	//D3DXMatrixMultiply(&matWorld, &matWorld, &matZRotation);
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	
	// Tell D3D we want to use our custom FVF define.
	// DX8 coders, remember DX9 uses SetFVF instead of SetVertexShader().
	g_pDevice->SetFVF(FVF_SIMPLEVERTEX);
	// Tell D3D we want to use our Sphere VB as the "source stream"	
	

	// And finally tell D3D to draw our fan!
	//g_pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 90);
	
	for (int dno=0; dno< No; dno++)
	{
        g_pDevice->SetStreamSource(0, g_pVBSphere[dno], 0, sizeof(SIMPLEVERTEX));
        
        //g_pDevice->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0,0, 961, 0, 1860);
		g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0, VertCont, 0, IndexCont);

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
void GenerateVertex(const int no, double Radial, double xo, double yo, double zo, int Red, int Green, int Blue )
{
  		int j = 0;
		SIMPLEVERTEX Sphere0[VertCont];
		
		double Teta = (D3DX_PI / nRings);
		double Phi = (2.0f * D3DX_PI / nSegments);

		for(int nCurrentRing = 0; nCurrentRing < nRings + 1; nCurrentRing++)
		{
			double r0 = Radial* sin(nCurrentRing * Teta);
			double y0 = yo+ Radial* cos(nCurrentRing * Teta); 

			//Generate the group of segments for the current ring
			for(int nCurrentSegment = 0; nCurrentSegment < nSegments + 1; nCurrentSegment++)
			{
				double x0 = xo+ r0 * sin(nCurrentSegment * Phi); 
				double z0 = zo+ r0 * cos(nCurrentSegment * Phi); 

	          
				//Add one vertex to the strip which makes up the sphere
	            
				Sphere0[j].x = x0;
				Sphere0[j].y = y0; 
				Sphere0[j].z = -z0;// Right handed coordinate
				
				//Sphere0[j].dwDiffuse = D3DCOLOR_XRGB(Red, Green, Blue);
				 Sphere0[j].dwDiffuse = D3DCOLOR_XRGB(int (Red* ( cos(nCurrentRing * Teta/2))),
													int (Green*( cos(nCurrentRing * Teta/2))),
													int (Blue*( cos(nCurrentRing * Teta/2)))); 
				j++;
			}
		}
		
		g_pDevice->CreateVertexBuffer(sizeof(Sphere0), 0, FVF_SIMPLEVERTEX, D3DPOOL_MANAGED ,
																					   &g_pVBSphere[no], NULL);
		//if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Sphere CreateVertexBuffer() failed."); }
	
		
		BYTE* pVerticeLock=0;
		g_pVBSphere[no]->Lock(0, sizeof(Sphere0), (void**)&pVerticeLock, 0);
		//if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Failed to lock Sphere Vertex Buffer."); }

		// ...wash...
		CopyMemory(pVerticeLock, &Sphere0, sizeof(Sphere0));

		// ...and repeat.
		g_pVBSphere[no]->Unlock();
		

		//return Sphere0[2601];
	}

void GenerateIndex()
{
	int wVertexIndex = 0;
	int i = 0;
		
	WORD SphereIndex0[IndexCont];
	
	for(int nCurrentRing = 0; nCurrentRing < nRings + 1; nCurrentRing++)
    {
		for(int nCurrentSegment = 0; nCurrentSegment < nSegments + 1; nCurrentSegment++)
        {
			 //Add two indices except for the last ring 
           if(nCurrentRing != nRings) 
           {
                SphereIndex0[i] = wVertexIndex; 
                i++;
                
                SphereIndex0[i] = wVertexIndex + (nSegments + 1); 
                i++;
                
                wVertexIndex++; 
           }
		}
	}
	g_pDevice->CreateIndexBuffer(sizeof(WORD)* IndexCont , 0, D3DFMT_INDEX16 , D3DPOOL_DEFAULT,
																						&g_pIBSphere, NULL);
	//if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Sphere CreateIndexBuffer() failed."); }
	
		
	BYTE* pIndicesLock =NULL;
	g_pIBSphere->Lock(0, sizeof(SphereIndex0), (void**)&pIndicesLock, 0);
	//if(FAILED(rslt)) { return D3DError(rslt, __LINE__, __FILE__, "Failed to lock Sphere Index Buffer."); }

	// ...wash...
	CopyMemory(pIndicesLock, &SphereIndex0,sizeof(WORD)* IndexCont);

	// ...and repeat.
	g_pIBSphere->Unlock();
	g_pDevice->SetIndices(g_pIBSphere);
}


int _stdcall GraphRun(double XCoordinate[],double YCoordinate[],double ZCoordinate[], int Red[], int Green[], int Blue[], double Radial[], int No, char string[]) 
{
	DllFunction (GhInstance, XCoordinate, YCoordinate, ZCoordinate, Red, Green, Blue, Radial, No, string);
	return 991;
}
int _stdcall EndDll(int No) 
{
	
	GameShutDown(No, 2);
	UnregisterClass( strAppname, wc.hInstance );
	//CloseWindow(g_hWnd);
	//DestroyWindow(g_hWnd);

	return 1;
}
int _stdcall View(void) 
{
	return -1;
}