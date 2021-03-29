#include <d3dx9.h>

IDirect3D9* g_pD3D = NULL;
IDirect3DDevice9* g_pD3DDevice = NULL;
IDirect3DVertexBuffer9* g_pVertexBuffer = NULL; // Buffer to hold vertices

struct CUSTOMVERTEX
{
    FLOAT x, y, z; 
    DWORD colour;
};

#define D3DFVF_CUSTOMVERTEX D3DFVF_XYZ|D3DFVF_DIFFUSE


#define SafeRelease(pObject) if(pObject != NULL) {pObject->Release(); pObject=NULL;}

HRESULT InitialiseD3D(HWND hWnd)
{
    //First of all, create the main D3D object. If it is created successfully we 
    //should get a pointer to an IDirect3D8 interface.
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if(g_pD3D == NULL)
    {
        return E_FAIL;
    }

    //Get the current display mode
    D3DDISPLAYMODE d3ddm;
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        return E_FAIL;
    }

    //Create a structure to hold the settings for our device
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    //Fill the structure. 
    //We want our program to be windowed, and set the back buffer to a format
    //that matches our current display mode
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    //Create a Direct3D device.
    if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
                                   D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
    {
        return E_FAIL;
    }
    
    //Turn on back face culling. This is becuase we want to hide the back of our polygons
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

    //Turn off lighting becuase we are specifying that our vertices have colour
    g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    return S_OK;
}

HRESULT InitialiseVertexBuffer()
{
    VOID* pVertices;
    
    //Store each point of the cube together with it's colour
    //Make sure that the points of a polygon are specified in a clockwise direction,
    //this is because anti-clockwise faces will be culled
    //We will use a three triangle strips to render these polygons (Top, Sides, Bottom).
    CUSTOMVERTEX cvVertices[] =
    { 
        //Top Face
        {-5.0f, 5.0f, -5.0f, D3DCOLOR_XRGB(0, 0, 255),}, //Vertex 0 - Blue 
        {-5.0f, 5.0f, 5.0f, D3DCOLOR_XRGB(255, 0, 0),}, //Vertex 1 - Red 
        {5.0f, 5.0f, -5.0f, D3DCOLOR_XRGB(255, 0, 0),}, //Vertex 2 - Red 
        {5.0f, 5.0f, 5.0f, D3DCOLOR_XRGB(0, 255, 0),}, //Vertex 3 - Green 

        //Face 1
        {-5.0f, -5.0f, -5.0f, D3DCOLOR_XRGB(255, 0, 0),}, //Vertex 4 - Red 
        {-5.0f, 5.0f, -5.0f, D3DCOLOR_XRGB(0, 0, 255),}, //Vertex 5 - Blue 
        {5.0f, -5.0f, -5.0f, D3DCOLOR_XRGB(0, 255, 0),}, //Vertex 6 - Green 
        {5.0f, 5.0f, -5.0f, D3DCOLOR_XRGB(255, 0, 0),}, //Vertex 7 - Red 

        //Face 2
        {5.0f, -5.0f, 5.0f, D3DCOLOR_XRGB(0, 0, 255),}, //Vertex 8 - Blue 
        {5.0f, 5.0f, 5.0f, D3DCOLOR_XRGB(0, 255, 0),}, //Vertex 9 - Green
        
        //Face 3
        {-5.0f, -5.0f, 5.0f, D3DCOLOR_XRGB(0, 255, 0),}, //Vertex 10 - Green 
        {-5.0f, 5.0f, 5.0f, D3DCOLOR_XRGB(255, 0, 0),}, //Vertex 11 - Red 

        //Face 4
        {-5.0f, -5.0f, -5.0f, D3DCOLOR_XRGB(255, 0, 0),}, //Vertex 12 - Red 
        {-5.0f, 5.0f, -5.0f, D3DCOLOR_XRGB(0, 0, 255),}, //Vertex 13 - Blue

        //Bottom Face
        {5.0f, -5.0f, -5.0f, D3DCOLOR_XRGB(0, 255, 0),}, //Vertex 14 - Green 
        {5.0f, -5.0f, 5.0f, D3DCOLOR_XRGB(0, 0, 255),}, //Vertex 15 - Blue 
        {-5.0f, -5.0f, -5.0f, D3DCOLOR_XRGB(255, 0, 0),}, //Vertex 16 - Red 
        {-5.0f, -5.0f, 5.0f, D3DCOLOR_XRGB(0, 255, 0),}, //Vertex 17 - Green
    };

    //Create the vertex buffer from our device.
    if(FAILED(g_pD3DDevice->CreateVertexBuffer(18 * sizeof(CUSTOMVERTEX),
                                               0, D3DFVF_CUSTOMVERTEX,
                                               D3DPOOL_DEFAULT, &g_pVertexBuffer,NULL)))
    {
        return E_FAIL;
    }


    //Get a pointer to the vertex buffer vertices and lock the vertex buffer
    if(FAILED(g_pVertexBuffer->Lock(0, sizeof(cvVertices), (void**)&pVertices, 0)))
    {
        return E_FAIL;
    }

    //Copy our stored vertices values into the vertex buffer
    memcpy(pVertices, cvVertices, sizeof(cvVertices));

    //Unlock the vertex buffer
    g_pVertexBuffer->Unlock();

    return S_OK;
}


