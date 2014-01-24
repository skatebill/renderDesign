#pragma once
#include "IDraw3DBase.h"
namespace xc
{
	namespace draw{
		class IDrawPath{
		public:
			//! ����path
			virtual void activate()=0;
			//! ע��path
			virtual void deActivate()=0;
		};
		class IColoredPath:public IDrawPath{
		public:
			//! ������ɫ
			virtual void setColor(colorf color)=0;
		};
		class IVertexColorPath:public IDrawPath{
		public:

		};
		class ITexturedPath:public IDrawPath{
		public:
			
		};
		class ITexturedLightedPath:public ITexturedPath{
		public:
			//! ���õƹ�
			virtual void activateLight(SLight light,u32 idx)=0;
		};
		class IMaterialPath{
		public:
			//! ���ò���
			virtual void activateMaterial(SMaterial mat)=0;

		};
		class IMaterialLightedPath:public IMaterialPath{
		public:
			//! ���õƹ�
			virtual void activateLight(SLight light,u32 idx)=0;
		};
		class IBoneAnimatedPath:public ITexturedPath{
		public:
			//! �ϴ������任����
			virtual void uploadBoneMatrix(void* data,u32 size)=0;
		};
		class IBoneAnimatedLightedPath:public ITexturedLightedPath{
		public:
			//! �ϴ������任����
			virtual void uploadBoneMatrix(void* data,u32 size)=0;

		};
		class IPathContext{
		public:
			//! ��ȡ��ɫ����path
			virtual shared_ptr<IColoredPath> getColorPath()=0;
			//! ��ȡ�������path
			virtual shared_ptr<ITexturedPath> getTexturePath()=0;
		};
	}
}