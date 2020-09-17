
#include "stdafx.h"

#include <fstream>
#include <iostream>

#include "TMesh.h"

using namespace std;


void TMesh::Allocate(int _vertsN, int _trisN) {

	vertsN = _vertsN;
	trisN = _trisN;
	verts = new V3[vertsN];
	colors = new V3[vertsN];
	normals = new V3[vertsN];
	tris = new unsigned int[trisN * 3];
}

void TMesh::SetToCube(V3 cc, float sideLength, unsigned int color0, unsigned int color1) {

	vertsN = 8;
	trisN = 6 * 2;
	Allocate(vertsN, trisN);

	for (int vi = 0; vi < 4; vi++) {
		colors[vi].SetFromColor(color0);
		colors[vi + 4].SetFromColor(color1);
	}

	int vi = 0;
	verts[vi] = cc + V3(-sideLength / 2.0f, +sideLength / 2.0f, +sideLength / 2.0f);
	vi++;
	verts[vi] = cc + V3(-sideLength / 2.0f, -sideLength / 2.0f, +sideLength / 2.0f);
	vi++;
	verts[vi] = cc + V3(+sideLength / 2.0f, -sideLength / 2.0f, +sideLength / 2.0f);
	vi++;
	verts[vi] = cc + V3(+sideLength / 2.0f, +sideLength / 2.0f, +sideLength / 2.0f);
	vi++;

	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength);
	vi++;

	int tri = 0;
	tris[3 * tri + 0] = 0;
	tris[3 * tri + 1] = 1;
	tris[3 * tri + 2] = 2;
	tri++;
	tris[3 * tri + 0] = 2;
	tris[3 * tri + 1] = 3;
	tris[3 * tri + 2] = 0;
	tri++;
	tris[3 * tri + 0] = 3;
	tris[3 * tri + 1] = 2;
	tris[3 * tri + 2] = 6;
	tri++;
	tris[3 * tri + 0] = 6;
	tris[3 * tri + 1] = 7;
	tris[3 * tri + 2] = 3;
	tri++;
	tris[3 * tri + 0] = 7;
	tris[3 * tri + 1] = 6;
	tris[3 * tri + 2] = 5;
	tri++;
	tris[3 * tri + 0] = 5;
	tris[3 * tri + 1] = 4;
	tris[3 * tri + 2] = 7;
	tri++;
	tris[3 * tri + 0] = 4;
	tris[3 * tri + 1] = 5;
	tris[3 * tri + 2] = 1;
	tri++;
	tris[3 * tri + 0] = 1;
	tris[3 * tri + 1] = 0;
	tris[3 * tri + 2] = 4;
	tri++;
	tris[3 * tri + 0] = 4;
	tris[3 * tri + 1] = 0;
	tris[3 * tri + 2] = 3;
	tri++;
	tris[3 * tri + 0] = 3;
	tris[3 * tri + 1] = 7;
	tris[3 * tri + 2] = 4;
	tri++;
	tris[3 * tri + 0] = 1;
	tris[3 * tri + 1] = 5;
	tris[3 * tri + 2] = 6;
	tri++;
	tris[3 * tri + 0] = 6;
	tris[3 * tri + 1] = 2;
	tris[3 * tri + 2] = 1;
	tri++;

}

