#include <assert.h>
#include "camera.h"

CCamera::CCamera()
{
	eye.set(0.0f, 0.0f, -5.0f); 
	look_at.set(0.0f, 0.0f, 0.0f); 
	up.set(0.0f, 1.0f, 0.0f); 

	move_amt = DEFAULT_MOVE_AMOUNT; 
}


CCamera::CCamera(CPos eyePos, CPos lookAt, CPos upVec, float moveAmount)
{
	assert(moveAmount > 0.0f);

	eye = eyePos;
	look_at = lookAt;
	up = upVec;
	move_amt = moveAmount;
}


void CCamera::moveBack()
{
	// Create the vector moving in a backwards direction
	CVector vec(0.0f, 0.0f, -move_amt);


	eye += vec;
	look_at += vec;
}


void CCamera::moveForward()
{

	CVector vec(0.0f, 0.0f, move_amt);

	
	eye += vec;
	look_at += vec;
}


void CCamera::moveLeft()
{

	CVector vec(-move_amt, 0.0f, 0.0f);


	eye += vec;
	look_at += vec;
}


void CCamera::moveRight()
{
	// Create the vector moving in the right direction
	CVector vec(move_amt, 0.0f, 0.0f);


	eye += vec;
	look_at += vec;
}

// Create out global camera
CCamera theCamera;
CCamera *gCamera = &theCamera;