void SetupRotation()
{
    //Here we will rotate our world around the x, y and z axis.
    D3DXMATRIX matWorld, matWorldX, matWorldY, matWorldZ;
    
    //Create the transformation matrices
    D3DXMatrixRotationX(&matWorldX, timeGetTime()/400.0f);
    D3DXMatrixRotationY(&matWorldY, timeGetTime()/400.0f); 
    D3DXMatrixRotationZ(&matWorldZ, timeGetTime()/400.0f); 

    //Combine the transformations by multiplying them together
    D3DXMatrixMultiply(&matWorld, &matWorldX, &matWorldY);
    D3DXMatrixMultiply(&matWorld, &matWorld, &matWorldZ);

    //Apply the tansformation
    g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
}

void SetupCamera()
{
    //Here we will setup the camera.
    //The camera has three settings: "Camera Position", "Look at Position" and "Up Direction"
    //We have set the following:
    //Camera Position: (0, 0, -30)
    //Look at Position: (0, 0, 0)
    //Up direction: Y-Axis.
    D3DXMATRIX matView;
    D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(0.0f, 0.0f,-30.0f), //Camera Position
                                 &D3DXVECTOR3(0.0f, 0.0f, 0.0f), //Look At Position
                                 &D3DXVECTOR3(0.0f, 1.0f, 0.0f)); //Up Direction
    g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void SetupPerspective()
{
    //Here we specify the field of view, aspect ration and near and far clipping planes.
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.0f, 1.0f, 500.0f);
    g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}


void Render()
{
    if(g_pD3DDevice == NULL)
    {
        return;
    }

    //Clear the backbuffer to black
    g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    
    //Begin the scene
    g_pD3DDevice->BeginScene();
    
    //Setup the rotation, camera, and perspective matrices
    SetupRotation();
    SetupCamera();
    SetupPerspective();


    //Rendering our objects
    g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer,0, sizeof(CUSTOMVERTEX));
    g_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	//g_pD3DDevice->SetVertexShader(D3DFVF_CUSTOMVERTEX);
    g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //Top
    g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 8); //Sides
    g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 14, 2); //Bottom

    //End the scene
    g_pD3DDevice->EndScene();
    
    //Filp the back and front buffers so that whatever has been rendered on the back buffer
    //will now be visible on screen (front buffer).
    g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CleanUp()
{
    SafeRelease(g_pVertexBuffer);
    SafeRelease(g_pD3DDevice);
    SafeRelease(g_pD3D);
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
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
    //Register the window class
    WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_CLASSDC, WinProc, 0L, 0L, 
                     GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                     "DX Project 3", NULL};
    RegisterClassEx(&wc);

    //Create the application's window
    HWND hWnd = CreateWindow("DX Project 3", "Simple Direct3D Program by: Lajevardipour", 
                              WS_OVERLAPPEDWINDOW, 50, 50, 500, 500,
                              GetDesktopWindow(), NULL, wc.hInstance, NULL);

    //Initialize Direct3D
    if(SUCCEEDED(InitialiseD3D(hWnd)))
    { 
        //Show our window
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);

        //Initialize Vertex Buffer
        if(SUCCEEDED(InitialiseVertexBuffer()))
        {
            //Start game running: Enter the game loop
            GameLoop();
        }
    }
    
    CleanUp();

    UnregisterClass("DX Project 3", wc.hInstance);
    
    return 0;
}
