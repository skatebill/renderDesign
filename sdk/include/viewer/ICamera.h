/************************************************************************/
/* 摄像机类接口
	authored by xiaochi
	@ 2013年11月13日22:10:38											*/
/************************************************************************/
#pragma once
#include<tools/MyTypes.h>
namespace xc{
	namespace viewer{
		class ICamera{
		public:
			//! 获取视界变化矩阵
			virtual mat4 getViewMatrix()=0;
			//! 沿着 x 轴转动
			virtual void roll(float angle)=0;
			//! 沿着 y 轴转动
			virtual void yaw(float angle)=0;
			//! 沿着 z 轴转动
			virtual void pitch(float angle)=0;
			//! 向前移动指定距离
			virtual void goForward(float)=0;
			//! 向右移动指定距离
			virtual void goRight(float)=0;
			//! 向上移动指定距离
			virtual void goUp(float)=0;
			//! 摄像机是否有变化
			virtual bool isChanged()=0;
			//! 设置摄像机位置
			virtual void setCamera(vector3df pos,vector3df lookat,vector3df upDir=vector3df(0,1,0))=0;
		};
	}
}