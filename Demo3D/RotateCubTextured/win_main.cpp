#include <windows.h>
#include <stdlib.h>
#include "d3d_obj.h"
#include "vector.h"

// Add the following libraries
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define class_name "GT_D3DRotatingCube"

// Width and height of the window (specifically the client rect)
const int kWinWid = 640;
const int kWinHgt = 480;

// Our 8 cube vertices, half blue and half green
SVertex gCubeVerts[] =
{
	{ -1.0f, -1.0f, -1.0f, D3DCOLOR_RGBA(0, 0, 200, 255),0,1 }, 
	{ -1.0f, 1.0f, -1.0f, D3DCOLOR_RGBA(0, 0, 200, 255),0,0}, 
	{ 1.0f, -1.0f, -1.0f, D3DCOLOR_RGBA(0, 0, 200, 255),1,1 }, 
	{ 1.0f, 1.0f, -1.0f, D3DCOLOR_RGBA(0, 0, 200, 255),1,0 }, 
	{ 1.0f, -1.0f, 1.0f, D3DCOLOR_RGBA(0, 200, 0, 255),1,1 }, 
	{ 1.0f, 1.0f, 1.0f, D3DCOLOR_RGBA(0, 200, 0, 255),1,0 },
	{ -1.0f, -1.0f, 1.0f, D3DCOLOR_RGBA(0, 200, 0, 255),0,1 }, 
	{ -1.0f, 1.0f, 1.0f, D3DCOLOR_RGBA(0, 200, 0, 255),0,0 }
};

// Our cube indices
WORD gCubeIndices[36] = {0, 1, 2, // Triangle 1
						 2, 1, 3, // Triangle 2
						 2, 3, 4, // Triangle 3
						 4, 3, 5, // Triangle 4
						 4, 5, 6, // Triangle 5
						 6, 5, 7, // Triangle 6
						 6, 7, 0, // Triangle 7
						 0, 7, 1, // Triangle 8
						 1, 7, 3, // Triangle 9
						 3, 7, 5, // Triangle 10
						 0, 2, 6, // Triangle 11
						 2, 4, 6}; // Triangle 12

void DrawAndRotateCube(); 

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprev, PSTR cmdline, int ishow)
{
    HWND hwnd;
	MSG msg;
    WNDCLASSEX wndclassex = {0};

	// Init fields we care about
	wndclassex.cbSize = sizeof(WNDCLASSEX); 
    wndclassex.style = CS_HREDRAW | CS_VREDRAW;
    wndclassex.lpfnWndProc = WinProc;
    wndclassex.hInstance = hinstance;
    wndclassex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassex.lpszClassName = class_name;
	wndclassex.hCursor = (HCURSOR)LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);

    RegisterClassEx(&wndclassex);

	RECT rect = { 0, 0, kWinWid, kWinHgt }; // Desired window client rect
	
	DWORD winStyleEx = WS_EX_CLIENTEDGE;
	DWORD winStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME;

	
	AdjustWindowRectEx(&rect, winStyle, false, winStyleEx);

    hwnd = CreateWindowEx(winStyleEx, // Window extended style
					      class_name,
						  "Alireza Lajevardipour -- Rotating Textured Cube",
						  winStyle, // Window style
						  CW_USEDEFAULT,
						  CW_USEDEFAULT,
						  rect.right - rect.left,
						  rect.bottom - rect.top,
						  NULL,
						  NULL,
						  hinstance,
						  NULL);

	// Init our global 3D object
	if(g3D->init(hwnd) == false)
		return EXIT_FAILURE; // There's been an error, lets get out of this joint

	
	GetClientRect(hwnd, &rect);
	assert(rect.right == kWinWid && rect.bottom == kWinHgt);

	
	g3D->setProjMatrix();

	ShowWindow(hwnd, ishow);
	UpdateWindow(hwnd);

    while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;
			
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			g3D->setViewMatrix(gCamera);
			DrawAndRotateCube();
		}
	
	} // end of while(1)

	UnregisterClass(class_name,hinstance); // Free up WNDCLASSEX
	    return EXIT_SUCCESS; // Application was a success
}

// WinProc
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch(message)
    {
		case WM_KEYDOWN:

			switch(wparam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
						break;

				case VK_UP: 
					gCamera->moveForward();
						break;

				case VK_DOWN: 
					gCamera->moveBack();
						break;

				case VK_RIGHT: 
					gCamera->moveRight();
						break;

				case VK_LEFT: 
					gCamera->moveLeft();
						break;
			}
			
			return 0;

		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
				return 0;
    }

    return DefWindowProc(hwnd, message, wparam, lparam);
}

// Draws and rotates our cube
void DrawAndRotateCube()
{
	D3DXMATRIXA16 matrix;
	static float angle = 0; // The angle of rotation

	g3D->begin(); // Begin the scene
	g3D->clear(); // Clear the viewport
	

	angle=1+angle;
	float angInRad = DEG2RAD(angle);
	
	
	D3DXMatrixRotationYawPitchRoll(&matrix, angInRad, angInRad+1.1f,angInRad);
	

	g3D->setWorldMatrix(&matrix);

	
	g3D->render(gCubeVerts, 8, gCubeIndices, 36);

	g3D->end(); 
}

/*----------------------------*\
|  Alireza Lajevardipour       |
|  1383/10/10                  |
|  © 2004-2005 Lajevardi       |
\*----------------------------*/
