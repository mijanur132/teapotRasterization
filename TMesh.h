#pragma once

#include "V3.h"
#include "ppc.h"
#include "framebuffer.h"

class TMesh {
public:
	int onFlag;
	V3* verts;
	V3* colors;
	V3* normals;
	int vertsN;
	unsigned int* tris;
	int trisN;
	TMesh() : verts(0), vertsN(0), tris(0), trisN(0), colors(0), normals(0), onFlag(1) {};
	void SetToCube(V3 cc, float sideLength, unsigned int color0, unsigned int color1);
	void SetToAABBQuad(V3 cc, V3 sideLength, unsigned int color0, unsigned int color1);
	void Allocate(int _vertsN, int _trisN);
	void DrawCubeQuadFaces(FrameBuffer* fb, PPC* ppc, unsigned int color);
	void DrawWireFrame(FrameBuffer* fb, PPC* ppc, unsigned int color);
	void GetAABBParam(V3& center, V3& sideL);
	void GetSidedNessParam(V3 p1, V3 p2, V3 p3, V3 a[3]);
	V3 CalcSidedNessE(V3 a[3], V3 p);
	void GetTriangleAABBparam(V3 pa, V3 pb, V3 pc, V3& center, V3& sideL,V3& leftMost, V3& topMost, V3& rightMost, V3& bottomMost);
	void DrawFilledFrame(FrameBuffer* fb, PPC* ppc, unsigned int color);
	void GetBarryCentric(V3 p1, V3 p2, V3 p3, V3 p,V3 &uvw);
	float CalcArea(V3 p1, V3 p2, V3 p3);
	void LoadBin(char* fname);
	V3 GetCenter();
	float GetSL();
	void SetCenter(V3 center);
	void Translate(V3 tv);
	void Scale(float scf);
	void Rotate(V3 O, V3 adir, float angle);
};