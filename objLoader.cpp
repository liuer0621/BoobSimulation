#include "objLoader.h"
#include <vector>
#include "Vector.h"
#include <stdio.h>
#include <cctype> // tell if it's space
#include <GLUT/glut.h>
#include <string.h>
#include <stdlib.h>
using namespace std;


float objLoader::min(float x, float y)
{
	float dif;
	dif = x - y;
	if(dif < 0)
		return x;
	else if (dif == 0)
		return x;
	else 
		return y;
}

float objLoader::max(float x, float y)
{
	float dif;
	dif = x - y;
	if(dif < 0)
		return y;
	else if (dif == 0)
		return y;
	else 
		return x;
}

void objLoader::scale()
{
	float minVX,minVY,minVZ,maxVX,maxVY,maxVZ;
	maxVX = minVX = VerticeD[0].x;
	maxVY = minVY = VerticeD[0].y;
	maxVZ = minVZ = VerticeD[0].z;
	for(int i = 0; i< VerticesCount; i++)
	{
		minVX = min((float)VerticeD[i].x,minVX);
		minVY = min((float)VerticeD[i].y,minVY);
		minVZ = min((float)VerticeD[i].z,minVZ);
		maxVX = max((float)VerticeD[i].x,maxVX);
		maxVY = max((float)VerticeD[i].y,maxVY);
		maxVZ = max((float)VerticeD[i].z,maxVZ);
 	}
	//printf("\nminx%f,miny%f,minz%f,maxx%f,maxy%f,maxz%f",minVX,minVY,minVZ,maxVX,maxVY,maxVZ);
	scaleD = Vector3d((maxVX-minVX),(maxVY-minVY),(maxVZ-minVZ));
	centerD = Vector3d((minVX+maxVX)/2.0f,(minVY+maxVY)/2.0f,(minVZ+maxVZ)/2.0f);
}

void objLoader::drawPoints()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    for(int i = 0; i<VerticesCount; i++)
    {
        //draw each vertices
        glVertex3f(VerticeD[i].x, VerticeD[i].y, VerticeD[i].z);
    }
    glEnd();
}