void TMesh::SetToAABBQuad(V3 cc, V3 sideLength, unsigned int color0, unsigned int color1) {

	vertsN = 8;
	trisN = 6 * 2;
	Allocate(vertsN, trisN);

	for (int vi = 0; vi < 4; vi++) {
		colors[vi].SetFromColor(color0);
		colors[vi + 4].SetFromColor(color1);
	}

	int vi = 0;
	verts[vi] = cc + V3(-sideLength.xyz[0] / 2.0f, +sideLength.xyz[1] / 2.0f, +sideLength.xyz[2] / 2.0f);
	vi++;
	verts[vi] = cc + V3(-sideLength.xyz[0] / 2.0f, -sideLength.xyz[1] / 2.0f, +sideLength.xyz[2] / 2.0f);
	vi++;
	verts[vi] = cc + V3(+sideLength.xyz[0] / 2.0f, -sideLength.xyz[1] / 2.0f, +sideLength.xyz[2] / 2.0f);
	vi++;
	verts[vi] = cc + V3(+sideLength.xyz[0] / 2.0f, +sideLength.xyz[1] / 2.0f, +sideLength.xyz[2] / 2.0f);
	vi++;

	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength.xyz[2]);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength.xyz[2]);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength.xyz[2]);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength.xyz[2]);
	vi++;

	int tri = 0;
	tris[3 * tri + 0] = 0;
	tris[3 * tri + 1] = 1;
	tris[3 * tri + 2] = 2;
	tri++;
	tris[3 * tri + 0] = 2;
	tris[3 * tri + 1] = 3;
	tris[3 * tri + 2] = 0;
	tri++;
	tris[3 * tri + 0] = 3;
	tris[3 * tri + 1] = 2;
	tris[3 * tri + 2] = 6;
	tri++;
	tris[3 * tri + 0] = 6;
	tris[3 * tri + 1] = 7;
	tris[3 * tri + 2] = 3;
	tri++;
	tris[3 * tri + 0] = 7;
	tris[3 * tri + 1] = 6;
	tris[3 * tri + 2] = 5;
	tri++;
	tris[3 * tri + 0] = 5;
	tris[3 * tri + 1] = 4;
	tris[3 * tri + 2] = 7;
	tri++;
	tris[3 * tri + 0] = 4;
	tris[3 * tri + 1] = 5;
	tris[3 * tri + 2] = 1;
	tri++;
	tris[3 * tri + 0] = 1;
	tris[3 * tri + 1] = 0;
	tris[3 * tri + 2] = 4;
	tri++;
	tris[3 * tri + 0] = 4;
	tris[3 * tri + 1] = 0;
	tris[3 * tri + 2] = 3;
	tri++;
	tris[3 * tri + 0] = 3;
	tris[3 * tri + 1] = 7;
	tris[3 * tri + 2] = 4;
	tri++;
	tris[3 * tri + 0] = 1;
	tris[3 * tri + 1] = 5;
	tris[3 * tri + 2] = 6;
	tri++;
	tris[3 * tri + 0] = 6;
	tris[3 * tri + 1] = 2;
	tris[3 * tri + 2] = 1;
	tri++;

}

void TMesh::DrawCubeQuadFaces(FrameBuffer* fb, PPC* ppc, unsigned int color) {

	V3 c0;
	c0.SetFromColor(color);
	for (int si = 0; si < 4; si++) {
		fb->Draw3DSegment(verts[si], verts[(si + 1) % 4], ppc, c0, c0);
		fb->Draw3DSegment(verts[4 + si], verts[4 + (si + 1) % 4], ppc, c0, c0);
		fb->Draw3DSegment(verts[si], verts[si + 4], ppc, c0, c0);
	}

}

void TMesh::DrawWireFrame(FrameBuffer* fb, PPC* ppc, unsigned int color) {

	for (int tri = 0; tri < trisN; tri++) {
		V3 V0 = verts[tris[3 * tri + 0]];
		V3 V1 = verts[tris[3 * tri + 1]];
		V3 V2 = verts[tris[3 * tri + 2]];
		V3 c0 = colors[tris[3 * tri + 0]];
		V3 c1 = colors[tris[3 * tri + 1]];
		V3 c2 = colors[tris[3 * tri + 2]];
		fb->Draw3DSegment(V0, V1, ppc, c0, c1);
		fb->Draw3DSegment(V1, V2, ppc, c1, c2);
		fb->Draw3DSegment(V2, V0, ppc, c2, c0);
	}

}

//p1
//........p3
//p2
//E(x3,y3)=x3*(y2-y1)-y3(x2-x1)-(x1y2-y1x2)
//=x3*a[0]-y3*a[1]+a[2]
V3 TMesh::CalcSidedNessE(V3 a[3], V3 p)
{
	V3 etemp;
	for (int i = 0; i < 3; i++)
	{
		etemp[i] = p.xyz[0] * a[i].xyz[0] - p.xyz[1] * a[i].xyz[1] - a[i][2];
	}
	return etemp;
}
void TMesh::GetSidedNessParam(V3 pa, V3 pb, V3 pc, V3 a[3])
{	
	
	for (int i = 0; i < 3; i++)
	{
		float x1, x2, y1, y2, x3, y3;
		V3 p1, p2, p3;
		if (i==0)
		{
			p1 = pa;
			p2 = pb;
			p3 = pc;
		}
		if (i == 1)
		{
			p1 = pb;
			p2 = pc;
			p3 = pa;
		}
		if (i == 3)
		{
			p1 = pc;
			p2 = pa;
			p3 = pb;
		}

		
		x1 = p1.xyz[0];
		x2 = p2.xyz[0];
		x3 = p3.xyz[0];

		y1 = p1.xyz[1];
		y2 = p2.xyz[1];
		y3 = p3.xyz[1];

		a[i].xyz[0] = y2 - y1;
		a[i].xyz[1] = x2 - x1;
		a[i].xyz[2] = x1 * y2 - x2 * y1;
		float etemp;
		
		V3 p = p3;
		etemp = p.xyz[0] * a[i].xyz[0] - p.xyz[1] * a[i].xyz[1] - a[i][2];
		if (etemp < 0)
		{
			a[i].xyz[0] = -1 * a[i].xyz[0];
			a[i].xyz[1] = -1*a[i].xyz[1];
			a[i].xyz[2] = -1 * a[i].xyz[2];
		}
		
	}
	
}

