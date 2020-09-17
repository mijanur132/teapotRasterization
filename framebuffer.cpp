#include "stdafx.h"

#include "framebuffer.h"
#include "math.h"
#include <iostream>
#include "scene.h"

#include <tiffio.h>



using namespace std;

//**************the constructor

FrameBuffer::FrameBuffer(int u0, int v0,   
	int _w, int _h, unsigned int _id) : Fl_Gl_Window(u0, v0, _w, _h, 0) {

	w = _w;
	h = _h;
	pix = new unsigned int[w*h];
	zb = new float[w * h];
	
}


void FrameBuffer::Set(int u, int v, unsigned int color) {  //*********************set a pixel to a color
	if (u < 0 || u > w - 1 || v < 0 || v > h - 1)
		return;
	pix[(h - 1 - v)*w + u] = color;

}

void FrameBuffer::SetBGR(unsigned int bgr) {  //********************set all pixel to a color

	for (int uv = 0; uv < w*h; uv++)
		pix[uv] = bgr;

}

// load ************************************a tiff image to pixel buffer
void FrameBuffer::LoadTiff(char* fname) {
	TIFF* in = TIFFOpen(fname, "r");
	if (in == NULL) {
		cerr << fname << " could not be opened" << endl;
		return;
	}

	int width, height;
	TIFFGetField(in, TIFFTAG_IMAGEWIDTH, &width);
	TIFFGetField(in, TIFFTAG_IMAGELENGTH, &height);
	if (w != width || h != height) {
		w = width;
		h = height;
		delete[] pix;
		pix = new unsigned int[w*h];
		size(w, h);
		glFlush();
		glFlush();
	}

	if (TIFFReadRGBAImage(in, w, h, pix, 0) == 0) {
		cerr << "failed to load " << fname << endl;
	}

	TIFFClose(in);
}

//********************************************* save as tiff image
void FrameBuffer::SaveAsTiff(char *fname) {

	TIFF* out = TIFFOpen(fname, "w");

	if (out == NULL) {
		cerr << fname << " could not be opened" << endl;
		return;
	}

	TIFFSetField(out, TIFFTAG_IMAGEWIDTH, w);
	TIFFSetField(out, TIFFTAG_IMAGELENGTH, h);
	TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, 4);
	TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 8);
	TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
	TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

	for (uint32 row = 0; row < (unsigned int)h; row++) {
		TIFFWriteScanline(out, &pix[(h - row - 1) * w], row);
	}

	TIFFClose(out);
}

//****************************draw axis alighned rectangle

//  uv3.............uv2


// uv0...............uv1

void FrameBuffer::DrawAxisAlignedRect(float uv0[2], float uv2[2], unsigned int borderCol) {

	float uv1[2], uv3[2];
	uv1[0] = uv2[0];
	uv1[1] = uv0[1];

	uv3[0] = uv0[0];
	uv3[1] = uv2[1];
	//cerr << uv0[0]<<"," << uv1[0] << ","<<uv2[0] <<","<< uv3[0] << endl;
	//cerr << uv0[1] << "," << uv1[1] << "," << uv2[1] << "," << uv3[1] << endl;
	Draw2DSegmentOld(uv0, uv1, borderCol);
	Draw2DSegmentOld(uv1, uv2, borderCol);
	Draw2DSegmentOld(uv2, uv3, borderCol);
	Draw2DSegmentOld(uv3, uv0, borderCol);
}

//****************************draw 2D triangle

void FrameBuffer::DrawTriangle(float uv0[2], float uv1[2], float uv2[2], unsigned int borderCol) {
	
	Draw2DSegmentOld(uv0, uv1, borderCol);
	Draw2DSegmentOld(uv1, uv2, borderCol);
	Draw2DSegmentOld(uv2, uv0, borderCol);
	
}

//******************************circle

void FrameBuffer::DrawCircle(float uv0[2], float radius, unsigned int borderCol, unsigned int circleCol)
{
	//get  bounding box

	float x = uv0[0];
	float y = uv0[1];
	float uv1[2], uv2[2], uv3[2], uv4[4];
	uv1[0] = x - radius;
	uv1[1] = y-radius;
	uv3[0] = x + radius;
	uv3[1] = y+radius;
	uv2[0] = x+radius;
	uv2[1] = y - radius;
	uv4[0] = x-radius;
	uv4[1] = y + radius;
	//DrawRect(uv1, uv2, uv3, uv4, borderCol);
	for (int i = 0; i < 2*radius; i++)
	{
		for (int j = 0; j < 2*radius; j++)
		{	
			float tempoint[2];
			tempoint[0]= i + uv1[0];
			tempoint[1]= j + uv1[1];
			//cerr << tempoint[0] << "," << tempoint[1] << endl;
			//cerr << uv0[0] << "," << uv0[1] << endl;
			float len = euclideanLength2D(uv0, tempoint);
			//cerr << len << endl;
			if (len > (radius-2) && len<(radius))
			{
				Set((int)tempoint[0], (int)tempoint[1], circleCol);
			}
		}

	}
	cerr << "done" << endl;

}

