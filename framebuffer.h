#pragma once

#include"V3.h"
#include"ppc.h"
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <GL/glut.h>
#

class FrameBuffer : public Fl_Gl_Window {
public:
	unsigned int *pix; // pixel array
	float* zb;
	float zb3d[2000][2000];
	int w, h;
	FrameBuffer(int u0, int v0, int _w, int _h, unsigned int _id);  //a
	void SetBGR(unsigned int bgr);   //b
	void Set(int u, int v, unsigned int color);  //c
	
	void DrawAxisAlignedRect(float uv0[2], float uv2[2], unsigned int borderCol);  //d
	void DrawTriangle(float uv0[2], float uv1[2], float uv2[2], unsigned int borderCol);   //e
	void DrawCircle(float uv0[2], float radius, unsigned int borderCol, unsigned int circleCol);    //f

	void LoadTiff(char* fname);  //g
	void SaveAsTiff(char* fname); //g


	void draw();
	void KeyboardHandle();
	int handle(int guievent);
	
	void SetChecker(unsigned int col0, unsigned int col1, int csize);
	void Draw2DSegmentOld(float uv0[2], float uv1[2], unsigned int col);
	void Draw2DSegment(V3 p0, V3 c0, V3 p1, V3 c1);
	void DrawRect(float uv0[2], float uv1[2], float uv2[2], float uv3[2], unsigned int borderCol);

	void Draw3DSegment(V3 P0, V3 P1, PPC* ppc, V3 c0, V3 c1);
	void DrawSquarePoint(float uf, float vf, int psize, unsigned int color);
	int Farther(int u, int v, float currz);
	int Farther3d(int u, int v, float currz);
	void ClearZB();
	void ClearZB3d();
	
	float euclideanLength2D(float uv[2], float uv1[2]);

};