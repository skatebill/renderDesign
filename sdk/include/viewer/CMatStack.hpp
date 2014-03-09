/************************************************************************/
/* 矩阵堆栈类接口
	authored by xiaochi
	@ 2013年11月13日22:10:38											*/
/************************************************************************/
#pragma once
#include"IMatrixStack.h"
namespace xc{
	namespace viewer{

		class CMatStack:public IMatStack{
		private:
			std::stack<mat4> mMatStack;
			mat4 mCurMat;
		public:
			CMatStack(){
				reSet();
			}
			//! 获取当前矩阵
			virtual mat4 getWorldTransMat(){
				return mCurMat;
			}
			//! 压栈当前矩阵
			virtual void push(){
				mMatStack.push(mCurMat);
			}
			//! 恢复上个矩阵
			virtual void pop(){
				mCurMat = mMatStack.top();
				mMatStack.pop();
			}
			//! 旋转
			virtual void rotate(float a,vector3df axis){
				mat4 temp;
				temp.setRotationAxisRadians(a,axis);
				mCurMat = temp * mCurMat;
			}
			//! 移动
			virtual void translate(vector3df t){
				mat4 temp;
				temp.setTranslation(t);
				mCurMat = temp * mCurMat;
			}
			//! 缩放
			virtual void scale(vector3df s){
				mat4 temp;
				temp.setScale(s);
				mCurMat = temp * mCurMat;
			}
			//! 重置矩阵
			virtual void reSet(){
				mCurMat.makeIdentity();
			}
			//! 直接进行矩阵操作
			virtual void mutipleMatrix(mat4 &m){
				mCurMat = m * mCurMat;
			}

		};
	}
}