#ifndef _H_OBJLOADER
#define _H_OBJLOADER

#include "Vector.h"
#include <stdio.h>

class objLoader
{
protected:
	// No copy construction
	objLoader(const objLoader &a){}
	objLoader &operator =(const objLoader &a){return *this;}
public:

	objLoader()
	{
		VerticeD=NormalD=0;
		FaceD=FaceNormalD=FaceTexD=0;
		VerTexD=0;
	}

	~objLoader()
	{
#define OBJLOAD_SAFEDELETE(x)	if(x)\
									delete [] x;\
								x=0;
		
		OBJLOAD_SAFEDELETE(VerticeD);
		OBJLOAD_SAFEDELETE(NormalD);
		OBJLOAD_SAFEDELETE(VerTexD);
		OBJLOAD_SAFEDELETE(FaceD);
		OBJLOAD_SAFEDELETE(FaceNormalD);
		OBJLOAD_SAFEDELETE(FaceTexD);
	}
	
	bool load(char *filename);
	void drawObj();
	void scale();
	void KillSpace(FILE *fp);
	void KillTrash(FILE *fp);
	void detectSlash(FILE *fp);
	int VerticesCount;
	int VerticeNormalCount;
	int FaceCount;
	int FaceNormalCount;
	int VerticeTextureCount;
	int FaceTextureCount;
	float min(float x, float y);
	float max(float x, float y);
	Vector3d *VerticeD;
	Vector4d *FaceD;
	Vector3d *NormalD;
	Vector4d *FaceNormalD;
	Vector3d scaleD;
	Vector3d centerD;
	Vector2d *VerTexD;
	Vector4d *FaceTexD;
};

//ReadtoData *Data;

#endif