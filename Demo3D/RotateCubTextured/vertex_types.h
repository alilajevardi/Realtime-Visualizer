#ifndef VERTEX_TYPES_H
#define VERTEX_TYPES_H




#define SVertexType D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1

// Our vertex struct  
struct SVertex
{
	float x, y, z; // Our position in space (world coordinates)
	DWORD color;// Our diffuse color
	FLOAT tu, tv;
};


#endif