void TMesh::GetTriangleAABBparam(V3 pa, V3 pb, V3 pc, V3& center, V3& sideL, V3& leftMost, V3& topMost, V3 &rightMost, V3 &bottomMost)
{
	V3 minV(100000.0f, 10000.0f, 100000.0f);
	V3 maxV(-100000.0f, -100000.0f, -100000.0f);
	V3 trs[3];
	trs[0] = pa;
	trs[1] = pb;
	trs[2] = pc;
	V3 minN(0,0,0), maxN(0,0,0);

	for (int vi = 0; vi < 3; vi++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (trs[vi].xyz[j] < minV.xyz[j])
			{
				minV.xyz[j] = trs[vi].xyz[j];
				minN.xyz[j] = vi;
			}
			if (trs[vi].xyz[j] > maxV.xyz[j])
			{
				maxV.xyz[j] = trs[vi].xyz[j];
				maxN.xyz[j] = vi;
			}
		}
		for (int j = 0; j < 3; j++)
		{
			center.xyz[j] = (minV.xyz[j] + maxV.xyz[j]) / 2.0f;
			sideL.xyz[j] = fabs(minV.xyz[j] - maxV.xyz[j]);
		}
		
	}
	//cout << "Zdepth:" << endl;
	//cout << pa << " " << pb << " " << pc << endl;
	//cout << maxN << " " << minN << endl;
	int temp = minN.xyz[0];
	leftMost = trs[temp];
	temp = maxN.xyz[0];
	rightMost = trs[temp];
	temp = minN.xyz[1];
	topMost = trs[temp];
	temp = maxN.xyz[1];
	bottomMost = trs[temp];

	//cout << "left right top bottom:" << endl;

	//cout << leftMost << rightMost << topMost << bottomMost << endl;
	//cout <<"minV: "<< minV << ";" << maxV << endl;
	//cout << "center: " << center << endl;
	//cout<<"sides: " << sideL << endl;
}

float TMesh::CalcArea(V3 p1, V3 p2, V3 p3)
{
	float area= ((p1.xyz[0] * (p2.xyz[1] - p3.xyz[1]) + p2.xyz[0] * (p3.xyz[1] - p1.xyz[1]) + p3.xyz[0] * (p1.xyz[1] - p2.xyz[1])) / 2.0f);
	return area;
}

/*
c
 \
|		w	\
	\			\
  u	 D *		-	-	b
|				/
	/	v	/

|		/
a

 some point P=ua+vb+wc

*/
void TMesh::GetBarryCentric(V3 a, V3 b, V3 c, V3 p, V3& uvw)
{
	float area_abc = CalcArea(a, b, c);
	float area_cap = CalcArea(c, a, p);
	float area_abp = CalcArea(a, b , p);
	float area_bcp = CalcArea(b, c, p);
	//cout <<"area: "<< area_abc << " " << area_cap << " " << area_abp << " " << area_bcp << endl;
	uvw.xyz[0] = area_cap / area_abc;
	uvw.xyz[1] = area_abp / area_abc;
	uvw.xyz[2] = area_bcp / area_abc;

}



