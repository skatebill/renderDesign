/************************************************************************/
/* 矩阵堆栈类接口
	authored by xiaochi
	@ 2013年11月13日22:10:38											*/
/************************************************************************/
#pragma once
#include <tools/MyTypes.h>
#include <stack>
namespace xc{
	namespace viewer{
		class IMatStack{
		public:
			//! 压栈当前矩阵
			virtual void push()=0;
			//! 恢复上个矩阵
			virtual void pop()=0;
			//! 旋转
			virtual void rotate(float a,vector3df axis)=0;
			//! 移动
			virtual void translate(vector3df t)=0;
			//! 缩放
			virtual void scale(vector3df s)=0;
			//! 重置矩阵
			virtual void reSet()=0;
			//! 获取当前矩阵
			virtual mat4 getWorldTransMat()=0;
			//! 直接进行矩阵操作
			virtual void mutipleMatrix(mat4 &m)=0;
		};
	}
}