void objLoader::drawObj()
{	
	for(int i = 0; i<FaceCount; i++)
	{
		if((int)FaceD[i].w == 0)
		{
			glBegin(GL_TRIANGLES); 
				//glNormal3f(FaceNormalD[i].x,FaceNormalD[i].y,FaceNormalD[i].z);
				glTexCoord2f(VerTexD[(int)FaceTexD[i].x-1].x,VerTexD[(int)FaceTexD[i].x-1].y);
				glNormal3f(NormalD[(int)FaceNormalD[i].x-1].x,NormalD[(int)FaceNormalD[i].x-1].y,NormalD[(int)FaceNormalD[i].x-1].z);
				glVertex3f(VerticeD[(int)FaceD[i].x-1].x,VerticeD[(int)FaceD[i].x-1].y,VerticeD[(int)FaceD[i].x-1].z);
				glTexCoord2f(VerTexD[(int)FaceTexD[i].y-1].x,VerTexD[(int)FaceTexD[i].y-1].y);
				glNormal3f(NormalD[(int)FaceNormalD[i].y-1].x,NormalD[(int)FaceNormalD[i].y-1].y,NormalD[(int)FaceNormalD[i].y-1].z);
				glVertex3f(VerticeD[(int)FaceD[i].y-1].x,VerticeD[(int)FaceD[i].y-1].y,VerticeD[(int)FaceD[i].y-1].z);
				glTexCoord2f(VerTexD[(int)FaceTexD[i].z-1].x,VerTexD[(int)FaceTexD[i].z-1].y);
				glNormal3f(NormalD[(int)FaceNormalD[i].z-1].x,NormalD[(int)FaceNormalD[i].z-1].y,NormalD[(int)FaceNormalD[i].z-1].z);
				glVertex3f(VerticeD[(int)FaceD[i].z-1].x,VerticeD[(int)FaceD[i].z-1].y,VerticeD[(int)FaceD[i].z-1].z);
				glEnd();
		}

		else 
		{
			glBegin(GL_QUADS);
				//glNormal3f(FaceNormalD[i].x,FaceNormalD[i].y,FaceNormalD[i].z);
				glTexCoord2f(VerTexD[(int)FaceTexD[i].x-1].x,VerTexD[(int)FaceTexD[i].x-1].y);
				glNormal3f(NormalD[(int)FaceNormalD[i].x-1].x,NormalD[(int)FaceNormalD[i].x-1].y,NormalD[(int)FaceNormalD[i].x-1].z);
				glVertex3f(VerticeD[(int)FaceD[i].x-1].x,VerticeD[(int)FaceD[i].x-1].y,VerticeD[(int)FaceD[i].x-1].z);
				glTexCoord2f(VerTexD[(int)FaceTexD[i].y-1].x,VerTexD[(int)FaceTexD[i].y-1].y);
				glNormal3f(NormalD[(int)FaceNormalD[i].y-1].x,NormalD[(int)FaceNormalD[i].y-1].y,NormalD[(int)FaceNormalD[i].y-1].z);
				glVertex3f(VerticeD[(int)FaceD[i].y-1].x,VerticeD[(int)FaceD[i].y-1].y,VerticeD[(int)FaceD[i].y-1].z);
				glTexCoord2f(VerTexD[(int)FaceTexD[i].z-1].x,VerTexD[(int)FaceTexD[i].z-1].y);
				glNormal3f(NormalD[(int)FaceNormalD[i].z-1].x,NormalD[(int)FaceNormalD[i].z-1].y,NormalD[(int)FaceNormalD[i].z-1].z);
				glVertex3f(VerticeD[(int)FaceD[i].z-1].x,VerticeD[(int)FaceD[i].z-1].y,VerticeD[(int)FaceD[i].z-1].z);
				glTexCoord2f(VerTexD[(int)FaceTexD[i].w-1].x,VerTexD[(int)FaceTexD[i].w-1].y);
				glNormal3f(NormalD[(int)FaceNormalD[i].w-1].x,NormalD[(int)FaceNormalD[i].w-1].y,NormalD[(int)FaceNormalD[i].w-1].z);
				glVertex3f(VerticeD[(int)FaceD[i].w-1].x,VerticeD[(int)FaceD[i].w-1].y,VerticeD[(int)FaceD[i].w-1].z);
			glEnd();
		}
	}
}

void objLoader::detectSlash(FILE *fp)
{
	char slash;
	do
	{
		slash = fgetc(fp);

	}
	while(slash!= '/');
}

void objLoader::KillSpace(FILE *fp)
{
	char space;
	do
	{
		space = fgetc(fp);
	}
	while (space != '\n');
}

void objLoader::KillTrash(FILE *fp)
{
	char trash;
	do
	{
		trash = fgetc(fp);
	}
	while (!isspace(trash));
}

