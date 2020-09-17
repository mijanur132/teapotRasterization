#include "stdafx.h"
#include "m33.h"
#include "V3.h"

float& V3::operator[](int i) {

	return xyz[i];

}

V3 V3::operator+(V3 v1) {

	V3 ret;
	V3 &v0 = *this;
	ret[0] = v0[0] + v1[0];
	ret[1] = v0[1] + v1[1];
	ret[2] = v0[2] + v1[2];
	return ret;

}

V3 V3::operator-(V3 v1) {

	V3 ret;
	V3& v0 = *this;
	ret[0] = v0[0] - v1[0];
	ret[1] = v0[1] - v1[1];
	ret[2] = v0[2] - v1[2];
	return ret;

}




ostream& operator<<(ostream& ostr, V3 v) {

	return ostr << v[0] << " " << v[1] << " " << v[2] << endl;

}

istream& operator>>(istream& in, V3 v) {
	
	printf( "input 3 numbers for vector:");
	in >> v[0];
	in >> v[1];
	in>> v[2];
	return in;
}

float V3::operator*(V3 v1) {

	V3 &v0 = *this;
	float ret = v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2];
	return ret;

}

float V3::Length() {
	
	V3 &v0 = *this;
	return sqrtf(v0*v0);

}

V3 V3::operator*(float scf) {

	V3 ret(*this);
	ret[0] = ret[0] * scf;
	ret[1] = ret[1] * scf;
	ret[2] = ret[2] * scf;
	return ret;

}


V3 V3::operator/(float scf) {

	V3 ret(*this);
	ret[0] = ret[0] / scf;
	ret[1] = ret[1] / scf;
	ret[2] = ret[2] / scf;
	return ret;

}

V3 V3::Normalized() {

	V3 ret(*this);
	return ret / ret.Length();

}

V3 V3::operator^(V3 v2) {

	V3 &v1 = *this;
	V3 ret(v1[1] * v2[2] - v1[2] * v2[1],
		v1[2] * v2[0] - v1[0] * v2[2],
		v1[0] * v2[1] - v1[1] * v2[0]);
	return ret;
}

V3 V3::UnitVector() {

	return (*this) * (1.0f / Length());

}

V3 V3::RotateThisPointAboutArbitraryAxis(V3 O, V3 a, float angle) {//O is original axis, a is axisDir

	
	V3 aux; 
	if (fabsf(a[0]) > fabsf(a[1])) {
		aux = V3(0.0f, 1.0f, 0.0f);
	}
	else {
		aux = V3(1.0f, 0.0f, 0.0f);
	}

	V3 a0 = (aux ^ a).UnitVector();
	V3 a2 = (a0 ^ a).UnitVector();
	M33 localCordinate;
	localCordinate[0] = a0;
	localCordinate[1] = a;
	localCordinate[2] = a2;
	V3& p = *this;	
	V3 p1 = localCordinate * (p - O);	
	M33 mr;
	mr.SetRotationAboutY(angle);
	V3 p2 = mr * p1;
	V3 p3 = localCordinate.Inverted() * p2 + O;
	return p3;

}

V3 V3::RotateThisVectorAboutDirection(V3 a, float angle) {
	
	V3 aux;
	if (fabsf(a[0]) > fabsf(a[1])) {
		aux = V3(0.0f, 1.0f, 0.0f);
	}
	else {
		aux = V3(1.0f, 0.0f, 0.0f);
	}
	V3 a0 = (aux ^ a).UnitVector();
	V3 a2 = (a0 ^ a).UnitVector();
	M33 localCordinate;
	localCordinate[0] = a0;
	localCordinate[1] = a;
	localCordinate[2] = a2;

	V3& p = *this;
	V3 p1 = localCordinate * p;
	M33 mr;
	mr.SetRotationAboutY(angle);
	V3 p2 = mr * p1;
	V3 p3 = localCordinate.Inverted() * p2;
	return p3;

}

void V3::SetFromColor(unsigned int color) {

	unsigned char* rgb = (unsigned char*)&color;
	V3& v = *this;
	v[0] = (float)(rgb[0]) / 255.0f;
	v[1] = (float)(rgb[1]) / 255.0f;
	v[2] = (float)(rgb[2]) / 255.0f;

}

unsigned int V3::GetColor() {

	unsigned int ret;
	V3& v = *this;
	unsigned char rgb[3];
	rgb[0] = (unsigned char)(255.0f * v[0]);
	rgb[1] = (unsigned char)(255.0f * v[1]);
	rgb[2] = (unsigned char)(255.0f * v[2]);
	ret = 0xFF000000 + rgb[2] * 256 * 256 + rgb[1] * 256 + rgb[0];
	return ret;

}
