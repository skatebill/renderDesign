#pragma once
#include<memory>
#include<irrlich/rect.h>
#include<irrlich/matrix4.h>
#include<irrlich/irrString.h>
#include<irrlich/Scolor.h>
#include<irrlich/quaternion.h>
namespace xc{
	typedef irr::core::vector3df vector3df;
	typedef irr::core::vector3d<double> vector3dd;
	static const vector3dd zero3dd(0,0,0);
	static const vector3df zero3df(0,0,0);

	typedef irr::core::vector2df vector2df;
	typedef irr::core::vector2d<double> vector2dd;
	typedef irr::core::vector2d<int> vector2di;

	typedef irr::core::CMatrix4<float> mat4f;
	typedef irr::core::CMatrix4<double> mat4d;
	typedef mat4f mat4;
	typedef irr::core::quaternion quaternion;

	typedef irr::video::SColorf colorf;
	namespace color{
		static const colorf RED(1,0,0);
		static const colorf GREEN(0,1,0);
		static const colorf BLUE(0,0,1);
		static const colorf BLACK(0,0,0);
		static const colorf WHITE(1,1,1);
	}

	typedef irr::core::stringc string;
	typedef irr::core::stringw stringw;
	typedef irr::core::recti rect;
	typedef irr::core::recti recti;
	typedef irr::core::rectf rectf;
	typedef unsigned int u32;
	typedef unsigned int UINT;
	typedef unsigned char u8;
	typedef unsigned short u16;
	typedef float	f32;
	typedef double f64;

	using std::shared_ptr;
	using irr::core::degToRad;
	using irr::core::radToDeg;


}