bool objLoader::load(char *filename)
{
	vector<Vector3d> Vertices;
	vector<Vector4d> Faces;
	vector<Vector3d> VerticeNormal;
	vector<Vector4d> FaceNormal;
	vector<Vector4d> FaceTex;
	vector<Vector2d> VTexture;
	Vector4d FNormal;
	Vector3d VerNormal;
	Vector4d FaceLoad;
	Vector3d Ver;
	Vector4d FTexture;
	Vector2d VerTex;
	char a;
	char aValue[20];
	FILE *fp;
	fp = fopen(filename,"rb");
	if(fp == NULL)
	{
		printf("\nThis file doesn't exist!!!");
		return false;
	}
	
	else
	{
		printf("\nOpen the file!");
		a = fgetc(fp); //first letter in the line
		do
		{
			switch(a)
			{
			case'#':
				KillSpace(fp); //go to the next line
				break;
			case'v':
				//vertices
				
				a = fgetc(fp);
				if(isspace(a))
				{
					fscanf(fp,"%s",aValue);//stringx
					Ver.x = atof(aValue); //copy to x
					//printf("\n%f",Ver.x);
					a = fgetc(fp); //space
					if(isspace(a))
					{
						fscanf(fp,"%s",aValue); //stringy
						Ver.y = atof(aValue); //copy to y
						//KillTrash(fp);
						a = fgetc(fp);
						if(isspace(a))
						{
							fscanf(fp,"%s",aValue); //string z
							//printf("\n%s",aValue);
							Ver.z = atof(aValue); //copy to z
							KillSpace(fp);
						}
					}
						Vertices.push_back(Ver);
				}

				else if(a == 't')
				{
					a = fgetc(fp);
					if(isspace(a));
					{
						fscanf(fp,"%s",aValue); //string texture u
						VerTex.x = atof(aValue);
						a = fgetc(fp);
						if(isspace(a))
						{
							fscanf(fp,"%s",aValue);
							VerTex.y = atof(aValue);
							KillSpace(fp);
						}
					}
					VTexture.push_back(VerTex);
				}

				else if(a == 'n')
				{
					a = fgetc(fp);
					if(isspace(a))
					{
						fscanf(fp,"%s",aValue); //string vnx
						VerNormal.x = atof(aValue);
						a = fgetc(fp);
						if (isspace(a))
						{
							fscanf(fp,"%s",aValue); //string vny
							VerNormal.y = atof(aValue);
							//KillTrash(fp);
							a = fgetc(fp);
							if(isspace(a))
							{
								fscanf(fp,"%s",aValue); //string vnz
								VerNormal.z = atof(aValue);
								KillSpace(fp);
							}
						}
					}

					VerticeNormal.push_back(VerNormal);

				}
				
				break;
			case'f':
				//face
				a = fgetc(fp);
				if(isspace(a))
				{
					fscanf(fp,"%s",aValue);
					//printf("%s\n",aValue);
					char *V, *VR;
					V = strchr(aValue,'/');
					//printf("the first slash' position is %d\n",V);
					if(V == NULL)
					{
						//printf("The face only has vertex!!!\n");
						sscanf(aValue,"%d",FaceLoad.x);
					}

					else
					{
						int F,T,N;
						//printf("the first slash' position is %d\n",V);
						VR = strrchr(aValue,'/');
						//printf("the second slash' position is %d\n",VR);
						if(VR == V)
						{
							//only has one slash 
							sscanf(aValue,"%d/%d",&F,&T);
							FaceLoad.x = F;
							FTexture.x = T;
						}

						else if(VR != V)
						{
							//has two different slashes
							if(VR == (V+1))
							{
								//doesn't have texnormal
								sscanf(aValue,"%d//%d",&F,&N);
								FaceLoad.x = F;
								FNormal.x = N;
							}

							else 
							{
								//have everything
								sscanf(aValue,"%d/%d/%d",&F,&T,&N);
								FaceLoad.x = F;
								FTexture.x = T;
								FNormal.x = N;
							}
						}

						a = fgetc(fp);
						if(isspace(a))
						{
							fscanf(fp,"%s",aValue);
							sscanf(aValue,"%d/%d/%d",&F,&T,&N);
							FaceLoad.y= F;
							FTexture.y = T;
							FNormal.y = N;

							//z
							a = fgetc(fp);
							if(isspace(a))
							{
								fscanf(fp,"%s",aValue);
								sscanf(aValue,"%d/%d/%d",&F,&T,&N);
								FaceLoad.z= F;
								FTexture.z = T;
								FNormal.z = N;

								a = fgetc(fp);
								if(isspace(a) && a!='\n')
								{
									fscanf(fp,"%s",aValue);
									sscanf(aValue,"%d/%d/%d",&F,&T,&N);
									FaceLoad.w= F;
									FTexture.w = T;
									FNormal.w = N;
	
								}

							}
						}

					}
				}

				Faces.push_back(FaceLoad);
				FaceNormal.push_back (FNormal);
				FaceTex.push_back(FTexture);

				break;
			default:
				//others
				break;
			}
			a = fgetc(fp);
		}
		while(a != EOF);

		//copy vertices to plane data 
		VerticesCount = Vertices.size();
		printf("%d",VerticesCount);
		VerticeD = new Vector3d [VerticesCount];
		for(int i = 0; i <VerticesCount; i++)
		{
			VerticeD[i].x = Vertices[i].x;
			VerticeD[i].y = Vertices[i].y;
			VerticeD[i].z = Vertices[i].z;
		}
		
		//copy verticeTexture to plane data
		VerticeTextureCount = VTexture.size();
		VerTexD = new Vector2d[VerticeTextureCount];
		for(int i = 0; i<VerticeTextureCount;i++)
		{
			VerTexD[i].x = VTexture[i].x;
			VerTexD[i].y = VTexture[i].y;
		}

		//copy verticeNormal to plane data
		VerticeNormalCount = VerticeNormal.size();
		printf("%d",VerticeNormalCount);
		NormalD = new Vector3d[VerticeNormalCount];
		for(int i = 0; i<VerticeNormalCount; i++)
		{
			NormalD[i].x = VerticeNormal[i].x;
			NormalD[i].y = VerticeNormal[i].y;
			NormalD[i].z = VerticeNormal[i].z;
		}

		//copy face to plane data
		FaceCount = Faces.size();
		printf("\n%d",FaceCount);
		FaceD = new Vector4d[FaceCount];
		for(int i = 0; i <FaceCount;i++)
		{
			FaceD[i].x = Faces[i].x;
			FaceD[i].y = Faces[i].y;
			FaceD[i].z = Faces[i].z;
			FaceD[i].w = Faces[i].w;
		}
		
		//copy faceNormal to plane data
		FaceNormalCount = FaceNormal.size();
		FaceNormalD = new Vector4d[FaceNormalCount];
		for(int i = 0; i < FaceNormalCount ; i++)
		{
			FaceNormalD[i].x = FaceNormal[i].x;
			FaceNormalD[i].y = FaceNormal[i].y;
			FaceNormalD[i].z = FaceNormal[i].z;
			FaceNormalD[i].w = FaceNormal[i].w;
		}

		//copy facetexture to plane data
		FaceTextureCount = FaceTex.size();
		FaceTexD = new Vector4d[FaceTextureCount];
		for(int i = 0; i < FaceTextureCount; i++)
		{
			FaceTexD[i].x = FaceTex[i].x;
			FaceTexD[i].y = FaceTex[i].y;
			FaceTexD[i].z = FaceTex[i].z;
			FaceTexD[i].w = FaceTex[i].w;
		}

		//write to new obj file
		
		 FILE * pFile;
		 pFile = fopen ("myfile.txt","w");
			if (pFile!=NULL)
				{
					fputs ("fopen example",pFile);
					for(int i = 0; i<VerticesCount; i++)
					{
						fprintf(pFile,"\nV\t%f %f %f",VerticeD[i].x,VerticeD[i].y,VerticeD[i].z);
					}
					for(int i = 0; i<VerticeTextureCount;i++)
					{
						fprintf(pFile,"\nVT\t%f %f %f",VerTexD[i].x,VerTexD[i].y);
					}
					for(int i = 0; i<VerticeNormalCount; i++)
					{
						fprintf(pFile,"\nVN\t%f %f %f",NormalD[i].x,NormalD[i].y,NormalD[i].z);
					}
					for(int i = 0; i<FaceCount;i++)
					{
						fprintf(pFile,"\nF\t%d//%d %d//%d %d//%d %d//%d",(int)FaceD[i].x,(int)FaceNormalD[i].x,(int)FaceD[i].y,(int)FaceNormalD[i].y,(int)FaceD[i].z,(int)FaceNormalD[i].z,(int)FaceD[i].w,(int)FaceNormalD[i].w);
					}
					fclose (pFile);
				}


		Vertices.clear();
		fclose(fp);
	}
    
    return true;
}

