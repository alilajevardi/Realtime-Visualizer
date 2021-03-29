#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

IDirect3D9* pD3D9 = NULL;
IDirect3DDevice9* pD3DDevice9 = NULL;
IDirect3DVertexBuffer9* pVertexBuffer = NULL; // Buffer to hold vertices


struct CustomVertex
{
    float x, y, z, rhw ; // The transformed position for the vertex.
    DWORD colour; // The vertex colour.
};

#define D3DFVF_CustomVertex D3DFVF_XYZRHW|D3DFVF_DIFFUSE
//const DWORD D3DFVF_CustomVertex= (D3DFVF_XYZ|D3DFVF_DIFFUSE);

#define SafeRelease(pObject) if(pObject != NULL) {pObject->Release(); pObject=NULL;}

HRESULT InitialiseD3D(HWND hWnd,int width, int height, bool fullscreen)
{
    //First of all, create the main D3D object. If it is created successfully we 
    //should get a pointer to an IDirect3D8 interface.
    pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
    if(pD3D9 == NULL)
    {
        return E_FAIL;
    }

    //Get the current display mode
    D3DDISPLAYMODE d3ddm;
    if(FAILED(pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        return E_FAIL;
    }

    //Create a structure to hold the settings for our device
   	// set the presentation parameters
	D3DPRESENT_PARAMETERS d3dpp; // ={0};
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	//d3dpp.BackBufferWidth = width;
	//d3dpp.BackBufferHeight = height;
	//d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.Windowed = !fullscreen;
	//d3dpp.EnableAutoDepthStencil = true;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	//d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	
	
    //Create a Direct3D device.
    if(FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
                                   D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice9)))
    {
        return E_FAIL;
    }
    
    return S_OK;
	//pD3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//pD3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE);

	//pD3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
}

HRESULT InitialiseVertexBuffer()
{
   void* pVertices;
    
    //Store each point of the triangle together with it's colour
    CustomVertex cvVertices[] =
    {
        {250.0f, 100.0f, 0.5f, 1.0f ,D3DCOLOR_ARGB(255, 255, 0, 0),}, //Vertex 1 - Red (250, 100)
        {400.0f, 350.0f, 0.5f, 1.0f ,D3DCOLOR_ARGB(255, 0, 255, 0),}, //Vertex 2 - Green (400, 350)
        {100.0f, 350.0f, 0.5f, 1.0f ,D3DCOLOR_ARGB(255, 0, 0, 255),}, //Vertex 3 - Blue (100, 350)
    };


   
	
	
	//Create the vertex buffer from our device
    if(FAILED(pD3DDevice9->CreateVertexBuffer(3 * sizeof(CustomVertex),
                                               0, D3DFVF_CustomVertex,
                                               D3DPOOL_MANAGED,&pVertexBuffer,NULL)))
    {
        return E_FAIL;
    }
	
    
	
	//Get a pointer to the vertex buffer vertices and lock the vertex buffer
    if(FAILED(pVertexBuffer->Lock(0,0, (void**)&pVertices, D3DLOCK_DISCARD)))
    {
        return E_FAIL;
    }

    //Copy our stored vertices values into the vertex buffer
    memcpy(pVertices, cvVertices, sizeof(cvVertices));

    //Unlock the vertex buffer
    pVertexBuffer->Unlock();

    return S_OK;
}

void Render()
{
    if(pD3DDevice9 == NULL)
    {
        return;
    }

    //Clear the backbuffer to black
    pD3DDevice9->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
    
    //Begin the scene
    pD3DDevice9->BeginScene();
    

    //Rendering our triangle
                                                
	pD3DDevice9->SetStreamSource(0, pVertexBuffer, 0,sizeof(CustomVertex));
	
	pD3DDevice9->SetFVF(D3DFVF_CustomVertex);
	
	
	
   pD3DDevice9->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);


    //End the scene
    pD3DDevice9->EndScene();
    
    //Filp the back and front buffers so that whatever has been rendered on the back buffer
    //will now be visible on screen (front buffer).
    pD3DDevice9->Present(NULL, NULL, NULL, NULL);
}

void CleanUp()
{
    SafeRelease(pVertexBuffer);
    SafeRelease(pD3DDevice9);
    SafeRelease(pD3D9);
}

void GameLoop()
{
    //Enter the game loop
    MSG msg; 
    BOOL fMessage;

    PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);
    
    while(msg.message != WM_QUIT)
    {
        fMessage = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE);

        if(fMessage)
        {
            //Process message
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //No message to process, so render the current scene
            Render();
        }

    }
}

//The windows message handler
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        break;
        case WM_KEYUP: 
            switch (wParam)
            { 
                case VK_ESCAPE:
                    //User has pressed the escape key, so quit
                    DestroyWindow(hWnd);
                    return 0;
                break;
            } 
        break;

    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

//Application entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    
	WNDCLASSEX windowClass;		// window class
	HWND hWND = NULL;

	// fill out the window class structure
	windowClass.cbSize		= sizeof(WNDCLASSEX);
	windowClass.style			= CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc		= WindowProc;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.hInstance		= hInstance;
	windowClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);			
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);	
	windowClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	windowClass.lpszMenuName	= NULL;						
	windowClass.lpszClassName	= "window";
	windowClass.hIconSm		= LoadIcon(NULL, IDI_WINLOGO);	

	// register the windows class
	if (!RegisterClassEx(&windowClass))
		return 0;
		

	hWND = CreateWindowEx(NULL, "window", "Simple Direct3D Program by: Lajevardipour",
	WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		50, 50, 500, 500,
 		NULL, NULL, hInstance,	 NULL);	

	// check if window creation failed (hwnd would equal NULL)
	if (!hWND)
		return 0;
		
	if (SUCCEEDED(InitialiseD3D(hWND, 800, 600, false)))
	{
		ShowWindow(hWND, SW_SHOWDEFAULT);
		UpdateWindow(hWND);
		if(SUCCEEDED(InitialiseVertexBuffer()))
        {
            //Start game running: Enter the game loop
            GameLoop();
        }
	}
		
	CleanUp();
	UnregisterClass("window", hInstance);
	return 0;
}