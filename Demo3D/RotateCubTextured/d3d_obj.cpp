#include "d3d_obj.h"

CD3DObj::CD3DObj()
{
	d3d_interface = NULL;
	d3d_device = NULL;

	// Set data to zero
	fov = aspect_ratio = near_clip = far_clip = 0.0f;
}


bool CD3DObj::init(HWND hwnd)
{
	
	d3d_interface = Direct3DCreate9(D3D_SDK_VERSION);

		// Error Check
		if(d3d_interface == NULL)
			return false;

	
	D3DPRESENT_PARAMETERS params = {0}; // Start by zeroing out the parameters
    
	// Set the parameters we care about
	params.Windowed = TRUE; // The app will be windowed
	params.SwapEffect = D3DSWAPEFFECT_DISCARD; 					  
    params.BackBufferFormat = D3DFMT_UNKNOWN; 

	params.EnableAutoDepthStencil = true; 

	params.AutoDepthStencilFormat = D3DFMT_D16; 

	
	


	HRESULT result = d3d_interface->CreateDevice(D3DADAPTER_DEFAULT,
												 D3DDEVTYPE_HAL,
												 hwnd,
												 D3DCREATE_HARDWARE_VERTEXPROCESSING,
												 &params,
												 &d3d_device);

	

	if(result != D3D_OK)
	{
		result = d3d_interface->CreateDevice(D3DADAPTER_DEFAULT,
											 D3DDEVTYPE_HAL,
											 hwnd,
											 D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											 &params,
											 &d3d_device);
		if(result != D3D_OK)
			return false; // Couldn't create a D3D 9.0 device
	}

	if(FAILED(D3DXCreateTextureFromFile( d3d_device, "TextureAli.jpg", &pTexture))){
		return false;
	}

	d3d_device ->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	
	// Turn off D3D lighting, since we are providing our own vertex colors
    d3d_device->SetRenderState(D3DRS_LIGHTING, FALSE);


    d3d_device->SetRenderState(D3DRS_ZENABLE, TRUE);
		
	RECT rect;
	GetClientRect(hwnd, &rect); // Get the client rect

	
	aspect_ratio = (float)rect.right / (float)rect.bottom;

	
	initToDefaultParams();
		return true; // We got loaded!
}

// Init all applicable parameters to a default value
void CD3DObj::initToDefaultParams()
{
	fov = kFOV; // Field of View
	near_clip = kNearClip; // Near Clip Plane
	far_clip = kFarClip; // Far Clip Plane
}

// Begins the scene
void CD3DObj::begin()
{
	// This begins our scene.
	HRESULT result = d3d_device->BeginScene();
	assert(result == D3D_OK);
}

// End the scene and draw it
void CD3DObj::end()
{
	// This ends the scene
	HRESULT result = d3d_device->EndScene();
	assert(result == D3D_OK);




	result = d3d_device->Present(NULL, NULL, NULL, NULL);
	assert(result == D3D_OK);
}

// Sets up the view of the scene based on the CCamera passed in
void CD3DObj::setViewMatrix(const CCamera *camera)
{
	D3DXMATRIXA16 matrix;

	// Create "D3D Vector" versions of our camera's eye, look at position, and up vector
	D3DXVECTOR3 eye(camera->getEye().x, camera->getEye().y, camera->getEye().z);
	D3DXVECTOR3 lookAt(camera->getLookAt().x, camera->getLookAt().y, camera->getLookAt().z);
	D3DXVECTOR3 up(camera->getUpVector().x, camera->getUpVector().y, camera->getUpVector().z);

	


	D3DXMatrixLookAtLH(&matrix, &eye, &lookAt, &up);
    d3d_device->SetTransform(D3DTS_VIEW, &matrix); // Set our view of the world
}

void CD3DObj::setProjMatrix()
{
	D3DXMATRIXA16 matrix;

	

    D3DXMatrixPerspectiveFovLH(&matrix, fov, aspect_ratio, near_clip, far_clip);
    d3d_device->SetTransform(D3DTS_PROJECTION, &matrix);
}

// Sets the world matrix to the matrix passed in
void CD3DObj::setWorldMatrix(const D3DXMATRIX *matrix)
{
	d3d_device->SetTransform(D3DTS_WORLD, matrix);
}

// Renders the passed in vertex list using the passed in index list
bool CD3DObj::render(SVertex *vList, int vertCount, WORD *iList, int indexCount)
{
	HRESULT result;

	IDirect3DVertexBuffer9 *vertexBuf = NULL; 
	IDirect3DIndexBuffer9 *indexBuf = NULL; // Our interface for manipulating index buffers
	
	// Get the size of our vertex list
	int vertListSize = sizeof(SVertex) * vertCount;
	assert(vertListSize > 0);

	


	result = d3d_device->CreateVertexBuffer(vertListSize, 0, SVertexType, 
											D3DPOOL_MANAGED, &vertexBuf, NULL);
											
	if(result != D3D_OK)
		return false;

	VOID *verts = NULL; // We'll use this as our pointer to the vertices



	result = vertexBuf->Lock(0, 0, (void**)&verts, 0);
	
		// Error Check
		if(result != D3D_OK)
		{
			vertexBuf->Release();
				return false;
		}
	
	

	memcpy(verts, vList, vertListSize);
	vertexBuf->Unlock(); // We're done with the vertex buffer so we unlock it
	
	// Calculate the size of the index list
	int indexListSize = sizeof(WORD) * indexCount;
	assert(indexListSize > 0);

	

	result = d3d_device->CreateIndexBuffer(indexListSize, 0, D3DFMT_INDEX16, 
										   D3DPOOL_MANAGED, &indexBuf, NULL);
	
	if(result != D3D_OK)
	{
		vertexBuf->Release(); // Free memory to this point
			return false;
	}

	VOID* indices = NULL; // We'll use this as the pointer to our indices 
	

	result = indexBuf->Lock(0, 0, (void**)&indices, 0);

    if(result != D3D_OK)
    {
		// Free memory to this point
		vertexBuf->Release();
		indexBuf->Release();
			return false;
	}

	// Copy over the index buffer list
	memcpy(indices, iList, indexListSize);
	indexBuf->Unlock(); // We've copied the data, unlock the buffer

	// Tell our 3D device where the vertex data is coming from
	result = d3d_device->SetStreamSource(0, vertexBuf, 0, sizeof(SVertex));
	assert(result == D3D_OK);

	// Tell our 3D device where the index data is coming from
	result = d3d_device->SetIndices(indexBuf);
	assert(result == D3D_OK);

	
	d3d_device->SetFVF(SVertexType);
	
	
	result = d3d_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST ,0,0,vertCount,0,indexCount / 3);
	assert(result == D3D_OK);

	d3d_device->SetTexture( 0, pTexture );

	// Free up our buffers
	vertexBuf->Release();
	indexBuf->Release();
		return true;
}


bool CD3DObj::clear(int color, float zDepth)
{
	HRESULT result = d3d_device->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
									   color, zDepth, 0);
	return (result == D3D_OK);
}

// Deconstructor -- Free up all the memory
CD3DObj::~CD3DObj()
{
	if(d3d_device != NULL)
		d3d_device->Release();

    if(d3d_interface != NULL)
		d3d_interface->Release();

	// Zero out our D3D interface and device 
	d3d_device = NULL;
	d3d_interface = NULL;
}

CD3DObj theD3DObj; // Create our 3D Object
CD3DObj *g3D = &theD3DObj; // Set the global pointer to our 3D Object