#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"


#define DEFAULT_MOVE_AMOUNT 0.3f

class CCamera
{
	public:

		CCamera();
		CCamera(CPos eyePos, CPos lookAt, CPos upVec, float moveAmount = DEFAULT_MOVE_AMOUNT);

		void moveForward();
		void moveBack();
		void moveLeft();
		void moveRight();



			CPos getEye() { return eye; }
			CPos getLookAt() { return look_at; }
			CVector getUpVector() { return up; }





			CPos getEye() const { return eye; }
			CPos getLookAt() const { return look_at; }
			CVector getUpVector() const { return up; }



	private:

		CPos eye; 
		CPos look_at;
		CVector up; 
					

		float move_amt; 
};

extern CCamera *gCamera;

#endif