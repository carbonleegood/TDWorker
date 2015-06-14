#pragma once
#include <atlstr.h>
class XVec3
{
public:
	XVec3(void);
	~XVec3(void);
public:
	float x, y, z;	// ����
	DWORD highAngle;
	DWORD Angle2D;
	CString ScenceName;  //��������
	//	float h;	// ����
	//int t;	// ����(Dragonica)
	//	float t;	// ������(Rift)

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
