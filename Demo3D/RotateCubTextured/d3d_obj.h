#ifndef D3D_OBJ_H
#define D3D_OBJ_H

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <assert.h>
#include "vertex_types.h"
#include "camera.h"

const float kFOV = DEG2RAD(60); // Default Field Of View
const float kNearClip = 1.0f; // Default Near Clip Plane
const float kFarClip = 8192.0f; // Default Far Clip Plane


class CD3DObj
{
	public:

		CD3DObj(); // 
		bool init(HWND hwnd); 
		void initToDefaultParams(); 

		void begin(); // Begins a scene
		void end(); // Ends a scene

		void setViewMatrix(const CCamera *camera); 
		void setProjMatrix(); 
		void setWorldMatrix(const D3DXMATRIX *matrix);

	
		bool render(SVertex *vertList, int vertCount, WORD *indexList, int indexCount);


		bool clear(int color = D3DCOLOR_XRGB(0,0,0), float zDepth = 1.0f);

		~CD3DObj(); // Deconstructor
		
	private:


		IDirect3D9 *d3d_interface;
		

		IDirect3DDevice9 *d3d_device;

		IDirect3DTexture9 *pTexture;

		float fov; // Field of view
		float aspect_ratio; 
		float near_clip; 
		float far_clip; // Far clip plane

		

		CD3DObj(const CD3DObj &obj) {}
		CD3DObj& operator =(CD3DObj &obj) { return *this; }
};


extern CD3DObj *g3D;

#endif