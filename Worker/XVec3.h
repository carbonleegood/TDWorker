#pragma once
#include <atlstr.h>
class XVec3
{
public:
	XVec3(void);
	~XVec3(void);
public:
	float x, y, z;	// 坐标
	DWORD highAngle;
	DWORD Angle2D;
	CString ScenceName;  //场景名字
	//	float h;	// 面向
	//int t;	// 类型(Dragonica)
	//	float t;	// 副面向(Rift)

	XVec3( float x, float y, float z/*, float f=0, float t=0int t=0*/);

	float &	operator [] ( const int iIndex );
	XVec3	operator - ();
	XVec3 &	operator = ( const XVec3 & a );

	float	operator * ( const XVec3 & a );
	XVec3	operator * ( const float a );
	XVec3	operator - ( const XVec3 & a );
	bool	Compare( const XVec3 &a );
	bool	operator == ( const XVec3 & a );

	bool	operator != (	const XVec3 & a );
	bool operator <(XVec3 a )const;
	float Length2D();
	float Length3D();
	bool IsNil();
	void Reset();
};
