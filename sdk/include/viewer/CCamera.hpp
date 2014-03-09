/************************************************************************/
/* 摄像机类接口
	authored by xiaochi
	@ 2013年11月13日22:10:38											*/
/************************************************************************/
#pragma once
#include"ICamera.h"
namespace xc{
	namespace viewer{

		class CCamera:public ICamera{
		private:
			vector3df mPos;
			vector3df mForwad;
			vector3df mUp;
			vector3df mRight;
			bool mChanged;

			mat4 temp;
			vector3df tempv;
			mat4 mViewMatrix;
		public:
			CCamera(){
				mForwad = vector3df(0,0,-1);
				mUp = vector3df(0,1,0);
				mRight = vector3df(1,0,0);
				mChanged=true;
			}
			//! 获取视界变化矩阵
			virtual mat4 getViewMatrix(){
				mViewMatrix.buildCameraLookAtMatrixRH(mPos,mPos+mForwad,mUp);
				return mViewMatrix;
			}
			inline void setChanged(){
				mChanged = true;
			}
			//! 沿着 x 轴转动
			virtual void roll(float angle){
				setChanged();
				temp.setRotationAxisRadians(angle,mRight);
				temp.rotateVect(tempv,mForwad);
				mForwad = tempv;
				mForwad.normalize();
				mUp = mRight.crossProduct(mForwad);
				mUp.normalize();
				mRight = mForwad.crossProduct(mUp);
				mRight.normalize();
			}
			//! 沿着 y 轴转动
			virtual void yaw(float angle){
				setChanged();
				temp.setRotationAxisRadians(angle,mUp);
				temp.rotateVect(tempv,mForwad);
				mForwad = tempv;
				mForwad.normalize();
				mRight = mForwad.crossProduct(mUp);
				mRight.normalize();
				mUp = mRight.crossProduct(mForwad);
				mUp.normalize();
			}
			//! 沿着 z 轴转动
			virtual void pitch(float angle){
				setChanged();
				temp.setRotationAxisRadians(angle,mForwad);
				temp.rotateVect(tempv,mUp);
				mUp = tempv;
				mUp.normalize();
				mRight = mForwad.crossProduct(mUp);
				mRight.normalize();
				mForwad = mUp.crossProduct(mRight);
				mForwad.normalize();
			}
			//! 向前移动指定距离
			virtual void goForward(float dis){
				setChanged();
				mPos = mPos + dis * mForwad;

			}
			//! 向右移动指定距离
			virtual void goRight(float dis){
				setChanged();
				mPos = mPos + dis * mRight;

			}
			//! 向上移动指定距离
			virtual void goUp(float dis){
				setChanged();
				mPos = mPos + dis * mUp;

			}
			//! 摄像机是否有变化
			virtual bool isChanged(){
				if(mChanged){
					mChanged = false;
					return true;
				}
				return mChanged;
			}
			//! 设置摄像机位置
			virtual void setCamera(vector3df pos,vector3df lookat,vector3df upDir=vector3df(0,1,0)){
				setChanged();
				mPos = pos;
				mForwad = lookat - pos;
				mForwad.normalize();
				mUp = upDir;
				mUp.normalize();
				mRight = mForwad.crossProduct(mUp);
				mRight.normalize();
			}

		};
	}
}