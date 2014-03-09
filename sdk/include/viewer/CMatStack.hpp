/************************************************************************/
/* �����ջ��ӿ�
	authored by xiaochi
	@ 2013��11��13��22:10:38											*/
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
			//! ��ȡ��ǰ����
			virtual mat4 getWorldTransMat(){
				return mCurMat;
			}
			//! ѹջ��ǰ����
			virtual void push(){
				mMatStack.push(mCurMat);
			}
			//! �ָ��ϸ�����
			virtual void pop(){
				mCurMat = mMatStack.top();
				mMatStack.pop();
			}
			//! ��ת
			virtual void rotate(float a,vector3df axis){
				mat4 temp;
				temp.setRotationAxisRadians(a,axis);
				mCurMat = temp * mCurMat;
			}
			//! �ƶ�
			virtual void translate(vector3df t){
				mat4 temp;
				temp.setTranslation(t);
				mCurMat = temp * mCurMat;
			}
			//! ����
			virtual void scale(vector3df s){
				mat4 temp;
				temp.setScale(s);
				mCurMat = temp * mCurMat;
			}
			//! ���þ���
			virtual void reSet(){
				mCurMat.makeIdentity();
			}
			//! ֱ�ӽ��о������
			virtual void mutipleMatrix(mat4 &m){
				mCurMat = m * mCurMat;
			}

		};
	}
}