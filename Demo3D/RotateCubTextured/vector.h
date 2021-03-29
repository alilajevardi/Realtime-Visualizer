#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>


#ifndef PI
#define PI 3.1415926535897932384626433832795f
#endif

// Macros
#define DEG2RAD(x) (x * (PI / 180.0f)) 
#define RAD2DEG(x) (x * (180.0f / PI)) 

class CVector
{
	public:
	
		// Constructors
		CVector();
		CVector(float xxx, float yyy, float zzz);
		
	
		CVector(const CVector &vec);

	
		bool operator ==(const CVector &vec);
		bool operator !=(const CVector &vec);
		CVector& operator =(const CVector &vec);
		CVector operator +(const CVector &vec);
		CVector operator -(const CVector &vec);
		CVector& operator +=(const CVector &vec);
		CVector& operator -=(const CVector &vec);

		float operator *(const CVector &vec); 


		inline void set(float xxx, float yyy, float zzz);
		inline void set(const CVector &vec);

		void negate(); // Negates the CVector
		void normalize(); 
		void scale(float amt);
		
		float magnitude(); 


		void crossProduct(const CVector &vec, CVector &result);
		CVector crossProduct(const CVector &vec);

		float x;
		float y;
		float z;
};


typedef CVector CPos;

#endif