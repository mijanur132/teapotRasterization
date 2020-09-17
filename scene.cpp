#include "stdafx.h"
#include<sstream>
#include<iostream>
#include "scene.h"

#include "V3.h"
#include "M33.h"
#include   <chrono>
#include "ppc.h"
#include "TMesh.h"
#include <stdlib.h>
#include"sortTemp.h"




Scene *scene;

using namespace std;




Scene::Scene() 
{


	{
	
		//int arr[]= { 64, 34, 25, 12, 22, 11, 90 };

		//int arr[200000];
		//randGen(arr,200000);
		//int n = sizeof(arr) / sizeof(arr[0]);
		//auto first = std::chrono::high_resolution_clock::now();
	//	printArray(arr, n);
		//bubbleSort(arr, n);
		
		//insertionSort(arr, n);

		//selectionSort(arr,n);

		//auto last = std::chrono::high_resolution_clock::now();
		//std::chrono::duration<double> elapsedFirst =last - first;
		//cout << "time:"<<elapsedFirst.count()*1000 << endl;
		//cout << "Sorted array: \n";
		//printArray(arr, n);
		//getchar();
		//return;
	
	}





	gui = new GUI();
	gui->show();

	int u0 = 20;
	int v0 = 20;
	int h = 800;
	int w = 1600;

	fb = new FrameBuffer(u0, v0, w, h, 0);
	fb->label("SW frame buffer");
	fb->show();
	fb->redraw();

	gui->uiw->position(u0, v0 + h + 50);




	float hfov = 120.0f;
	ppc = new PPC(hfov, fb->w, fb->h);
	
	PPC* ppc1 = new PPC(hfov, fb->w, fb->h);
	PPC* ppc2=new PPC(hfov, fb->w, fb->h);
	
	
	ppc2->Roll(150.0f);
	ppc2->TranslateFrontBack(-300.0f);
	tmeshesN = 6;
	tmeshes = new TMesh[tmeshesN];


	tmeshes[1].LoadBin("geometry/teapot57K.bin");
	tmeshes[1].SetCenter(V3(-200.0f, -100.0f, -350.0f));
	tmeshes[2].LoadBin("geometry/teapot57K.bin");
	tmeshes[2].SetCenter(V3(-200.0f, 100.0f, -350.0f));
	tmeshes[3].LoadBin("geometry/teapot57K.bin");
	tmeshes[3].SetCenter(V3(0.0f, 0.0f, -200.0f));
	tmeshes[4].LoadBin("geometry/teapot57K.bin");
	tmeshes[4].SetCenter(V3(200.0f, -100.0f, -350.0f));
	tmeshes[5].LoadBin("geometry/teapot57K.bin");
	tmeshes[5].SetCenter(V3(200.0f, 100.0f, -350.0f));
	

	V3 AABBcenter(0.0f, 0.0f, 0.0f);
	V3 AABBsideL(0.0f, 0.0f, 0.0f);

	int fN = 1;	
	float scale = 1.0f;
	for (int fi = 0; fi < fN; fi++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int ii = 1; ii < 300; ii++)
		{

			
			fb->SetBGR(0xFFFFFFFF);
			fb->ClearZB();
			fb->ClearZB();
			if (ii > 150) {
				cout <<"ii:"<< ii << endl;
				
				ppc->SetInterpolated(ppc1, ppc2, (ii-150), 150);
			}

			tmeshes[1].Rotate(tmeshes[1].GetCenter(), V3(0.0f, 1.0f, 0.0f), 10.0f);
			tmeshes[2].Rotate(tmeshes[2].GetCenter(), V3(1.0f, 0.0f, 0.0f), 10.0f);
			tmeshes[3].Rotate(tmeshes[3].GetCenter(), V3(0.0f, 0.0f, 1.0f), 10.0f);
			tmeshes[4].Rotate(tmeshes[4].GetCenter(), V3(1.0f, 1.0f, 0.0f), 10.0f);
			tmeshes[5].Rotate(tmeshes[5].GetCenter(), V3(0.0f, 1.0f, 1.0f), 10.0f);


			tmeshes[1].GetAABBParam(AABBcenter, AABBsideL);

			for (int i = 1; i < tmeshesN; i++)
			{
				tmeshes[i].DrawCubeQuadFaces(fb, ppc, 0xFF00FF00);
				tmeshes[i].DrawFilledFrame(fb, ppc, 0xFF00FF00);
			}


			tmeshes[6].SetToAABBQuad(AABBcenter, AABBsideL, 0xFF0000FF, 0xFF000000);
			tmeshes[6].DrawWireFrame(fb, ppc, 0xFF00FFFF);
			cout << AABBcenter << ";" << AABBsideL << endl;

			fb->redraw();
			Fl::check();

			auto firstFrame = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsedFirst = firstFrame - start;
			while (elapsedFirst.count() * 1000 < 34)
			{
				firstFrame = std::chrono::high_resolution_clock::now();
				elapsedFirst = firstFrame - start;
			}
			start = firstFrame;
		}

		

	}

	


}