void FrameBuffer::DrawRect(float uv0[2], float uv1[2], float uv2[2], float uv3[2], unsigned int borderCol) {

	Draw2DSegmentOld(uv0, uv1, borderCol);
	Draw2DSegmentOld(uv1, uv2, borderCol);
	Draw2DSegmentOld(uv2, uv3, borderCol);
	Draw2DSegmentOld(uv3, uv0, borderCol);
}



float FrameBuffer::euclideanLength2D(float uv[2], float uv1[2])
{
	float ret = sqrt((uv[0] - uv1[0]) * (uv[0] - uv1[0]) + (uv[1] - uv1[1]) * (uv[1] - uv1[1]));
	return ret;
}

void FrameBuffer::Draw2DSegmentOld(float uv0[2], float uv1[2], unsigned int col) {

	float du = fabsf(uv0[0] - uv1[0]);
	float dv = fabsf(uv0[1] - uv1[1]);
	int stepsN;
	if (du < dv) {
		stepsN = 1+(int)dv;
	}
	else {
		stepsN =1+ (int)du;
	}
	for (int i = 0; i <= stepsN; i++) {
		float cuv[2];
		cuv[0] = uv0[0] + (uv1[0] - uv0[0]) / (float)stepsN * (float)i;
		cuv[1] = uv0[1] + (uv1[1] - uv0[1]) / (float)stepsN * (float)i;
		Set((int)cuv[0], (int)cuv[1], col);
	}

}


void FrameBuffer::SetChecker(unsigned int col0, unsigned int col1, int csize) {

	for (int v = 0; v < h; v++) {
		for (int u = 0; u < w; u++) {
			int cv = v / csize;
			int cu = u / csize;
			if ((cu + cv) % 2) {
				Set(u, v, col0);
			}
			else {
				Set(u, v, col1);
			}
		}
	}

}



void FrameBuffer::draw() {

	glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_BYTE, pix);

}

int FrameBuffer::handle(int event) {

	switch (event)
	{
	case FL_KEYBOARD: {
		KeyboardHandle();
		return 0;
	}
	default:
		break;
	}
	return 0;
}

void FrameBuffer::KeyboardHandle() {

	int key = Fl::event_key();
	switch (key) {
	case FL_Up: {
		cerr << "INFO: pressed up key";
		break;
	}
	default:
		cerr << "INFO: do not understand keypress" << endl;
	}
}



void FrameBuffer::DrawSquarePoint(float uf, float vf, int psize, unsigned int color) {

	int u = (int)uf;
	int v = (int)vf;
	for (int cv = v - psize / 2; cv <= v + psize / 2; cv++)
		for (int cu = u - psize / 2; cu <= u + psize / 2; cu++)
			Set(cu, cv, color);
}

void FrameBuffer::Draw2DSegment(V3 p0, V3 c0, V3 p1, V3 c1) {

	float du = fabsf((p0 - p1)[0]);
	float dv = fabsf((p0 - p1)[1]);
	int stepsN;
	if (du < dv) {
		stepsN = 1 + (int)dv;
	}
	else {
		stepsN = 1 + (int)du;
	}
	for (int i = 0; i <= stepsN; i++) {
		V3 cp, cc;
		cp = p0 + (p1 - p0) * (float)i / (float)stepsN;
		// cp[2] depth (one over w) at current pixel
		int u = (int)cp[0], v = (int)cp[1];
		if (Farther(u, v, cp[2]))
			continue;
		cc = c0 + (c1 - c0) * (float)i / (float)stepsN;
		Set(u, v, cc.GetColor());
	}

}

void FrameBuffer::Draw3DSegment(V3 P0, V3 P1, PPC* ppc, V3 c0, V3 c1) {

	V3 p0, p1;
	if (!ppc->Project(P0, p0))
		return;
	if (!ppc->Project(P1, p1))
		return;

	Draw2DSegment(p0, c0, p1, c1);

}



void FrameBuffer::ClearZB() {

	for (int uv = 0; uv < w * h; uv++)
		zb[uv] = 0.0f;

}



void FrameBuffer::ClearZB3d() {

	for (int u = 0; u < 2000; u++)
	{
		for (int v = 0; v < 2000; v++)
		{
			zb3d[u][v] = -1000.0f;
		}
		
	}
}

int FrameBuffer::Farther(int u, int v, float currz) {

	if (u < 0 || u > w - 1 || v < 0 || v > h - 1)
		return 1;
	int uv = (h - 1 - v) * w + u;
	if (currz < zb[uv])
		return 1;
	zb[uv] = currz;
	return 0;

}


int FrameBuffer::Farther3d(int u, int v, float currz) {

	if (u < 0 || u > w - 1 || v < 0 || v > h - 1)
		return 1;
	
	if (currz < zb3d[u][v])
		return 1;
	zb3d[u][v] = currz;
	return 0;

}