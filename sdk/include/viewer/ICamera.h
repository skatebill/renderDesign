/************************************************************************/
/* �������ӿ�
	authored by xiaochi
	@ 2013��11��13��22:10:38											*/
/************************************************************************/
#pragma once
#include<tools/MyTypes.h>
namespace xc{
	namespace viewer{
		class ICamera{
		public:
			//! ��ȡ�ӽ�仯����
			virtual mat4 getViewMatrix()=0;
			//! ���� x ��ת��
			virtual void roll(float angle)=0;
			//! ���� y ��ת��
			virtual void yaw(float angle)=0;
			//! ���� z ��ת��
			virtual void pitch(float angle)=0;
			//! ��ǰ�ƶ�ָ������
			virtual void goForward(float)=0;
			//! �����ƶ�ָ������
			virtual void goRight(float)=0;
			//! �����ƶ�ָ������
			virtual void goUp(float)=0;
			//! ������Ƿ��б仯
			virtual bool isChanged()=0;
			//! ���������λ��
			virtual void setCamera(vector3df pos,vector3df lookat,vector3df upDir=vector3df(0,1,0))=0;
		};
	}
}