void TMesh::DrawFilledFrame(FrameBuffer* fb, PPC* ppc, unsigned int color) {
	fb->ClearZB();
	fb->ClearZB3d();
	for (int tri = 100; tri < 200; tri++) 
	{
		
		V3 pa = verts[tris[3 * tri + 0]];
		V3 pb = verts[tris[3 * tri + 1]];
		V3 pc = verts[tris[3 * tri + 2]];
		V3 c0 = colors[tris[3 * tri + 0]];
		V3 c1 = colors[tris[3 * tri + 1]];
		V3 c2 = colors[tris[3 * tri + 2]];
		V3 V0(0.0f, 0.0f, 0.0f), V1(0.0f,0.0f,0.0f), V2(0.0f, 0.0f, 0.0f);

		ppc->Project(pa,V0);
		ppc->Project(pb,V1);
		ppc->Project(pc,V2);



		//V3 retx = ppc->UnProject(V0);
		//cout <<"unproject: "<< pa << retx << endl;

		V3 center(0.0f, 0.0f, 0.0f), sideL(0.0f, 0.0f, 0.0f), leftP(0.0f, 0.0f, 0.0f), rightP(0.0f, 0.0f, 0.0f), topP(0.0f, 0.0f, 0.0f), bottomP(0.0f, 0.0f, 0.0f);
		
		/*
		cout << "pa's and v's:" << endl;
		cout<< pa.xyz[2]<<", "<< V0.xyz[2] << endl;
		cout <<pb.xyz[2]<<" ,"<< V1.xyz[2] << endl;
		cout <<pc.xyz[2]<<", "<< V2.xyz[2] << endl;
		*/
		GetTriangleAABBparam(V0, V1, V2, center, sideL,leftP, topP,rightP, bottomP);
		//cout << "lr" << leftP << rightP <<topP<<bottomP<< endl;
		//cout << "centers" << endl;
		//cout << center << endl;
		//cout << sideL << endl;
		//GetSidedNessParam(V0, V1, V2, a);

		float delta = 0.5f;

		//cout << left << " lb:" << right <<" "<<top<<" "<<bottom<< endl;
		for (int i = leftP.xyz[0]-delta; i <= rightP.xyz[0]+delta; i++)
		{
			for (int j = topP.xyz[1]-delta; j <=bottomP.xyz[1] +delta; j++)
			{
				float mul = 1.0f;
				float tempZ = leftP.xyz[2] + (i - leftP.xyz[0]) * sideL.xyz[2]*mul/ (sideL.xyz[0]);
				float tempZ2 = topP.xyz[2] + (j - topP.xyz[1]) * sideL.xyz[2]*mul / (sideL.xyz[1]);
				float zfinal = (tempZ + tempZ2) / 2.0f;


				zfinal = (V0.xyz[2] + V1.xyz[2] + V2.xyz[2])/3.0f; //temp

				
				//cout << tempZ << " " << tempZ2 << endl;
				//cout << pa << pb << pc << endl;
				//cout << "zfinal:" << zfinal << endl;
				
			//	cout << "zfinal:" << zfinal << endl;
				//V3 Eval=CalcSidedNessE(a, V3(i,j,zfinal));
				//cout<<i<<","<<j<<" and eval: "<< Eval << endl;

				V3 uvw(0, 0, 0);
				GetBarryCentric(V0, V1, V2, V3(i, j, zfinal), uvw);
				//cout <<"uvw"<< uvw << endl;
				//zfinal = (uvw.xyz[0] * V0.xyz[2] + uvw.xyz[1] * V1.xyz[2] + uvw.xyz[2] * V2.xyz[2]) * mul;

				//V3 up = ppc->UnProject(V3(i, j, zfinal));
				//cout << up << endl;
				//if (!fb->Farther3d((int)up.xyz[0], (int)up.xyz[1], up.xyz[2]*100.0f)) 

				V3 a[3];
				GetSidedNessParam(V0,V1,V2,a);

				if (!fb->Farther3d(i, j, zfinal))
				{
					V3 color_uvw = c0 * uvw.xyz[0] + c1 * uvw.xyz[1] + c2 * uvw.xyz[2];		
					//V3 E=CalcSidedNessE(a, V3(i, j, zfinal/mul));
					if (uvw.xyz[0] >= 0 && uvw.xyz[1] >= 0 && uvw.xyz[2] >= 0)
					//if(E.xyz[0]>=0 && E.xyz[1]>=0 && E.xyz[2]>=0)
					{						
						//V3 p(0.0f, 0.0f, 0.0f);
						//ppc->Project(V3(i, j, zfinal), p);						
						fb->Set(i, j, color_uvw.GetColor());
					}				

					
				
				}
									
				
				
			}

		}


	}

}


