/************************************************************************/
/* �����ջ��ӿ�
	authored by xiaochi
	@ 2013��11��13��22:10:38											*/
/************************************************************************/
#pragma once
#include <tools/MyTypes.h>
#include <stack>
namespace xc{
	namespace viewer{
		class IMatStack{
		public:
			//! ѹջ��ǰ����
			virtual void push()=0;
			//! �ָ��ϸ�����
			virtual void pop()=0;
			//! ��ת
			virtual void rotate(float a,vector3df axis)=0;
			//! �ƶ�
			virtual void translate(vector3df t)=0;
			//! ����
			virtual void scale(vector3df s)=0;
			//! ���þ���
			virtual void reSet()=0;
			//! ��ȡ��ǰ����
			virtual mat4 getWorldTransMat()=0;
			//! ֱ�ӽ��о������
			virtual void mutipleMatrix(mat4 &m)=0;
		};
	}
}