void Scene::Render() {

	fb->SetBGR(0xFFFFFFFF);
	fb->ClearZB();

	for (int tmi = 0; tmi < tmeshesN; tmi++) {
		if (!tmeshes[tmi].onFlag)
			continue;
		tmeshes[tmi].DrawWireFrame(fb, ppc, 0xFF000000);
	}

	fb->redraw();


}



void Scene::DBG() {

	{	{
			V3 p1(0, 1, 0);
			V3 p2(1, 0, 0);
			V3 p3(0, 0, 1);
			V3 p4(0.5f, 0.5f, 0.5f);
			TMesh t1;
			V3 center(0.0f,0.0f,0.0f), sideL(0,0,0.0f);
			//t1.CalcSidedNessParam(p1, p2, p3,p4);
			//t1.TriangleAABB(p1, p2, p3, center, sideL);
			t1.GetBarryCentric(p1, p2, p3, p4, center);
			cout << center << endl;
			return;
			
		
		}

		{
			int w = fb->w;
			int h = fb->h;
			float hfov = 90.0f;
			PPC ppc(hfov, w, h);
			V3 cc(0.0f, 0.0f, -100.0f);
			V3 tv(0.10f, 0.0f, 0.0f);
			unsigned int color = 0xFF00FF00;
			float sideLength = 300.0f;
			
			TMesh tm;
			tm.SetToCube(cc, sideLength, 0xFF0000FF, 0xFF000000);
			int fN = 1;
			float tstep = .1f;
			float scale = 1.0f;
			for (int fi = 0; fi < fN; fi++) {	
												
				fb->SetBGR(0xFFFFFFFF);				
				tm.Translate(tv * 5);
				tm.DrawCubeQuadFaces(fb, &ppc, color);
				//tm.DrawWireFrame(fb, &ppc, color);
				tm.DrawFilledFrame(fb, &ppc, color);
				//fb->redraw();
				//Fl::check();
				
			//	ppc.TranslateRightLeft(-tstep);
				//ppc.TranslateFrontBack(tstep);
				//tm.Translate(tv*5);
				scale = scale * 1.01f;
				//TMesh tm2 = tm;
				//tm2.SetCenter(tm.GetCenter());
				//cout << tm2.GetSL() << ";" << tm2.GetCenter() << endl;
				//tm2.Rotate(tm2.GetCenter(), V3(0.0f,1.0f,0.0f), 15.0f);
				//tm2.SetToCube(tm2.GetCenter(), tm2.GetSL(), 0xFF0000FF, 0xFF000000);
				//fb->SetBGR(0xFFFFFFFF);

				//tm2.DrawCubeQuadFaces(fb, &ppc, color);
				//tm2.DrawWireFrame(fb, &ppc, color);
				fb->redraw();
				Fl::check();
				Sleep(100);
							
			}
		
			return;
		}



		{
			V3 point=V3( 600.0f, 100.0f, 0.0f );
			V3 axis = V3(01.0f, 0.50f, 0.5f);



			V3 rotationPole = V3(250.0f, 120.0f, 0.0f);
			float uv0[2] = { 300.0f, 200.0f };

			unsigned int col = 0xFF000000;
			unsigned int col1 = 0xFFFF0000;
			fb->SetBGR(0xFFFFFFFF);
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < 360; i++)
			{
				float deltaAngle = i * 1.0f;
				V3 newPoint = point.RotateThisPointAboutArbitraryAxis(rotationPole, axis, deltaAngle);
				float np[2]; np[0] = newPoint[0]; np[1] = newPoint[1];

				//fb->SetBGR(0xFFFFFFFF);
				
				fb->Set((int)np[0], np[1], col1);
				fb->DrawCircle(np, 5.0f, col, col);

				fb->redraw();
				cerr << i << endl;
				
				Fl::check();

				auto firstFrame = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> elapsedFirst = firstFrame - start; 
				
				
				while (elapsedFirst.count()*1000  < 34)
				{
					firstFrame = std::chrono::high_resolution_clock::now();
					elapsedFirst = firstFrame - start;
				}
				start = firstFrame;
			}		

		}

		return;
		{			
			float uv0[2] = { 300.0f, 200.0f };			
			unsigned int col = 0xFF000000;
			unsigned int col1 = 0xFFF00000;
			int fN = 1;
			for (int fi = 0; fi < fN; fi++)
			{
				fb->SetBGR(0xFFFFFFFF);
				fb->DrawCircle(uv0, 100.0f, col1,col);

				fb->redraw();
				Fl::check();
			}
		}
		return;


		{
			float uv0[2] = { 1.0f, 01.0f };
			float uv1[2] = { 200.0f, 0.0f };
			float uv2[2] = { 200.0f, 400.0f };
			unsigned int col = 0xFF000000;
			int fN = 1;
			for (int fi = 0; fi < fN; fi++)
			{
				fb->SetBGR(0xFFFFFFFF);
				fb->DrawTriangle(uv0, uv1, uv2, col);

				fb->redraw();
				Fl::check();
			}
		}
		return;
		
		{
			float uv0[2] = { 1.0f, 01.0f };
			float uv1[2] = { 400.0f, 400.0f };
			unsigned int col = 0xFF000000;
			int fN = 30;
			for (int fi = 0; fi < fN; fi++) {
				fb->SetBGR(0xFFFFFFFF);
				//fb->Draw2DSegment(uv0, uv1, col);
				fb->DrawAxisAlignedRect(uv0, uv1, col);
				//uv0[1] += 1.0f;
				//uv1[1] -= 1.0f;
				fb->redraw();
				Fl::check();
				Sleep(1000);
			}
			fb->SaveAsTiff("im.tif");
		}

		return;

		M33 m;
		V3 r0(1.0f, 1.0f, 1.0f);
		V3 r1(-2.0f, 2.0f, 2.0f);
		V3 r2(3.0f, -3.0f, 3.0f);
		m[0] = r0;
		m[1] = r1;
		m[2] = r2;
		V3 v(1.0f, 2.0f, 3.0f);
		V3 ret = m*v;
		cerr << ret;
		M33 m1 = m.Inverted();
		cerr << m*m1.GetColumn(0) << m*m1.GetColumn(1) << m*m1.GetColumn(2);
		return;
	}


	{
		M33 m;
		V3 v0(1.0f, 3.0f, -1.0f);
		m[0] = v0;
		cerr << m[0] << endl;
		cerr << m[0][2] << endl;
		m[0][2] = 1000.0f;
		cerr << m[0][2] << endl;
		return;
	}

	{

		V3 v0(2.0f, 2.0f, 2.0f);
		V3 v1(4.0f, 3.0f, 5.0f);
		cerr << v0 + v1;
		cerr << "v0*v1 " << v0*v1 << endl;
		cerr << v0.Length() << endl;
		cerr << (v0.Normalized()).Length() << endl;
		cerr << v0;
		return;

	}

	{
		V3 v;
		v.xyz[0] = 1.0f;
		v.xyz[1] = -1.0f;
		v.xyz[2] = 0.0f;
		cerr << v[0] << endl;
		v[0] = 100.0f;
		cerr << v[0] << endl;
		return;

	}

	fb->LoadTiff("mydbg/im.tif");
	fb->redraw();
	return;
	cerr << "INFO: pressed DBG Button" << endl;
	/*

	{
		float uv0[2] = { 10.1f, 20.2f };
		float uv1[2] = { 510.1f, 420.2f };
		unsigned int col = 0xFF000000;
		int fN = 300;
		for (int fi = 0; fi < fN; fi++) {
			fb->SetBGR(0xFFFFFFFF);
			fb->Draw2DSegment(uv0, uv1, col);
			uv0[1] += 1.0f;
			uv1[1] -= 1.0f;
			fb->redraw();
			Fl::check();
		}
		fb->SaveAsTiff("mydbg/im.tif");
	}

	return;

	{
		fb->SetBGR(0xFF0000FF);
		fb->SetChecker(0xFF000000, 0xFFFFFFFF, 40);
		fb->SetBGR(0xFFFFFFFF);
		float uv0[2] = { 20.3f, 300.45f };
		float uv1[2] = { 420.73f, 100.45f };
		unsigned int col = 0xFF000000;
		fb->Draw2DSegment(uv0, uv1, col);
	}
	*/
}


void Scene::NewButton() {
	cerr << "INFO: pressed New Button" << endl;
}
