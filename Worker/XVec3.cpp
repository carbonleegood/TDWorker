#include "StdAfx.h"
#include "XVec3.h"
#include <cmath>

XVec3::XVec3(void)
{
	x = y = z  = 0;
	highAngle = 0;
	Angle2D = 0;
}

XVec3::~XVec3(void)
{
}
XVec3::XVec3( float x, float y, float z/*, float h,  float tint t*/)
{
	this->x = x;
	this->y = y;
	this->z = z;
	highAngle = 0;
	Angle2D = 0;
	//this->h = h;
	//this->t = t;
}

float &	XVec3::operator [] ( const int iIndex )
{
	return ( &x )[ iIndex ];
}

XVec3 XVec3::operator - ()
{
	return XVec3( -x, -y, -z );
}

XVec3 &	XVec3::operator = ( const XVec3 & a )
{
	x = a.x;
	y = a.y;
	z = a.z;
	highAngle = a.highAngle;
	Angle2D = a.Angle2D;

	return *this;
}

float XVec3::operator * ( const XVec3 & a )
{
	return x * a.x + y * a.y + z * a.z;
}

XVec3 XVec3::operator * ( const float a )
{
	return XVec3( x * a, y * a, z * a );
}

XVec3 XVec3::operator - ( const XVec3 & a )
{
	return XVec3( x - a.x, y - a.y, z - a.z );
}

bool XVec3::Compare( const XVec3 &a )
{
	return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) );
}

bool XVec3::operator == ( const XVec3 & a )
{
	return Compare( a );
}

bool XVec3::operator != (	const XVec3 & a )
{
	return !Compare( a );
}
bool XVec3::operator <(XVec3 a )const
{
	if(this->x==a.x)
	{
		if(this->y==this->y)
			return this->z<a.z;
		return this->y<a.y;
	}
	return this->x<a.x;
}
float XVec3::Length2D()
{
	return sqrt( x * x + y * y );
}

float XVec3::Length3D()
{
	return sqrt( x * x + y * y + z * z);
}

bool XVec3::IsNil()
{ 
	return (x==0)&&(y==0)&&(z==0) ;
}

void XVec3::Reset()
{ 
	x=y=z=0;
	highAngle = 0;
	Angle2D = 0;
}