void TMesh::GetAABBParam(V3 &center, V3& sideL) {
	cout << "Only works for max xyz=100000 and min xyz=-100000. For higher values change code in TMesh::DrawBoundingBox" << endl;
	V3 minV(100000.0f, 10000.0f, 100000.0f);
	V3 maxV(-100000.0f, -100000.0f, -100000.0f);
	//V3 center(0.0f, 0.0f, 0.0f);
	//V3 sideL(0.0f, 0.0f, 0.0f);
	for (int vi = 0; vi < vertsN; vi++) 
	{
		for (int j = 0; j < 3; j++)
		{
			if (verts[vi].xyz[j] < minV.xyz[j])
			{
				minV.xyz[j] = verts[vi].xyz[j];
			}
			if (verts[vi].xyz[j] > maxV.xyz[j])
			{
				maxV.xyz[j] = verts[vi].xyz[j];
			}
		}
		for (int j = 0; j < 3; j++)
		{
			center.xyz[j] = (minV.xyz[j] + maxV.xyz[j])/2.0f;
			sideL.xyz[j] = fabs(minV.xyz[j] - maxV.xyz[j]);

		}
		

	}
	//SetToBoundingBox(center, sideL, 0xFF0000FF, 0xFF000000);

}

void TMesh::LoadBin(char* fname) {

	ifstream ifs(fname, ios::binary);
	if (ifs.fail()) {
		cerr << "INFO: cannot open file: " << fname << endl;
		return;
	}

	ifs.read((char*)&vertsN, sizeof(int));
	char yn;
	ifs.read(&yn, 1); // always xyz
	if (yn != 'y') {
		cerr << "INTERNAL ERROR: there should always be vertex xyz data" << endl;
		return;
	}
	if (verts)
		delete verts;
	verts = new V3[vertsN];

	ifs.read(&yn, 1); // cols 3 floats
	if (colors)
		delete colors;
	colors = 0;
	if (yn == 'y') {
		colors = new V3[vertsN];
	}

	ifs.read(&yn, 1); // normals 3 floats
	if (normals)
		delete normals;
	normals = 0;
	if (yn == 'y') {
		normals = new V3[vertsN];
	}

	ifs.read(&yn, 1); // texture coordinates 2 floats
	float* tcs = 0; // don't have texture coordinates for now
	if (tcs)
		delete tcs;
	tcs = 0;
	if (yn == 'y') {
		tcs = new float[vertsN * 2];
	}

	ifs.read((char*)verts, vertsN * 3 * sizeof(float)); // load verts

	if (colors) {
		ifs.read((char*)colors, vertsN * 3 * sizeof(float)); // load cols
	}

	if (normals)
		ifs.read((char*)normals, vertsN * 3 * sizeof(float)); // load normals

	if (tcs)
		ifs.read((char*)tcs, vertsN * 2 * sizeof(float)); // load texture coordinates

	ifs.read((char*)&trisN, sizeof(int));
	if (tris)
		delete tris;
	tris = new unsigned int[trisN * 3];
	ifs.read((char*)tris, trisN * 3 * sizeof(unsigned int)); // read tiangles

	ifs.close();

	cerr << "INFO: loaded " << vertsN << " verts, " << trisN << " tris from " << endl << "      " << fname << endl;
	cerr << "      xyz " << ((colors) ? "rgb " : "") << ((normals) ? "nxnynz " : "") << ((tcs) ? "tcstct " : "") << endl;

}

V3 TMesh::GetCenter() {

	V3 ret(0.0f, 0.0f, 0.0f);
	for (int vi = 0; vi < vertsN; vi++) {
		ret = ret + verts[vi];
	}
	ret = ret / (float)vertsN;
	return ret;

}

float TMesh::GetSL()
{
	return(fabs((GetCenter()[0] - verts[0][0]))) * 2;
}

void TMesh::Translate(V3 tv) {

	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi] + tv;
	}

}

void TMesh::Scale(float scf) {
	V3 oldCenter = GetCenter();
	SetCenter(V3(0.0f, 0.0f, 0.0f));
	
	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi] * scf;
		
	}
	SetCenter(oldCenter);
	

}


void TMesh::SetCenter(V3 center) {

	V3 currCenter = GetCenter();
	Translate(center - currCenter);
	

}


void TMesh::Rotate(V3 a0, V3 adir, float angle) {
	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi].RotateThisPointAboutArbitraryAxis(a0,adir, angle);
	}
	


}

